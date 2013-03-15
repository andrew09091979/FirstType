#ifndef PROTOCOLCALLBACK_H
#define PROTOCOLCALLBACK_H

template <class DataType>
class Protocol;

template <class DataType>
class ProtocolCallback
{
    typedef typename Protocol<DataType>::ValuesRetType RetType;
public:
    virtual int actualValuesReceived(RetType) const = 0;
};

#endif // PROTOCOLCALLBACK_H
