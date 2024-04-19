#include "PlayerAttack.h"

void PlayerAttack::Update()
{
	const int MaxCoolCnt = 8;	//1画像アニメ時間
	const int AnimeNum = 6;		//画像数

	m_CoolCnt++;
	if (m_CoolCnt > MaxCoolCnt)
	{
		m_CoolCnt -= MaxCoolCnt;
		m_AnimeCnt++;
		if (m_AnimeCnt >= AnimeNum)
		{
			//最後で止まるように
			//-1は最後の画像を出力するため
			m_AnimeCnt = AnimeNum - 1;
		}
	}
}