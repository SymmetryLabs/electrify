#-------------------------------------------------
#
# Project created by QtCreator 2015-07-07T16:48:33
#
#-------------------------------------------------

QT       += core gui

unix:QMAKE_CXX = ccache g++
win32:QMAKE_CXX = g++

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = designer
TEMPLATE = app


SOURCES += main.cpp\
    component_grid_qt.cpp \
    component_grid_item_qt.cpp \
    component_list_qt.cpp \
    designer_window_qt.cpp \
    output_simulation_qt.cpp

HEADERS  += \
    component_grid_qt.h \
    component_grid_item_qt.h \
    component_list_qt.h \
    designer_window_qt.h \
    output_simulation_qt.h

FORMS    += \
    component_grid_qt.ui \
    component_grid_item_qt.ui \
    designer_window_qt.ui

# Link against symmetry engine lib
LIBS += -L$$OUT_PWD/engine -lSymmetryEngine

# Include system headers (for boost only at the moment)
QMAKE_INCDIR += /usr/local/include

# Include engine headers
INCLUDEPATH += $$OUT_PWD/engine/include

# Note: not needed on mac anymore, possibly needed on others, so not deleting it yet
# DEPENDPATH += $$DESTDIR/../../engine/src

mac {
    # Bundles the engine library with the app
    EngineLib.path = Contents/Frameworks
    EngineLib.files = engine/libSymmetryEngine.dylib
    QMAKE_BUNDLE_DATA += EngineLib

    # Makes it so the app can find the lib based on the @rpath
    QMAKE_LFLAGS += '-Wl,-rpath,@loader_path/../Frameworks'
}

win32 {
    INCLUDEPATH += $$(BOOST_ROOT)
    LIBS += -L$$(BOOST_ROOT)/stage/lib/
    LIBS += $$(SYSTEMROOT)/System32/opengl32.dll
}
