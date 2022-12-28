#pragma once
#ifndef CONFIG_H
#define CONFIG_H


#define NET_SERVER 0
#define NET_CLIENT 1
#define PLATFORM_WINDOWS 0
#define PLATFORM_UNIX 1

#define IP_ADDR "127.0.0.1"
//#define IP_ADDR "192.168.56.1"
#define PORT 1234

#define DEBUG 0 

#define TARGET_PLATFORM PLATFORM_UNIX
#if TARGET_PLATFORM == PLATFORM_WINDOWS
    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <conio.h>
    #include <windows.h> //for sleep
    //#include <winsock2.h> 
    #include <ws2tcpip.h>
    #include <pthread.h>
    #include <vector>
    #include <string>
    #include <sstream>
    #include <map>
    #include <cstring>
    #include <algorithm> //for replace
    #pragma comment(lib,"wsock32.lib")
#elif TARGET_PLATFORM == PLATFORM_UNIX
    #include <iostream>
    #include <cstring>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sstream>
    #include <vector>
    #include <map>
    #include <pthread.h>
    #include <unistd.h> //for usleep
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
#endif
#endif

//if(strcmp(data, " ") != 0)
//strcpy(data, data);