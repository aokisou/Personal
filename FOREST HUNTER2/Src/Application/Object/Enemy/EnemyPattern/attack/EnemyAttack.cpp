#include "EnemyAttack.h"
#include "../../../Player/Player.h"
#include "../../../../Scene/BaseScene/Game/GameScene.h"
#include "../../slime/Slime.h"
#include "../../Wolf/Wolf.h"
#include "../../Orc/Orc.h"
#include "../../Minotaur/Minotaur.h"

void EnemyAttack::Update()
{
	const int MaxCoolCnt = 5;	//1画像アニメ時間
	int AnimeNum = 6;			//画像数

	if (typeid(*m_enemy) == typeid(Minotaur))
	{
		AnimeNum = 9;
	}

	m_coolCnt++;
	if (m_coolCnt > MaxCoolCnt)
	{
		m_coolCnt -= MaxCoolCnt;
		m_animeNum++;
		if (typeid(*m_enemy) == typeid(Minotaur))
		{
			if(m_animeNum >= 1 && m_animeNum <= 3){ Attack(); }
		}
		if (m_animeNum >= AnimeNum)
		{
			m_animeNum = 0;
			if (typeid(*m_enemy) != typeid(Minotaur))
			{
				Attack();
			}
			m_enemy->ResetAttackCoolTime();
			m_enemy->SetRunState();
		}
	}
}

void EnemyAttack::Attack()
{
	if (m_bAttack) { return; }
	std::shared_ptr<Player> p = m_enemy->GetOwner()->GetPlayer();
	Math::Vector2 v = p->GetFuturePos() - m_enemy->GetFuturePos();
	if (v.Length() < p->GetHalfSize() - p->GetSpaceWidthImg() + m_enemy->GetHalfSize() - m_enemy->GetSpaceWidthImg())
	{
		if (p->GetFuturePos().x - m_enemy->GetFuturePos().x >= 0)
		{
			p->SetDmg(m_enemy->GetDmg(), 5.0f);
		}
		else
		{
			p->SetDmg(m_enemy->GetDmg(), -5.0f);
		}
		m_bAttack = true;
	}
}
