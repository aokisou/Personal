#include "PlayerJump.h"

void PlayerJump::Update()
{
	const int MaxCoolCnt = 20;	//1‰æ‘œƒAƒjƒŽžŠÔ
	const int AnimeNum = 2;		//‰æ‘œ”

	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt -= MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt >= AnimeNum)
		{
			m_AnimeCnt = 0;
		}
	}
}