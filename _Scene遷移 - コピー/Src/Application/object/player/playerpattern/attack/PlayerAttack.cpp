#include "PlayerAttack.h"

void PlayerAttack::Update()
{
	const int MaxCoolCnt = 10;	//1画像アニメ時間
	const int AnimeNum = 6;		//画像数

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (m_animeNum >= AnimeNum)
		{
			//最後で止まるように
			//-1は最後の画像を出力するため
			m_animeNum = AnimeNum - 1;
		}
	}
}