#include "PlayerFall.h"

void PlayerFall::Update()
{
	const int MaxCoolCnt = 5;	//1�摜�A�j������
	const int AnimeNum = 2;		//�摜��

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (m_animeNum >= AnimeNum)
		{
			m_animeNum = 0;
		}
	}
}
