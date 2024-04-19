#include "PlayerJump.h"

void PlayerJump::Update()
{
	const int MaxCoolCnt = 20;	//1�摜�A�j������
	const int AnimeNum = 2;		//�摜��

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