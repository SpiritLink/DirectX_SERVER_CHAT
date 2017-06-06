// DirectX_SERVER_CHAT.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Server_CHAT.h"

unsigned _stdcall ThChat_ACCEPT(LPVOID lpParam)
{
	Server_CHAT * pServerChat = ((Server_CHAT*)lpParam);
	pServerChat->Setup();
	return 0;
}

int main()
{
	DWORD dwThID1, dwThID2;
	HANDLE hThread;
	unsigned long ulStackSize = 0;

	Server_CHAT * pServerChat;
	pServerChat = new Server_CHAT;

	hThread = (HANDLE)_beginthreadex(NULL, 0, (unsigned(_stdcall*)(void*))ThChat_ACCEPT, (void*)&pServerChat, 0, (unsigned*)&dwThID1);

	while (1)
	{
		pServerChat->Update();
	}
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);

	pServerChat->Destory();
    return 0;
}

