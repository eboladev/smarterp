#ifndef IMSMAINWINDOW_H
#define IMSMAINWINDOW_H
#include "datapublics.h"
#include <QMainWindow>
#include <QtSql>
#include "sqlmodels.h"

namespace Ui {
class ImsMainWindow;
}

class ImsMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit ImsMainWindow(QWidget *parent = 0,
			       QSqlDatabase database = QSqlDatabase());
	~ImsMainWindow();

private slots:
	void on_actionOpen_triggered();
	void openFile(QString fileID);
	void newFile();

	void reloadProductList();
	void loadLPODetails();
	void loadPFIDetails();
	void loadProductDetails(QString productID);

	void loadIDFDetails();
	void loadShipments();

	void keepConnectionAlive();
	void loadShipmentDetails();

	void loadContainers();

	void on_lstLPODetails_clicked(const QModelIndex &index);

	void on_lstLPODetails_doubleClicked(const QModelIndex &index);

	void on_cmdLPO_NewProduct_clicked();



	void on_cmdUploadFile_clicked();

	void uploadFile(QString columnName, QString fileNameCol, QString id, QString tableName = "files", QString idCol = "EntryID");
	void downloadFile(QString columnName, QString fileNameCol, QString id, QString tableName = "files", QString idCol = "EntryID");
	void on_cmdPFI_UploadFile_clicked();

	void on_lstShipments_clicked(const QModelIndex &index);

	void saveFileChanges();

	void on_cmdLPO_DeleteProduct_clicked();

	void on_cmdIDF_PrintApplication_clicked();

	void on_cmdIDF_UploadIDF_clicked();

	void on_cmdIDF_OpenIDF_clicked();

	void on_cmdPFI_DownloadFile_clicked();

	void on_cmdDownloadLpo_clicked();

	void on_actionNew_Shipment_triggered();

	void on_cmdUploadInvoice_clicked();

	void on_cmdUploadBL_clicked();

	void on_cmdUploadPackingList_clicked();

	void on_cmdOpenInvoice_clicked();

	void on_cmdOpenBL_clicked();

	void on_cmdOpenPackingList_clicked();

	void on_toolButton_clicked();

	void on_toolButton_2_clicked();

	void on_toolButton_3_clicked();

	void on_actionSave_Shipment_triggered();

	void on_actionPrint_Marine_Cover_triggered();

	void on_cmdAddContainer_clicked();

	void on_cmdRemoveContainer_clicked();

	void on_lstContainers_doubleClicked(const QModelIndex &index);

	void on_actionDelete_File_triggered();

	void on_cmdDeleteShipment_clicked();

	void on_actionDelete_Shipment_triggered();

	void on_actionCharges_triggered();

	void on_actionPrint_Marine_Declaration_triggered();

	void on_actionMarine_Declaration_PDF_triggered();
	void generateMarineDeclaration(bool pdf  = false);
	void on_txtShipmentQty_textChanged(const QString &arg1);
	void updatePacking();
	void on_spingNoOfContainers_valueChanged(const QString &arg1);

private:
	Ui::ImsMainWindow *ui;
	QSqlDatabase db;
	bool fileOpen;
	QString currentFileNo;
	QString currentFileId;

	void enableDisable();
	void clearBoxes();


	bool shipmentOpen;
	QString currentShipmentId;
	QString currentShipmentNo;

	bool isAddingProduct;
	QString currentProductID;

	QTimer *connectionTimer;

	SqlTableModel *containerModel;
};

#endif // IMSMAINWINDOW_H
