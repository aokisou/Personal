#include "PlayerAttack.h"

void PlayerAttack::Update()
{
	const int MaxCoolCnt = 8;	//1�摜�A�j������
	const int AnimeNum = 6;		//�摜��

	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt -= MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt >= AnimeNum)
		{
			//�Ō�Ŏ~�܂�悤��
			//-1�͍Ō�̉摜���o�͂��邽��
			m_AnimeCnt = AnimeNum - 1;
		}
	}
}