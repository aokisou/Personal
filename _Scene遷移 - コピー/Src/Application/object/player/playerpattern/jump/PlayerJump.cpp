#include "PlayerJump.h"

void PlayerJump::Update()
{
	const int MaxCoolCnt = 20;	//1‰æ‘œƒAƒjƒŽžŠÔ
	const int AnimeNum = 2;		//‰æ‘œ”

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