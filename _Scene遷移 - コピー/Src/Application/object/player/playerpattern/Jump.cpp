#include "Jump.h"

#define MaxCoolCnt 20	//1�摜�A�j������
#define AnimeNum 2		//�摜��

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