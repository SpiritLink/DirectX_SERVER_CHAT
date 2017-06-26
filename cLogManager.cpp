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
	string szFullPath2 = string("Server/") + string("AllChat.txt");
	ofstream writeFile(szFullPath.data(), ios::app);
	ofstream writeFile2(szFullPath2.data(), ios::app);
	if (!writeFile.is_open()) 
	{
		char strFolderPath[] = "Server";
		int nResult = _mkdir(strFolderPath);
		if (nResult == 0)
			cout << "���� ���� ����" << endl;
		else if (nResult == -1)
		{
			perror("���� ���� ���� - ������ �̹� �ְų� ����Ȯ�� \n");
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
