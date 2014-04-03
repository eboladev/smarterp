#ifndef STARTNEWEMPLOYEE_H
#define STARTNEWEMPLOYEE_H

#include <QDialog>

namespace Ui {
class StartNewEmployee;
}

class StartNewEmployee : public QDialog
{
	Q_OBJECT

public:
	explicit StartNewEmployee(QWidget *parent = 0);
	~StartNewEmployee();

	QString fName() const;
	void setFName(const QString &fName);

	QString lName() const;
	void setLName(const QString &lName);

	QString idNo() const;
	void setIdNo(const QString &idNo);

	QString nssfNo() const;
	void setNssfNo(const QString &nssfNo);

	QString nhifNo() const;
	void setNhifNo(const QString &nhifNo);

	QString pinNo() const;
	void setPinNo(const QString &pinNo);

private slots:
	void on_cmdSaveEmployee_clicked();

private:
	Ui::StartNewEmployee *ui;

	QString m_fName;
	QString m_lName;
	QString m_idNo;
	QString m_nssfNo;
	QString m_nhifNo;
	QString m_pinNo;
};

#endif // STARTNEWEMPLOYEE_H
