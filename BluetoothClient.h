#ifndef BLUETOOTHCLIENT_H
#define BLUETOOTHCLIENT_H

#include <QtBluetooth/QBluetoothServiceInfo>

#include <QtCore/QObject>

QT_FORWARD_DECLARE_CLASS(QBluetoothSocket)

QT_USE_NAMESPACE

class BluetoothClient : public QObject
{
	Q_OBJECT

public:
	explicit BluetoothClient(QObject *parent = 0);
	~BluetoothClient();

	void startClient(const QBluetoothServiceInfo &remoteService);
	void stopClient();

public slots:
	void sendMessage(const QString &message);

signals:
	void messageReceived(const QString &sender, const QString &message);
	void connected(const QString &name);
	void disconnected();

private slots:
	void readSocket();
	void connected();

private:
	QBluetoothSocket *socket;
};

#endif // BLUETOOTHCLIENT_H
