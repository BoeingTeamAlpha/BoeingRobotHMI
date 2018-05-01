#include "BoeingVehicleControl.h"

#include "SendMessageIndex.h"
#include <QHostAddress>

#include <stdint.h>
#include <QDebug>
#include <QThread>
#include <QTime>
#define BeagleBluetoothAddress ("80:30:DC:04:39:D4")
#define UUID ("00001101-0000-1000-8000-00805f9b34fb")

#define ReceiveMessageSize ( 4 )
#define SendMessageSize ( 16 )
#define BluetoothPollRate ( 50 )

BoeingVehicleControl::BoeingVehicleControl()
	: QObject()
	, _bluetoothConnected( false )
	, _metalDetected( false )
	, _receiveMessageTime( 0 )
	, _batteryPercent( 0 )
{
	_receiveMessage.resize( ReceiveMessageSize );
	_sendMessage.resize( SendMessageSize );

	zeroReceiveMessage();
	zeroSendMessage();

	setupSocket();

	_timer = new QTimer( this );
	connect( _timer, &QTimer::timeout, this, &BoeingVehicleControl::update );
}

BoeingVehicleControl::~BoeingVehicleControl()
{
	delete _timer;
	delete _socket;
}

int BoeingVehicleControl::leftDriveMotor() const
{
	return ( signed int )( ( _sendMessage[ SendMessageIndex::LeftDriveMotor ] << 8 ) | ( _sendMessage[ SendMessageIndex::LeftDriveMotor - 1 ] ) );
}

int BoeingVehicleControl::rightDriveMotor() const
{
	return ( signed int )( ( _sendMessage[ SendMessageIndex::RightDriveMotor ] << 8 ) | ( _sendMessage[ SendMessageIndex::RightDriveMotor - 1 ] ) );
}

uint BoeingVehicleControl::cameraLeftRight() const
{
	return ( _sendMessage[ SendMessageIndex::CameraLeftRight ] << 8 ) | ( _sendMessage[ SendMessageIndex::CameraLeftRight - 1 ] );
}

uint BoeingVehicleControl::dumpBedRaiseLower() const
{
	return ( _sendMessage[ SendMessageIndex::DumpBedRaiseLower ] << 8 ) | ( _sendMessage[ SendMessageIndex::DumpBedRaiseLower - 1 ] );
}

uint BoeingVehicleControl::gripperRaiseLower() const
{
	return ( _sendMessage[ SendMessageIndex::GripperRaiseLower ] << 8 ) | ( _sendMessage[ SendMessageIndex::GripperRaiseLower - 1 ] );
}

uint BoeingVehicleControl::gripperOpenClose() const
{
	return ( _sendMessage[ SendMessageIndex::GripperOpenClose ] << 8 ) | ( _sendMessage[ SendMessageIndex::GripperOpenClose - 1 ] );
}

uint BoeingVehicleControl::batteryPercent() const
{
	return _receiveMessage[ 0 ];
}

bool BoeingVehicleControl::metalDetected() const
{
	return _receiveMessage[ 1 ] & 0x01;
}

bool BoeingVehicleControl::bluetoothConnected() const
{
	return _bluetoothConnected;
}

void BoeingVehicleControl::update()
{
//	int currentTime = QTime::currentTime().msec();
//	if ( currentTime - _receiveMessageTime > BluetoothPollRate * 2 )
//	{
//		peerDisconnected();
//		qDebug() << "bluetooth timeout";
//		return;
//	}

	_socket->write( _sendMessage );
}

void BoeingVehicleControl::setLeftDriveMotor( const int dutyCycle )
{
	uint16_t temp = _bluetoothConnected ? static_cast< uint16_t >( dutyCycle ) : 0;
	_sendMessage[ SendMessageIndex::LeftDriveMotor - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::LeftDriveMotor ] = ( temp >> 8 ) & 0xff;
}

void BoeingVehicleControl::setRightDriveMotor( const int dutyCycle )
{
	uint16_t temp = _bluetoothConnected ? static_cast< uint16_t >( dutyCycle ) : 0;
	_sendMessage[ SendMessageIndex::RightDriveMotor - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::RightDriveMotor ] = ( temp >> 8 ) & 0xff;
}

