#ifndef CHANWIDGETLED_H
#define CHANWIDGETLED_H

#include <QColor>
#include "chanwidget.h"

class ChanWidgetLED : public ChanWidget
{
     Q_OBJECT
     Q_PROPERTY( bool checked READ isChecked 	WRITE setChecked)
     Q_PROPERTY( QColor color READ color 	WRITE setColor)


public:

     ChanWidgetLED(QWidget *parent = 0);
     virtual ~ChanWidgetLED() {}
     void paintEvent(QPaintEvent * event);

     bool isChecked () const ;


     QColor color() const;
     void setColor(QColor);
     void showVal(float);
     void show();
     QSize sizeHint() const;
public slots:

     void setChecked(bool) ;

signals:

     void checkChanged(bool val);

protected:
     void initCoordinateSystem(QPainter & painter);
     void paintBackground(QPainter & painter);

protected:

     bool m_checked;
     QColor m_color;

};

#endif // CHANWIDGETLED_H
