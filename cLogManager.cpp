#include "stdafx.h"
#include "cLogManager.h"


cLogManager::cLogManager()
{
}


cLogManager::~cLogManager()
{
}

void cLogManager::CreateLog(ST_CHAT stData)
{
	string szFullPath = "Server/" + string(stData.ROOM_NAME) + ".txt";
	ofstream writeFile(szFullPath.data(), ios::app);
	if (!writeFile.is_open()) 
	{
		char strFolderPath[] = "Server";
		int nResult = mkdir(strFolderPath);
		if (nResult == 0)
			cout << "폴더 생성 성공" << endl;
		else if (nResult == -1)
		{
			perror("폴더 생성 실패 - 폴더가 이미 있거나 부정확함 \n");
			cout << "errorno :" << errno << endl;
		}
	}
	writeFile << g_pTime->GetLocalTime() << " ";
	writeFile << stData.TEXT;
	writeFile.close();
}
