#ifndef ZCHATPLUGIN_H
#define ZCHATPLUGIN_H

#include "zchat_global.h"
#include <QtGui>
#include "interfaces.h"

class MainWindow;

class ZCHATSHARED_EXPORT ZChatPlugin: public QObject, public MainWindowInterface {
        Q_OBJECT
        Q_INTERFACES(MainWindowInterface)
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.erp.universal.chat")
#endif
    public:
        QMainWindow *pluginMainWindow(QWidget *parent, QSqlDatabase database);
        QString pluginName();
        QString pluginDescription();
        QString pluginVersion();
        QString releaseDate();
        QString pluginAuthor();
        QStringList subWindows();
        QString projectName();
    private:
        MainWindow *m_chat_window;
};

#endif // ZCHATPLUGIN_H
