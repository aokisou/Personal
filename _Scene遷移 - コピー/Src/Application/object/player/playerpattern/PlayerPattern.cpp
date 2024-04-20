#include "PlayerPattern.h"
#include "../../BaseObject.h"

void PlayerPattern::Init(Player* _player,std::string _filename)
{
	bool bLoad = false;
	m_player = _player;
	m_animeNum = 0;
	m_coolCnt = 0;
	bLoad = m_tex.Load(_filename);
	_ASSERT_EXPR(bLoad, _filename);
}

void PlayerPattern::Update()
{
	const int MaxCoolCnt = 5;	//1�摜�A�j������
	const int AnimeNum = 4;		//�摜��

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