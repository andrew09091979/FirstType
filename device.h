#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <vector>
#include "protocol.h"
#include "protocol10007.h"
#include "deviceCallback.h"
template<
        template <class, class> class Prtcl,
                                class Connection,
                                class DataType
        >
class Device : public ProtocolCallback<DataType>
{
public:
    typedef typename Protocol<DataType>::ValuesRetType RetType;
    typedef Protocol<DataType> ProtocolType;
    typedef typename Protocol<DataType>::Command Command;

    Device(DeviceCallback<DataType> *);
    int actualValuesReceived(RetType) const;
    int actualValues();

private:
    std::auto_ptr<ProtocolType> protocol_;
    mutable DeviceCallback<DataType> *clb_;
};

template<
        template <class, class> class Prtcl,
                                class Connection,
                                class DataType
        >
Device<Prtcl, Connection, DataType>::Device(DeviceCallback<DataType>* clb)
    :clb_(clb)
{
    protocol_.reset(new Prtcl<Connection, DataType>(this));
}

template<
        template <class, class> class Prtcl,
                                class Connection,
                                class DataType
        >
int Device<Prtcl, Connection, DataType>::actualValues()
{
    return protocol_->executeCommand(Protocol<DataType>::GetValues);
    //return protocol_->askForActualValues();
}
template<
        template <class, class> class Prtcl,
                                class Connection,
                                class DataType
        >
int Device<Prtcl, Connection, DataType>::actualValuesReceived(RetType ret) const
{
    qDebug() << "Device::actualValuesReceived" ;
    if(ret.get() != nullptr)
        clb_->renewScreen(ret);
    return 1;
}

#endif // DEVICE_H
