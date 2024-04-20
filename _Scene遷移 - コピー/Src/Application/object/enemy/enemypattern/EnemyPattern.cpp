#include "EnemyPattern.h"

void EnemyPattern::Init(BaseEnemy* _enemy,std::string _filename)
{
	bool bLoad;
	m_enemy = _enemy;
	m_animeNum = 0;
	m_coolCnt = 0;
	bLoad = m_tex.Load(_filename);
	_ASSERT_EXPR(bLoad, _filename);
}

void EnemyPattern::Update()
{
	const int MaxCoolCnt = 5;	//1画像アニメ時間
	const int AnimeNum = 6;		//画像数

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt =- MaxCoolCnt;
		m_animeNum++;
		if (m_animeNum >= AnimeNum)
		{
			m_animeNum = 0;
		}
	}
}