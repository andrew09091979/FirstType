#include "connectionImplRandomStub.h"

connectionImplRandomStub::connectionImplRandomStub()
{
}

connectionImplRandomStub::RetType connectionImplRandomStub::getAnsver(int length)
{
    qint64 lenCopied = 0;
    int size = 0;
    BufferType * bfr = nullptr;
    std::auto_ptr< BufferType > res(bfr);
    ConnectionImpl::bfr_.clear();

    if (isConnected)
    {
        size = InputBfr_.size();
        QMutexLocker ml(&mtxInputBuffer_);
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
int connectionImplRandomStub::sendCommand(const QByteArray &)
{
    return 0;
}
int connectionImplRandomStub::connect_()
{
    return 0;
}
