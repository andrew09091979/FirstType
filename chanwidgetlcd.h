#ifndef CHANWIDGETLCD_H
#define CHANWIDGETLCD_H

#include <QPainter>
#include <memory>
#include <QLCDNumber>
#include <QDebug>
#include "chanwidget.h"

class ChanWidgetLCD : public ChanWidget
{
    mutable QLCDNumber lcdNum;
public:
    explicit ChanWidgetLCD(QWidget * parent = 0);
    virtual ~ChanWidgetLCD();
    void showVal(float);
    void show();
    QSize sizeHint() const;
    void paintBackground(QPainter & painer);
};

#endif // CHANWIDGETLCD_H
