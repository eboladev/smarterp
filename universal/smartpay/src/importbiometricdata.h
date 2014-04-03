#ifndef IMPORTBIOMETRICDATA_H
#define IMPORTBIOMETRICDATA_H

#include <QDialog>

namespace Ui {
class ImportBiometricData;
}

class ImportBiometricData : public QDialog
{
	Q_OBJECT

public:
	explicit ImportBiometricData(QWidget *parent = 0);
	~ImportBiometricData();

private slots:
	void on_cmdSelectDataFile_clicked();

private:
	Ui::ImportBiometricData *ui;
};

#endif // IMPORTBIOMETRICDATA_H