void BoeingVehicleControl::setCameraLeftRight( const uint dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::CameraLeftRight - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::CameraLeftRight ] = ( temp >> 8 ) & 0xff;
}

void BoeingVehicleControl::setDumpBedRaiseLower( const uint dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::DumpBedRaiseLower - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::DumpBedRaiseLower ] = ( temp >> 8 ) & 0xff;
}

void BoeingVehicleControl::setGripperRaiseLower( const uint dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::GripperRaiseLower - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::GripperRaiseLower ] = ( temp >> 8 ) & 0xff;
}

void BoeingVehicleControl::setGripperOpenClose( const uint dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::GripperOpenClose - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::GripperOpenClose ] = ( temp >> 8 ) & 0xff;
}

void BoeingVehicleControl::setLeftMotorSliderChangedState( bool isPressed )
{
	if ( !isPressed )
	{
		setLeftDriveMotor( 0 );
	}

	emit leftDriveMotorChanged();
}

void BoeingVehicleControl::setRightMotorSliderChangedState( bool isPressed )
{
	if ( !isPressed )
	{
		setRightDriveMotor( 0 );
	}

	emit rightDriveMotorChanged();
}

void BoeingVehicleControl::socketError( QTcpSocket::SocketError error )
{
	switch ( error )
	{
	case QTcpSocket::ConnectedState:
		qDebug() << "no socket error";
		_timer->start( BluetoothPollRate );
		break;

	default:
		qDebug() << "socket error " << error << _socket->state();
		if ( _socket->state() != QTcpSocket::ClosingState )
		{
			peerDisconnected();
		}
		break;
	}
}

void BoeingVehicleControl::readSocket()
{
	_receiveMessage = _socket->readAll();
	_receiveMessageTime = QTime::currentTime().msec();

	emit batteryPercentChanged();
	emit metalDetectedChanged();
}

void BoeingVehicleControl::peerConnected()
{
	_bluetoothConnected = true;
	qDebug() << "connect time" << _receiveMessageTime;
	_receiveMessageTime = QTime::currentTime().msec();
	_timer->start( BluetoothPollRate );
	emit bluetoothConnectedChanged();
	emit metalDetectedChanged();
}

void BoeingVehicleControl::peerDisconnected()
{
	_timer->stop();
	_bluetoothConnected = false;
	_socket->close();
	_receiveMessage = _socket->readAll();
//	_socket->disconnectFromService();
	emit bluetoothConnectedChanged();
	emit metalDetectedChanged();
	QThread::usleep( 250000 );
//	_socket->connectToService( QBluetoothAddress( BeagleBluetoothAddress ), QBluetoothUuid( QString( UUID ) ), QIODevice::ReadWrite );
}

void BoeingVehicleControl::setupSocket()
{
	_socket = new QTcpSocket( this );
//	_socket->setCurrentReadChannel( 1 );
//	_socket->setCurrentWriteChannel( 1 );


	connect( _socket, &QTcpSocket::readyRead, this, &BoeingVehicleControl::readSocket );
	connect( _socket, &QTcpSocket::connected, this, &BoeingVehicleControl::peerConnected );
	connect( _socket, &QTcpSocket::disconnected, this, &BoeingVehicleControl::peerDisconnected );
	connect( _socket, QOverload<QTcpSocket::SocketError>::of(&QTcpSocket::error),
			 this, &BoeingVehicleControl::socketError);
	_socket->connectToHost( QHostAddress( QString( "192.168.8.1" ) ), 555 );

//	if( _socket->waitForConnected( 3000 ) )
//	{
//		_socket->disconnectFromHost();
//	}
}

void BoeingVehicleControl::zeroReceiveMessage()
{
	for ( int j = 0; j < _receiveMessage.size(); ++j )
	{
		_receiveMessage[ j ] = 0;
	}
}

void BoeingVehicleControl::zeroSendMessage()
{
	for ( int j = 0; j < _sendMessage.size(); ++j )
	{
		_sendMessage[ j ] = 0;
	}
}
