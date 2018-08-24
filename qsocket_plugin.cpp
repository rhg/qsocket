#include "serverhandler.h"

#include <qqml.h>
#include <QCoreApplication>

static void registerTypes()
{
    qmlRegisterType<ServerHandler>("com.rhg135.socket", 0, 1, "TcpSocket");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes)
