
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
//#include <winsock2.h>
#include <ws2tcpip.h>
#include <pthread.h>
#include <vector>
#include <string>
#include <sstream>

#include "pack_data.h"

int x=1;
int y=0;
char msg[200];
char packet_data[1024];
StructData recData;

BOOL event_F2=FALSE;
BOOL event_F3=FALSE;



void printSerial();

void chat(SOCKET s)
{
    //чтение сообщений без таймаута
    WSAEventSelect(s,0,FD_READ);

    do
    {
        if((GetKeyState(VK_F1) < 0) && (GetForegroundWindow() == GetConsoleWindow()))
        {
            printf("msg: ");
            //избавление от символов потока ввода до нажатия F1
            while(getch() != 0);

            scanf("\n%200[0-9a-zA-Z.,! ]",msg);
            send(s,msg,sizeof(msg),0);
        }

        if((GetKeyState(VK_F2) < 0)&&(GetForegroundWindow() == GetConsoleWindow())&&(event_F2==FALSE))
        {
            event_F2=TRUE;
            printf("sendData\n");
            while(getch() != 0);

            send(s,(const char*)&x,sizeof(x),0);
        }
        if(GetKeyState(VK_F2)==0){event_F2=FALSE;}

        if((GetKeyState(VK_F3) < 0)&&(GetForegroundWindow() == GetConsoleWindow())&&(event_F3==FALSE))
        {
            event_F3=TRUE;
            printf("sendStructData \n");
            while(getch() != 0);

            send(s,(const char*)&sendData,sizeof(sendData),0);
        }
        if(GetKeyState(VK_F3)==0){event_F3=FALSE;}

        int rb;
        rb = recv(s,packet_data,sizeof(packet_data),0);

        if(rb>0)
        {
            printf("msg: %s",packet_data);

            memcpy(&y,packet_data,rb);
            printf(" data: %d",y);

            memcpy(&recData,packet_data,rb);
            printf("  structData: %d\n",recData.y);
        }  
    }
    while (GetKeyState(VK_ESCAPE) >= 0);
}


int main()
{
    fillSendData();

    WSADATA ws;
    //версия сокета
    WSAStartup(MAKEWORD(2,2),&ws);

    SOCKET s;
    //создает дискриптор сокета
    s = socket(AF_INET,SOCK_STREAM,0);

    //настройки соединения
    SOCKADDR_IN sa;
    memset(&sa,0,sizeof(sa));
    sa.sin_family = AF_INET; //IP_W4
    sa.sin_port = htons(1234);

    char c;
    printf("s - server\nc - client\n");
    scanf("%c",&c);

    //при выборе клиента задает адрес подключения
    if(c == 'c')
    {
        printf("Client is active\n");
        printSerial();

        sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

        //подключение к серверу
        connect(s,(const SOCKADDR*)&sa,sizeof(sa));

        chat(s);
    }

    //при выборе сервера
    if(c == 's')
    {
        printf("Server is active\n");
        printSerial();

        //настройки соединения к серверу
        bind(s,(const SOCKADDR*)&sa,sizeof(sa));

        //прослушка сервером
        listen(s,100);

        //буфер для приема данных
        char buf[200];

        memset(buf,0,sizeof(buf));
        //настройки входящего подключения
        SOCKET client_socket;
        SOCKADDR_IN client_addr;
        int client_addr_size = sizeof(client_addr);


        //ожидание входящего подключения
        while(client_socket = accept(s,(SOCKADDR*)&client_addr,&client_addr_size))
        {
            printf("%s", inet_ntoa(client_addr.sin_addr));
	        printf(": %d\n", ntohs(client_addr.sin_port));

            printf("Connect Client success\n");
            //printf("%d.%d.%d.%d",(client_addr>>24)&0xff,(client_addr>>16)&0xff,(client_addr>>8)&0xff,(client_addr>>0)&0xff); 
            chat(client_socket);
        }
    }

    if(c != 's' && c != 'k')
    {
        printf("ERROR input, enter any char\n");
        getchar();
    }

    closesocket(s);

    getchar();
    return 0;
}

void printSerial()
{
    printf("Press F1 for send msg\n");
    printf("Press F2 for send data\n");
    printf("Press F3 for send struct data\n");
}

//*/