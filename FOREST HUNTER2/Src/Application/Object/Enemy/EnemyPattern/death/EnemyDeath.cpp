#include "EnemyDeath.h"
#include "../../BaseEnemy.h"

void EnemyDeath::Update()
{
	const int MaxCoolCnt = 5;	//1画像アニメ時間
	const int AnimeNum = 6;		//画像数

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (m_animeNum >= AnimeNum)
		{
			m_animeNum = AnimeNum - 1;
			m_enemy->SetFalseAlive();
		}
	}
}