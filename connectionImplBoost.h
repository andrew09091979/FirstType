#ifndef CONNECTIONIMPLBOOST_H
#define CONNECTIONIMPLBOOST_H
#include <QScopedPointer>
#include <QDebug>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/error.hpp>
#include <boost/bind.hpp>
#include "connectionImpl.h"

using boost::asio::ip::tcp;

class ConnectionImplBoost : public ConnectionImpl
{
public:
    typedef ConnectionImpl::BufferType BufferType;
    typedef ConnectionImpl::RetType RetType;
    ConnectionImplBoost(const std::string &ip, unsigned short port, const ConnectionCallback* c);
    ConnectionImplBoost(){qDebug()<<"default ctor";}
    virtual ~ConnectionImplBoost(){}
    virtual RetType getAnsver(int length);
    virtual int sendCommand(const QByteArray&);
    void handle_connect(const boost::system::error_code&);
    void handle_read(const boost::system::error_code& e);
private:
    boost::asio::io_service iosrv_;
    QScopedPointer<boost::asio::io_service> io_service_;
    QScopedPointer<tcp::socket> socket_;
    bool bConnected;

    virtual int connect_();
    BufferType bfr_;
};

#endif // CONNECTIONIMPLBOOST_H
