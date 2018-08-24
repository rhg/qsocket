#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QObject>
#include <QPointer>
#include <QTcpSocket>

class ServerHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString host MEMBER mHost)
    Q_PROPERTY(quint16 port MEMBER mPort)
private:
    QPointer<QTcpSocket> mTcpSocket;
    QString mHost;
    quint16 mPort;
public:
    explicit ServerHandler(QObject *parent = nullptr);
    Q_INVOKABLE void connectServer();
signals:
    void line(QString msg);
    void canWrite();
public slots:
    void write(QString line);
    void flush();
    void handleRead();
    void onError(QAbstractSocket::SocketError err);
};

#endif // SERVERHANDLER_H
