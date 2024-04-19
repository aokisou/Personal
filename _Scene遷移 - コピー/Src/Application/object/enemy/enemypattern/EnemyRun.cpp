#include "EnemyRun.h"

void EnemyRun::Update()
{
	const int MaxCoolCnt = 5;	//1‰æ‘œƒAƒjƒŽžŠÔ
	const int AnimeNum = 4;		//‰æ‘œ”

	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt -= MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt >= AnimeNum)
		{
			m_AnimeCnt = 0;
		}
	}
}