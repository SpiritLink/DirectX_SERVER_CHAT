// DirectX_SERVER_CHAT.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Server_CHAT.h"

/* Setup함수 (connect대기)를 무한루프 합니다 */
unsigned _stdcall ThChat_ACCEPT(LPVOID lpParam)
{
	Server_CHAT * pServerChat = ((Server_CHAT*)lpParam);
	pServerChat->Setup();
	return 0;
}

/*  Server_CHAT 클래스를 생성하고 ThChat_ACCEPT 스레드 함수를 실행합니다.
	이후 Server_CHAT의 Update를 무한 루프합니다
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

