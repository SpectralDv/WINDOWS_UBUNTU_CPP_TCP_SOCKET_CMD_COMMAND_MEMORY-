#ifndef _CONTROLLERINPUT_H_
#define _CONTROLLERINPUT_H_

#include "IController.h"
#include "IObserver.h"
#include "ModelData.h"

class ControllerInput : IController, IObservable
{
private:
	std::vector<IObserver*> observers;
	std::string str;
	std::stringstream strStream;
	ModelString mString;
public:
    ControllerInput(){this->name="ControllerInput";}
    ~ControllerInput(){}
    void AddObserver(IObserver* o)
	{
		if(DEBUG==1){printf("ControllerInput add: %s\n",((IController*)o)->name.c_str());}
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
		for (auto o : this->observers)
		{
			((IController*)o)->UpdateController(mString);
		}
	}
	int Input()
    {
		int i = 0;
		getline(std::cin,mString.str);
		while(mString.str[i])
		{
			if(mString.str[i]==' '){mString.str[i]='/';}
			i++;
		}
		if(!(mString.str.empty())){mString.str.push_back('/');}
		this->Notify(mString);
		return 0;
    }
};
#endif