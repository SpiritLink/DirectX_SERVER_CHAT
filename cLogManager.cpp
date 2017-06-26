#include "stdafx.h"
#include "cLogManager.h"


cLogManager::cLogManager()
{
}


cLogManager::~cLogManager()
{
}

/* txt���Ϸ� ä���� ����ϴ� �Լ��Դϴ� */
void cLogManager::CreateLog(ST_CHAT stData)
{
	// ���̸�.txt ���ϰ� AllChat.txt���� �ΰ��� ���Ͽ� ä���� ��ϵ˴ϴ�.
	// �渶�� ä���� ����Ǹ� ��� ä���� ������� AllChat�̶�� ���Ͽ� ����˴ϴ�
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
