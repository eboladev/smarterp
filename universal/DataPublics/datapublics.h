#ifndef DATAPUBLICS_H
#define DATAPUBLICS_H
//sadfsfsdfsdfsdfdsfds
#include "DataPublics_global.h"
#include <QtSql>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#include <QtPrintSupport/QPrinter>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#include <QPrinter>
#endif

//class DATAPUBLICSSHARED_EXPORT DataPublics {
#include "smtpclient/emailaddress.h"
enum ConstraintType {
	TeacherConstraint=1,
	StudentConstraint=2,
	SubjectConstraint=3,
	ClassConstraint=4,
	RoomConstraint=5
};

class DataPublics {
public:
	int x;
	DataPublics();
	static void LoadQueryToTreeWidget(QString query, QSqlDatabase db,
					  QTreeWidget *tree);

	static void LoadQueryToTreeWidget(QString query, QSqlDatabase db,
					  QTreeWidget *tree, bool addCheckBoxes = false,
					  Qt::CheckState checkStates = Qt::Unchecked,
					  int checkCol = 0);

	static void showInformation(QString msg = "", QString title = "Message");
	static void showWarning(QString msg = "", QString title = "Warning");
	static QString mysqlDate(QDate dat);
	static void setComboBoxTextBasedOnID(QString tableName, QString idCol, QString id, QString return_col, QComboBox *cbo);
	static bool ExecuteQuery(QString query = "SELECT NOW()",
				 QSqlDatabase db = QSqlDatabase(), QString error = "");
	static bool checkUserAccess(QString userID = "", QString roleName = "",
				    QSqlDatabase db = QSqlDatabase());
	static bool checkUserAccess(QString roleName = "", QSqlDatabase db = QSqlDatabase());
	static QVariant getDbValue(QString query = "", QSqlDatabase db = QSqlDatabase::database(),
				   QString returnVal = "");
	static QSqlDatabase getDatabase();
	static QSqlDatabase getDatabase(
			QString connectionName = "NewConnection" + QDateTime::currentDateTime().toString(),
			QString databaseName = "megvel");
	static QSqlDatabase getDatabaseAndOpen(
			QString connectionName = "NewConnection" + QDateTime::currentDateTime().toString(), QString databaseName = "megvel");
	static QVariant getSettingValue(QString settingName = "");
	static void setSettingValue(QString settingName = "", QVariant value = 0);
	static void loadQueryToComboBox(QString query = "SELECT NOW()", QString col = "NOW()", QSqlDatabase db = QSqlDatabase(), QComboBox *cbo = new QComboBox(0));
	static QString getReportXML(QString query = "SELECT NOW()", QString title="Report", QSqlDatabase db = QSqlDatabase(), bool lines=false, bool landscape = true, bool pagenumbers = true,
				    bool ignoreFirstColumn = false);
	static QString getReportXML(QAbstractItemModel *reportModel, QString query = "SELECT NOW()", QString title="Report", QSqlDatabase db = QSqlDatabase(), bool lines=false, bool landscape = true, bool pagenumbers = true,
				    bool ignoreFirstColumn = false);
	static void showReportPreview(QString xml, QSqlDatabase db);
	static QString getCurrentUserName(QSqlDatabase db);
	static QString getCurrentUserID();
	static bool getUserPermission(QString role = "Role",
				      QSqlDatabase db = QSqlDatabase());
	static QStringList getDbListItems(QString query, QString col, QSqlDatabase db);
	static void logAuditTrail(QString section, QString action, QSqlDatabase db);
	static void clearInputs(QWidget *parent);
	static void setInputsEnabled(QWidget *parent, bool enabled);

	static EmailAddress *stringToEmail(const QString &str);
	static QString getIniSetting(QString settingName = "", QString defaultValue = "");
	static QString buildHtmlEmail(QString title = "Smart ERP (Megvel Cartons Ltd)", QString body = "Message", QString footer = "(c)Megvel Cartons Ltd (" + QString::number(QDate::currentDate().year())  +")");
	static void ShowOpenRPTReport(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), QString where = QString(),
				      QString report = QString(), bool pdf = false);
	static void htmlToQtPrinter(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(),
				    QSqlQuery query = QSqlQuery(),
				    QString title = QString(""),
				    bool firstColumnHidden = true,
				    QString reportQuery = "SELECT (NOW)",
				    QStringList columnsToSum = QStringList());
	static void bindLineEditToQuery(QLineEdit *txt, QSqlQuery qu);
	static void bindComboBoxToQuery(QComboBox *cbo, QSqlQuery qu);
	static void bindForeignComboToQuery(QComboBox *cbo, QSqlQuery qu,
					    QString fkID, QString fkData
					    , QString fkTable);
	static void bindTextEditToQuery(QTextEdit *tex, QSqlQuery qu);
	static QString addLineEditToUpdate(QLineEdit *txt);
	static QString addComboBoxToUpdate(QComboBox *cbo);
	static QString addTextEditToUpdate(QTextEdit *txt);
};

#endif // DATAPUBLICS_H
