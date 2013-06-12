#ifndef DEVICEIMITATOR_H
#define DEVICEIMITATOR_H
#include <QByteArray>
class DeviceImitator
{
public:
    DeviceImitator();
    virtual QByteArray* GetAnsver(QByteArray*) = 0;
};

#endif // DEVICEIMITATOR_H
