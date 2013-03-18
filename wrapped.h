#ifndef WRAPPED_H
#define WRAPPED_H
#include <QMutex>
class NullType
{
public:
    NullType(NullType*){}
    NullType(){}
};

template <class SyncObj, class LockerObj>
class ThreadSafetyStrategy
{
public:
    typedef SyncObj SyncronizationObjectType;
    typedef LockerObj LockerType;
    ThreadSafetyStrategy(SyncronizationObjectType * mtx_):Locker(mtx_){}
private:
   LockerType Locker;
};

template <class Type, class ThreadSafety = ThreadSafetyStrategy<NullType, NullType>, class Ctor_type1 = int, class Ctor_type2 = int>
class Wrapped
{
public:
    Wrapped():var(0){}
    Wrapped(Type v):var(v){}
    Wrapped(Ctor_type1 arg1, Ctor_type2 arg2):var(arg1, arg2){}
    operator Type(){/*qDebug()<<"Wrapped::operator Type()";*/ ThreadSafety ml(&mtx_); return var;}
    const Type operator =(const Type t){/*qDebug()<<"Wrapped::operator =()";*/ThreadSafety ml(&mtx_); var = t; return var;}
protected:
    typename ThreadSafety::SyncronizationObjectType mtx_;

    Type var;
};

template<class Type, class ThreadSafety = ThreadSafetyStrategy<QMutex, QMutexLocker>, class Ctor_type1 = int, class Ctor_type2 = int>
class WrappedContainer : public Wrapped<Type, ThreadSafety, Ctor_type1, Ctor_type2>
{
    typedef typename ThreadSafety::LockerType Locker;
public:
    WrappedContainer():Wrapped(){}
    WrappedContainer(Type v):Wrapped(v){}
    WrappedContainer(Ctor_type1 arg1, Ctor_type2 arg2):Wrapped(arg1, arg2){}
    void push_back(const Type & v){ThreadSafety ml(&mtx_); var.push_back(v);}
    void push_back (const char * str){ThreadSafety ml(&mtx_); var.push_back(str);}
    void push_back (char ch){ThreadSafety ml(&mtx_); var.push_back(ch);}
    char at(int i) const {ThreadSafety ml(&mtx_); return var.at(i);}
    void clear(){ThreadSafety ml(&mtx_); var.clear();}
};

#endif // WRAPPED_H
