#ifndef IMS_REELLINKER_H
#define IMS_REELLINKER_H

#include <QMainWindow>
#include <QtSql>
namespace Ui {
class ims_reellinker;
}

class ims_reellinker : public QMainWindow
{
	Q_OBJECT

public:
	explicit ims_reellinker(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~ims_reellinker();
public slots:
	void reloadReels();
private slots:
	void on_lstReels_doubleClicked(const QModelIndex &index);

private:
	Ui::ims_reellinker *ui;
	QSqlDatabase db;
};

#endif // IMS_REELLINKER_H
