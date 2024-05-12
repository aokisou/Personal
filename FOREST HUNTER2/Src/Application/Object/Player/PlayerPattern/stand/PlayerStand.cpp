#include "PlayerStand.h"

void PlayerStand::Update()
{
	const int MaxCoolCnt = 15;	//1�摜�A�j������
	const int AnimeNum = 4;		//�摜��

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