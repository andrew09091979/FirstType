#ifndef PROTOCOL10007_H
#define PROTOCOL10007_H
#include <QMutex>
#include "protocol.h"

template <class ConnectionImpl, class DataType>
class Protocol10007: public Protocol<DataType>, public ConnectionCallback
{
public:
    typedef ConnectionImpl ConnectionImplType;
    typedef typename ConnectionImpl::RetType ConnImplRetType;
    typedef typename std::vector<DataType> ValuesBfrType;
    typedef typename std::auto_ptr< ValuesBfrType > ValuesRetType;
    Protocol10007(const ProtocolCallback<DataType> * clb);
    int askForActualValues();
    int executeCommand(typename Protocol<DataType>::Command);
    int sendCommand(QByteArray&);
    virtual void ansverReceived(qint64) const;
    virtual void connected() const;
    virtual void disconnected() const;
protected:
    void setWaitingFor(qint64) const;
    qint64 getWaitingFor() const;
    quint32 getAddress(const QByteArray&) const;
    quint16 getDataSize(const QByteArray&) const;
private:
    std::auto_ptr< ConnectionImplType > pImpl_;
    Protocol10007& operator =(const Protocol10007&);
    const quint8 HEADER_LEN;// = 9;
    const quint8 TAIL_LEN;// = 4;
    mutable qint64 waitingFor_;
    mutable QMutex mtxWaitingFor_;
    mutable QByteArray bfr;
};

template <class ConnectionImpl, class DataType>
Protocol10007<ConnectionImpl, DataType>::Protocol10007(const ProtocolCallback<DataType> *clb)
    :Protocol<DataType>(clb), waitingFor_(0), HEADER_LEN(9), TAIL_LEN(4)
{
    std::string ip("192.168.5.234");
    pImpl_.reset(new ConnectionImplType(ip, 6001, this));
    mtxWaitingFor_.unlock();
}

template <class ConnectionImpl, class DataType>
qint64 Protocol10007<ConnectionImpl, DataType>::getWaitingFor() const
{
    QMutexLocker ml(&mtxWaitingFor_);
    return waitingFor_;
}

template <class ConnectionImpl, class DataType>
void Protocol10007<ConnectionImpl, DataType>::setWaitingFor(qint64 w) const
{
    QMutexLocker ml(&mtxWaitingFor_);
    waitingFor_ = w;
}
template <class ConnectionImpl, class DataType>
int Protocol10007<ConnectionImpl, DataType>::executeCommand(typename Protocol<DataType>::Command cmd)
{
//    if (cmd == GetValues)
//    {
//        askForActualValues();
//    }
    switch (cmd)
    {
        case Protocol<DataType>::GetValues:
            askForActualValues();
        break;
    }
    return 0;
}

template <class ConnectionImpl, class DataType>
int Protocol10007<ConnectionImpl, DataType>::askForActualValues()
{
    QByteArray getValuesCommand;
    QByteArray ValBfr;

    ValBfr.reserve(sizeof(typename ValuesBfrType::value_type));
    const unsigned char chReq[13] = {0x3f,0x30,0x31,0x20,0x08,0x0,0x0,0x68,0x0,0xc9,0x7a,0x0d,0x0};
    getValuesCommand.append((const char *)chReq,13);

    int res = pImpl_->sendCommand(getValuesCommand);
    if (res != -1)
        setWaitingFor(117);

    return res;
}

template <class ConnectionImpl, class DataType>
int Protocol10007<ConnectionImpl, DataType>::sendCommand(QByteArray & bfr)
{
 qDebug() << "Protocol10007::sendCommand";
    return pImpl_->sendCommand(bfr);
}

//connectionCallback interface
template <class ConnectionImpl, class DataType>
void Protocol10007<ConnectionImpl, DataType>::ansverReceived(qint64 length) const
{
    ValuesRetType ret(nullptr);
    qint64 tmp, size;
    qint16 pos = 17;
    qint8 *ptr;
    quint32 addr;
    quint16 dataSize;
    typename ValuesBfrType::value_type val;
    qint8 dummyBytes = 0;
    QByteArray tmpBfr;
    tmp = this->getWaitingFor();
//  qDebug() << "Protocol10007::ansverReceived length = " << length << " waiting for = " << tmp;
    bfr += *pImpl_->getAnsver(length).get();
    size = bfr.size();
    if (size > 0)
    {
        while(bfr.at(dummyBytes) != '>')//looking for starting byte
        {
            if(dummyBytes<size-1)
                ++dummyBytes;
            else
                break;
        }

        if (dummyBytes>0)
            bfr.remove(0,dummyBytes);

        size = bfr.size();
        if (size >= HEADER_LEN)//header received
        {
            addr = getAddress(bfr);
            dataSize = getDataSize(bfr);
//          qDebug() << "Protocol10007::ansverReceived addr = " << addr << " size = " << size << "dataSize = "<< dataSize;
            length -= dummyBytes;
//          qDebug() << "Protocol10007::ansverReceived bfr = " << bfr.toHex();
            if (tmp - length > 0)
                setWaitingFor(tmp - length);
            else
                setWaitingFor(0);
//          qDebug() << "Protocol10007::ansverReceived tmp - length = " << tmp - length;
            if (size >= dataSize+HEADER_LEN+TAIL_LEN)
            {
                ret.reset(new ValuesBfrType());
                while(pos<109)
                {
                    ptr = (qint8*)&val;
                    for(int i=0; i<sizeof(typename ValuesBfrType::value_type);++i)
                    {
                        *ptr = bfr.at(pos);
                        tmpBfr.push_back(bfr.at(pos));
                        ++ptr;
                        ++pos;
                    }
                    ret->push_back(val);
//                  qDebug() << "val = " << val<<" pos = " << pos << " tmpBfr = " << tmpBfr.toHex() ;
                    tmpBfr.clear();
                }
                Protocol<DataType>::clb_->actualValuesReceived(ret);
                bfr.clear();
            }
        }
    }
    else
    {

    }
}
template <class ConnectionImpl, class DataType>
quint32 Protocol10007<ConnectionImpl, DataType>::getAddress(const QByteArray& bfr) const
{
    quint32 res = 0;
    quint8 *ptr = (quint8*)&res;

    if (bfr.size() > 6)
    {
        for(int i=3; i<7; ++i)
        {
            *ptr = bfr.at(i);
            ++ptr;
        }
    }
    return res;
}

template <class ConnectionImpl, class DataType>
quint16 Protocol10007<ConnectionImpl, DataType>::getDataSize(const QByteArray& bfr) const
{
    quint16 res = 0;
    quint8 *ptr = (quint8*)&res;
    if (bfr.size() > 8)
    {
        for(int i=7; i<9; ++i)
        {
            *ptr = bfr.at(i);
            ++ptr;
        }
    }
    return res;
}

template <class ConnectionImpl, class DataType>
void Protocol10007<ConnectionImpl, DataType>::connected() const
{

}
template <class ConnectionImpl, class DataType>
void Protocol10007<ConnectionImpl, DataType>::disconnected() const
{

}

#endif // PROTOCOL10007_H
