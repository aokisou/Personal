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
	_ASSERT_EXPR(bLoad, "�G�l�~�[�p�^�[���摜�ǂݎ��G���[");
}

void EnemyPattern::Update()
{
	const int MaxCoolCnt = 5;	//1�摜�A�j������
	int AnimeNum = 6;		//�摜��

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