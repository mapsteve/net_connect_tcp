// tcp_server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

UINT serverthread(LPVOID pParam)
{
	SOCKET server;
	WSADATA wsaData;
	sockaddr_in local;
	int wsaret = WSAStartup(0x101,&wsaData);

	printf("Starting up Tcp server\r\n");

	if(wsaret != 0)
		return 0;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons((u_short)3490);

	server = socket(AF_INET,SOCK_STREAM,0);

	if(server == INVALID_SOCKET)
		return 0;

	if(bind(server,(sockaddr*)&local,sizeof(local)) !=0)
		return 0;

	if(listen(server,10) != 0)
		return 0;

	SOCKET client;
	sockaddr_in from;
	int fromlen = sizeof(from);

	while(true)
	{
		char temp[512];
		printf("1\n");
		client = accept(server,(struct sockaddr *)&from,&fromlen);
		printf("2\n");
		sprintf(temp,"You IP is %s\r\n",inet_ntoa(from.sin_addr));
		while(true)
		{
			int n = 0;
			char buffer[512] = {0};
			n = recv(client,buffer,512,0);
			if(n == SOCKET_ERROR)
				break;
			printf("%s \n", buffer);

			send(client,temp,strlen(temp),0);
		}
		printf("Connection from %s\r\n",inet_ntoa(from.sin_addr));
		closesocket(client);
		
	}
	printf("5\n");
	closesocket(server);
	WSACleanup();
}

int _tmain(int argc, _TCHAR* argv[])
{
	int nRetcode= 0;

	printf("Press esc to terminate program\r\n");

	AfxBeginThread(serverthread,0);

	while(1);

	return 0;
}