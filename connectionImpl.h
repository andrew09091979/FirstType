#ifndef CONNECTIONIMPL_H
#define CONNECTIONIMPL_H

#include <QByteArray>
#include <QTime>
#include <memory>
#include <vector>
#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/io_service.hpp>
#include <QMutex>
#include "connectionCallback.h"
#include "wrapped.h"
class ConnectionImpl
{
public:
    typedef float T;
    //typedef QByteArray BufferType;
    typedef  WrappedContainer<QByteArray, ThreadSafetyStrategy<QMutex, QMutexLocker>, int, char> BufferType;
    typedef std::auto_ptr <BufferType> RetType;
    ConnectionImpl(const std::string & ip, unsigned short port, const ConnectionCallback* c)
        :ip_(ip), port_(port), clb_(c), bfr_(50,0),isConnected(false){}
    ConnectionImpl(){}
    virtual ~ConnectionImpl(){}
    virtual RetType getAnsver(int length) = 0;
    virtual int sendCommand(const QByteArray&) = 0;
private:
    virtual int connect_() = 0;
protected:
    std::string ip_;
    unsigned short port_;
    BufferType bfr_;

    Wrapped<bool, ThreadSafetyStrategy<NullType, NullType> > isConnected;
    const ConnectionCallback* clb_;
};


#endif // CONNECTIONIMPL_H
