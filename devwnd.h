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

class DevWnd : public QMdiSubWindow
{
    Q_OBJECT
public:
    explicit DevWnd(WidgetCreator *c, QWidget *parent = 0);
    ~DevWnd();
    const QBuffer& out();
    DevWnd& operator << (std::auto_ptr< std::vector<float> >);
    template<class T>
    void Func(){T t;}
private:

    QBuffer ValBfr_;
    QGridLayout *gridLayout_;
    WidgetCreator *chanWidgetCreator_;
signals:
};

#endif // DEVWND_H
