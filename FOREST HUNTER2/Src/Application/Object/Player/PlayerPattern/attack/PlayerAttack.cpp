#include "PlayerAttack.h"

void PlayerAttack::Update()
{
	const int MaxCoolCnt = 4;	//1‰æ‘œƒAƒjƒŠÔ
	const int AnimeNum = 6;		//‰æ‘œ”

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (m_animeNum >= AnimeNum)
		{
			//ÅŒã‚Å~‚Ü‚é‚æ‚¤‚É
			//-1‚ÍÅŒã‚Ì‰æ‘œ‚ğo—Í‚·‚é‚½‚ß
			m_animeNum = AnimeNum - 1;
		}
	}
}