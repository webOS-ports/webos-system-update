#ifndef MONITOREDAPPLICATION_H
#define MONITOREDAPPLICATION_H

#include <QObject>
#include <QProcess>

class MonitoredApplication : public QObject
{
    Q_OBJECT
public:
    explicit MonitoredApplication(QObject *parent = 0);

    Q_PROPERTY( QString scriptAction READ scriptAction WRITE setScriptAction )

    QString scriptAction() const;
    void setScriptAction(const QString &scriptAction);

    Q_INVOKABLE void launchScript();

Q_SIGNALS:
    void newStepString(const QString stepDescription);
    void newProgressHint(int hint);
    void newDetailString(const QString detailText);

private:
    QProcess *m_process;
    QString m_ScriptAction;

private Q_SLOTS:
    void onReadyReadStandardOutput();
};

#endif // MONITOREDAPPLICATION_H
