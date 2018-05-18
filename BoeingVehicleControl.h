#ifndef BOEINGVEHICLECONTROL_H
#define BOEINGVEHICLECONTROL_H

#include <QTcpSocket>
#include <QByteArray>
#include <QObject>
#include <QTimer>
#include "LinearConverter.h"

class BoeingVehicleControl : public QObject
{
	Q_OBJECT
	Q_PROPERTY( int leftDriveMotor		READ leftDriveMotor		WRITE setLeftDriveMotor		NOTIFY leftDriveMotorChanged )
	Q_PROPERTY( int rightDriveMotor		READ rightDriveMotor	WRITE setRightDriveMotor	NOTIFY rightDriveMotorChanged )
	Q_PROPERTY( uint cameraLeftRight	READ cameraLeftRight	WRITE setCameraLeftRight	NOTIFY cameraLeftRightChanged )
	Q_PROPERTY( uint dumpBedRaiseLower	READ dumpBedRaiseLower	WRITE setDumpBedRaiseLower	NOTIFY dumpBedRaiseLowerChanged )
	Q_PROPERTY( uint gripperRaiseLower	READ gripperRaiseLower	WRITE setGripperRaiseLower	NOTIFY gripperRaiseLowerChanged )
	Q_PROPERTY( uint gripperOpenClose	READ gripperOpenClose	WRITE setGripperOpenClose	NOTIFY gripperOpenCloseChanged )
	Q_PROPERTY( uint batteryPercent		READ batteryPercent									NOTIFY batteryPercentChanged )
	Q_PROPERTY( bool metalDetected		READ metalDetected									NOTIFY metalDetectedChanged )
	Q_PROPERTY( bool connected			READ connected										NOTIFY connectedChanged )

private:

	// typedef the appropriate range for the class
	typedef LibBBB::Math::Range< int > RangeType;
	
	// typedef the converter for easier instantiation
	typedef LibBBB::Math::LinearConverter< int > Converter;
	
	bool _connected;
	bool _metalDetected;
	Converter _motorConverter;
	int _receiveMessageTime;
	uint _batteryPercent;
	QTcpSocket* _socket;
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

	uint batteryPercent() const;

	bool metalDetected() const;

	bool connected() const;

public slots:

	void update();

	void setLeftDriveMotor( const int dutyCycle );

	void setRightDriveMotor( const int dutyCycle );

	void setCameraLeftRight( const uint dutyCycle );

	void setDumpBedRaiseLower( const uint dutyCycle );

	void setGripperRaiseLower( const uint dutyCycle );

	void setGripperOpenClose( const uint dutyCycle );

	void setLeftMotorSliderChangedState( bool isPressed );

	void setRightMotorSliderChangedState( bool isPressed );

	void socketError( QTcpSocket::SocketError error );

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

	void batteryPercentChanged();

	void metalDetectedChanged();

	void connectedChanged();

private:

	void setupSocket();

	void zeroReceiveMessage();

	void zeroSendMessage();

};

#endif // BOEINGVEHICLECONTROL_H
