#ifndef BLUETOOTHSERVER_H
#define BLUETOOTHSERVER_H

#include <QtBluetooth/QBluetoothServiceInfo>
#include <QtBluetooth/QBluetoothAddress>
#include <unistd.h>
#include <pthread.h>
#include <QtCore/QObject>
//#include <QtCore/QList>

QT_FORWARD_DECLARE_CLASS(QBluetoothServer)
QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE

class BluetoothServer : public QObject
{
	Q_OBJECT

private:

	QBluetoothServer* _rfcommServer;
	QBluetoothServiceInfo _serviceInfo;
	QBluetoothSocket* _clientSockets;

public:

	explicit BluetoothServer( QObject* parent = 0 );
	~BluetoothServer();

	void startServer( const QBluetoothAddress& localAdapter = QBluetoothAddress() );
	void stopServer();

public slots:

	void sendMessage(const QString &message);

signals:

	void messageReceived(const QString &sender, const QString &message);
	void clientConnected(const QString &name);
	void clientDisconnected(const QString &name);

private slots:

	void clientConnected();
	void clientDisconnected();
	void readSocket();
};

#endif // BLUETOOTHSERVER_H
