#ifndef CHANWIDGETCREATOR_H
#define CHANWIDGETCREATOR_H
#include <QWidget>
class WidgetCreator
{
public:
    WidgetCreator(){}
    virtual ~WidgetCreator(){}
    virtual QWidget* Create(QWidget* p = 0) = 0;
};

template <class W>
class ChanWidgetCreator : public WidgetCreator
{
public:
    typedef W WidgetType;
    ChanWidgetCreator();
    virtual ~ChanWidgetCreator(){}
    QWidget* Create(QWidget* parent = 0){return new W(parent);}
};

template<class W>
ChanWidgetCreator<W>::ChanWidgetCreator()
{
}

#endif // CHANWIDGETCREATOR_H
