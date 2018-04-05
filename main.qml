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
		x: 356
		y: 432
		width: 112
		height: 330
		from: 0
		to: 180
		orientation: Qt.Vertical
		value: BoeingVehicleControl.dumpBedRaiseLower
		font.pointSize: 10

		Label {
			id: dumpbedraiselowerlabel
			x: 80
			y: 156
			width: 118
			height: 19
			text: qsTr("Camera Left Right")
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			color: "#f4f4f4"
			font.pointSize: 10
		}
	}

	Slider {
		id: cameraleftright
		x: 247
		y: 345
		width: 330
		height: 112
		from: 0
		to: 180
		orientation: Qt.Horizontal
		value: BoeingVehicleControl.cameraLeftRight
		font.pointSize: 10

		Label {
			id: cameraleftrightlabel
			x: parent.x / 2
			y: 8
			text: qsTr("Camera Left Right")
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			color: "#f4f4f4"
			font.pointSize: 10
		}
	}

	Slider {
		id: gripperraiselower
		x: 847
		y: 432
		width: 112
		height: 330
		from: 0
		to: 180
		orientation: Qt.Vertical
		value: BoeingVehicleControl.gripperRaiseLower
		font.pointSize: 10

		Label {
			id: gripperraiselowerlabel
			x: -9
			y: -28
			text: qsTr("Gripper Raise Lower")
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			color: "#f4f4f4"
			font.pointSize: 10
		}
	}

	Slider {
		id: gripperopenclose
		x: 738
		y: 541
		width: 330
		height: 112
		from: 0
		to: 180
		orientation: Qt.Horizontal
		value: BoeingVehicleControl.gripperOpenClose
		font.pointSize: 10

		Label {
			id: gripperopencloselabel
			x: 0
			y: 0
			text: qsTr("Gripper Open Close")
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

	property int camerLeftRightValue: cameraleftright.value
	onCamerLeftRightValueChanged: BoeingVehicleControl.setCameraLeftRight( camerLeftRightValue )

	property int dumpBedRaiseLower: dumpbedraiselower.value
	onDumpBedRaiseLowerChanged: BoeingVehicleControl.setDumpBedRaiseLower( dumpBedRaiseLower )

	property int gripperRaiseLower: gripperraiselower.value
	onGripperRaiseLowerChanged:  BoeingVehicleControl.setGripperRaiseLower( gripperRaiseLower )

	property int gripperOpenClose: gripperopenclose.value
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

	Label {
		id: batterylabel
		x: 431
		y: 21
		width: 87
		height: 23
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		text: qsTr("Battery %")
		color: "#f4f4f4"
	}

	Light {
		id: metaldetected
		x: 546
		y: 83
		width: 188
		height: 91
		visible: metalDetected
		color: "#0000ff"
	}

	Label {
		id: label
		x: 565
		y: 118
		width: 134
		height: 37
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		visible: metalDetected
		text: qsTr("MetalDetected")
		color: "#f4f4f4"
	}
}
