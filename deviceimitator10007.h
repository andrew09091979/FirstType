#ifndef DEVICEIMITATOR10007_H
#define DEVICEIMITATOR10007_H
#include "deviceImitator.h"
class DeviceImitator10007 : public DeviceImitator
{
public:
    DeviceImitator10007();
    QByteArray* GetAnsver(QByteArray *);
};

#endif // DEVICEIMITATOR10007_H
