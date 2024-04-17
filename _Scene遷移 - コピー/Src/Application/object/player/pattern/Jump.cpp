#include "Jump.h"

#define MaxCoolCnt 20	//1‰æ‘œƒAƒjƒŽžŠÔ
#define AnimeNum 2		//‰æ‘œ”

void PlayerJump::Update()
{
	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt -= MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt > AnimeNum)
		{
			m_AnimeCnt = 0;
		}
	}
}