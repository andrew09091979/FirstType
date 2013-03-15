#include "chanwidget.h"

ChanWidget::ChanWidget(QWidget *parent)
    : QFrame(parent)
{
    m_pixmap.reset(new QPixmap(size()));
    m_modified = false;
}

ChanWidget::~ChanWidget()
{
}

void ChanWidget::drawBackground()
{
  if (m_pixmap->size() != size() || m_modified )
    {
        m_pixmap.reset(new QPixmap(size()));
        m_modified=true;
        repaintBackground();
        m_modified=false;
    }
    QPainter painter(this);
    painter.drawPixmap(0,0,*m_pixmap);
}

void ChanWidget::updateWithBackground()
{
  m_modified=true;
  update();
}

bool ChanWidget::doRepaintBackground()
{
  return m_modified;
}

void ChanWidget::repaintBackground()
{
  m_pixmap->fill(QColor(0,0,0,0));
  QPainter painter(m_pixmap.get());
  paintBackground(painter);
}
