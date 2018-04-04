#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include "BoeingVehicleControl.h"

int main(int argc, char *argv[])
{
	QGuiApplication app( argc, argv );
	BoeingVehicleControl boeingVehicleControl;
	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty( "BoeingVehicleControl", &boeingVehicleControl );
	engine.load( QUrl( "qrc:/main.qml" ) );

	QQuickWindow* window = qobject_cast< QQuickWindow* >( engine.rootObjects().first() );
	window->showFullScreen();
	return app.exec();
}
