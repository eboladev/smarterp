#ifndef ERP_DBSETTINGS_H
#define ERP_DBSETTINGS_H

#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif
#include <QDialog>
namespace Ui {
class ERP_DbSettings;
}

class ERP_DbSettings : public QDialog
{
	Q_OBJECT

public:
	explicit ERP_DbSettings(QWidget *parent = 0);
	~ERP_DbSettings();

private slots:
	void on_cmdSaveSettings_clicked();

private:
	Ui::ERP_DbSettings *ui;
};

#endif // ERP_DBSETTINGS_H
