#include "EnemyPattern.h"

void EnemyPattern::Init(BaseEnemy* _enemy,std::string _filename)
{
	bool bLoad;
	m_enemy = _enemy;
	m_AnimeCnt = 0;
	m_CoolCnt = 0;
	bLoad = m_tex.Load(_filename);
	_ASSERT_EXPR(bLoad, _filename);
}

void EnemyPattern::Update()
{
	const int MaxCoolCnt = 5;	//1‰æ‘œƒAƒjƒŽžŠÔ
	const int AnimeNum = 6;		//‰æ‘œ”

	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt =- MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt >= AnimeNum)
		{
			m_AnimeCnt = 0;
		}
	}
}