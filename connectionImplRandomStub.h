#ifndef CONNECTIONIMPLRANDOMSTUB_H
#define CONNECTIONIMPLRANDOMSTUB_H
#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QTimer>
#include "connectionImpl.h"
class connectionImplRandomStub : public QObject, public ConnectionImpl
{
    Q_OBJECT
public:
    typedef ConnectionImpl::BufferType BufferType;
    typedef ConnectionImpl::RetType RetType;
    connectionImplRandomStub(const std::string &ip, unsigned short port, const ConnectionCallback* c);
    connectionImplRandomStub();//{qDebug()<<"default ctor";}
    virtual ~connectionImplRandomStub(){}
    virtual RetType getAnsver(int length);
    virtual int sendCommand(const QByteArray &);
private:
    virtual int connect_();
    QMutex mtx_;
    QMutex mtxInputBuffer_;
    QByteArray InputBfr_;
    QTimer timer_;
public slots:
    void slotReadyRead();

//    void slotError(QAbstractSocket::SocketError){}

//    void slotConnected(){}
   // void slotConnect(QHostAddress);
   // void slotSendToServer();
};

#endif // CONNECTIONIMPLRANDOMSTUB_H
