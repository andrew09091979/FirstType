#include "devwnd.h"

DevWnd::DevWnd( WidgetCreator* c, DeviceWndCallback *dwc, QWidget *parent) :
    QMdiSubWindow(parent), chanWidgetCreator_(c),devWndClb_(dwc)
{
    this->setBaseSize(100,100);
    gridLayout_ = new QGridLayout;
    QWidget *wgtDev = new QWidget;
    QWidgetItem *wgtItemP;
    QWidget *chanIndicator;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
        {
             chanIndicator = chanWidgetCreator_->Create();
             wgtItemP = new QWidgetItem(chanIndicator);
             gridLayout_->addItem(wgtItemP,i,j);
        }
    wgtDev->setLayout(gridLayout_);
    this->setWidget(wgtDev);

}

const QBuffer &DevWnd::out()
{
    return ValBfr_;
}

DevWnd::~DevWnd()
{
   // qDebug() << "DevWnd dtor//////////////////////////////////";
}
void DevWnd::closeEvent(QCloseEvent *event)
{
    this->devWndClb_->closed();//оповещаем DeviceHolder о том, что пользователь закрыл окно
    qDebug() << "closeEvent///////////////////////////////////";
}
DevWnd& DevWnd::operator <<(std::auto_ptr< std::vector<float> > bfr)
{
    QWidget *wgt;
    float fVal;
    //qDebug() << "DevWnd operator << ";
    if ((gridLayout_)&& bfr.get() != nullptr)
    {
        for (int i = 0; i < gridLayout_->count(); ++i)
        {
            if (i<bfr->size())
                fVal = bfr->at(i);

            wgt = gridLayout_->itemAt(i)->widget();
            ChanWidget* lcd = dynamic_cast<ChanWidget*>(wgt);
           // qDebug()<<fVal;
            if (lcd != 0)
               lcd->showVal(fVal);
        }
    }
    return *this;
}
