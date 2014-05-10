#include "datapublics.h"
#include <QMessageBox>
#include <QSettings>
#include <QDebug>
#include "reportpreview.h"
#include "qtprinter.h"
#include "htmltoqtprinter.h"
DataPublics::DataPublics()
{
}

/*!
 * \brief DataPublics::LoadQueryToTreeWidget Load a query to a QTreeWidget
 * \param query
 * \param db
 * \param tree
 */
void DataPublics::LoadQueryToTreeWidget(QString query, QSqlDatabase db, QTreeWidget *tree)
{
	LoadQueryToTreeWidget(query, db, tree, false, Qt::Unchecked, 0);
}

/*!
 * \brief DataPublics::LoadQueryToTreeWidget Load a query to a QTreeWidget
 * \param query
 * \param query
 * \param db
 * \param tree
 * \param addCheckBoxes
 * \param checkStates
 * \param checkCol
 */
void DataPublics::LoadQueryToTreeWidget(QString query, QSqlDatabase db, QTreeWidget *tree,
					bool addCheckBoxes, Qt::CheckState checkStates, int checkCol)
{
	QSqlQueryModel *model = new QSqlQueryModel(0);
	model->setQuery(query, db);
	tree->clear();
	tree->setColumnCount(model->columnCount());
	QStringList columns;
	for (int c = 0; c < model->columnCount(); c++) {
		columns << model->record().fieldName(c);
	}

	tree->setHeaderLabels(columns);

	for (int r = 0; r < model->rowCount(); r++) {
		QTreeWidgetItem *it = new QTreeWidgetItem(tree);
		for (int c = 0; c < model->columnCount(); c++) {
			it->setText(c, model->record(r).value(c).toString());
			if (c == checkCol && addCheckBoxes) {
				it->setCheckState(checkCol, checkStates);
			}
		}
	}
}

/*!
 * \brief DataPublics::showInformation show an information QMessageBox
 * \param msg
 * \param title
 */
void DataPublics::showInformation(QString msg, QString title)
{
	QMessageBox::information(0, title, msg);
}

/*!
 * \brief DataPublics::showWarning show a warning QMessageBox
 * \param msg
 * \param title
 */
void DataPublics::showWarning(QString msg, QString title)
{
	QMessageBox::warning(0, title, msg);
}

/*!
 * \brief DataPublics::mysqlDate Return a mysql compatible date value from a QDate
 * \param dat
 * \return
 */
QString DataPublics::mysqlDate(QDate dat)
{
	return dat.toString("yyyy-MM-dd");
}

void DataPublics::setComboBoxTextBasedOnID(QString tableName, QString idCol, QString id, QString return_col, QComboBox *cbo)
{
	QString txt = getDbValue("SELECT " + return_col + " FROM " + tableName + " WHERE " + idCol + " = '" + id + "'"
				 , QSqlDatabase::database("closures"), return_col).toString();
	cbo->setCurrentText(txt);
}

/*!
 * \brief DataPublics::ExecuteQuery Execute an SQl query in the specified QSqlDatabase
 * \param query
 * \param db
 * \param error
 * \return
 */
bool DataPublics::ExecuteQuery(QString query, QSqlDatabase db, QString error)
{
	db.exec(query);
	bool ret = (!db.lastError().isValid());
	if (!ret)
		error = db.lastError().text();
	return ret;
}

/*!
 * \brief DataPublics::checkUserAccess Check whether a user is allowed to access a specific role in the database
 * \param userID
 * \param roleName
 * \param db
 * \return
 */
bool DataPublics::checkUserAccess(QString userID, QString roleName, QSqlDatabase db)
{
	QString roleID = getDbValue("SELECT * FROM roles WHERE RoleName = '" + roleName + "'", db, "RoleID").toString();
	QSqlQuery qu = db.exec("SELECT * FROM userroles WHERE RoleID = '" + roleID + "' AND UserID = '" + userID + "'");
	int ret = 0;
	ret = qu.size();
	return ret;
}

