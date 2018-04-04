#ifndef BOEINGVEHICLECONTROL_H
#define BOEINGVEHICLECONTROL_H

#include <QBluetoothSocket>
#include <QByteArray>
#include <QObject>
#include <QTimer>

class BoeingVehicleControl : public QObject
{
	Q_OBJECT
	Q_PROPERTY( int leftDriveMotor		READ leftDriveMotor		WRITE setLeftDriveMotor		NOTIFY leftDriveMotorChanged )
	Q_PROPERTY( int rightDriveMotor		READ rightDriveMotor	WRITE setRightDriveMotor	NOTIFY rightDriveMotorChanged )
	Q_PROPERTY( uint cameraLeftRight	READ cameraLeftRight	WRITE setCameraLeftRight	NOTIFY cameraLeftRightChanged )
	Q_PROPERTY( uint dumpBedRaiseLower	READ dumpBedRaiseLower	WRITE setDumpBedRaiseLower	NOTIFY dumpBedRaiseLowerChanged )
	Q_PROPERTY( uint gripperRaiseLower	READ gripperRaiseLower	WRITE setGripperRaiseLower	NOTIFY gripperRaiseLowerChanged )
	Q_PROPERTY( uint gripperOpenClose	READ gripperOpenClose	WRITE setGripperOpenClose	NOTIFY gripperOpenCloseChanged )

private:

	QBluetoothSocket* _socket;
	QByteArray _receiveMessage;
	QByteArray _sendMessage;
	QTimer* _timer;

public:
	BoeingVehicleControl();

	~BoeingVehicleControl();

	int leftDriveMotor() const;

	int rightDriveMotor() const;

	uint cameraLeftRight() const;

	uint dumpBedRaiseLower() const;

	uint gripperRaiseLower() const;

	uint gripperOpenClose() const;

public slots:

	void update();

	void setLeftDriveMotor( const int dutyCycle );

	void setRightDriveMotor( const int dutyCycle );

	void setCameraLeftRight( const uint dutyCycle );

	void setDumpBedRaiseLower( const uint dutyCycle );

	void setGripperRaiseLower( const uint dutyCycle );

	void setGripperOpenClose( const uint dutyCycle );

	void socketError( QBluetoothSocket::SocketError error );

	void readSocket();

	void peerConnected();

	void peerDisconnected();

Q_SIGNALS:

	void leftDriveMotorChanged();

	void rightDriveMotorChanged();

	void cameraLeftRightChanged();

	void dumpBedRaiseLowerChanged();

	void gripperRaiseLowerChanged();

	void gripperOpenCloseChanged();

private:

	void setupSocket();

	void zeroReceiveMessage();

	void zeroSendMessage();

};

#endif // BOEINGVEHICLECONTROL_H