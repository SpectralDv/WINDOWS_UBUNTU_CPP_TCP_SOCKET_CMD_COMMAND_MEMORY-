#pragma once
#ifndef _CONTROLLERDATA_H_
#define _CONTROLLERDATA_H_

#include "config.h"
#include "IController.h"
#include "IObserver.h"
#include "ModelAttribute.h"
#include "ModelData.h"
#include "ModelCommand.h"
#include "ControllerCommand.h"


class ControllerData : IController, IObserver, IObservable
{
private:
    std::vector<IObserver*> observers;
public:
	ModelCommand mCommand;
	ControllerCommand* controllerCommand;
	std::vector<std::string> vectorInput;
	std::vector<ModelData*> vectorData;
public:
    ControllerData()
    {
        controllerCommand = new ControllerCommand();
        this->name="ControllerData";
    }
    ~ControllerData(){}
    void AddObserver(IObserver* o)
	{
		observers.push_back(o);
	}
    void RemoveObserver(IObserver* o)
	{
		std::vector<IObserver*>::iterator itErase = observers.begin();
		for (itErase; itErase != observers.end(); itErase++)
		{
			if (*itErase == o) { observers.erase(itErase); break; }
		}
	}
    void Notify(ModelString mString)
	{
		for (auto o : observers)
		{
			((IController*)o)->UpdateController(mString);
		}
	}
    void UpdateObserver(std::string data){}
    void UpdateController(ModelString mString)
	{
        this->mCommand.data=mString.str;
        this->ProcessingMessage();
        //this->Notify(data);
        //this->ProcessingCommand();
	}
    int ProcessingMessage()
    {
        int pos=0;

        if(this->mCommand.data.find("addobject")==0)
        {
            if(this->mCommand.data.size()<strlen("addobject")+2){return 1;}
            
            this->mCommand.nameCommand="addobject";
            this->mCommand.data.erase(0,strlen("addobject")+1);
            pos = this->mCommand.data.find("/");

            this->mCommand.nameObject = this->mCommand.data.erase(pos,this->mCommand.data.back());
            if(this->mCommand.nameObject.empty()){return 1;}
            
            auto it = this->controllerCommand->mapCommand.find(this->mCommand.nameCommand);
            if(it->first.c_str()==this->mCommand.nameCommand)
            {
                (it->second)->UpdateCommand(&vectorData, &mCommand);
                return 0;
            }
            
            return 1;
        }
        else if(this->mCommand.data.find("addattribute")==0)
        {
            //addattribute/nameObject/type/nameAttribute/
            if(this->mCommand.data.size()<strlen("addattribute")+2){return 1;}

            this->mCommand.nameCommand="addattribute";
            this->mCommand.data.erase(0,strlen("addattribute")+1);
            pos = this->mCommand.data.find("/"); //eee/char/text/
            this->mCommand.nameObject = this->mCommand.data.substr(0,pos);
            this->mCommand.data.erase(0,pos+1);
            pos = this->mCommand.data.find("/"); //char/text/
            this->mCommand.typeAttribute = this->mCommand.data.substr(0,pos);
            this->mCommand.data.erase(0,pos+1);
            pos = this->mCommand.data.find("/"); ///text/
            this->mCommand.nameAttribute = this->mCommand.data.substr(0,pos);
            this->mCommand.data.clear();

            auto it = this->controllerCommand->mapCommand.find(this->mCommand.nameCommand);
            if(it->first.c_str()==this->mCommand.nameCommand)
            {
                (it->second)->UpdateCommand(&vectorData, &mCommand);
                return 0;
            }

            return 1;
        }
        else if(this->mCommand.data.find("addvalue")==0)
        {
            //addvalue/nameObject/nameAttribute/value/
            if(this->mCommand.data.size()<strlen("addvalue")+2){return 1;}

            this->mCommand.nameCommand="addvalue";
            this->mCommand.data.erase(0,strlen("addvalue")+1);
            pos = this->mCommand.data.find("/"); 
            this->mCommand.nameObject = this->mCommand.data.substr(0,pos);
            this->mCommand.data.erase(0,pos+1);
            pos = this->mCommand.data.find("/"); 
            this->mCommand.nameAttribute = this->mCommand.data.substr(0,pos);
            this->mCommand.data.erase(0,pos+1);
            pos = this->mCommand.data.find("/"); 
            this->mCommand.valueAttribute = this->mCommand.data.substr(0,pos);
            this->mCommand.data.clear();

            auto it = this->controllerCommand->mapCommand.find(this->mCommand.nameCommand);
            if(it->first.c_str()==this->mCommand.nameCommand)
            {
                (it->second)->UpdateCommand(&vectorData, &mCommand);
                return 0;
            }
        }
        else if(this->mCommand.data.find("deleteattribute")==0)
        {   
            //deleteattribute/nameObject/indexAttribute
            if(this->mCommand.data.size()<strlen("deleteattribute")+2){return 1;}

            this->mCommand.nameCommand="deleteattribute";
            this->mCommand.data.erase(0,strlen("deleteattribute")+1);
            pos = this->mCommand.data.find("/"); 
            this->mCommand.nameObject = this->mCommand.data.substr(0,pos);
            this->mCommand.data.erase(0,pos+1);
            pos = this->mCommand.data.find("/"); 
            this->mCommand.indexAttribute = this->mCommand.data.substr(0,pos);
            this->mCommand.data.clear();

            auto it = this->controllerCommand->mapCommand.find(this->mCommand.nameCommand);
            if(it->first.c_str()==this->mCommand.nameCommand)
            {
                (it->second)->UpdateCommand(&vectorData, &mCommand);
                return 0;
            }
        }
        else if(this->mCommand.data.find("deleteobject")==0)
        {  
            //deleteobject/nameObject/
            if(this->mCommand.data.size()<strlen("deleteobject")+2){return 1;}

            this->mCommand.nameCommand="deleteobject";
            this->mCommand.data.erase(0,strlen("deleteobject")+1);
            pos = this->mCommand.data.find("/"); 
            this->mCommand.nameObject = this->mCommand.data.substr(0,pos);
            this->mCommand.data.clear();

            auto it = this->controllerCommand->mapCommand.find(this->mCommand.nameCommand);
            if(it->first.c_str()==this->mCommand.nameCommand)
            {
                (it->second)->UpdateCommand(&vectorData, &mCommand);
                return 0;
            }
        }
        else if(this->mCommand.data.find("getlistobject")==0)
        {
            //getlistobject/
            if(this->vectorData.size()==0){printf("List is empty\n");return 1;}
            GetListObject();
        }
        else if(this->mCommand.data.find("getobject")==0)
        {
            //getobject/nameObject
            if(this->mCommand.data.size()<strlen("getobject")+2){return 1;}
            GetObject();
        }

        return 0;
    }
    int ProcessingCommand()
	{
        return 0;
    }
    int GetListObject()
	{
		for (int i = 0; i < this->vectorData.size(); i++)
		{
			printf("  %s\n", vectorData[i]->name.c_str());
		}
		return 0;
	}
    int GetObject()
	{
        this->mCommand.data.erase(0,10);
        int pos = this->mCommand.data.find("/");
        this->mCommand.nameObject = this->mCommand.data.erase(pos,this->mCommand.data.back());

        for (int j = 0; j < this->vectorData.size(); j++)
        {
            if(this->vectorData[j]->name==mCommand.nameObject)
            {
                PrintParams(j);
                break;
            }
        }
		return 0;
	}
    int PrintParams(int indexData)
	{
		printf("  Object   Attribute    Name     Type     Value\n");
		for (int i = 0; i < this->vectorData[indexData]->mattribute.size(); i++)
		{
			printf("  %s", this->vectorData[indexData]->name.c_str());
			printf("          %d", i);
			printf("        %s", (this->vectorData[indexData]->mattribute[i]->name.c_str()));
			printf("     %s", (this->vectorData[indexData]->mattribute[i]->type.c_str()));
			if (this->vectorData[indexData]->mattribute[i]->type=="char")
			{
				//printf("     %s\n", ((ModelChar*)this->vectorData[indexData]->mattribute[i])->text.c_str());
                printf("     %s\n", (this->vectorData[indexData]->mattribute[i])->text.c_str());
			}
			if (this->vectorData[indexData]->mattribute[i]->type=="int")
			{
				//printf("     %d\n", ((ModelInt*)this->vectorData[indexData]->mattribute[i])->value);
                printf("     %d\n", (this->vectorData[indexData]->mattribute[i])->value);
			}
			if (this->vectorData[indexData]->mattribute[i]->type=="bool")
			{
				//printf("     %d\n", ((ModelBool*)this->vectorData[indexData]->mattribute[i])->event);
                printf("     %d\n", (this->vectorData[indexData]->mattribute[i])->event);
			}
		}
		printf("\n");
		return 0;
	}
};
#endif