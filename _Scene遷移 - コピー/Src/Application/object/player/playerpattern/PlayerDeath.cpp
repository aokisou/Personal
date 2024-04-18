#include "PlayerDeath.h"
#include "../Player.h"

#define MaxCoolCnt 5	//1‰æ‘œƒAƒjƒŽžŠÔ
#define AnimeNum 7		//‰æ‘œ”

void PlayerDeath::Update()
{
	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt -= MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt >= AnimeNum)
		{
			m_AnimeCnt = 0;
			m_player->DisableAlive();
		}
	}
}