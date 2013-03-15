#include "syncronizer.h"

Syncronizer::Syncronizer(Syncronizeable *sync, QObject *parent) : s_(sync),
    QObject(parent)
{
    this->timer_ = new QTimer();
    connect(timer_, SIGNAL(timeout()), this, SLOT(tick()));
    this->timer_->start(1000);
}

void Syncronizer::tick()
{
    s_->tick();
}