/*!
 * \brief DataPublics::checkUserAccess
 * \param roleName
 * \param db
 * \return
 */
bool DataPublics::checkUserAccess(QString roleName, QSqlDatabase db)
{
	return checkUserAccess(getCurrentUserID(), roleName, db);
}

/*!
 * \brief DataPublics::getDbValue Gets a variable from a database query.
 * \param query
 * \param db
 * \param returnVal
 * \return
 */
QVariant DataPublics::getDbValue(QString query, QSqlDatabase db, QString returnVal)
{
	QSqlQuery qu = db.exec(query);
	if (qu.lastError().isValid()) {
		return 0;
	} else {
		qu.first();
		return qu.record().value(returnVal);
	}
}

QSqlDatabase DataPublics::getDatabase()
{
	return QSqlDatabase::database();
}

/*!
 * \brief DataPublics::getDatabase Creates an instance of QSqlDatabase based on the application settings file.
 * \param connectionName
 * \param databaseName
 * \return
 */
QSqlDatabase DataPublics::getDatabase(QString connectionName, QString databaseName)
{
	QString hostName = "192.168.0.8";
	QString userName = "root";
	QString password = "pledge";

	//qDebug() << "Connecting to MySQL database";

	QString fileName = QApplication::applicationDirPath() + QDir::separator() + "settings.cfg";
	QFile fil(fileName);
	QString lineBreaks = "\n";
#ifdef Q_OS_WIN
	lineBreaks = "\r\n";
#endif
	if (fil.exists()) {
		if (fil.open(QIODevice::Text | QIODevice::ReadOnly)) {
			//File successfully open
			QString fileData = fil.readAll();
#ifdef Q_OS_WIN
			if (fileData.contains("\r\n")) { //using windows line breaks

			} else {
				fileData.replace("\n", "\r\n");
			}
#endif
			QStringList fileLines = fileData.split(lineBreaks);
			if (fileLines.count() > 0) {
				for (int i = 0; i < fileLines.count(); i++) {

					QString thisLine = fileLines.at(i);

					if (!thisLine.startsWith("#")) {
						if (thisLine.contains("=")) {
							if (thisLine.split("=").count() > 0) {
								QString lineLabel = thisLine.split("=").at(0);
								QString lineValue = thisLine.split("=").at(1);

								if (lineLabel == "hostName") {
									if (lineLabel.contains(";")) {
										hostName = lineValue.split(";").at(0);
									} else {
										hostName = lineValue;
									}
								}

								if (lineLabel == "userName")
									userName = lineValue;

								if (lineLabel == "password")
									password = lineValue;
							}
						}
					}
				}
			}
			fil.close();
		} else {
			//File open error.
		}
	} else {
		//File not found. Create It
		//        QString fileData = "hostName=" + hostName + lineBreaks
		//                + "userName=" + userName + lineBreaks
		//                + "password=" + password + lineBreaks;
		QString fileData = "hostName=192.168.0.8" + lineBreaks
				+ "userName=root" + lineBreaks
				+ "password=pledge" + lineBreaks
				+ "mysqlPort=3306" + lineBreaks
				+ "tlmServerIP=192.168.0.188" + lineBreaks
				+ "tlmServerPort=4317" + lineBreaks
				+ "smtpHostName=192.168.0.245" + lineBreaks
				+ "smtpPort=110" + lineBreaks
				+ "smtpUserName=admin@mcl.co.ke" + lineBreaks
				+ "smptPassword=meg123!!" + lineBreaks
				+ "smtpSSL=yes" + lineBreaks;
		if (fil.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			fil.write(fileData.toUtf8());
			fil.close();
		}
	}

	//Q_UNUSED(connectionName);

	if (QSqlDatabase::drivers().contains("QMYSQL")) {
		//qDebug() << "Using QMYSQL";
		QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
		db.setDatabaseName(databaseName);
		db.setUserName(userName);
		if (password.length() > 0)
			db.setPassword(password);
		db.setHostName(hostName);
		return db;
	} else {
		//qDebug() << "Using QODBC";
		QSqlDatabase db2 = QSqlDatabase::addDatabase("QODBC", connectionName);
		db2.setHostName("localhost");
		db2.setDatabaseName("cartons");
		return db2;
	}

}

