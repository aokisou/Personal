#include "PlayerJump.h"

void PlayerJump::Update()
{
	const int MaxCoolCnt = 20;	//1画像アニメ時間
	const int AnimeNum = 2;		//画像数

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