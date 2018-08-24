#include "serverhandler.h"

ServerHandler::ServerHandler(QObject *parent) : QObject(parent), mTcpSocket(nullptr), mHost("irc.freenode.net"),
    mPort(6667)
{
}

void ServerHandler::connectServer()
{
    if (mTcpSocket == nullptr)
    {
    mTcpSocket = new QTcpSocket();
    connect(mTcpSocket, &QAbstractSocket::readyRead,
            this, &ServerHandler::handleRead);
    connect(mTcpSocket, &QAbstractSocket::connected,
            this, &ServerHandler::canWrite);
    connect(mTcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
            this, &ServerHandler::onError);
    mTcpSocket->connectToHost(mHost, mPort);
    }
}

void ServerHandler::write(QString line) {
#ifdef DEBUG
    qDebug() << "-> " << line;
#endif
    auto arr = line.toLocal8Bit();
    mTcpSocket->write(arr);
    mTcpSocket->write("\r\n", 2);
}

void ServerHandler::flush() {
    mTcpSocket->flush();
}

void ServerHandler::handleRead()
{
    while (mTcpSocket->canReadLine())
    {
        auto arr = mTcpSocket->readLine();
        if (arr == nullptr) {
            qCritical() << "Error on read";
            return;
        }
        auto s = arr.data();
#ifdef DEBUG
        qDebug() << "<-" << s;
#endif
        emit line(s);
    }
}

void ServerHandler::onError(QAbstractSocket::SocketError err)
{
    Q_UNUSED(err)
    qCritical() << "Error: " << mTcpSocket->errorString();
    mTcpSocket->disconnectFromHost();
    mTcpSocket = nullptr;
}
