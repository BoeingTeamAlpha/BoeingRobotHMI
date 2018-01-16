#include "BluetoothClient.h"

#include <QtBluetooth/QBluetoothSocket>

BluetoothClient::BluetoothClient( QObject* parent )
	: QObject(parent)
	, socket(0)
{
}

BluetoothClient::~BluetoothClient()
{
	stopClient();
}

//! [startClient]
void BluetoothClient::startClient(const QBluetoothServiceInfo &remoteService)
{
	if (socket)
		return;

	// Connect to service
	socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
	qDebug() << "Create socket";
	socket->connectToService(remoteService);
	qDebug() << "ConnectToService done";

	connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
	connect(socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
}
//! [startClient]

//! [stopClient]
void BluetoothClient::stopClient()
{
	delete socket;
	socket = 0;
}
//! [stopClient]

//! [readSocket]
void BluetoothClient::readSocket()
{
	if (!socket)
		return;

	while (socket->canReadLine()) {
		QByteArray line = socket->readLine();
		emit messageReceived(socket->peerName(),
							 QString::fromUtf8(line.constData(), line.length()));
	}
}
//! [readSocket]

//! [sendMessage]
void BluetoothClient::sendMessage(const QString &message)
{
	QByteArray text = message.toUtf8() + '\n';
	socket->write(text);
}
//! [sendMessage]

//! [connected]
void BluetoothClient::connected()
{
	emit connected(socket->peerName());
}
//! [connected]
