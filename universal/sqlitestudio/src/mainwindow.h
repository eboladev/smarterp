#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtSql>
#include "database.h"
#include "sqlmodels.h"
#include <QSettings>
#include "createtabledialog.h"
#include "aboutdialog.h"
#include "logdialog.h"
#include "highlighter.h"
#include "selectobjectdialog.h"
#include "createindexdialog.h"
#include "preferencesdialog.h"
#include "advancedsearchdialog.h"
#include "importcsvdialog.h"
#include "createviewdialog.h"
#include <QActionGroup>
#include <QAction>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
        void dragEnterEvent(QDragEnterEvent *event);
        void dropEvent(QDropEvent *event);
        void changeEvent(QEvent *);
    protected slots:
        void slotLanguageChanged(QAction *action);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QActionGroup *tableActions;
    QActionGroup *indexActions;
    QActionGroup *databaseActions;
    QSqlDatabase db;
    SqlTableModel *model;
    LogDialog *myLog;
    Highlighter *highlighter;
    QStringList tableList;
    QStringList indexList;
    QStringList viewList;
    void loadLanguage(const QString& rLanguage);
    void createLanguageMenu(void);
    QTranslator m_translator;
    QTranslator m_translatorQt;
    QString m_currLang;
    QString m_langPath;
private slots:
    void on_cmdExecuteQuery_clicked();
    void on_cmdSaveChanges_clicked();
    void on_cmdDeleteRecord_clicked();
    void on_cmdNewRecord_clicked();
    void showTable(QString tableName);
    void showTable();
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void aboutQt();
    void closeFile();
    void openRecentFile();
    void newTable();
    void editTable();
    void dropTable();
    void dropIndex();
    void createIndex();
    void showPreferences();
    void preferencesChanged();
    void exportDatabaseAsSQL();
    void importDatabaseFromSQL();
    void exportTableToCSV();
    void importTableFromCSV();
    void compactDb();
    void searchAll();
    void advancedSearch();
    QString getTableCreateSQL(QString tableName);
    QString getTableInsertSQL(QString tableName);
    void reloadDbList();
    void newView();
    void modifyView();
    void deleteView();
private:
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QString curFile;
    void updateRecentFileActions();
    enum { MaxRecentFiles = 5 };
    QAction *recentFileActs[MaxRecentFiles];
    QString getTable();
    QString getTableNView();
    QString getIndex();
    QString getView();
    void doSearch(QString searchQuery);
    void switchTranslator(QTranslator &translator, const QString &fileName);
};

#endif // MAINWINDOW_H
