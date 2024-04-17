#include "Jump.h"

#define MaxCoolCnt 20	//1画像アニメ時間
#define AnimeNum 2		//画像数

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