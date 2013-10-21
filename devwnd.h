#ifndef DEVWND_H
#define DEVWND_H

#include <QMdiSubWindow>
#include <QBuffer>
#include <QGridLayout>
#include <QLCDNumber>
#include <QTimer>
#include <QPointer>
#include <QDebug>
#include <vector>
#include <memory>
#include "chanwidgetcreator.h"
#include "chanwidget.h"
#include "devWndCallback.h"
class DevWnd : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit DevWnd(WidgetCreator *c, DeviceWndCallback *dwc ,QWidget *parent = 0);
    ~DevWnd();
    const QBuffer& out();
    DevWnd& operator << (std::auto_ptr< std::vector<float> >);
    template<class T>
    void Func(){T t;}
protected:
    void closeEvent(QCloseEvent *event);
private:

    QBuffer ValBfr_;
    QGridLayout *gridLayout_;
    WidgetCreator *chanWidgetCreator_;
    DeviceWndCallback *devWndClb_;
signals:
    void closing();
};

#endif // DEVWND_H
