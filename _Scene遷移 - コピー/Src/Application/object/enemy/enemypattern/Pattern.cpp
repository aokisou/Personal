#include "Pattern.h"

#define MaxCoolCnt 5	//1‰æ‘œƒAƒjƒŽžŠÔ
#define AnimeNum 4		//‰æ‘œ”

void EnemyPattern::Init(BaseEnemy* _enemy)
{
	m_enemy = _enemy;
	m_AnimeCnt = 0;
	m_CoolCnt = 0;
}

void EnemyPattern::Update()
{
	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt =- MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt > AnimeNum)
		{
			m_AnimeCnt = 0;
		}
	}
}