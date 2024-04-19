#include "PlayerPattern.h"
#include "../../BaseObject.h"

void PlayerPattern::Init(Player* _player,std::string _filename)
{
	bool bLoad = false;
	m_player = _player;
	m_AnimeCnt = 0;
	m_CoolCnt = 0;
	bLoad = m_tex.Load(_filename);
	_ASSERT_EXPR(bLoad, _filename);
}

void PlayerPattern::Update()
{
	const int MaxCoolCnt = 5;	//1‰æ‘œƒAƒjƒŽžŠÔ
	const int AnimeNum = 4;		//‰æ‘œ”

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