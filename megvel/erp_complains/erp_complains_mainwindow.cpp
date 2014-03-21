#include "erp_complains_mainwindow.h"
#include "ui_erp_complains_mainwindow.h"

#include "datapublics.h"
#include "qtprinter.h"
Erp_Complains_MainWindow::Erp_Complains_MainWindow(QWidget *parent, QSqlDatabase database) :
    QMainWindow(parent),
    ui(new Ui::Erp_Complains_MainWindow)
{
    ui->setupUi(this);
    db = database;

    ui->lstComplains->setQuery("SELECT * FROM vw_complains ORDER BY ComplainID DESC", db, "Complains", true);
    ui->lstComplains->setColumnHidden(0, true);
    ui->lstComplains->setColumnHidden(7, true);
}

Erp_Complains_MainWindow::~Erp_Complains_MainWindow()
{
    delete ui;
}

#include "erp_complains_editor.h"
void Erp_Complains_MainWindow::on_actionNew_Complain_triggered()
{
    erp_complains_editor *ed = new erp_complains_editor(this, db);
    ed->AddNew();
    if (ed->exec() == QDialog::Accepted) {
        ui->lstComplains->setQuery("SELECT * FROM vw_complains ORDER BY ComplainID DESC", db, "Complains", true);
        ui->lstComplains->setColumnHidden(0, true);
        ui->lstComplains->setColumnHidden(7, true);
    }
}

void Erp_Complains_MainWindow::on_lstComplains_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index);
    QString id = ui->lstComplains->getCurrentID();
    if (id.length() > 0) {
        erp_complains_editor *ed = new erp_complains_editor(this, db);
        ed->Edit(id);
        if (ed->exec() == QDialog::Accepted) {
            ui->lstComplains->setQuery("SELECT * FROM vw_complains ORDER BY ComplainID DESC", db, "Complains", true);
            ui->lstComplains->setColumnHidden(0, true);
            ui->lstComplains->setColumnHidden(7, true);
        }
    }
}

void Erp_Complains_MainWindow::on_actionPrint_triggered()
{
    QString id = ui->lstComplains->getCurrentID();
    if (id.length() > 0) {
        QString paramWhere = " WHERE ComplainID = '" + id + "'";
        QtPrinter *qp = new QtPrinter(this, db, paramWhere, "CustomerComplaintForm");

        Q_UNUSED(qp);
    } else {
        DataPublics::showWarning("Please select a complain to print");
    }
}

#include <QMessageBox>
void Erp_Complains_MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}
