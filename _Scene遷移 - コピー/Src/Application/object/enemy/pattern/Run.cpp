#include "Run.h"

#define MaxCoolCnt 5	//1画像アニメ時間
#define AnimeNum 5		//画像数

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