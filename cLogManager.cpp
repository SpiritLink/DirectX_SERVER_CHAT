#include "stdafx.h"
#include "cLogManager.h"


cLogManager::cLogManager()
{
}


cLogManager::~cLogManager()
{
}

/* txt파일로 채팅을 기록하는 함수입니다 */
void cLogManager::CreateLog(ST_CHAT stData)
{
	// 방이름.txt 파일과 AllChat.txt파일 두개의 파일에 채팅이 기록됩니다.
	// 방마다 채팅이 저장되며 모든 채팅이 순서대로 AllChat이라는 파일에 저장됩니다
	string szFullPath = "Server/" + string(stData.ROOM_NAME) + ".txt";
	string szFullPath2 = string("Server/") + string("AllChat.txt");
	ofstream writeFile(szFullPath.data(), ios::app);
	ofstream writeFile2(szFullPath2.data(), ios::app);
	if (!writeFile.is_open()) 
	{
		char strFolderPath[] = "Server";
		int nResult = _mkdir(strFolderPath);
		if (nResult == 0)
			cout << "폴더 생성 성공" << endl;
		else if (nResult == -1)
		{
			perror("폴더 생성 실패 - 폴더가 이미 있거나 부정확함 \n");
			cout << "errorno :" << errno << endl;
		}
	}
	writeFile << g_pTime->GetLocalTime() << " ";
	writeFile << stData.TEXT << endl;
	writeFile2 << g_pTime->GetLocalTime() << " ";
	writeFile2 << stData.TEXT << endl;
	writeFile.close();
	writeFile2.close();
}