/*!
 * \brief DataPublics::getDatabaseAndOpen Gets a database and opens it
 * \param connectionName
 * \param databaseName
 * \return
 */
QSqlDatabase DataPublics::getDatabaseAndOpen(QString connectionName, QString databaseName)
{
	//qDebug() << "Attempting to open database.";
	QSqlDatabase db = DataPublics::getDatabase(connectionName, databaseName);
	if (db.open()) {
		//qDebug() << "Database connection successful";
	} else {
		//qDebug() << "Database connection failed. MySQL Message: " + db.lastError().text();
	}
	return db;
}

/*!
 * \brief DataPublics::getSettingValue Reads a setting from the settings registry
 * \param settingName
 * \return
 */
QVariant DataPublics::getSettingValue(QString settingName)
{
	QSettings sett("PantherTechnologies", "MegvelERP2.0");
	return sett.value(settingName, "");
}

/*!
 * \brief DataPublics::setSettingValue Sets a setting to the settings registry
 * \param settingName
 * \param value
 */
void DataPublics::setSettingValue(QString settingName, QVariant value)
{
	QSettings sett("PantherTechnologies", "MegvelERP2.0");
	sett.setValue(settingName, value);
}

/*!
 * \brief DataPublics::loadQueryToComboBox Loads a query to a specified QComboBox
 * \param query
 * \param col
 * \param db
 * \param cbo
 */
void DataPublics::loadQueryToComboBox(QString query, QString col, QSqlDatabase db, QComboBox *cbo)
{
	QSqlQuery qu = db.exec(query);
	if (!qu.lastError().isValid()) {
		while (qu.next()) {
			cbo->addItem(qu.record().value(col).toString());
		}
	} else {
		//qDebug() << qu.lastError().text();
	}
}


QString DataPublics::getReportXML(QString query, QString title, QSqlDatabase db, bool lines, bool landscape, bool pagenumbers, bool ignoreFirstColumn)
{
	QSqlQueryModel *reportModel = new QSqlQueryModel(0);
	reportModel->setQuery(query, db);
	return getReportXML(reportModel, query, title, db, lines, landscape, pagenumbers, ignoreFirstColumn);
}


/*!
 * \brief DataPublics::getReportXML is used to generate a reportmaster report xml based on a \a QAbstractItemModel.
 * \param reportModel The model to use
 * \param query The query to be used in the report
 * \param title The report title
 * \param db The QSqlDatabase to use
 * \param lines Whether or not lines are visible between rows
 * \param landscape Whether landscape orientation will be used. Otherwise, Portrait is used.
 * \param pagenumbers Whether or not to show page numbers in the footer
 * \param ignoreFirstColumn Whether or not to hide the firsr column, usually an ID
 * \return  A \c QString value.
 */
