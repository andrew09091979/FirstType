#ifndef SYNCRONIZEABLE_H
#define SYNCRONIZEABLE_H

class Syncronizeable
{
public:
    Syncronizeable(){}
    virtual ~Syncronizeable(){}
    virtual void tick() = 0;
};

#endif // SYNCRONIZEABLE_H
