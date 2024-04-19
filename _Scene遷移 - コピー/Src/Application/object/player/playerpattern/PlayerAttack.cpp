#include "PlayerAttack.h"

void PlayerAttack::Update()
{
	const int MaxCoolCnt = 8;	//1‰æ‘œƒAƒjƒŠÔ
	const int AnimeNum = 6;		//‰æ‘œ”

	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt -= MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt >= AnimeNum)
		{
			//ÅŒã‚Å~‚Ü‚é‚æ‚¤‚É
			//-1‚ÍÅŒã‚Ì‰æ‘œ‚ğo—Í‚·‚é‚½‚ß
			m_AnimeCnt = AnimeNum - 1;
		}
	}
}