#include "EnemyPattern.h"
#include "../slime/Slime.h"
#include "../Wolf/Wolf.h"
#include "../Orc/Orc.h"
#include "../Minotaur/Minotaur.h"

void EnemyPattern::Init(BaseEnemy* _enemy, std::string _file)
{
	bool bLoad;
	m_enemy = _enemy;
	m_animeNum = 0;
	m_coolCnt = 0;
	bLoad = m_tex.Load(_file);
	_ASSERT_EXPR(bLoad, "エネミーパターン画像読み取りエラー");
}

void EnemyPattern::Update()
{
	const int MaxCoolCnt = 5;	//1画像アニメ時間
	int AnimeNum = 6;		//画像数

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