#include "PlayerJump.h"

void PlayerJump::Update()
{
	const int MaxCoolCnt = 20;	//1画像アニメ時間
	const int AnimeNum = 2;		//画像数

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