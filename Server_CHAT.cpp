#include "stdafx.h"
#include "Server_CHAT.h"

// >> : 구현이 완료되었습니다.
HANDLE hMutex_CHAT;
CRITICAL_SECTION CS_CHAT;
int clntCnt = 0;
HANDLE hThread;
SOCKET clntSocks[MAX_CLNT];

unsigned int _stdcall HandleClnt(void * arg);
void SendMsg(char* msg, int Len);

Server_CHAT::Server_CHAT()
{
}


Server_CHAT::~Server_CHAT()
{
}

void Server_CHAT::Setup()
{
	InitializeCriticalSection(&CS_CHAT);
	EnterCriticalSection(&CS_CHAT);
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		cout << "Server_CHAT WSAStartup() Error!" << endl;

	hMutex_CHAT = CreateMutex(NULL, FALSE, NULL);		// << : Create Mutex
	hServSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = PORT_CHAT;

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		cout << "bind() Error" << endl;
	if (listen(hServSock, CLIENT_NUM) == SOCKET_ERROR)
		cout << "listen() error" << endl;
	LeaveCriticalSection(&CS_CHAT);
	/* 요청을 받은뒤 모든 클라이언트에게 전송합니다. */
	while (1)
	{
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);
		cout << "accept IP : " << inet_ntoa(clntAdr.sin_addr) << endl;
		WaitForSingleObject(hMutex_CHAT, INFINITE);	// << : Wait Mutex
		clntSocks[clntCnt++] = hClntSock;
		ReleaseMutex(hMutex_CHAT);					// << : Release Mutex
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);	/// << : 모든 클라이언트에게 스레드를 통해 전송
		//if (g_pDataManager->GetQuit()) break;	// << : Quit Game
	}
}

void Server_CHAT::Update()
{
	if (GetAsyncKeyState(VK_NUMPAD9) & 0x0001)
	{
		cout << g_pTime->GetLocalTime() << endl;
	}
}

void Server_CHAT::Destory()
{
	closesocket(hServSock);
	WSACleanup();
}

unsigned int _stdcall HandleClnt(void * arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	ST_CHAT chat;

	while ((strLen = recv(hClntSock, (char*)&chat, NAME_SIZE + BUF_SIZE, 0)) != 0)
	{
		if (strLen != -1)
		{
			SendMsg(chat.TEXT, sizeof(chat.TEXT));
			g_pLog->CreateLog(chat);
		}
	}

	WaitForSingleObject(hMutex_CHAT, INFINITE);	// << : Wait Mutex
	for (i = 0; i < clntCnt; i++)
	{
		if (hClntSock == clntSocks[i])
		{
			while (i++ < clntCnt - 1)
				clntSocks[i] = clntSocks[i + 1];
			break;
		}
	}
	clntCnt--;
	ReleaseMutex(hMutex_CHAT);					// << : Release Mutex
	closesocket(hClntSock);
	return 0;
}

/* Server -> Client 로 채팅을 전송하는 부분 */
void SendMsg(char* msg, int len)
{
	int i;
	WaitForSingleObject(hMutex_CHAT, INFINITE);	// << : Wait Mutex
	for (i = 0; i < clntCnt; i++)
	{
		send(clntSocks[i], msg, len, 0);
		cout << "send Msg " << endl;
	}
	ReleaseMutex(hMutex_CHAT);					//	<< : Release Mutex
}

void Errorhandling(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	//exit(1);
}