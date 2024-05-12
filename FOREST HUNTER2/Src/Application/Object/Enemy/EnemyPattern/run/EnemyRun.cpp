#include "EnemyRun.h"
#include "../../slime/Slime.h"
#include "../../Wolf/Wolf.h"
#include "../../Orc/Orc.h"
#include "../../Minotaur/Minotaur.h"

void EnemyRun::Update()
{
	const int MaxCoolCnt = 10;	//1�摜�A�j������
	int AnimeNum = 4;		//�摜��

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