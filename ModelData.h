#ifndef _MODELDATA_H_
#define _MODELDATA_H_

#include "IModel.h"
#include "IAttribute.h"
#include "ModelAttribute.h"

class ModelString : public IModel
{
public:
    std::string str;
    //std::stringstream strStream;
public:
    ModelString(){}
    ~ModelString(){}
};

class ModelData : public IModel
{
public:
    std::string name; //имя объекта
    std::vector<IAttribute*> iattribute;
    std::vector<ModelAttribute*> mattribute;
public:
    ModelData(){}
    ~ModelData(){}
};

#endif