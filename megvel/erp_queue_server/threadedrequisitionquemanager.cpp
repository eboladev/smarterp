#include "threadedrequisitionquemanager.h"

/**
 * @brief ThreadedRequisitionQueManager::ThreadedRequisitionQueManager
 * Loops through requisitions and posts unposted ones to quickbooks.
 * @param parent
 */
ThreadedRequisitionQueManager::ThreadedRequisitionQueManager(QObject *parent) :
    QThread(parent)
{
    db = QSqlDatabase::database();
    emit status("Starting requisition manager.");
}

void ThreadedRequisitionQueManager::run()
{
    tmr = new QTimer(this);
    connect (tmr, SIGNAL(timeout(QPrivateSignal)), SLOT(timeout()));
    tmr->start(15000);
}


void ThreadedRequisitionQueManager::timeout()
{
    QSqlQuery qu = db.exec("SELECT * FROM store_requisition_master WHERE status = 'Queued'");
    while (qu.next()) {

    }
}
