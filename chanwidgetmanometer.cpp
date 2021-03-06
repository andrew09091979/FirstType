#include "chanwidgetmanometer.h"

#include "chanwidgetled.h"
#include <QtGui>
#include "chanwidgetled.h"
chanwidgetManometer::chanwidgetManometer(QWidget * parent):ChanWidget(parent)
{
  m_checked = true;
  m_color = Qt::red;
  resize(330,330);
}


bool chanwidgetManometer::isChecked ()
{
  return m_checked;
}


void chanwidgetManometer::setChecked(bool i)
{
  m_checked = i;
  updateWithBackground();
  checkChanged( m_checked );
}


QColor chanwidgetManometer::color() const
{
  return m_color;
}


void chanwidgetManometer::setColor(QColor i)
{
  m_color = i;
  updateWithBackground();
}
void chanwidgetManometer::showVal(float fVal)
{
   setChecked(fVal>50);
}

void chanwidgetManometer::paintEvent(QPaintEvent * /* event*/ )
{
  QPainter painter(this);
  initCoordinateSystem(painter);
  int h,s,v,a;
  QColor c,back = color();
  c=back;

  if (!m_checked || !isEnabled())
  {
    back.getHsv(&h,&s,&v,&a);
    s*=0.20;
    back.setHsv(h,s,v,a);
  }
  painter.setBrush(back);

  QPen pen;
  c.getHsv(&h,&s,&v,&a);
  s*=0.5;
  c.setHsv(h,s,v,a);

  pen.setColor(c);
  pen.setWidthF(3.0);

  painter.drawEllipse(-149,-149,299,299);
  painter.end();

  drawBackground(); // to maluje na tym co dotychczas to co jest w bitmapce
}

void chanwidgetManometer::paintBackground(QPainter & painter)
{
  initCoordinateSystem(painter);
  painter.setPen(Qt::NoPen);
  QRadialGradient shine(QPointF(-40.0,-40.0),120.0,QPointF(-40,-40));
  QColor white1(255,255,255,200);
  QColor white0(255,255,255,0);

  shine.setColorAt(0.0,white1);
  shine.setColorAt(1.0,white0);

  painter.setBrush(shine);
  painter.drawEllipse(-147,-147,297,297);

}
void chanwidgetManometer::show()
{
    QWidget::show();
}

QSize chanwidgetManometer::sizeHint() const
{
    return QWidget::sizeHint();
}
void chanwidgetManometer::initCoordinateSystem(QPainter & painter)
{
  int side = qMin(width(), height());
  painter.setRenderHint(QPainter::Antialiasing);
  painter.translate(width() / 2, height() / 2);
  painter.scale(side / 330.0, side / 330.0);
}

