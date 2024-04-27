#include "EnemyAttack.h"
#include "../../BaseEnemy.h"
#include "../../../Player/Player.h"
#include "../../../../Scene/BaseScene/Game/GameScene.h"

void EnemyAttack::Update()
{
	const int MaxCoolCnt = 5;	//1‰æ‘œƒAƒjƒŽžŠÔ
	const int AnimeNum = 6;		//‰æ‘œ”

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (m_animeNum >= AnimeNum)
		{
			m_animeNum = 0;
			Player* p = m_enemy->GetOwner()->GetPlayer();
			Math::Vector2 v = p->GetFuturePos() - m_enemy->GetFuturePos();
			if (v.Length() < p->GetHalfSize() - p->GetSpaceWidthImg() + m_enemy->GetHalfSize() - m_enemy->GetSpaceWidthImg())
			{
				if (p->GetFuturePos().x - m_enemy->GetFuturePos().x > 0)
				{
					p->SetDmg(m_enemy->GetDmg(), 5.0f);
				}
				else
				{
					p->SetDmg(m_enemy->GetDmg(), -5.0f);
				}
			}
			m_enemy->ResetAttackCoolTime();
			m_enemy->SetRunState();
		}
	}
}