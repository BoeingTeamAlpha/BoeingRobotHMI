#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include "BluetoothDevice.h"

#define BeagleBluetoothAddress ("80:30:DC:04:39:D4")
#define UUID ("00001101-0000-1000-8000-00805f9b34fb")

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;

	BluetoothDevice device;
	QBluetoothAddress address( BeagleBluetoothAddress );


//	device.setBluetoothPower( true );
//	device.setDiscoverable( true );

//	device.startPairing( address );

	int count = 0;
//	while ( device.pairingStatus( address ) != 1 )
//	{
//		++count;

//		if ( count % 100 == 0 )
//		{
//			qDebug() << "waiting to pair\r\n";
//		}

//	}

	qDebug() << "paired?";

	QBluetoothSocket* socket = new QBluetoothSocket( QBluetoothServiceInfo::RfcommProtocol );
	qDebug() << "Socket create";
	socket->connectToService( QBluetoothAddress(BeagleBluetoothAddress), QBluetoothUuid( QString( UUID ) ), QIODevice::ReadWrite );
	qDebug() << "Tentative connection";

	qDebug() << "peer is " << socket->peerName();
	qDebug() << "peer is " << socket->isOpen();

	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
	if (engine.rootObjects().isEmpty())
		return -1;

//	while ( true )
//	{
//		++count;

//		if ( count % 5000 == 0 )
//		{

//		}


//	}

	return app.exec();
}
