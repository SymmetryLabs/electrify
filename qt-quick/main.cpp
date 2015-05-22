
#include <QGuiApplication>

#include <QtQuick/QQuickView>

#include "GLRenderer.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<GLRenderer>("OpenGLUnderQML", 1, 0, "GLRenderer");

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:///scenegraph/electrifyingstunt/main.qml"));
    view.show();

    return app.exec();
}