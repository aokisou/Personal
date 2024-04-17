#include "Run.h"

#define MaxCoolCnt 5	//1�摜�A�j������
#define AnimeNum 4		//�摜��

void EnemyRun::Update()
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