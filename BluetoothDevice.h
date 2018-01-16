#ifndef BLUETOOTHDEVICE_H
#define BLUETOOTHDEVICE_H

#include <QtBluetooth/QBluetoothLocalDevice>

#include <QtBluetooth/QBluetoothServiceInfo>
#include <QObject>

QT_FORWARD_DECLARE_CLASS(QBluetoothServiceDiscoveryAgent)
QT_FORWARD_DECLARE_CLASS(QBluetoothDeviceInfo)

class BluetoothClient;
class BluetoothServer;

QT_USE_NAMESPACE

class BluetoothDevice : public QObject
{
	Q_OBJECT

private:

	BluetoothClient* _client;
	BluetoothServer* _server;
public:
	explicit BluetoothDevice( QObject *parent = 0 );
	~BluetoothDevice();

public:

	void setBluetoothPower( bool isOn );
	void setDiscoverable( bool isDiscoverable );
	void displayPairingMenu(const QPoint &pos);
	void pairingDone(const QBluetoothAddress&, QBluetoothLocalDevice::Pairing);

	void startScan();

	void stopScan();

	void setGeneralUnlimited(bool unlimited);

	void startPairing( const QBluetoothAddress& address );

	int pairingStatus( const QBluetoothAddress& address );

signals:

	void sendMessage(const QString &message);

private slots:

//	void connectClicked();
//	void sendClicked();

	void showMessage(const QString &sender, const QString &message);

	void clientConnected(const QString &name);
	void clientDisconnected(const QString &name);
	void clientDisconnected();
//	void connected(const QString &name);

private:
	QBluetoothServiceDiscoveryAgent *discoveryAgent;
	QBluetoothLocalDevice *localDevice;

	QBluetoothAddress address;

	QBluetoothServiceInfo m_service;

private slots:
	void serviceDiscovered( const QBluetoothServiceInfo& serviceInfo );
};


#endif // BLUETOOTHDEVICE_H
