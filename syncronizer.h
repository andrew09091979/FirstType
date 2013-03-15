#ifndef SYNCRONIZER_H
#define SYNCRONIZER_H

#include <QObject>
#include <QPointer>
#include <QTimer>
#include "syncronizeable.h"
class Syncronizer : public QObject
{
    Q_OBJECT
public:
    explicit Syncronizer(Syncronizeable *sync, QObject *parent = 0);
signals:
    
public slots:
    void tick();
private:
    QPointer<QTimer> timer_;
    Syncronizeable *s_;
};

#endif // SYNCRONIZER_H
