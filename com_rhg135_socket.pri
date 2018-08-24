QT += network qml

INCLUDEPATH += $$PWD/
VPATH += $$PWD/

SOURCES += \
  serverhandler.cpp \
  qsocket_plugin.cpp

HEADERS += \
  serverhandler.h

VERSION = 0.1.1
TARGET = socket
