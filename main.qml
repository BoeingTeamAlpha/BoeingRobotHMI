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
		x: 1074
		y: 44
		width: 206
		height: 713
		to: 100
		from: -100
		value: BoeingVehicleControl.rightDriveMotor
		font.pointSize: 10
		orientation: Qt.Vertical
	}

	Label {
		id: rightmotorlabel
		x: 1095
		y: 21
		width: 185
		height: 25
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		text: qsTr("Right Drive Control")
		color: "#f4f4f4"
	}

	Text {
		id: rightmotorvalue
		x: 1187
		y: 379
		width: 62
		height: 45
		color: "#f4f4f4"
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		text: rightMotorValue
		font.pixelSize: 12
	}

	Slider {
		id: leftmotorcontrol
		x: 0
		y: 44
		width: 206
		height: 713
		orientation: Qt.Vertical
		font.pointSize: 10
		value: BoeingVehicleControl.leftDriveMotor
		to: 100
		from: -100
	}

	Label {
		id: leftmotorlabel
		x: 11
		y: 21
		width: 185
		height: 25
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		text: qsTr("Left Drive Control")
		color: "#f4f4f4"
	}

	Text {
		id: leftmotorvalue
		x: 22
		y: 378
		width: 62
		height: 45
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		color: "#f4f4f4"
		text: leftMotorValue
		font.pixelSize: 12
	}

	Slider {
		id: dumpbedraiselower
		x: 177
		y: 526
		width: 112
		height: 242
		from: 0
		to: 180
		orientation: Qt.Vertical
		value: BoeingVehicleControl.dumpBedRaiseLower
		font.pointSize: 10

		Label {
			id: dumpbedraiselowerlabel
			x: 1
			y: -31
			width: 118
			height: 19
			text: qsTr("Dump Bed Raise Lower")
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			color: "#f4f4f4"
			font.pointSize: 10
		}
	}

	property real batteryPercent: BoeingVehicleControl.batteryPercent
	property bool metalDetected: BoeingVehicleControl.metalDetected

	property int leftMotorValue: leftmotorcontrol.value
	onLeftMotorValueChanged: BoeingVehicleControl.setLeftDriveMotor( leftMotorValue )

	property int rightMotorValue: rightmotorcontrol.value
	onRightMotorValueChanged: BoeingVehicleControl.setRightDriveMotor( rightMotorValue )

	property bool leftMotorSliderReleased: leftmotorcontrol.pressed
	onLeftMotorSliderReleasedChanged: BoeingVehicleControl.setLeftMotorSliderChangedState( leftMotorSliderReleased )

	property bool rightMotorSliderReleased: rightmotorcontrol.pressed
	onRightMotorSliderReleasedChanged: BoeingVehicleControl.setRightMotorSliderChangedState( rightMotorSliderReleased )

	property int dumpBedRaiseLower: dumpbedraiselower.value
	onDumpBedRaiseLowerChanged: BoeingVehicleControl.setDumpBedRaiseLower( dumpBedRaiseLower )

	Rectangle {
		id: container
		x: 856
		y: 537
		width: 220; height: 220
		color: "#282525"

		Rectangle {
			id: rect
			x: 80
			y: 80
			width: 60; height: 60
			color: "#f4f4f4"
			opacity: (600.0 - rect.x) / 600
			radius: width

			MouseArea {
				id: gripmouse
				anchors.fill: parent
				drag.target: rect
				drag.axis: Drag.XAndYAxis
				drag.minimumX: 0
				drag.maximumX: container.width - rect.width
				drag.minimumY: 0
				drag.maximumY: container.height - rect.height
			}
		}
	}

	property int gripperRaiseLower: rect.x
	onGripperRaiseLowerChanged:  BoeingVehicleControl.setGripperRaiseLower( gripperRaiseLower )

	property int gripperOpenClose: rect.y
	onGripperOpenCloseChanged: BoeingVehicleControl.setGripperOpenClose( gripperOpenClose )

	ProgressBar {
		id: batterypercent
		x: 531
		y: 13
		width: 218
		height: 25
		value: batteryPercent
		indeterminate: false
		from: 0
		to: 100
	}

	Text {
		id: batteryPercentText
		x: 755
		y: -6
		width: 87
		height: 63
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		color: "#f4f4f4"
		text: batteryPercent
		font.pixelSize: 12
	}

	Label {
		id: batterylabel
		x: 447
		y: 15
		width: 87
		height: 23
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		text: qsTr("Battery %")
		color: "#f4f4f4"
	}

	Image {
		id: bluetoothimage
		x: 267
		y: 6
		width: 61
		height: 54
		source: "Bluetooth.png"
		visible: BoeingVehicleControl.bluetoothConnected
	}

	Image {
		id: magnetimage
		x: 350
		y: 6
		width: 61
		height: 54
		source: "magnet.png"
		visible: BoeingVehicleControl.metalDetected
	}

	BusyIndicator {
		id: busyIndicator
		x: 268
		y: 6
		visible: !BoeingVehicleControl.bluetoothConnected
	}

	Label {
		id: gripperupdownlabel
		x: 811
		y: 754
		width: 213
		height: 39
		transform: Rotation { origin.x: 0; origin.y: 0; angle: 270}
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		color: "#f4f4f4"
		text: qsTr("Gripper Down Up")
	}

	Label {
		id: gripperleftrightlabel
		x: 860
		y: 492
		width: 213
		height: 39
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		color: "#f4f4f4"
		text: qsTr("Gripper Open Close")
	}

}
