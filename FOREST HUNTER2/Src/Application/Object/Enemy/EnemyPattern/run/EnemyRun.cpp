#include "EnemyRun.h"
#include "../../slime/Slime.h"
#include "../../Wolf/Wolf.h"
#include "../../Orc/Orc.h"
#include "../../Minotaur/Minotaur.h"

void EnemyRun::Update()
{
	const int MaxCoolCnt = 10;	//1画像アニメ時間
	int AnimeNum = 4;		//画像数

	if (typeid(*m_enemy) == typeid(Minotaur))
	{
		AnimeNum = 8;
	}

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