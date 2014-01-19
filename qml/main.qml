/*
 * Copyright (C) 2013 Christophe Chapuis <chris.chapuis@gmail.com>
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

import QtQuick 2.0
import org.webosports.webossystemupdate 1.0

Rectangle {
    id: root

    color: "black";

    Column {
        id: contentColumn

        property string stepDescription;
        property string detailText;
        property int progressHint;

        width: parent.width
        anchors.centerIn: parent

        Text {
            id: stepTextItem

            color: "white"
            text: qsTr("Current step: " + contentColumn.stepDescription);
            anchors.horizontalCenter: parent.horizontalCenter
        }
        AnimatedSprite {
            id: progressAnimation
            anchors.horizontalCenter: parent.horizontalCenter
            width: 76
            height: 66
            source: "images/activity-progress.png"
            frameWidth: 76
            frameHeight: 66
            frameCount: 20
            frameRate: 16
            paused: true
            currentFrame: contentColumn.progressHint
        }
        Text {
            id: detailTextItem
            color: "white"
            text: contentColumn.detailText
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    MonitoredApp {
        id: myAppMonitor
        scriptAction: "/bin/sh " + scriptPath

        onNewStepString:contentColumn.stepDescription = stepDescription;
        onNewDetailString:contentColumn.detailText = detailText;
        onNewProgressHint: contentColumn.progressHint = hint;
    }

    Component.onCompleted:myAppMonitor.launchScript();
}
