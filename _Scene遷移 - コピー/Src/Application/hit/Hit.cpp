#include "hit.h"
#include "../scene/game/GameScene.h"
#include "../object/player/player.h"
#include "../object/enemy/BaseEnemy.h"
#include "../object/bullet/Bullet.h"
#include "../utility/utility.h"

void Hit::Init()
{
}

void Hit::PlyEmyHit()
{
	Player* ply = (Player*)m_pOwner->GetPlayer();
	BaseEnemy* emy = (BaseEnemy*)m_pOwner->GetEnemy();

	if (ply->GetbDmg()) { return; }

	if (!ply->GetbAlive() || !emy->GetbDead()) { return; }
	//空白スペースあるから少し少なくとる
	const float plyRight	= ply->GetPos().x + ply->GetHalfSize() / Half;
	const float plyLeft	= ply->GetPos().x - ply->GetHalfSize() / Half;
	const float plyTop	= ply->GetPos().y + ply->GetHalfSize() / Half;
	const float plyBottom = ply->GetPos().y - ply->GetHalfSize() / Half;

	const float plyNextRight	= ply->GetFuturePos().x + ply->GetHalfSize() / Half;
	const float plyNextLeft	= ply->GetFuturePos().x - ply->GetHalfSize() / Half;
	const float plyNextTop	= ply->GetFuturePos().y + ply->GetHalfSize() / Half;
	const float plyNextBottom = ply->GetFuturePos().y - ply->GetHalfSize() / Half;

	const float emyRight	= emy->GetPos().x + emy->GetHalfSize() / Half;
	const float emyLeft	= emy->GetPos().x - emy->GetHalfSize() / Half;
	const float emyTop	= emy->GetPos().y + emy->GetHalfSize() / Half;
	const float emyBottom = emy->GetPos().y - emy->GetHalfSize() / Half;

	const float emyNextRight	= emy->GetFuturePos().x + emy->GetHalfSize() / Half;
	const float emyNextLeft	= emy->GetFuturePos().x - emy->GetHalfSize() / Half;
	const float emyNextTop	= emy->GetFuturePos().y + emy->GetHalfSize() / Half;
	const float emyNextBottom = emy->GetFuturePos().y - emy->GetHalfSize() / Half;

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

void Hit::BltEmyHit()
{
	std::vector<Bullet*>* pBlt;
	pBlt = ((Player*)m_pOwner->GetPlayer())->GetBullet();
	std::vector<Bullet*>::iterator it = pBlt->begin();
	while (it != pBlt->end())
	{
		BaseEnemy* emy = (BaseEnemy*)m_pOwner->GetEnemy();
		if (!emy->GetbAlive() || emy->GetbDead()) { break; }
		float a, b, c;
		a = (*it)->GetFuturePos().x - emy->GetFuturePos().x - 22;
		b = (*it)->GetFuturePos().y - emy->GetFuturePos().y - 22;
		c = sqrt(a * a + b * b);
		float Dist = emy->GetHalfSize() + (*it)->GetHalfSize() - 22;

		if (c < Dist)
		{
			emy->ApplyDamage();
			(*it)->DisableAlive();
		}
		it++;
	}
}