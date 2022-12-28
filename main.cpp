

#include "ControllerSocket.h"
#include "ControllerData.h"
#include "ControllerInput.h"

//g++ -o main.exe main.cpp -lws2_32 -lpthread

class ViewMain
{
private:
    ControllerSocket* controllerSocket;
    ControllerData* controllerData;
    ControllerInput* controllerInput;
public:
    ViewMain(int type)
    {
        controllerSocket = new ControllerSocket(type);
        controllerData = new ControllerData();
        controllerInput = new ControllerInput();
        UpdateControllerSocket((IController*)controllerData);
        UpdateControllerInput((IController*)controllerData);
        UpdateControllerInput((IController*)controllerSocket);

        controllerSocket->InitSocket(IP_ADDR,PORT);
    }
    ~ViewMain(){delete controllerSocket;}
    void UpdateControllerSocket(IController* controller)
	{
		this->controllerSocket->AddObserver((IObserver*)controller);
	}
    void UpdateControllerInput(IController* controller)
	{
		this->controllerInput->AddObserver((IObserver*)controller);
	}
    void Update()
    {
        controllerSocket->UpdateSocket();
        
        while(true)
        {
            if(controllerInput->Input()==1){break;}
        }
    }
    void MainInfo()
    {
        printf("For create object, input: addobject nameobject \n");
        printf("For get all object, input: getlistobject \n");
        printf("For create attribute in object, input: addattribute nameobject char/int/bool nameattribute\n");
        printf("For get object's params, input: addvalue nameobject nameattribute text/value/true\n");
        printf("For get object's params, input: getobject nameobject \n");
        printf("For delete attribute, input: deleteattribute nameobject indexttribute\n");
        printf("For delete object, input: deleteobject nameobject\n");
        printf("For exit, input: exit \n");
    }
};

///*
int main()
{
    ViewMain *viewMain;

    char str;
    printf("s - server\nc - client\n");
    scanf("%c",&str);
    //std::cin>>str;

    //и клиент и сервер работает с одним сокетом
    if(str=='s')
    {
        viewMain = new ViewMain(NET_SERVER);
    }
    if(str=='c')
    {
        viewMain = new ViewMain(NET_CLIENT);
    }

    viewMain->MainInfo();
    viewMain->Update();
    delete viewMain;
    return 0;
}
//*/

