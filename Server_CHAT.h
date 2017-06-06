#pragma once
#define PORT_CHAT 9090

class Server_CHAT
{
private:
	int clntAdrSz;

	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
public:
	Server_CHAT();
	~Server_CHAT();

	void Setup();
	void Update();
	void Destory();
};

