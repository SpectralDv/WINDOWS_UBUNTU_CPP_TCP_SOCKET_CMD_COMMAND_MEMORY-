#pragma once
#ifndef _IOBSERVER_H
#define _IOBSERVER_H

#include "config.h"
#include "ModelData.h"


//namespace SpaceObserver
//{
    class IObserver
    {
    public:
        virtual void UpdateObserver(ModelString mString){}
    };

    class IObservable
    {
    public:
        virtual ~IObservable(){}
        virtual void AddObserver(IObserver* o){}
        virtual void RemoveObserver(IObserver* o){}
        virtual void Notify(ModelString mString){}
    };
//}
#endif