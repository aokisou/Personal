#include "PlayerAttack.h"

void PlayerAttack::Update()
{
	const int MaxCoolCnt = 4;	//1�摜�A�j������
	const int AnimeNum = 6;		//�摜��

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (m_animeNum >= AnimeNum)
		{
			//�Ō�Ŏ~�܂�悤��
			//-1�͍Ō�̉摜���o�͂��邽��
			m_animeNum = AnimeNum - 1;
		}
	}
}