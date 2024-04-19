#include "EnemyDeath.h"
#include "../BaseEnemy.h"

void EnemyDeath::Update()
{
	const int MaxCoolCnt = 5;	//1‰æ‘œƒAƒjƒŽžŠÔ
	const int AnimeNum = 8;		//‰æ‘œ”
	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt -= MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt >= AnimeNum)
		{
			m_AnimeCnt = 0;
			m_enemy->DisableAlive();
		}
	}
}