#pragma once
#include "stdafx.h"

#define g_pTime cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETONE(cTimeManager);
	time_t m_stTimer;
	struct tm m_stT;
public:
	string GetLocalTime();	
};

