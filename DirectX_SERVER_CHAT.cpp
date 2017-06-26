// DirectX_SERVER_CHAT.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "Server_CHAT.h"

/* Setup�Լ� (connect���)�� ���ѷ��� �մϴ� */
unsigned _stdcall ThChat_ACCEPT(LPVOID lpParam)
{
	Server_CHAT * pServerChat = ((Server_CHAT*)lpParam);
	pServerChat->Setup();
	return 0;
}

/*  Server_CHAT Ŭ������ �����ϰ� ThChat_ACCEPT ������ �Լ��� �����մϴ�.
	���� Server_CHAT�� Update�� ���� �����մϴ�
*/
int main()
{
	DWORD dwThID1;
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

