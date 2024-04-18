#include "PlayerRun.h"

#define MaxCoolCnt 5	//1‰æ‘œƒAƒjƒŽžŠÔ
#define AnimeNum 5		//‰æ‘œ”

void PlayerRun::Update()
{
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