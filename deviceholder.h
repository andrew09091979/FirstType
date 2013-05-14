#ifndef DEVICEHOLDER_H
#define DEVICEHOLDER_H

#include <QObject>
#include <QMdiSubWindow>
#include <QPointer>
#include <QDebug>
#include <memory>

#include "devwnd.h"
#include "deviceCallback.h"
#include "syncronizer.h"
#include "syncronizeable.h"
#include "chanwidgetcreator.h"
#include "chanwidget.h"
#include "chanwidgetlcd.h"
#include "chanwidgetled.h"
#include "protocol.h"
template <
    template <
            template <class, class> class Proto,
                                    class Conn,
                                    class Type
               > class Device,
    template <class, class> class Prtcl,
    class ConnectionImpl,
    class Type
>
class DeviceHolder : public Syncronizeable, public DeviceCallback<Type>
{
public:
    DeviceHolder();
    QMdiSubWindow* operator()(){return devWnd_;}
    void show(){devWnd_->show();}
    void renewScreen(typename Protocol<Type>::ValuesRetType);
    ~DeviceHolder();
    virtual void tick();

private:
    std::auto_ptr< Device<Prtcl, ConnectionImpl, Type> >  dev_;
    QPointer<DevWnd> devWnd_;
    QPointer<Syncronizer> syncronizer_;
    DeviceHolder& operator = (const DeviceHolder&);
};

template <
    template <
            template <class, class> class Proto,
                                    class Conn,
                                    class Type
               > class Device,
    template <class, class> class Prtcl,
    class ConnectionImpl,
    class Type
>
DeviceHolder<Device, Prtcl, ConnectionImpl, Type>::DeviceHolder()
{
  devWnd_ = new DevWnd(new ChanWidgetCreator<ChanWidgetLCD>);
//devWnd_ = new DevWnd(new ChanWidgetCreator<ChanWidgetLED>);
    syncronizer_ = new Syncronizer(this);
    dev_.reset(new Device<Prtcl, ConnectionImpl, Type>(this));
}

template <
    template <
            template <class, class> class Proto,
                                    class Conn,
                                    class Type
               > class Device,
    template <class, class> class Prtcl,
    class ConnectionImpl,
    class Type
>
void DeviceHolder<Device, Prtcl, ConnectionImpl, Type>::tick()
{
    dev_->actualValues();
}

template <
    template <
            template <class, class> class Proto,
                                    class Conn,
                                    class Type
               > class Device,
    template <class, class> class Prtcl,
    class ConnectionImpl,
    class Type
>
DeviceHolder<Device, Prtcl, ConnectionImpl, Type>::~DeviceHolder()
{
}

template <
    template <
            template <class, class> class Proto,
                                    class Conn,
                                    class Type
               > class Device,
    template <class, class> class Prtcl,
    class ConnectionImpl,
    class Type
>
void DeviceHolder<Device, Prtcl, ConnectionImpl, Type>::renewScreen(typename Protocol<Type>::ValuesRetType values)
{
    //qDebug()<< "DeviceHolder::renewScreen";
    *devWnd_ << values;
}

#endif // DEVICEHOLDER_H
