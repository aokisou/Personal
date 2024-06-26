#include "PlayerGetHit.h"
#include "../../Player.h"

void PlayerGetHit::Update()
{
	const int MaxCoolCnt = 5;	//1画像アニメ時間
	const int AnimeNum = 3;		//画像数

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (m_animeNum >= AnimeNum)
		{
			m_animeNum = 0;
			m_player->EndDamageEfc();
		}
	}
}
