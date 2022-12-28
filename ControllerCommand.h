#ifndef _CONTROLLERCOMMAND_H_
#define _CONTROLLERCOMMAND_H_

#include "ICommand.h"
#include "ModelCommand.h"


class CommandAddObject  : public ICommand
{
public:
    CommandAddObject(){}
	~CommandAddObject(){}
	void UpdateCommand(std::vector<ModelData*>* vectorData,ModelCommand *mCommand) override
    {
		ModelData* md = new ModelData();
        md->name = mCommand->nameObject;
		vectorData->push_back(md);
		printf("  Addobject %s\n", md->name.c_str());
    }
};

class CommandAddAttribute : public ICommand
{
public:
    CommandAddAttribute(){}
	~CommandAddAttribute(){}
	void UpdateCommand(std::vector<ModelData*>* vectorData,ModelCommand *mCommand) override
    {
		for (int i = 0; i < (*vectorData).size(); i++)
		{
			if((*vectorData)[i]->name==mCommand->nameObject)
			{
				if(mCommand->typeAttribute=="char")
				{
					if(mCommand->nameAttribute!=" ")
					{
						ModelAttribute* ma = new ModelAttribute();
                        ma->type=mCommand->typeAttribute;
                        ma->name=mCommand->nameAttribute;
                        ma->text=" ";
                        //((ModelChar*)ma)->text=" ";
						(*vectorData)[i]->mattribute.push_back(ma);
                        printf("  AddAttribute %s", mCommand->nameAttribute.c_str());
                        printf(",  size: %ld\n", (*vectorData)[i]->mattribute.size());
						break;
					}
				}
                else if(mCommand->typeAttribute=="int")
				{
					if (mCommand->nameAttribute!=" ")
					{
						ModelAttribute* ma = new ModelAttribute();
                        ma->type=mCommand->typeAttribute;
                        ma->name=mCommand->nameAttribute;
                        ma->value = 0;
						//((ModelInt*)ma)->value = 0;
						(*vectorData)[i]->mattribute.push_back(ma);
                        printf("  AddAttribute %s", mCommand->nameAttribute.c_str());
                        printf(",  size: %ld\n", (*vectorData)[i]->mattribute.size());
						break;
					}
				}
                else if(mCommand->typeAttribute=="bool")
				{
                    if (mCommand->nameAttribute!=" ")
                    {
                        ModelAttribute* ma = new ModelAttribute();
                        ma->type=mCommand->typeAttribute;
                        ma->name=mCommand->nameAttribute;
                        ma->event = false;
                        //((ModelBool*)ma)->event = false;
                        (*vectorData)[i]->mattribute.push_back(ma);
                        printf("  AddAttribute %s", mCommand->nameAttribute.c_str());
                        printf(",  size: %ld\n", (*vectorData)[i]->mattribute.size());
                        break;
                    }
				}
                break;
			}
		}
	}
};

class CommandAddValue : public ICommand
{
public:
	CommandAddValue(){}
    ~CommandAddValue() {}
	void UpdateCommand(std::vector<ModelData*>* vectorData,ModelCommand *mCommand) override
	{
		int indexData = 0;

		for (int i = 0; i < (*vectorData).size(); i++)
		{
			if ((*vectorData)[i]->name==mCommand->nameObject)
			{
				indexData = i;
				break;
			}
		}
		for (int j = 0; j < (*vectorData)[indexData]->mattribute.size(); j++)
		{
			if ((*vectorData)[indexData]->mattribute[j]->name==mCommand->nameAttribute)
			{
				if ((*vectorData)[indexData]->mattribute[j]->type=="char")
				{
					//((ModelChar*)(*vectorData)[indexData]->mattribute[j])->text, (*vectorInput)[3].data);
                    ((*vectorData)[indexData]->mattribute[j])->text = mCommand->valueAttribute;
				}
				if ((*vectorData)[indexData]->mattribute[j]->type=="int")
				{
					//((ModelInt*)(*vectorData)[indexData]->mattribute[j])->value = atoi((*vectorInput)[3].data);
                    ((*vectorData)[indexData]->mattribute[j])->value = atoi(mCommand->valueAttribute.c_str());
				}
				if ((*vectorData)[indexData]->mattribute[j]->type=="bool")
				{
					if (mCommand->valueAttribute=="true")
					{
                        ((*vectorData)[indexData]->mattribute[j])->event = true;
						//((ModelBool*)(*vectorData)[indexData]->mattribute[j])->event = true;
					}
					if (mCommand->valueAttribute=="false")
					{
                        ((*vectorData)[indexData]->mattribute[j])->event = false;
						//((ModelBool*)(*vectorData)[indexData]->mattribute[j])->event = false;
					}
				}
				printf("  AddValue %s\n", mCommand->valueAttribute.c_str());
				break;
			}
		}
	}
};

class CommandDeleteAttribute : public ICommand
{
public:
	CommandDeleteAttribute() {}
	~CommandDeleteAttribute() {}
	void UpdateCommand(std::vector<ModelData*>* vectorData,ModelCommand *mCommand) override
	{
		int indexData = 0;

		for (int i = 0; i < (*vectorData).size(); i++)
		{
			if ((*vectorData)[i]->name==mCommand->nameObject)
			{
				indexData = i;
				break;
			}
		}
		for (int j = 0; j < (*vectorData)[indexData]->mattribute.size(); j++)
		{
			if (j == atoi(mCommand->indexAttribute.c_str()))
			{
				(*vectorData)[indexData]->mattribute.erase((*vectorData)[indexData]->mattribute.begin() + j);
				std::vector<ModelAttribute*>((*vectorData)[indexData]->mattribute).swap((*vectorData)[indexData]->mattribute);
                printf("  DeleteAttribute id: %d", j);
                printf(",  size: %ld\n", (*vectorData)[indexData]->mattribute.size());
				break;
			}
		}
	}
};

class CommandDeleteObject : public ICommand
{
public:
	CommandDeleteObject() {}
	~CommandDeleteObject() {}
	void UpdateCommand(std::vector<ModelData*>* vectorData,ModelCommand *mCommand) override
	{
		for (int i = 0; i < (*vectorData).size(); i++)
		{
			if ((*vectorData)[i]->name==mCommand->nameObject)
			{
				(*vectorData).erase((*vectorData).begin() + i);
				std::vector<ModelData*>(*vectorData).swap(*vectorData);
                printf("  DeleteObject %s\n",mCommand->nameObject.c_str());
				break;
			}
		}
	}
};

class ControllerCommand : public IController
{
public:
    std::map<std::string, ICommand*> mapCommand;
public:
    ControllerCommand()
    {
		this->name="ControllerCommand";
        this->mapCommand.emplace("addobject", new CommandAddObject());
        this->mapCommand.emplace("addattribute", new CommandAddAttribute());
        this->mapCommand.emplace("addvalue", new CommandAddValue());
        this->mapCommand.emplace("deleteattribute", new CommandDeleteAttribute());
        this->mapCommand.emplace("deleteobject", new CommandDeleteObject());
    }
	~ControllerCommand(){}
};

#endif