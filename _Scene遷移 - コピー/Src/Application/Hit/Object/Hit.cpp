#include "hit.h"
#include "../../Scene/BaseScene/Game/GameScene.h"
#include "../../Object/Player/player.h"
#include "../../Object/Enemy/BaseEnemy.h"
#include "../../Object/Arrow/Arrow.h"
//#include "../../Object/Player/PlayerPattern/PlayerPattern.h"
#include "../../Object/Enemy/EnemyPattern/EnemyPattern.h"
#include "../../Utility/utility.h"

void Hit::ArrEmyHit()
{
	std::vector<Arrow*>* pArr = m_pOwner->GetPlayer()->GetArrow();
	std::vector<Arrow*>::iterator it = pArr->begin();
	while (it != pArr->end())
	{
		for (auto& emy : m_pOwner->GetEnemy())
		{
			if (!emy->GetAlive() || emy->GetEnemyState()->GetStateType() == enemyDeath) { continue; }
			Math::Vector2 v = emy->GetFuturePos() - (*it)->GetFuturePos();
			float Dist = (float)(emy->GetHalfSize() - emy->GetSpaceWidthImg()) + (float)((*it)->GetHalfSize() - (*it)->GetSpaceWidthImg());

			if (v.Length() < Dist)
			{
				emy->SetDamage((*it)->GetDmg());
				(*it)->SetFalseAlive();
				break;
			}
		}
		it++;
	}
}