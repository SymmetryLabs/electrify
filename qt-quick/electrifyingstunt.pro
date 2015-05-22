QT += qml quick

HEADERS += glrenderer.h
SOURCES += glrenderer.cpp main.cpp
RESOURCES += electrifyingstunt.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/electrifyingstunt
INSTALLS += target