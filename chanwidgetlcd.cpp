#include "chanwidgetlcd.h"

ChanWidgetLCD::ChanWidgetLCD(QWidget *parent)
    : ChanWidget(parent), lcdNum(this)
{
}

ChanWidgetLCD::~ChanWidgetLCD()
{

}

void ChanWidgetLCD::showVal(float f)
{
    lcdNum.display(f);
}

void ChanWidgetLCD::show()
{
    lcdNum.show();
}

QSize ChanWidgetLCD::sizeHint() const
{
    return lcdNum.sizeHint();
}

void ChanWidgetLCD::paintBackground(QPainter & painer)
{
    lcdNum.update();
}
