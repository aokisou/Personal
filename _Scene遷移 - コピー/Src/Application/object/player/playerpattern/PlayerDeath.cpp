#include "PlayerDeath.h"
#include "../Player.h"

void PlayerDeath::Update()
{
	const int MaxCoolCnt = 5;	//1画像アニメ時間
	const int AnimeNum = 10;	//画像数

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