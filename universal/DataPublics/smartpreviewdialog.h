#ifndef SMARTPREVIEWDIALOG_H
#define SMARTPREVIEWDIALOG_H

#include <QDialog>

class ORODocument;
class QPrinter;

namespace Ui {
class SmartPreviewDialog;
}

class SmartPreviewDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SmartPreviewDialog(ORODocument *document, QPrinter *pPrinter, QWidget *parent = 0);
	~SmartPreviewDialog();

private slots:
	void on_cmdPrint_clicked();

private:
	Ui::SmartPreviewDialog *ui;
};

#endif // SMARTPREVIEWDIALOG_H
