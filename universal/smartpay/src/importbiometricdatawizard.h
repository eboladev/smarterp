#ifndef IMPORTBIOMETRICDATAWIZARD_H
#define IMPORTBIOMETRICDATAWIZARD_H

#include <QWizard>

namespace Ui {
class ImportBiometricDataWizard;
}

class ImportBiometricDataWizard : public QWizard
{
	Q_OBJECT

public:
	explicit ImportBiometricDataWizard(QWidget *parent = 0);
	~ImportBiometricDataWizard();

private slots:
	void on_ImportBiometricDataWizard_customButtonClicked(int which);

	void on_ImportBiometricDataWizard_finished(int result);

private:
	Ui::ImportBiometricDataWizard *ui;
};

#endif // IMPORTBIOMETRICDATAWIZARD_H
