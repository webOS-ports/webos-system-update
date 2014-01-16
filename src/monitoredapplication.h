#ifndef MONITOREDAPPLICATION_H
#define MONITOREDAPPLICATION_H

#include <QObject>
#include <QProcess>

class MonitoredApplication : public QObject
{
    Q_OBJECT
public:
    explicit MonitoredApplication(QObject *parent = 0);

    Q_PROPERTY( QString appName READ appName WRITE setAppName )

    QString appName() const;
    void setAppName(const QString &appName);

    Q_INVOKABLE void launchScript();

private:
    QProcess *m_process;
    QString m_AppName;
};

#endif // MONITOREDAPPLICATION_H
