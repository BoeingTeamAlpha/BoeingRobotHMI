import QtQuick 2.0

Item {
	property color color

	Rectangle {

		anchors.fill: parent
		anchors.margins: 3
		color: parent.color
		//		text: parent.text
		radius: width
		visible: parent.visible
	}
}