QString DataPublics::getReportXML(QAbstractItemModel *reportModel, QString query,
				  QString title, QSqlDatabase db,
				  bool lines, bool landscape, bool pagenumbers, bool ignoreFirstColumn)
{
	Q_UNUSED(db);

	/*! \todo Future Parameters.
     */
	bool forceLandscape = true;
	/*! End of future parameters   */

	int startcol = 0;
	if (ignoreFirstColumn)
		startcol = 1;

	QTreeView *trv = new QTreeView(0);
	if (reportModel->columnCount() < 5 && forceLandscape)
		landscape = false;
	trv->setModel(reportModel);

	int width = 1000 - 10;
	if (!landscape)
		width = 700 - 10;

	int height = 750;
	if (!landscape)
		height = 1100;
	int colCount = reportModel->columnCount();

	QMap<int, double> widths;

	QString rpt = "";
	rpt.append("<!DOCTYPE openRPTDef>\n");
	rpt.append("<report>\n");
	rpt.append("<title>" + title + "</title>\n");
	rpt.append("<name>" + title + "</name>\n");
	rpt.append("<description>" + title + "</description>\n");
	rpt.append("<size>A4</size>\n");
	if (landscape) {
		rpt.append("<landscape/>\n");
	}else{
		rpt.append("<portrait/>\n");
	}
	rpt.append("<topmargin>20</topmargin>\n"
		   "<bottommargin>100</bottommargin>\n"
		   "<rightmargin>60</rightmargin>\n"
		   "<leftmargin>50</leftmargin>\n"
		   "<querysource>\n"
		   "<name>Master</name>\n<sql>"
		   + query +
		   "</sql>\n</querysource>\n");
	rpt.append("<pghead>\n<height>80</height>\n");
	double colWidths = 0;
	for (int col = startcol; col < colCount; col++) {
		trv->resizeColumnToContents(col);
		colWidths = trv->columnWidth(col) + colWidths;
	}
	int top = 60;
	int startx = 3;
	int lineStart = startx;
	for (int col = startcol; col < colCount; col++)
	{
		double perc = (trv->columnWidth(col) / colWidths) * 100;
		double pWid = (perc / 100) * width;
		widths.insert(col, pWid);
		//Draw a line to the left of each column
		top = 60;
		if (col == startcol)
			top = 0;
		rpt.append(""
			   "<line>\n"
			   "<xstart>" + QString::number(lineStart - 1) + "</xstart>\n"
			   "<ystart>" + QString::number(top) + "</ystart>\n"
			   "<xend>"+ QString::number(lineStart - 1) + "</xend>\n<yend>"+ QString::number(height -  45) + "</yend>\n"
			   "<weight>1</weight>\n</line>\n"
			   "");
		lineStart = lineStart + pWid;
	}
	top = 60;
	//Draw a line to the right of the last column
	int ender =  lineStart + 2;
	if (reportModel->columnCount() < 5)
		ender = lineStart - 1;
	rpt.append(""
		   "<line>\n"
		   "<xstart>" + QString::number(ender) + "</xstart>\n"
		   "<ystart>0</ystart>\n"
		   "<xend>"+ QString::number(ender) + "</xend>\n<yend>"+ QString::number(height - 45) + "</yend>\n"
		   "<weight>1</weight>\n</line>\n"
		   "");
	//Draw a line at the footer
	rpt.append(""
		   "<line>\n"
		   "<xstart>" + QString::number(2) + "</xstart>\n"
		   "<ystart>"+ QString::number(height - 45) + "</ystart>\n"
		   "<xend>"+ QString::number(width) + "</xend>\n<yend>"+ QString::number(height - 45) + "</yend>\n"
		   "<weight>1</weight>\n</line>\n"
		   "");
	//Show Page Number at the footer
	if (pagenumbers) {
		rpt.append("\n<label>\n"
			   "<rect>\n"
			   "<x>" + QString::number(2) + "</x>\n"
			   "<y>" + QString::number(height - 30) + "</y>\n"
			   "<width>35</width>\n"
			   "<height>20</height>\n"
			   "</rect>\n"
			   "<font>\n"
			   "<face>Helvetica</face>\n"
			   "<size>9</size>\n"
			   "<weight>bold</weight>\n"
			   "</font>\n"
			   "<left/>\n"
			   "<top/>\n"
			   "<string>" + "Page " + "</string>\n"
			   "</label>\n");

		rpt.append("<field>\n"
			   "<rect>\n"
			   "<x>" + QString::number(37) +"</x>\n"
			   "<y>" + QString::number(height - 30) +"</y>\n"
			   "<width>" + QString::number(20)+"</width>\n"
			   "<height>20</height>\n"
			   "</rect>\n"
			   "<font>\n"
			   "<face>Helvetica</face>\n"
			   "<size>9</size>\n"
			   "<weight>bold</weight>\n"
			   "</font>\n"
			   "<left/>\n"
			   "<top/>\n"
			   "<data>\n"
			   "<query>Context Query</query>\n"
			   "<column>" + "page_number" + "</column>\n"
			   "</data>\n"
			   "</field>\n"
			   "");

		rpt.append("\n<label>\n"
			   "<rect>\n"
			   "<x>" + QString::number(47) + "</x>\n"
			   "<y>" + QString::number(height - 30) + "</y>\n"
			   "<width>28</width>\n"
			   "<height>20</height>\n"
			   "</rect>\n"
			   "<font>\n"
			   "<face>Helvetica</face>\n"
			   "<size>9</size>\n"
			   "<weight>bold</weight>\n"
			   "</font>\n"
			   "<left/>\n"
			   "<top/>\n"
			   "<string>" + " of " + "</string>\n"
			   "</label>\n");

		rpt.append("<field>\n"
			   "<rect>\n"
			   "<x>" + QString::number(75) +"</x>\n"
			   "<y>" + QString::number(height - 30) +"</y>\n"
			   "<width>" + QString::number(100)+"</width>\n"
			   "<height>20</height>\n"
			   "</rect>\n"
			   "<font>\n"
			   "<face>Helvetica</face>\n"
			   "<size>9</size>\n"
			   "<weight>bold</weight>\n"
			   "</font>\n"
			   "<left/>\n"
			   "<top/>\n"
			   "<data>\n"
			   "<query>Context Query</query>\n"
			   "<column>" + "page_count" + "</column>\n"
			   "</data>\n"
			   "</field>\n"
			   "");
		rpt.append("\n<label>\n"
			   "<rect>\n"
			   "<x>" + QString::number(200) + "</x>\n"
			   "<y>" + QString::number(height - 30) + "</y>\n"
			   "<width>" + QString::number(width - 200) + "</width>\n"
			   "<height>20</height>\n"
			   "</rect>\n"
			   "<font>\n"
			   "<face>Helvetica</face>\n"
			   "<size>9</size>\n"
			   "<weight>bold</weight>\n"
			   "</font>\n"
			   "<right/>\n"
			   "<top/>\n"
			   "<string>Printed on " + QDateTime::currentDateTime().toString("dd-MMM-yyyy hh:mm:ss")  + "</string>\n"
			   "</label>\n");
	}

	for (int col = startcol; col < reportModel->columnCount(); col++) {
		//QString colName = reportModel->record().fieldName(col);
		QString colName = reportModel->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString() ;//reportModel->record().fieldName(col);
		double thisColWidth = widths[col];
		// startx = startx;
		rpt.append("\n<label>\n"
			   "<rect>\n"
			   "<x>" + QString::number(2 + startx) + "</x>\n"
			   "<y>" + QString::number(60 + 3) + "</y>\n"
			   "<width>" + QString::number(thisColWidth) + "</width>\n"
			   "<height>20</height>\n"
			   "</rect>\n"
			   "<font>\n"
			   "<face>Helvetica</face>\n"
			   "<size>9</size>\n"
			   "<weight>bold</weight>\n"
			   "</font>\n"
			   "<left/>\n"
			   "<top/>\n"
			   "<string>" + colName + "</string>\n"
			   "</label>\n");
		startx = startx + thisColWidth;
	}

	rpt.append("<label>\n"
		   "<rect>\n"
		   "<x>0</x>\n"
		   "<y>0</y>\n"
		   "<width>"+ QString::number(width) +"</width>\n"
		   "<height>" + QString::number(60) + "</height>\n"
		   "</rect>\n"
		   "<font>\n"
		   "<face>Helvetica</face>\n"
		   "<size>20</size>\n"
		   "<weight>bold</weight>\n"
		   "</font>\n"
		   "<hcenter/>\n"
		   "<vcenter/>\n"
		   "<string>" + title + "</string>\n"
		   "</label>\n"
		   "");
	//Line before title
	rpt.append(""
		   "<line>\n"
		   "<xstart>2</xstart>\n"
		   "<ystart>0</ystart>\n"
		   "<xend>"+ QString::number(width) + "</xend>\n<yend>0</yend>\n"
		   "<weight>1</weight>\n</line>\n"
		   "");
	//Line after title
	rpt.append(""
		   "<line>\n"
		   "<xstart>2</xstart>\n"
		   "<ystart>" + QString::number(60) + "</ystart>\n"
		   "<xend>"+ QString::number(width) + "</xend>\n<yend>" + QString::number(60) + "</yend>\n"
		   "<weight>1</weight>\n</line>\n"
		   "");
	//Line after header Columns
	rpt.append(""
		   "<line>\n"
		   "<xstart>2</xstart>\n"
		   "<ystart>" + QString::number(60 + 20) + "</ystart>\n"
		   "<xend>"+ QString::number(width) + "</xend>\n<yend>" + QString::number(60 + 20) + "</yend>\n"
		   "<weight>1</weight>\n</line>\n"
		   "");
	rpt.append("</pghead>\n");

	rpt.append("<section>\n");
	rpt.append("<name>Detail</name>\n"
		   "<detail>\n"
		   "<key>\n"
		   "<query>Master</query>\n"
		   "</key>\n"
		   "<height>16</height>\n");

	startx = 3;
	for (int col = startcol; col < colCount; col++) {
		double thisColWidth = widths[col];
		//QString colName = reportModel->record().fieldName(col);
		QString colName = reportModel->headerData(col, Qt::Horizontal, Qt::DisplayRole).toString();
		//startx = startx + 2;
		rpt.append("<field>\n"
			   "<rect>\n"
			   "<x>" + QString::number(2 + startx) +"</x>\n"
			   "<y>0</y>\n"
			   "<width>" + QString::number(thisColWidth)+"</width>\n"
			   "<height>20</height>\n"
			   "</rect>\n"
			   "<font>\n"
			   "<face>Helvetica</face>\n"
			   "<size>9</size>\n"
			   "<weight>normal</weight>\n"
			   "</font>\n"
			   "<left/>\n"
			   "<top/>\n"
			   "<data>\n"
			   "<query>Master</query>\n"
			   "<column>" + colName + "</column>\n"
			   "</data>\n"
			   "</field>\n"
			   "");
		startx = startx + (thisColWidth);
	}
	if (lines) {
		rpt.append(""
			   "<line>\n"
			   "<xstart>2</xstart>\n"
			   "<ystart>15</ystart>\n"
			   "<xend>"+ QString::number(width) + "</xend>\n<yend>15</yend>\n"
			   "<weight>0</weight>\n</line>\n"
			   "");
	}
	rpt.append("</detail>\n</section>\n</report>\n");

	return rpt;
}


