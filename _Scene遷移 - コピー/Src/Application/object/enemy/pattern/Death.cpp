#include "Death.h"
#include "../BaseEnemy.h"

#define MaxCoolCnt 5	//1�摜�A�j������
#define AnimeNum 7		//�摜��

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