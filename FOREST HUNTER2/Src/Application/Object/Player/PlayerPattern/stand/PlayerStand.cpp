#include "PlayerStand.h"

void PlayerStand::Update()
{
	const int MaxCoolCnt = 15;	//1画像アニメ時間
	const int AnimeNum = 4;		//画像数

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