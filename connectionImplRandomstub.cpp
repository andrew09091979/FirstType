#include "connectionImplRandomStub.h"

connectionImplRandomStub::connectionImplRandomStub()
{
    timer_.setInterval(500);
    timer_.setSingleShot(true);
    InputBfr_.reserve(117);
    char * chPtr;
    for(float i=0; i<16; ++i)
    {
        chPtr = (char*)&i;
        for(int cnt=0; cnt<4; ++cnt)
        {
            InputBfr_.push_back(*chPtr);
            ++chPtr;
        }
    }
}
connectionImplRandomStub::connectionImplRandomStub(const std::string &ip, unsigned short port, const ConnectionCallback *c)
   : ConnectionImpl(ip, port, c)
{
    timer_.setInterval(500);
    timer_.setSingleShot(true);
    InputBfr_.reserve(117);
    char * chPtr;
    for(float i=0; i<16; ++i)
    {
        chPtr = (char*)&i;
        for(int cnt=0; cnt<4; ++cnt)
        {
            InputBfr_.push_back(*chPtr);
            ++chPtr;
        }
    }
}
<<<<<<< HEAD
connectionImplRandomStub::RetType connectionImplRandomStub::getAnsver(int length)
=======
connectionImplRandomStub::connectionImplRandomStub(const std::string &ip, unsigned short port, const ConnectionCallback* c)
    : ConnectionImpl(ip, port, c)
{

}

connectionImplRandomStub::RetType connectionImplRandomStub::connectionImplRandomStub::getAnsver(int length)
>>>>>>> 90b446bd21f7645c423249c07ee2c9e85d114fa5
{
    qint64 lenCopied = 0;
    int size = 0;
    BufferType * bfr = nullptr;
    std::auto_ptr< BufferType > res(bfr);
    ConnectionImpl::bfr_.clear();
<<<<<<< HEAD
    if (!isConnected)
        connect_();
=======
    for(char i =0; i<16;++i)
        InputBfr_.push_back(i);
>>>>>>> 90b446bd21f7645c423249c07ee2c9e85d114fa5
    if (isConnected)
    {
        size = InputBfr_.size();
        QMutexLocker ml(&mtxInputBuffer_);
        bfr = new BufferType;
        res.reset(bfr);
        res->push_back('>');
        res->push_back('0'); res->push_back('1');
        res->push_back('\x20'); res->push_back('\x08');res->push_back('\x00'); res->push_back('\x00');

        res->push_back('\x68');
//        res->append(InputBfr_);
qDebug() <<" connectionImplRandomStub::getAnsver InputBfr_ = "<< res->toHex() << " size = " << size;
        for(int i = 0; (i<length)&&(i<size);++i)
        {

           res->push_back(InputBfr_.at(i));
           qDebug()<<InputBfr_.at(i)<<' ';
           ++lenCopied;
        }

<<<<<<< HEAD
       // InputBfr_.remove(0, lenCopied);
=======
        InputBfr_.remove(0, lenCopied);
        clb_->ansverReceived(length);
>>>>>>> 90b446bd21f7645c423249c07ee2c9e85d114fa5
    }
    else
    {
    }
    return res;
}
void connectionImplRandomStub::slotReadyRead()
{
    clb_->ansverReceived(117);

}

int connectionImplRandomStub::sendCommand(const QByteArray & data)
{
    quint64 res;
    if (!isConnected)
    {
        res = -1;
        connect_();
    }
    else
    {
        res = data.size();
        timer_.singleShot(500,this, SLOT(slotReadyRead()));
    }
    return res;
}
int connectionImplRandomStub::connect_()
{
<<<<<<< HEAD
    isConnected = true;
=======
    for(char i =0; i<16;++i)
        InputBfr_.push_back(i);
>>>>>>> 90b446bd21f7645c423249c07ee2c9e85d114fa5
    return 0;
}