void DataPublics::showReportPreview(QString xml, QSqlDatabase db)
{
	ReportPreview *rp = new ReportPreview(0, db);
	rp->setWindowModality(Qt::ApplicationModal);
	rp->setXML(xml);
	rp->showNormal();
}

QString DataPublics::getCurrentUserName(QSqlDatabase db)
{
	QString userID = getCurrentUserID();
	return getDbValue("SELECT * FROM users WHERE UserID = '" + userID + "'", db, "UserName").toString();
}

QString DataPublics::getCurrentUserID()
{
	QString fileName = qApp->applicationDirPath() + QDir::separator() + "~tmpcurrentuser.dat";
	QFile fil(fileName);
	if (fil.open(QIODevice::ReadOnly)) {
		QString userID = fil.readAll();
		fil.close();
		return userID;
	}
	return "";
}

bool DataPublics::getUserPermission(QString role,
				    QSqlDatabase db)
{
	bool ret = false;
	QSqlQuery qu = db.exec("SELECT * FROM vw_roles_by_userid WHERE UserID = '" + getCurrentUserID() + "'");
	if (!qu.lastError().isValid()) {
		while (qu.next()) {
			QString roleName = qu.record().value("RoleName").toString();
			//qDebug() << roleName << role;
			if (roleName == role)
				ret = true;
		}
	}
	return ret;
}

