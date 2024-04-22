#include "hit.h"
#include "../../Scene/BaseScene/Game/GameScene.h"
#include "../../Object/Player/player.h"
#include "../../Object/Enemy/BaseEnemy.h"
#include "../../Object/Arrow/Arrow.h"
#include "../../Utility/utility.h"

void Hit::PlyEmyHit()
{
	Player* ply = m_pOwner->GetPlayer();

	for (auto& emy : m_pOwner->GetEnemy())
	{
		if (ply->GetDmg() || ply->GetDead() || emy->GetDead() || !emy->GetAlive()) { continue; }

		const float plyRight = ply->GetPos().x + ply->GetHalfSize() - ply->GetSpaceWidthImg();
		const float plyLeft = ply->GetPos().x - ply->GetHalfSize() + ply->GetSpaceWidthImg();
		const float plyTop = ply->GetPos().y + ply->GetHalfSize() - ply->GetSpaceHeightImg();
		const float plyBottom = ply->GetPos().y - ply->GetHalfSize() + ply->GetSpaceHeightImg();

		const float plyNextRight = ply->GetFuturePos().x + ply->GetHalfSize() - ply->GetSpaceWidthImg();
		const float plyNextLeft = ply->GetFuturePos().x - ply->GetHalfSize() + ply->GetSpaceWidthImg();
		const float plyNextTop = ply->GetFuturePos().y + ply->GetHalfSize() - ply->GetSpaceHeightImg();
		const float plyNextBottom = ply->GetFuturePos().y - ply->GetHalfSize() + ply->GetSpaceHeightImg();

		const float emyRight = emy->GetPos().x + emy->GetHalfSize() - emy->GetSpaceWidthImg();
		const float emyLeft = emy->GetPos().x - emy->GetHalfSize() + emy->GetSpaceWidthImg();
		const float emyTop = emy->GetPos().y + emy->GetHalfSize();
		const float emyBottom = emy->GetPos().y - emy->GetHalfSize() + emy->GetSpaceHeightImg();

		const float emyNextRight = emy->GetFuturePos().x + emy->GetHalfSize() - emy->GetSpaceWidthImg();
		const float emyNextLeft = emy->GetFuturePos().x - emy->GetHalfSize() + emy->GetSpaceWidthImg();
		const float emyNextTop = emy->GetFuturePos().y + emy->GetHalfSize();
		const float emyNextBottom = emy->GetFuturePos().y - emy->GetHalfSize() + emy->GetSpaceHeightImg();

		if (plyTop > emyBottom && plyTop < emyTop)
		{
			if (plyNextRight >= emyNextLeft && plyNextRight <= emyNextRight)
			{
				ply->SetDamage(emy->GetMovePow().x * 2);
			}
			else if (plyNextLeft >= emyNextRight && plyNextLeft <= emyNextLeft)
			{
				ply->SetDamage(emy->GetMovePow().x * 2);
			}
		}
		else if (plyRight > emyLeft && plyLeft < emyRight)
		{
			if (plyNextTop >= emyNextBottom && plyNextTop <= emyNextTop)
			{
				ply->SetDamage(emy->GetMovePow().x * 2);
			}
			else if (plyNextBottom >= emyNextTop && plyNextBottom <= emyNextBottom)
			{
				ply->SetDamage(emy->GetMovePow().x * 2);
			}
		}
	}
}

void Hit::ArrEmyHit()
{
	std::vector<Arrow*>* pArr = m_pOwner->GetPlayer()->GetArrow();
	std::vector<Arrow*>::iterator it = pArr->begin();
	while (it != pArr->end())
	{
		for (auto& emy : m_pOwner->GetEnemy())
		{
			if (!emy->GetAlive() || emy->GetDead()) { continue; }
			float a, b, c;
			a = (*it)->GetFuturePos().x - emy->GetFuturePos().x;
			b = (*it)->GetFuturePos().y - emy->GetFuturePos().y;
			c = sqrt(a * a + b * b);
			float Dist = (emy->GetHalfSize() - emy->GetSpaceWidthImg()) + ((*it)->GetHalfSize() - (*it)->GetSpaceWidthImg());

			if (c < Dist)
			{
				emy->SetDamage((*it)->GetDmg());
				(*it)->SetFalseAlive();
			}
		}
		it++;
	}
}