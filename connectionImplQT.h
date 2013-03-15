#ifndef CONNECTIONIMPLQT_H
#define CONNECTIONIMPLQT_H
#include <QScopedPointer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QTimer>
#include <QMutex>
#include "connectionImpl.h"
#include "syncronizeable.h"

//class connector_;

class ConnectionImplQT : public QObject, public ConnectionImpl
{
    Q_OBJECT
public:
    typedef ConnectionImpl::BufferType BufferType;
    typedef ConnectionImpl::RetType RetType;
    ConnectionImplQT(const std::string &ip, unsigned short port, const ConnectionCallback* c);
    ConnectionImplQT(){qDebug()<<"default ctor";}
    virtual ~ConnectionImplQT(){}
    virtual RetType getAnsver(int length);
    virtual int sendCommand(const QByteArray &);
private:
    virtual int connect_();
    QTcpSocket sock_;
    QMutex mtx_;
    QMutex mtxInputBuffer_;
    QByteArray InputBfr_;
public slots:
    void slotReadyRead();

    void slotError(QAbstractSocket::SocketError);

    void slotConnected();
   // void slotConnect(QHostAddress);
   // void slotSendToServer();
};

#endif // CONNECTIONIMPLQT_H
