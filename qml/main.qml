import QtQuick 2.0
import org.webosports.webosupdater 1.0

Rectangle {
    width: 360
    height: 360
    Text {
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
    AnimatedSprite {
        anchors.fill: parent
        source: "images/activity-progress.png"
        frameWidth: 76
        frameHeight: 66
        frameCount: 20
        frameRate: 16
    }

    MonitoredApp {
        id: myAppMonitor
        appName: "echo \"Hello\" This is a Simple test from C++"
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            myAppMonitor.launchScript()
            //Qt.quit();
        }
    }
}
