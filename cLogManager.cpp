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
			cout << "���� ���� ����" << endl;
		else if (nResult == -1)
		{
			perror("���� ���� ���� - ������ �̹� �ְų� ����Ȯ�� \n");
			cout << "errorno :" << errno << endl;
		}
	}
	writeFile << g_pTime->GetLocalTime() << " ";
	writeFile << stData.TEXT;
	writeFile.close();
}