QStringList DataPublics::getDbListItems(QString query, QString col, QSqlDatabase db)
{
	QSqlQuery qu = db.exec(query);
	QStringList lst;
	while (qu.next()) {
		lst.append(qu.record().value(col).toString());
	}
	return lst;
}

void DataPublics::logAuditTrail(QString section, QString action, QSqlDatabase db)
{
	QString userID = getCurrentUserID();
	QString actionDate = QDate::currentDate().toString("yyyy-MM-dd");
	QString actionTime = QTime::currentTime().toString("hh:mm:ss");
	QString computerName = "";

	db.exec("INSERT INTO audittrail(UserID, UserName, Date, Time, ComputerName, Section, Action) VALUES ('" +
		userID + "', '" +
		getCurrentUserName(db)  + "', '" +
		actionDate  + "', '" +
		actionTime  + "', '" +
		computerName  + "', '" +
		section  + "', '" +
		action + "')");
}

void DataPublics::clearInputs(QWidget *parent)
{
	//qDebug() << "Parent: " << parent->objectName();
	for (int i = 0; i < parent->children().count(); i++) {

		if (parent->children().at(i)->children().count() > 0) {
			if (qobject_cast<QWidget *>(parent->children().at(i))) {
				QWidget *wid = qobject_cast<QWidget *>(parent->children().at(i));
				if (wid->children().count() > 0) {
					clearInputs(wid);
				}
			}
		} else {
			if (qobject_cast<QLineEdit *>(parent->children().at(i))) {
				QLineEdit *txt = qobject_cast<QLineEdit *>(parent->children().at(i));
				txt->setText("");
			}
			if (qobject_cast<QComboBox *>(parent->children().at(i))) {
				QComboBox *cbo = qobject_cast<QComboBox *>(parent->children().at(i));
				cbo->setCurrentIndex(0);
			}
		}
	}
}

