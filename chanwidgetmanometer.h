#ifndef CHANWIDGETMANOMETER_H
#define CHANWIDGETMANOMETER_H
#include <QColor>
#include "chanwidget.h"
class chanwidgetManometer: public ChanWidget
{
     Q_OBJECT
     Q_PROPERTY( bool checked READ isChecked 	WRITE setChecked)
     Q_PROPERTY( QColor color READ color 	WRITE setColor)


public:

     chanwidgetManometer(QWidget *parent = 0);
     virtual ~chanwidgetManometer() {}
     void paintEvent(QPaintEvent * event);

     bool isChecked () ;

     QColor color() const;
     void setColor(QColor);
     void showVal(float);
     void show();
     QSize sizeHint() const;
public slots:

     void setChecked(bool);
signals:

     void checkChanged(bool val);

protected:
     void initCoordinateSystem(QPainter & painter);
     void paintBackground(QPainter & painter);

protected:

     bool m_checked;
     QColor m_color;

};

#endif // CHANWIDGETMANOMETER_H
