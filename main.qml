import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

Window {
    visible: true
    width: 1280
    height: 800
    color: "#070606"
    title: qsTr("Main")

    Switch {
        id: switch1
        x: 265
        y: 220
        width: 156
        height: 131
        text: qsTr("Switch")
    }

    Slider {
        id: slider1
        x: 937
        y: 68
        width: 159
        height: 623
        to: 100
        from: -100
        font.pointSize: 10
        value: 0.5
        orientation: Qt.Vertical
    }

    PageIndicator {
        id: pageIndicator
        x: 1181
        y: 39
        count: 3
    }

    Slider {
        id: slider2
        x: 57
        y: 68
        width: 159
        height: 623
        orientation: Qt.Vertical
        font.pointSize: 10
        value: 0.5
        to: 100
        from: -100
    }

    Text {
        id: text1
        x: 583
        y: 231
        width: 335
        height: 360
        text: qsTr("Text")
        font.pixelSize: 12
    }
}
