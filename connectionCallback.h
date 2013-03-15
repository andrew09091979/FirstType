#ifndef CONNECTIONCALLBACK_H
#define CONNECTIONCALLBACK_H
class ConnectionCallback
{
public:
    virtual void ansverReceived(qint64) const = 0 ;
    virtual void disconnected() const = 0;
    virtual void connected() const = 0;
};

#endif // CONNECTIONCALLBACK_H
