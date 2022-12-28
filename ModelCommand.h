#ifndef _MODELCOMMAND_H_
#define _MODELCOMMAND_H_

#include "IModel.h"
#include "IAttribute.h"


class ModelCommand : public IModel
{
public:
    std::string data;
    std::string nameCommand;
    std::string nameObject;
    std::string typeAttribute;
    std::string nameAttribute;
    std::string valueAttribute;
    //std::vector<IAttribute*> iattribute;
    std::string indexAttribute;
public:
    ModelCommand(){}
    ~ModelCommand(){}
};

#endif