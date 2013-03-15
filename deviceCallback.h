#ifndef DEVICECALLBACK_H
#define DEVICECALLBACK_H
#include "protocol.h"
template <class DataType>
class DeviceCallback
{
public:
    virtual void renewScreen(typename Protocol<DataType>::ValuesRetType ) = 0;
};

#endif // DEVICECALLBACK_H
