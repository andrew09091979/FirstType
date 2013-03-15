#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <vector>
#include "connectionImplBoost.h"
#include "protocolCallback.h"
template <class DataType>
class Protocol
{
public:
    enum Command{GetValues} ;
    typedef ConnectionImpl ConnectionImplType;
    typedef typename ConnectionImpl::RetType ConnImplRetType;
    typedef typename std::vector<DataType> ValuesBfrType;
    typedef typename std::auto_ptr< ValuesBfrType > ValuesRetType;

    Protocol(const std::string &, unsigned short){}
    Protocol(const ProtocolCallback<DataType> * clb): clb_(clb){}
    virtual ~Protocol(){}
    virtual int askForActualValues() = 0;
    virtual int executeCommand(Command) = 0;
    virtual int sendCommand(QByteArray&) = 0;
protected:
    const ProtocolCallback<DataType> * clb_;
};
#endif // PROTOCOL_H
