#include "hit.h"
#include "../scene/game/GameScene.h"
#include "../object/player/player.h"
#include "../object/enemy/BaseEnemy.h"
#include "../object/arrow/Arrow.h"
#include "../utility/utility.h"

void Hit::Init()
{
}

void Hit::PlyEmyHit()
{
	Player* ply = (Player*)m_pOwner->GetPlayer();
	BaseEnemy* emy = (BaseEnemy*)m_pOwner->GetEnemy();

	if (ply->GetbDmg() || !ply->GetbAlive() || emy->GetbDead() || !emy->GetbAlive()) { return; }

	const float plyRight	= ply->GetPos().x + ply->GetHalfSize() - ply->GetSpaceWidthImg();
	const float plyLeft		= ply->GetPos().x - ply->GetHalfSize() + ply->GetSpaceWidthImg();
	const float plyTop		= ply->GetPos().y + ply->GetHalfSize() - ply->GetSpaceHeightImg();
	const float plyBottom	= ply->GetPos().y - ply->GetHalfSize() + ply->GetSpaceHeightImg();

	const float plyNextRight	= ply->GetFuturePos().x + ply->GetHalfSize() - ply->GetSpaceWidthImg();
	const float plyNextLeft		= ply->GetFuturePos().x - ply->GetHalfSize() + ply->GetSpaceWidthImg();
	const float plyNextTop		= ply->GetFuturePos().y + ply->GetHalfSize() - ply->GetSpaceHeightImg();
	const float plyNextBottom	= ply->GetFuturePos().y - ply->GetHalfSize() + ply->GetSpaceHeightImg();

	const float emyRight	= emy->GetPos().x + emy->GetHalfSize() - emy->GetSpaceWidthImg();
	const float emyLeft		= emy->GetPos().x - emy->GetHalfSize() + emy->GetSpaceWidthImg();
	const float emyTop		= emy->GetPos().y + emy->GetHalfSize();
	const float emyBottom	= emy->GetPos().y - emy->GetHalfSize() + emy->GetSpaceHeightImg();

	const float emyNextRight	= emy->GetFuturePos().x + emy->GetHalfSize() - emy->GetSpaceWidthImg();
	const float emyNextLeft		= emy->GetFuturePos().x - emy->GetHalfSize() + emy->GetSpaceWidthImg();
	const float emyNextTop		= emy->GetFuturePos().y + emy->GetHalfSize();
	const float emyNextBottom	= emy->GetFuturePos().y - emy->GetHalfSize() + emy->GetSpaceHeightImg();

	if (plyTop > emyBottom && plyTop < emyTop)
	{
		if (plyNextRight > emyNextLeft && plyNextRight < emyNextRight)
		{
			ply->ApplyDamage();
		}
		else if (plyNextLeft > emyNextRight && plyNextLeft < emyNextLeft)
		{
			ply->ApplyDamage();
		}
	}
	else if (plyRight > emyLeft && plyLeft < emyRight)
	{
		if (plyNextTop > emyNextBottom && plyNextTop < emyNextTop)
		{
			ply->ApplyDamage();
		}
		else if (plyNextBottom > emyNextTop && plyNextBottom < emyNextBottom)
		{
			ply->ApplyDamage();
		}
	}
}

void Hit::ArrEmyHit()
{
	std::vector<Arrow*>* pArr = m_pOwner->GetPlayer()->GetArrow();
	std::vector<Arrow*>::iterator it = pArr->begin();
	while (it != pArr->end())
	{
		BaseEnemy* emy = (BaseEnemy*)m_pOwner->GetEnemy();
		if (!emy->GetbAlive() || emy->GetbDead()) { break; }
		float a, b, c;
		a = (*it)->GetFuturePos().x - emy->GetFuturePos().x;
		b = (*it)->GetFuturePos().y - emy->GetFuturePos().y;
		c = sqrt(a * a + b * b);
		float Dist = (emy->GetHalfSize() - emy->GetSpaceWidthImg()) + ((*it)->GetHalfSize() - (*it)->GetSpaceWidthImg());

		if (c < Dist)
		{
			emy->ApplyDamage((*it)->GetDmg());
			(*it)->DisableAlive();
		}
		it++;
	}
}