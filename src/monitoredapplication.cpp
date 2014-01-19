/*
 * Copyright (C) 2014 Christophe Chapuis <chris.chapuis@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include "monitoredapplication.h"

#include <QProcess>
#include <QDebug>

MonitoredApplication::MonitoredApplication(QObject *parent) :
    QObject(parent),
    m_process(new QProcess(this))
{
    connect(m_process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadyReadStandardOutput()));
}

QString MonitoredApplication::scriptAction() const
{
    return m_ScriptAction;
}
void MonitoredApplication::setScriptAction(const QString &scriptAction)
{
    m_ScriptAction = scriptAction;
}
void MonitoredApplication::launchScript()
{
    // You can use start() if you want to start a external application
    m_process->start(m_ScriptAction);
}

void MonitoredApplication::onReadyReadStandardOutput()
{
    if( m_process )
    {
        m_process->setReadChannel(QProcess::StandardOutput);
        QByteArray mStdOutput;
        do {
            mStdOutput = m_process->readLine();
            if( !mStdOutput.isEmpty() ) {
                QString mLineToSend(mStdOutput);
                if( mLineToSend.startsWith("NOTE: ") ) {
                    emit newStepString(mLineToSend.right(mLineToSend.length() - 6));
                }
                else if( mLineToSend.startsWith("PROGRESS: ") ) {
                    emit newProgressHint(mLineToSend.right(mLineToSend.length() - 10).toInt());
                }
                else {
                    emit newDetailString(mLineToSend);
                }
            }
        } while( !mStdOutput.isEmpty() );
    }
}
