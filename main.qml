import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3

ApplicationWindow {
    visible: true
    width: 1280
    height: 800
    color: "#070606"
    title: qsTr("Main")

    Slider {
        id: rightmotorcontrol
        x: 1059
        y: 0
        width: 221
        height: 800
        to: 100
        from: -100
        value: 0.5
        font.pointSize: 10
        orientation: Qt.Vertical
    }

    Slider {
        id: leftmotorcontrol
        x: 0
        y: 0
        width: 221
        height: 800
        orientation: Qt.Vertical
        font.pointSize: 10
        value: 0.5
        to: 100
        from: -100
    }

    property int leftMotorValue: leftmotorcontrol.value
    onLeftMotorValueChanged: BoeingVehicleControl.setLeftDriveMotor( leftMotorValue )

    property int rightMotorValue: rightmotorcontrol.value
    onRightMotorValueChanged: BoeingVehicleControl.setRightDriveMotor( rightMotorValue )

    property int leftMotorInt: BoeingVehicleControl.leftDriveMotor
    property int rightMotorInt: BoeingVehicleControl.rightDriveMotor

    Text {
        id: leftmotorvalue
        x: 9
        y: 378
        width: 62
        height: 45
        color: "#f4f4f4"
        text: leftMotorInt
        font.pixelSize: 12
    }

    Text {
        id: rightmotorvalue
        x: 1202
        y: 378
        width: 62
        height: 45
        color: "#f4f4f4"
        text: rightMotorInt
        font.pixelSize: 12
    }
}
