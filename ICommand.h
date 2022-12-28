#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

#include "config.h"
#include "ModelData.h"


//namespace SpaceICommand
class ICommand
{
public:
	virtual void UpdateCommand(std::vector<ModelData*>* vectorData,ModelCommand *mCommand){}
};

#endif