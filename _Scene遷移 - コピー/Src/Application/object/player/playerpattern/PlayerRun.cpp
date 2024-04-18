#include "PlayerRun.h"

#define MaxCoolCnt 5	//1�摜�A�j������
#define AnimeNum 5		//�摜��

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