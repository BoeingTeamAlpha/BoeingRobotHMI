#include "BluetoothDevice.h"


#include <QtBluetooth/QBluetoothAddress>
#include <QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include <QtBluetooth/QBluetoothServiceDiscoveryAgent>
#include <QtBluetooth/QBluetoothLocalDevice>

#include <QDebug>

#include "BluetoothClient.h"
#include "BluetoothServer.h"

BluetoothDevice::BluetoothDevice( QObject *parent /* = 0 */ )
	: QObject( parent )
	, localDevice(new QBluetoothLocalDevice)
{

	address = localDevice->address();
	_client = new BluetoothClient();
	_server = new BluetoothServer( this );

	connect(_server, SIGNAL(clientConnected(QString)), this, SLOT(clientConnected(QString)));
	connect(_server, SIGNAL(clientDisconnected(QString)), this, SLOT(clientDisconnected(QString)));
	connect(_server, SIGNAL(messageReceived(QString,QString)),
			this, SLOT(showMessage(QString,QString)));
	connect(this, SIGNAL(sendMessage(QString)), _server, SLOT(sendMessage(QString)));

	_server->startServer( address );

	qDebug() << "My address is " << address;
	discoveryAgent = new QBluetoothServiceDiscoveryAgent( address );

	connect( discoveryAgent, SIGNAL(serviceDiscovered(QBluetoothServiceInfo)),
			 this, SLOT(serviceDiscovered(QBluetoothServiceInfo)));

	// add context menu for devices to be able to pair device
}

BluetoothDevice::~BluetoothDevice()
{
	delete discoveryAgent;
	delete _client;
	delete _server;
}

void BluetoothDevice::startScan()
{
	discoveryAgent->start();
}

void BluetoothDevice::stopScan()
{
	discoveryAgent->stop();
}

void BluetoothDevice::setGeneralUnlimited(bool unlimited)
{
	if ( unlimited )
	{
//		discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::GeneralUnlimitedInquiry);
	}
	else
	{
//		discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::LimitedInquiry);
	}
}

void BluetoothDevice::startPairing( const QBluetoothAddress& address )
{
	localDevice->requestPairing( address, QBluetoothLocalDevice::Paired );
}

int BluetoothDevice::pairingStatus( const QBluetoothAddress& address )
{
	return localDevice->pairingStatus( address );
}

void BluetoothDevice::showMessage(const QString &sender, const QString &message)
{
	qDebug() << sender << " sent " << message;
}

void BluetoothDevice::clientConnected(const QString &name)
{
	qDebug() << "Client connected " << name;
}

void BluetoothDevice::clientDisconnected(const QString &name)
{
	qDebug() << "Client disconnected " << name;
}

void BluetoothDevice::clientDisconnected()
{
	BluetoothClient* client = qobject_cast< BluetoothClient* >( sender() );
	if ( client )
	{
		qDebug() << "Client disconnected\r\n";
		client->deleteLater();
	}
}

void BluetoothDevice::serviceDiscovered(const QBluetoothServiceInfo &serviceInfo)
{
	qDebug() << serviceInfo.socketProtocol();
}

//void BluetoothDevice::itemActivated(QListWidgetItem *item)
//{
//	QString text = item->text();

//	int index = text.indexOf(' ');

//	if (index == -1)
//		return;

//	QBluetoothAddress address(text.left(index));
//	QString name(text.mid(index + 1));

//	ServiceDiscoveryDialog d(name, address);
//	d.exec();
//}

void BluetoothDevice::setDiscoverable( bool isDiscoverable )
{
	if ( isDiscoverable )
	{
		localDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
	}
	else
	{
		localDevice->setHostMode(QBluetoothLocalDevice::HostConnectable);
	}
}

void BluetoothDevice::setBluetoothPower( bool isOn )
{
	if ( isOn )
	{
		localDevice->powerOn();
	}
	else
	{
		localDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
	}
}


void BluetoothDevice::displayPairingMenu(const QPoint &pos)
{
	//	if (ui->list->count() == 0)
	//		return;
	//	QMenu menu(this);
	//	QAction *pairAction = menu.addAction("Pair");
	//	QAction *removePairAction = menu.addAction("Remove Pairing");
	//	QAction *chosenAction = menu.exec(ui->list->viewport()->mapToGlobal(pos));
	//	QListWidgetItem *currentItem = ui->list->currentItem();

	//	QString text = currentItem->text();
	//	int index = text.indexOf(' ');
	//	if (index == -1)
	//		return;

	//	QBluetoothAddress address (text.left(index));
	//	if (chosenAction == pairAction) {
	//		localDevice->requestPairing(address, QBluetoothLocalDevice::Paired);
	//	} else if (chosenAction == removePairAction) {
	//		localDevice->requestPairing(address, QBluetoothLocalDevice::Unpaired);
	//	}
}
void BluetoothDevice::pairingDone(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
	//	QList<QListWidgetItem *> items = ui->list->findItems(address.toString(), Qt::MatchContains);

	//	if (pairing == QBluetoothLocalDevice::Paired || pairing == QBluetoothLocalDevice::AuthorizedPaired ) {
	//		for (int var = 0; var < items.count(); ++var) {
	//			QListWidgetItem *item = items.at(var);
	//			item->setTextColor(QColor(Qt::green));
	//		}
	//	} else {
	//		for (int var = 0; var < items.count(); ++var) {
	//			QListWidgetItem *item = items.at(var);
	//			item->setTextColor(QColor(Qt::red));
	//		}
	//	}
}
