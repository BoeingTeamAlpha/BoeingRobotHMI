#include "BluetoothServer.h"

#include <QtBluetooth/QBluetoothServer>
#include <QtBluetooth/QBluetoothSocket>
#include <QtBluetooth/QBluetoothLocalDevice>
//#include <qdebug.h>

//! [Service UUID]
static const QLatin1String serviceUuid("e8e10f95-1a70-4b27-9ccf-02010264e9c8");
//! [Service UUID]

BluetoothServer::BluetoothServer(QObject *parent)
	:   QObject(parent)
	, _rfcommServer(0)
{
}

BluetoothServer::~BluetoothServer()
{
	stopServer();
}

void BluetoothServer::startServer(const QBluetoothAddress& localAdapter)
{
	if (_rfcommServer)
		return;

	//! [Create the server]
	_rfcommServer = new QBluetoothServer(QBluetoothServiceInfo::RfcommProtocol, this);
	connect(_rfcommServer, SIGNAL(newConnection()), this, SLOT(clientConnected()));
	bool result = _rfcommServer->listen( localAdapter, 1 );
	if (!result) {
		qWarning() << "Cannot bind chat server to" << localAdapter.toString();
		return;
	}
	//! [Create the server]

	//serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceRecordHandle, (uint)0x00010010);

	//! [Class Uuuid must contain at least 1 entry]
	QBluetoothServiceInfo::Sequence classId;

	classId << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::SerialPort));
	_serviceInfo.setAttribute(QBluetoothServiceInfo::BluetoothProfileDescriptorList,
							 classId);

	classId.prepend(QVariant::fromValue(QBluetoothUuid(serviceUuid)));

	_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceClassIds, classId);
	//! [Class Uuuid must contain at least 1 entry]


	//! [Service name, description and provider]
	_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceName, tr("Boeing Alpha Tablet"));
	_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceDescription,
							 tr("RC for Alpha"));
	_serviceInfo.setAttribute(QBluetoothServiceInfo::ServiceProvider, tr("siu.edu"));
	//! [Service name, description and provider]

	//! [Service UUID set]
	_serviceInfo.setServiceUuid(QBluetoothUuid(serviceUuid));
	//! [Service UUID set]

	//! [Service Discoverability]
	QBluetoothServiceInfo::Sequence publicBrowse;
	publicBrowse << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::PublicBrowseGroup));
	_serviceInfo.setAttribute(QBluetoothServiceInfo::BrowseGroupList,
							 publicBrowse);
	//! [Service Discoverability]

	//! [Protocol descriptor list]
	QBluetoothServiceInfo::Sequence protocolDescriptorList;
	QBluetoothServiceInfo::Sequence protocol;
	protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::L2cap));
	protocolDescriptorList.append(QVariant::fromValue(protocol));
	protocol.clear();
	protocol << QVariant::fromValue(QBluetoothUuid(QBluetoothUuid::Rfcomm))
			 << QVariant::fromValue(quint8(_rfcommServer->serverPort()));
	protocolDescriptorList.append(QVariant::fromValue(protocol));
	_serviceInfo.setAttribute(QBluetoothServiceInfo::ProtocolDescriptorList,
							 protocolDescriptorList);
	//! [Protocol descriptor list]

	//! [Register service]
	_serviceInfo.registerService(localAdapter);
	//! [Register service]
}

//! [stopServer]
void BluetoothServer::stopServer()
{
	// Unregister service
	_serviceInfo.unregisterService();

	// Close server
	delete _rfcommServer;
	_rfcommServer = 0;
}
//! [stopServer]

//! [sendMessage]
void BluetoothServer::sendMessage(const QString &message)
{
//	QByteArray text = message.toUtf8() + '\n';

//	foreach (QBluetoothSocket *socket, clientSockets)
//		socket->write(text);
}
//! [sendMessage]


//! [clientConnected]
void BluetoothServer::clientConnected()
{
	QBluetoothSocket *socket = _rfcommServer->nextPendingConnection();
	if (!socket)
		return;

	connect(socket, SIGNAL(readyRead()), this, SLOT(readSocket()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));
	emit clientConnected(socket->peerName());
}
//! [clientConnected]

//! [clientDisconnected]
void BluetoothServer::clientDisconnected()
{
	QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
	if (!socket)
		return;

	emit clientDisconnected(socket->peerName());

	socket->deleteLater();
}
//! [clientDisconnected]

//! [readSocket]
void BluetoothServer::readSocket()
{
	QBluetoothSocket *socket = qobject_cast<QBluetoothSocket *>(sender());
	if (!socket)
		return;

	while (socket->canReadLine())
	{
		QByteArray line = socket->readLine().trimmed();
		emit messageReceived(socket->peerName(),
							 QString::fromUtf8(line.constData(), line.length()));
	}
}
//! [readSocket]
