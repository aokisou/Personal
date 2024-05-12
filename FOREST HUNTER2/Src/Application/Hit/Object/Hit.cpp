#include "hit.h"
#include "../../Scene/BaseScene/Game/GameScene.h"
#include "../../Object/Player/player.h"
#include "../../Object/Enemy/BaseEnemy.h"
#include "../../Object/Arrow/Arrow.h"
#include "../../Object/Enemy/EnemyPattern/EnemyPattern.h"
#include "../../Utility/utility.h"

void Hit::ArrEmyHit()
{
	for(int i = 0;i < 99;i++)
	{
		std::shared_ptr<Arrow>* a = m_pOwner->GetPlayer()->GetArrow(i);
		if ((*a)->GetAlive())
		{
			for (auto& emy : m_pOwner->GetEnemy())
			{
				if (!emy->GetAlive() || emy->GetEnemyState()->GetStateType() == enemyDeath) { continue; }
				Math::Vector2 v = emy->GetFuturePos() - (*a)->GetFuturePos();
				float Dist = (float)(emy->GetHalfSize() - emy->GetSpaceWidthImg()) + (float)((*a)->GetHalfSize() - (*a)->GetSpaceWidthImg());

				if (v.Length() < Dist)
				{
					emy->SetDmg((*a)->GetDmg());
					(*a)->SetFalseAlive();
					m_pOwner->SetTrueShake();
					break;
				}
			}
		}
	}
}