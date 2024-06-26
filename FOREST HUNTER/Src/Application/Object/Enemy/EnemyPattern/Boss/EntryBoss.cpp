#include "EntryBoss.h"
#include "../../../../Scene/BaseScene/Game/GameScene.h"
//ボスとして登場させるものをinclude
#include "../../Minotaur/Minotaur.h"

void EnemyEntry::Update()
{
	const int MaxCoolCnt = 15;	//1画像アニメ時間
	int AnimeNum = 9;			//画像数

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (!m_bFirst && m_animeNum == 5)
		{
			m_animeNum = 3;
			m_bFirst = true;
		}
		if (m_animeNum >= AnimeNum)
		{
			m_animeNum = 0;
			m_enemy->GetOwner()->SetFalseEntry();
			m_enemy->GetOwner()->ResetScreenScale();
			m_enemy->SetRunState();
		}
	}
}