#include "Death.h"
#include "../BaseEnemy.h"

#define MaxCoolCnt 5	//1画像アニメ時間
#define AnimeNum 7		//画像数

void EnemyDeath::Update()
{
	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt -= MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt > AnimeNum)
		{
			m_AnimeCnt = 0;
			m_enemy->DisableAlive();
		}
	}
}