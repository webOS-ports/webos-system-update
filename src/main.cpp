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

#include <QtGui/QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"

#include "monitoredapplication.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<MonitoredApplication>("org.webosports.webossystemupdate", 1 , 0 , "MonitoredApp");

    QString scriptPath;
    if( app.arguments().size() > 0 )
    {
        scriptPath = app.arguments().at(1);
    }

    QtQuick2ApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("scriptPath",  scriptPath);
    viewer.setMainQmlFile(QStringLiteral("qml/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
