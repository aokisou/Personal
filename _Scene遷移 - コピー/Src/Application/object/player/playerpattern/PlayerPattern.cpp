#include "PlayerPattern.h"
#include "../../BaseObject.h"

#define MaxCoolCnt 5	//1‰æ‘œƒAƒjƒŽžŠÔ
#define AnimeNum 4		//‰æ‘œ”

void PlayerPattern::Init(Player* _player)
{
	m_player = _player;
	m_AnimeCnt = 0;
	m_CoolCnt = 0;
}

void PlayerPattern::Update()
{
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