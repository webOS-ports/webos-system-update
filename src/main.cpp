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
#include <QQuickView>
#include <QFont>

#include "monitoredapplication.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<MonitoredApplication>("org.webosports.webossystemupdate", 1 , 0 , "MonitoredApp");

    QString scriptPath;
    if (app.arguments().size() != 2) {
        qWarning("usage: webos-system-update <path to update script>");
        exit(1);
    }

    scriptPath = app.arguments().at(1);

    if (!QFile::exists(scriptPath)) {
        qWarning("Update script at path %s does not exists!", scriptPath.toUtf8().constData());
        exit(1);
    }

    qDebug() << "Using script at" << scriptPath;

    QFont defaultFont("Prelude");
    app.setFont(defaultFont);

    QQuickView viewer;
    viewer.rootContext()->setContextProperty("scriptPath",  scriptPath);
    viewer.setSource(QUrl("qrc:///qml/main.qml"));
    viewer.setResizeMode(QQuickView::SizeRootObjectToView);
    viewer.showFullScreen();

    return app.exec();
}
