#ifndef EDITPRODUCT_H
#define EDITPRODUCT_H

#include <QDialog>
#include "calculations/product.h"
#include <QtSql>
#include <QCheckBox>
#include <QTimer>
namespace Ui {
class EditProduct;
}

class EditProduct : public QDialog
{
	Q_OBJECT

public:
	explicit EditProduct(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase(), bool costing = false);
	~EditProduct();
	QString currentID;
	void Edit(QString ProductID);
	Product *getProduct() const;
	void setProduct(Product *value);
	bool isCosting() const;
	void setIsCosting(bool isCosting);

signals:
	void changed();
private slots:
	void reloadDetails();
	void plyChanged();
	void on_cboPL_currentIndexChanged(int index);
	void on_optB_toggled(bool checked);
	void on_optE_toggled(bool checked);
	void on_optC_toggled(bool checked);
	void reloadCalculated();

	void idChanged();
	void odChanged();

	void saveID();
	void saveOD();
	void savePaperSpec();
	void saveBoardDetails();

	void boardChanged();
	void paperSpecChanged();

	void recalculateAll();
	void on_cmdSaveChanges_clicked();
	void disableInputs();
	void disableParent(QWidget *parent);
	void on_cmdDelete_clicked();

	void on_NoOfInks_valueChanged(int arg1);

	void onChangesTimer();
private:
	Ui::EditProduct *ui;
	Product *m_product;
	QSqlDatabase db;
	bool calculating;
	bool m_isCosting;
	void enable2();
	void enable3();
	void enable5();

	void clearDimensions();

	int countBCE();
	void checkBCE(QCheckBox *chk);

	QTimer *changesTimer;
	int changesCount;
};

#endif // EDITPRODUCT_H
