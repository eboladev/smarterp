#ifndef ROLESMANAGER_H
#define ROLESMANAGER_H

#include <QtSql>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif
#if QT_VERSION < 0x50000
#include <QtGui>
#endif

namespace Ui {
class RolesManager;
}

class RolesManager : public QDialog
{
	Q_OBJECT

public:
	explicit RolesManager(QWidget *parent = 0, QSqlDatabase database = QSqlDatabase());
	~RolesManager();

private slots:
	void on_lstGroups_clicked(const QModelIndex &index);

	void on_cmdNewRole_clicked();

private:
	Ui::RolesManager *ui;
	QSqlDatabase db;
	QSqlQueryModel *groupModel;
	QSqlQueryModel *roleModel;
	void reloadGroups();
	QString groupID;
	void reloadRoles();
};

#endif // ROLESMANAGER_H
