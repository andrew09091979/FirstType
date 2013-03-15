#include "connectionImplQT.h"

ConnectionImplQT::ConnectionImplQT(const std::string &ip, unsigned short port, const ConnectionCallback *c)
    : ConnectionImpl(ip, port, c)
{
    ConnectionImpl::isConnected = false;
    QObject::connect(&sock_,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
    QObject::connect(&sock_,SIGNAL(connected()),this,SLOT(slotConnected()));
    QObject::connect(&sock_,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));
}

int ConnectionImplQT::connect_()
{
    if (mtx_.tryLock())//Can't use QMutexLocker, because mtx_ should be unlocked in slotConnected()
    {
        qDebug() << "connecting to..." << ConnectionImpl::ip_.c_str() << ":" << ConnectionImpl::port_;
        //sock_.connectToHost(ConnectionImpl::ip_.c_str() , ConnectionImpl::port_);
        sock_.connectToHost("192.168.5.234", 6001);
        return 1;
    }
    return 0;
}

ConnectionImplQT::RetType ConnectionImplQT::getAnsver(int length)
{
    qint64 lenCopied = 0;
    int size = 0;
    BufferType * bfr = nullptr;
    std::auto_ptr< BufferType > res(bfr);
    ConnectionImpl::bfr_.clear();
//    qDebug()<<"ConnectionImplQT::getAnsver length = " << length;
    if (!isConnected)
        connect_();
    if (isConnected)
    {
        size = InputBfr_.size();
        //qDebug()<<"ConnectionImplQT::getAnsver isConnected ok locking...";
        QMutexLocker ml(&mtxInputBuffer_);
        //qDebug() <<" ConnectionImplQT::getAnsver InputBfr_ = "<< InputBfr_.toHex() << " size = " << size;
        bfr = new BufferType;
        res.reset(bfr);
        for(int i = 0; (i<length)&&(i<size);++i)
        {
           res->push_back(InputBfr_.at(i));
           ++lenCopied;
        }
        InputBfr_.remove(0, lenCopied);
    }
    else
    {
    }
    return res;
}

int ConnectionImplQT::sendCommand(const QByteArray & data)
{
    quint64 res;
    if (!isConnected)
    {
        res = -1;
        connect_();
    }
    else
    {
       res = sock_.write(data);
       qDebug()<< "sent "<< res << " bytes" << " data size = " << data.size();
       if (res == -1)
           isConnected = false;
       sock_.flush();
    }
    return res;
}

void ConnectionImplQT::slotReadyRead()
{
    qint64 bytesAvailable;

    {
        QMutexLocker ml(&mtxInputBuffer_);
        bytesAvailable = sock_.bytesAvailable();
        InputBfr_.append(sock_.read(bytesAvailable));
    }
    qDebug()<<"ConnectionImplQT::bytesAvailable = " << bytesAvailable;
    clb_->ansverReceived(bytesAvailable);
}

void ConnectionImplQT::slotError(QAbstractSocket::SocketError e)
{
    qDebug()<<"slotError " << e;
    clb_->disconnected();
}

void ConnectionImplQT::slotConnected()
{
    qDebug()<<"slotConnected";
    mtx_.unlock();
    isConnected = true;
    clb_->connected();
}
/*
connector_::connector_(Syncronizeable *s) : s_(s)
{
    QObject::connect(&timer_, SIGNAL(timeout()), this, SLOT(slotTimer()));
    QObject::connect(&sock_,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
    QObject::connect(&sock_,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(slotError(QAbstractSocket::SocketError)));
    timer_.start(1000);
}

void connector_::slotReadyRead()
{

}

void connector_::slotError(QAbstractSocket::SocketError)
{

}


void connector_::slotTimer()
{
    timer_.start(1000);
    s_->tick();
}
*/
