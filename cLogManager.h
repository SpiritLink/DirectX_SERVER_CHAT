#pragma once
#include "stdafx.h"

#define g_pLog cLogManager::GetInstance()

class cLogManager
{
private:
	SINGLETONE(cLogManager);
public:
	void CreateLog(ST_CHAT stData);
};

