#include "connectionImplRandomStub.h"

connectionImplRandomStub::connectionImplRandomStub()
{
}
connectionImplRandomStub::connectionImplRandomStub(const std::string &ip, unsigned short port, const ConnectionCallback* c)
    : ConnectionImpl(ip, port, c)
{

}

connectionImplRandomStub::RetType connectionImplRandomStub::connectionImplRandomStub::getAnsver(int length)
{
    qint64 lenCopied = 0;
    int size = 0;
    BufferType * bfr = nullptr;
    std::auto_ptr< BufferType > res(bfr);
    ConnectionImpl::bfr_.clear();
    for(char i =0; i<16;++i)
        InputBfr_.push_back(i);
    if (isConnected)
    {
        size = InputBfr_.size();
        QMutexLocker ml(&mtxInputBuffer_);
        bfr = new BufferType;
        res.reset(bfr);

        for(int i = 0; (i<length)&&(i<size);++i)
        {

           res->push_back(InputBfr_.at(i));
           qDebug()<<InputBfr_.at(i)<<' ';
           ++lenCopied;
        }

        InputBfr_.remove(0, lenCopied);
        clb_->ansverReceived(length);
    }
    else
    {
    }
    return res;
}
int connectionImplRandomStub::sendCommand(const QByteArray &)
{
    return 0;
}
int connectionImplRandomStub::connect_()
{
    for(char i =0; i<16;++i)
        InputBfr_.push_back(i);
    return 0;
}