void DataPublics::setInputsEnabled(QWidget *parent, bool enabled)
{
	for (int i = 0; i < parent->children().count(); i++) {
		if (parent->children().at(i)->children().count() > 0) {
			QWidget *wid = qobject_cast<QWidget *>(parent->children().at(i));
			wid->setEnabled(enabled);
		}
	}
}

EmailAddress *DataPublics::stringToEmail(const QString &str)
{
	int p1 = str.indexOf("<");
	int p2 = str.indexOf(">");

	if (p1 == -1)
	{
		// no name, only email address
		return new EmailAddress(str);
	}
	else
	{
		return new EmailAddress(str.mid(p1 + 1, p2 - p1 - 1), str.left(p1));
	}
}

QString DataPublics::getIniSetting(QString settingName, QString defaultValue)
{
	QString fileName = QApplication::applicationDirPath() + QDir::separator() + "settings.cfg";
	QFile fil(fileName);
	QString lineBreaks = "\n";
#ifdef Q_OS_WIN
	lineBreaks = "\r\n";
#endif
	if (fil.exists()) {
		if (fil.open(QIODevice::Text | QIODevice::ReadOnly)) {
			//File successfully open
			QString fileData = fil.readAll();
#ifdef Q_OS_WIN
			if (fileData.contains("\r\n")) { //using windows line breaks

			} else {
				fileData.replace("\n", "\r\n");
			}
#endif
			QStringList fileLines = fileData.split(lineBreaks);
			if (fileLines.count() > 0) {
				for (int i = 0; i < fileLines.count(); i++) {

					QString thisLine = fileLines.at(i);

					if (!thisLine.startsWith("#")) {
						if (thisLine.contains("=")) {
							if (thisLine.split("=").count() > 0) {
								QString lineLabel = thisLine.split("=").at(0);
								QString lineValue = thisLine.split("=").at(1);

								if (lineLabel == settingName)
									return lineValue;

							}
						}
					}
				}
			}
			fil.close();
		} else {
			//File open error.
		}
	} else {
		//File not found. Create It
		QString fileData = "hostName=192.168.0.8" + lineBreaks
				+ "userName=root" + lineBreaks
				+ "password=pledge" + lineBreaks
				+ "mysqlPort=3306" + lineBreaks
				+ "tlmServerIP=192.168.0.188" + lineBreaks
				+ "tlmServerPort=4317" + lineBreaks
				+ "smtpHostName=192.168.0.245" + lineBreaks
				+ "smtpPort=110" + lineBreaks
				+ "smtpUserName=admin@mcl.co.ke" + lineBreaks
				+ "smptPassword=meg123!!" + lineBreaks
				+ "smtpSSL=yes" + lineBreaks;
		if (fil.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			fil.write(fileData.toUtf8());
			fil.close();
		}
	}
	return defaultValue;
}

