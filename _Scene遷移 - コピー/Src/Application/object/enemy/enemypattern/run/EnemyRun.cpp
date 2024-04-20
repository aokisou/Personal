#include "EnemyRun.h"

void EnemyRun::Update()
{
	const int MaxCoolCnt = 10;	//1‰æ‘œƒAƒjƒŽžŠÔ
	const int AnimeNum = 4;		//‰æ‘œ”

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (m_animeNum >= AnimeNum)
		{
			m_animeNum = 0;
		}
	}
}