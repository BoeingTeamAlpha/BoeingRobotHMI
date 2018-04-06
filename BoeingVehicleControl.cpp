#include "BoeingVehicleControl.h"

#include "SendMessageIndex.h"

#include <stdint.h>
#include <QDebug>
#include <QThread>
#define BeagleBluetoothAddress ("80:30:DC:04:39:D4")
#define UUID ("00001101-0000-1000-8000-00805f9b34fb")

#define ReceiveMessageSize ( 4 )
#define SendMessageSize ( 16 )
#define BluetoothPollRate ( 50 )

BoeingVehicleControl::BoeingVehicleControl()
	: QObject()
	, _bluetoothConnected( false )
	, _metalDetected( false )
	, _batteryPercent( 0 )
{
	_receiveMessage.resize( ReceiveMessageSize );
	_sendMessage.resize( SendMessageSize );

	zeroReceiveMessage();
	zeroSendMessage();

	setupSocket();

	_timer = new QTimer( this );
	connect( _timer, &QTimer::timeout, this, &BoeingVehicleControl::update );

//	_timer->start( BluetoothPollRate );
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
//	for ( int j = 0; j < _sendMessage.size(); ++j )
//	{
//		qDebug() << j << (uint8_t)_sendMessage[ j ];// << endl;
//	}
//	qDebug() << "updating" <<
	_socket->write( _sendMessage );
}

void BoeingVehicleControl::setLeftDriveMotor( const int dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::LeftDriveMotor - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::LeftDriveMotor ] = ( temp >> 8 ) & 0xff;
}

void BoeingVehicleControl::setRightDriveMotor( const int dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::RightDriveMotor - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::RightDriveMotor ] = ( temp >> 8 ) & 0xff;
}

void BoeingVehicleControl::setCameraLeftRight( const uint dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::CameraLeftRight - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::CameraLeftRight ] = ( temp >> 8 ) & 0xff;
//	emit cameraLeftRightChanged();
}

void BoeingVehicleControl::setDumpBedRaiseLower( const uint dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::DumpBedRaiseLower - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::DumpBedRaiseLower ] = ( temp >> 8 ) & 0xff;
//	emit dumpBedRaiseLowerChanged();
}

void BoeingVehicleControl::setGripperRaiseLower( const uint dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::GripperRaiseLower - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::GripperRaiseLower ] = ( temp >> 8 ) & 0xff;
//	emit gripperRaiseLowerChanged();
}

void BoeingVehicleControl::setGripperOpenClose( const uint dutyCycle )
{
	uint16_t temp = static_cast< uint16_t >( dutyCycle );
	_sendMessage[ SendMessageIndex::GripperOpenClose - 1 ] = temp & 0xFF;
	_sendMessage[ SendMessageIndex::GripperOpenClose ] = ( temp >> 8 ) & 0xff;
//	emit gripperOpenCloseChanged();
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

void BoeingVehicleControl::socketError( QBluetoothSocket::SocketError error )
{
	switch ( error )
	{
	case QBluetoothSocket::NoSocketError:
		qDebug() << "no socket error";
		_timer->start( BluetoothPollRate );
		break;

	default:
		qDebug() << "socket error " << error << _socket->state();
//		_socket->close();
//		delete _socket;
//		setupSocket();
//		_timer->stop();
//		zeroReceiveMessage();
//		zeroSendMessage();
//		_socket->close();
//		_socket->open( QIODevice::ReadWrite );
		break;
	}
}

void BoeingVehicleControl::readSocket()
{
	_receiveMessage = _socket->readAll();
//	qDebug() << "read " << _receiveMessage.size();

//	for ( int j = 0; j < _receiveMessage.size(); ++j )
//	{
//		qDebug() << j << (uint8_t)_receiveMessage[ j ];// << endl;
//	}

	emit batteryPercentChanged();
	emit metalDetectedChanged();
}

void BoeingVehicleControl::peerConnected()
{
	qDebug() << "peer connected";
//	QThread::usleep( 500000 );
	_bluetoothConnected = true;
	_timer->start( BluetoothPollRate );
	emit bluetoothConnectedChanged();
}

void BoeingVehicleControl::peerDisconnected()
{
	qDebug() << "peer disconnected";
	_bluetoothConnected = false;
	_timer->stop();
	emit bluetoothConnectedChanged();
}

void BoeingVehicleControl::setupSocket()
{
	_socket = new QBluetoothSocket( QBluetoothServiceInfo::RfcommProtocol );

//	_socket->setCurrentWriteChannel( 1 );
//	_socket->setCurrentReadChannel( 1 );
	_socket->connectToService( QBluetoothAddress( BeagleBluetoothAddress ), QBluetoothUuid( QString( UUID ) ), QIODevice::ReadWrite );

	connect( _socket, &QBluetoothSocket::readyRead, this, &BoeingVehicleControl::readSocket );
	connect( _socket, &QBluetoothSocket::connected, this, &BoeingVehicleControl::peerConnected );
	connect( _socket, &QBluetoothSocket::disconnected, this, &BoeingVehicleControl::peerDisconnected );
	connect( _socket, QOverload<QBluetoothSocket::SocketError>::of(&QBluetoothSocket::error),
			 this, &BoeingVehicleControl::socketError);
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