QString DataPublics::buildHtmlEmail(QString title, QString body, QString footer)
{
	QString html = "<HTML><HEAD><TITLE>";
	html += title + "</TITLE><?HEAD></BODY>";
	html += "<H2>" + title + "</H2>";
	html += body;
	html += "<BR/><BR/><BR/>";
	html += footer;

	return html;
}

void DataPublics::ShowOpenRPTReport(QWidget *parent, QSqlDatabase database, QString where, QString report, bool pdf)
{
	QtPrinter *pr = new QtPrinter(parent, database, where, report, pdf);
	Q_UNUSED(pr);
}

void DataPublics::htmlToQtPrinter(QWidget *parent, QSqlDatabase database, QSqlQuery query, QString title, bool firstColumnHidden, QString reportQuery, QStringList columnsToSum)
{
	HtmlToQtPrinter(parent, database, query, title, firstColumnHidden,
			reportQuery, columnsToSum);
}

void DataPublics::bindLineEditToQuery(QLineEdit *txt, QSqlQuery qu)
{
	txt->setText(qu.record().value(txt->objectName()).toString());
}

void DataPublics::bindComboBoxToQuery(QComboBox *cbo, QSqlQuery qu)
{
	QString val = qu.record().value(cbo->objectName()).toString();
	for (int i = 0; i < cbo->count(); i++) {
		if (cbo->itemText(i) == val) {
			cbo->setCurrentIndex(i);
		}
	}

	cbo->setEditText(val);
}

void DataPublics::bindForeignComboToQuery(QComboBox *cbo, QSqlQuery qu, QString fkID, QString fkData, QString fkTable)
{
	QString colName = cbo->objectName();
	QString dataVal = getDbValue("SELECT `" + fkData + "` FROM `" + fkTable + "` WHERE `" + fkID + "` = '" + qu.record().value(colName).toString() + "'",
				     QSqlDatabase::database(), fkData).toString();
	for (int i = 0; i < cbo->count(); i++) {
		if (cbo->itemText(i) == dataVal) {
			cbo->setCurrentIndex(i);
			return;
		}
	}
	cbo->setEditText(dataVal);
}

void DataPublics::bindTextEditToQuery(QTextEdit *tex, QSqlQuery qu)
{
	tex->setText(qu.record().value(tex->objectName()).toString());
}

QString DataPublics::addLineEditToUpdate(QLineEdit *txt)
{
	return " `" + txt->objectName() + "` = '" + txt->text() + "' ";
}

QString DataPublics::addComboBoxToUpdate(QComboBox *cbo)
{
	return " `" + cbo->objectName() + "` = '" + cbo->currentText() + "' ";
}

QString DataPublics::addTextEditToUpdate(QTextEdit *txt)
{
	return " `" + txt->objectName() + "` = '" + txt->toPlainText() + "' ";
}


