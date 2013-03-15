#ifndef CHANWIDGET_H
#define CHANWIDGET_H
#include <QPainter>
#include <memory>
#include "QLCDNumber"
#include "QDebug"
class ChanWidget : public QFrame
{
public:
    explicit ChanWidget(QWidget * parent = 0);

    ~ChanWidget();
    virtual void showVal(float) = 0;
    virtual void show() = 0;

    void drawBackground ();
    void updateWithBackground ();
    bool doRepaintBackground();

protected:
   void repaintBackground();
   virtual void paintBackground(QPainter & painer) = 0;

protected:
    std::auto_ptr<QPixmap> m_pixmap;
    bool m_modified;
};

#endif // CHANWIDGET_H
