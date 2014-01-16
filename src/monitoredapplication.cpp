#include "monitoredapplication.h"

#include <QProcess>
#include <QDebug>

MonitoredApplication::MonitoredApplication(QObject *parent) :
    QObject(parent),
    m_process(new QProcess(this))
{
}

QString MonitoredApplication::appName() const
{
    return m_AppName;
}
void MonitoredApplication::setAppName(const QString &appName)
{
    m_AppName = appName;
}
void MonitoredApplication::launchScript()
{
    // You can use start() if you want to start a external application
    m_process->start(m_AppName);
}
