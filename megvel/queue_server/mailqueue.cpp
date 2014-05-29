#include "mailqueue.h"
#include "datapublics.h"
#include <QDebug>
#include "datapublics.h"
#include "mailassistant.h"
#include "qtprinter.h"
MailQueue::MailQueue(QObject *parent) :
	QThread(parent)
{
	db = QSqlDatabase::addDatabase("QMYSQL", "QueueConnectuib");//DataPublics::getDatabase("QueueConnectuib", "cartons");
	db.setHostName("192.168.0.8");
	db.setUserName("root");
	db.setPassword("pledge");
	db.setDatabaseName("cartons");
	emit message("Starting mail queue...");
	db.setDatabaseName("cartons");

	if (db.open()) {
		qDebug() << "Email Queue Db Open";
		emit message("Database connected.");
	} else {
		qDebug() << "Email Queue db error";
		emit message("Database connection failed. [" + db.lastError().text() + "]");
	}
	started = false;
	mailTimer = new QTimer(this);
	connect (mailTimer, SIGNAL(timeout()), SLOT(onMailTimer()));
	mailTimer->start(2000);
}

void MailQueue::run()
{
	started = true;
}

void MailQueue::onMailTimer()
{
	if (!started)
		return;
	QSqlQuery qu = db.exec("SELECT * FROM email_queue WHERE status = 'Pending'");
	while (qu.next()) {
		QString type = qu.record().value("QueueType").toString();
		QString fk = qu.record().value("FK").toString();
		QString entry_id = qu.record().value("EntryID").toString();
		db.exec("UPDATE email_queue SET status = 'Sent' WHERE EntryID = '" + entry_id + "'");
		QString lpoNo = fk;

		if (type == "OC") {
			QString ocQuery = "SELECT * FROM newreport WHERE TicketNo = '" + fk + "'";
			QSqlQuery ocQu = db.exec(ocQuery);
			if (!ocQu.lastError().isValid()) {
				ocQu.first();

				QString html = "";
				html +=  "<html><head><h2>Order Generated (" + fk + ")</h2></head>"
						"<body>"
						"<table width='100%' border='0'>"

						"<tr><td><b>Customer: </b>" + ocQu.record().value("Client").toString() +"</td></tr> "
						"<tr><td><b>Product: </b>" + ocQu.record().value("Product").toString() +"</td></tr> "
						"<tr><td><b>Qty: </b>" + ocQu.record().value("Qty").toString() +"</td></tr> "
						"<tr><td><b>Tons: </b>" + ocQu.record().value("Tons").toString() +"</td></tr> "
						"<tr><td><b>Price: </b>" + ocQu.record().value("Price").toString() +"</td></tr> "
						"<br>"
						"</table></body></html>";

				QStringList recepients;
				recepients.append("Joseph W Joshua<joshua@megvel.me.ke>");
				//recepients.append("Joseph W Joshua<joejoshw@gmail.com>");
				//recepients.append("Paras Shah<@gmail.com>");


				MailAssistant *ma = new MailAssistant(this);

				QStringList files;
				//files.append(pdfFileName);

				ma->setVars("New OC: " + fk + "-" + ocQu.record().value("Client").toString(), html, recepients, files, "Megvel Cartons Ltd ERP<lpos@megvel.me.ke>");
				ma->start();
				emit message("Sending OC " + fk);
			}
		}
		else if (type == "Approved Requisition") {
			QString rqQuery = "SELECT "
					" store_requisition_master.EntryID "
					" , suppliers.SupplierName "
					" , store_requisition_master.RequisitionDate "
					" , store_requisition_master.RequestedBy "
					" , store_requisition_master.Department "
					" FROM "
					" `cartons`.`suppliers` "
					" INNER JOIN `cartons`.`store_requisition_master` "
					" ON (`suppliers`.`SupplierID` = `store_requisition_master`.SupplierID) WHERE `store_requisition_master`.`EntryID` = '" + fk + "'";
			//qDebug() << rqQuery;
			QSqlQuery qu2 = db.exec(rqQuery);
			if (qu2.lastError().isValid()) {
				qDebug() << qu2.lastError().text();
				emit message("Database Error: " + qu2.lastError().text());
			} else {
				while (qu2.next()) {
					lpoNo =  "LPO " + lpoNo + " " + qu2.record().value("SupplierName").toString() + "";
				}
			}

			QString pdfFileName = QDir::tempPath() + QDir::separator() + lpoNo + ".pdf";
			QFile testFile(pdfFileName);
			if (testFile.exists()) {
				if (!testFile.remove()) {
					emit message("Could not delete exisiting proforma file.");
					return;
				}
			}
			QtPrinter *prn = new QtPrinter(this);
			prn->QtPdfPrinter(db, fk, "LPO", pdfFileName);
			sleep(0.5);
			if (testFile.exists()) {
				emit message("LPO " + fk + " generated.");
				QString html = "";
				html +=  "<html><head><h2>LPO</h2></head>"
						"<body>"
						"<table width='100%' border='0'>"
						"<tr><td><b>Dear Sir/Madam</b></td></tr> "
						"<tr><td><br><span>Please find the attached LPO.</span>"
						"<br>"
						"</table></body></html>";

				QStringList recepients;
				recepients.append("Joseph W Joshua<joshua@megvel.me.ke>");
				//recepients.append("Paras Shah<dodhia.paras@gmail.com>");
				//recepients.append("Prasul Shah<megvelcartons@gmail.com>");
				QSqlQuery rece_qu = db.exec("SELECT * FROM email_recepients WHERE Enabled = '1' AND ReportName = 'LPO'");
				if (rece_qu.lastError().isValid()) {
					emit message("Recepient Error: -" + rece_qu.lastError().text());
				} else {
					while (rece_qu.next()) {
						QString str_rec = rece_qu.record().value("RecepientName").toString() + "<"
								+ rece_qu.record().value("EmailAddress").toString() + ">";
						recepients.append(str_rec);
						emit message("Found Recepient: " + str_rec);
					}
				}

				MailAssistant *ma = new MailAssistant(this);

				QStringList files;
				files.append(pdfFileName);

				ma->setVars(lpoNo, html, recepients, files, "Megvel Cartons Ltd ERP<lpos@megvel.me.ke>");
				ma->start();
				emit message("Sending LPO " + fk);
			}
		}
		else if (type == "Requisition") {
			QString rqnID = fk;
			emit message("Sending requisition " + rqnID);
			QStringList recepients;
			recepients.append("Joseph W Joshua<joshua@megvel.me.ke>");
			//recepients.append("Prasul Shah<megvelcartons@gmail.com>");
			QSqlQuery rece_qu = db.exec("SELECT * FROM email_recepients WHERE Enabled = '1' AND ReportName = 'Requisition'");
			if (rece_qu.lastError().isValid()) {
				emit message("Recepient Error: -" + rece_qu.lastError().text());
			} else {
				while (rece_qu.next()) {
					QString str_rec = rece_qu.record().value("RecepientName").toString() + "<"
							+ rece_qu.record().value("EmailAddress").toString() + ">";
					recepients.append(str_rec);
					emit message("Found Recepient: " + str_rec);
				}
			}

			QString html = "<HTML><HEAD></HEAD><BODY><h3><a href=http://www.megvel.me.ke/stores/approve_requisition.php?id=" + rqnID + ">Approve Requisition No: " + rqnID +"</a></h3>";
			QString rqQuery = "SELECT "
					" store_requisition_master.EntryID "
					" , suppliers.SupplierName "
					" , store_requisition_master.RequisitionDate "
					" , store_requisition_master.RequestedBy "
					" , store_requisition_master.Department "
					" FROM "
					" `cartons`.`suppliers` "
					" INNER JOIN `cartons`.`store_requisition_master` "
					" ON (`suppliers`.`SupplierID` = `store_requisition_master`.SupplierID) WHERE `store_requisition_master`.`EntryID` = '" + rqnID + "'";
			//qDebug() << rqQuery;
			QSqlQuery qu2 = db.exec(rqQuery);
			if (qu2.lastError().isValid()) {
				qDebug() << qu2.lastError().text();
				emit message("Database Error: " + qu2.lastError().text());
			} else {
				while (qu2.next()) {
					html += "<p><b>Requisition Date:</b> " + qu2.record().value("RequisitionDate").toString() + "";
					html += "<br/><b>Requested By:</b> " + qu2.record().value("RequestedBy").toString() + "";
					html += "<br/><b>Department:</b> " + qu2.record().value("Department").toString() + "";
					html += "<br/><b>Supplier:</b> " + qu2.record().value("SupplierName").toString() + "";
					html += "<br/><b>Order Total:</b> " + DataPublics::getDbValue("SELECT     store_requisition_detail.ItemID , Format(SUM(store_requisition_detail.SubTotal), 2) as 'Sum' FROM     cartons.store_requisition_detail     INNER JOIN cartons.inventory          ON (store_requisition_detail.ItemID = inventory.ItemID)  WHERE store_requisition_detail.MasterID = '" + rqnID + "'"
												      , db, "Sum").toString()

							+ "</p>";
					html += "<h3>Requisition Details:</h3>";
					html += "<table width=80% border=1 cellspacing=1><tr><td><b>Item Name</b></td><td><b>Unit Price</b><td><b>Qty Needed</b></td> <td><b>Subtotal</b></td> <td><b>VAT</b></td> <td><b>Total</b></td></tr>";
					QString detailQu = "SELECT     store_requisition_detail.ItemName        "
							", FORMAT(store_requisition_detail.UnitPrice, 2) as 'UnitPrice'"
							", FORMAT(store_requisition_detail.Qty, 2) as 'Qty'"
							", FORMAT(store_requisition_detail.Total, 2) as 'Total'"
							", FORMAT(store_requisition_detail.VAT, 2) as 'VAT'"
							", FORMAT(store_requisition_detail.SubTotal, 2) as 'SubTotal'"
							", inventory.UnitPrice as 'Price' FROM     cartons.store_requisition_detail     INNER JOIN cartons.inventory          ON (store_requisition_detail.ItemID = inventory.ItemID)  WHERE store_requisition_detail.MasterID = '" + rqnID + "'";
					QSqlQuery qu3 = db.exec(detailQu);
					while (qu3.next()) {
						html += "<tr><td>";
						html += qu3.record().value("ItemName").toString() + "</td><td>";
						html += qu3.record().value("UnitPrice").toString() + "</td><td>";
						html += qu3.record().value("Qty").toString() + "</td><td>";
						html += qu3.record().value("Total").toString() + "</td><td>";
						html += qu3.record().value("VAT").toString() + "</td><td>";
						html += qu3.record().value("SubTotal").toString() + "</td>";
						html += "</tr>";
					}
					html += "</table></BODY></HTML>";
					QString msg = DataPublics::buildHtmlEmail("Requisition", html);
					MailAssistant *ma = new MailAssistant(this);
					connect (ma, SIGNAL(errorOccurred(QString)), SLOT(smtpError(QString)));
					connect (ma, SIGNAL(messageStatus(QString)), SLOT(smtpSuccess(QString)));
					ma->setVars("Requisition " + rqnID + " (" + qu2.record().value("SupplierName").toString() + ")", msg, recepients, QStringList(), "Megvel Cartons Ltd ERP<erp@megvel.me.ke>");
					ma->start();



				}
			}
		} else if (type == "Proforma") {
			QString proformaNo = DataPublics::getDbValue("SELECT ProformaNo FROM proforma WHERE UniqueID = '" + fk + "'", db, "ProformaNo").toString();
			proformaNo.replace("/", "-");
			QString pdfFileName = QDir::tempPath() + QDir::separator() + "Proforma " + proformaNo + ".pdf";
			QFile testFile(pdfFileName);
			if (testFile.exists()) {
				if (!testFile.remove()) {
					emit message("Could not delete exisiting proforma file.");
					return;
				}
			}

			QtPrinter *prn = new QtPrinter(this);
			prn->QtPdfPrinter(db, fk, "Proforma", pdfFileName);
			sleep(0.5);
			if (testFile.exists()) {
				emit message("Proforma " + proformaNo + " generated.");
				QString html = "";
				html +=  "<html><head><h2>Proforma Invoice</h2></head>"
						"<body>"
						"<table width='100%' border='0'>"
						"<tr><td><b>Dear Sir/Madam</b></td></tr> "
						"<tr><td><br><span>Please find attached proforma invoice and process the same for an Export Entry.</span>"
						"<br><span  style='background-color: rgb(255, 255, 51);'><b>Please acknowledge safe receipt of the same.</b></span></td></tr>"
						"<br>"
						"</table></body></html>";

				QStringList recepients;

				QSqlQuery recQu = db.exec("SELECT * FROM ProformaRecipients");

				if (recQu.lastError().isValid()) {
					emit message("Could not fetch proforma recipients. Using default list.");
					recepients.append("Joseph W Joshua<joshua@megvel.me.ke>");
					recepients.append("Joseph Samanayo<treo@megvelcartons.com>");
				} else {
					while (recQu.next()) {
						QString addre = QString("%1<%2>").arg(recQu.record().value("PersonName").toString()
										      , recQu.record().value("EmailAddress").toString());
						recepients.append(addre);
					}
				}

				MailAssistant *ma = new MailAssistant(this);
				connect (ma, SIGNAL(errorOccurred(QString)), SLOT(smtpError(QString)));
				connect (ma, SIGNAL(messageStatus(QString)), SLOT(smtpSuccess(QString)));
				QStringList files;
				files.append(pdfFileName);

				ma->setVars("Proforma " + proformaNo, html, recepients, files, "Megvel Cartons Ltd ERP<proforma@megvel.me.ke>");
				ma->start();
				emit message("Sending proforma " + proformaNo);
			}
		}

	}
}

void MailQueue::smtpError(QString err)
{
	emit message("Email Error: " + err);
}

void MailQueue::smtpSuccess(QString msg)
{
	emit message("Email Status: " + msg);
}

