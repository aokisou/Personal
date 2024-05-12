#include "BaseEnemy.h"
#include "../../Scene/BaseSCene/Game/GameScene.h"
#include "EnemyPattern/Death/EnemyDeath.h"
#include "EnemyPattern/Run/EnemyRun.h"
#include "EnemyPattern/Attack/EnemyAttack.h"
#include "../../UI/HP/Enemy/EnemyHPBar.h"
#include "../../Particle/Walk/Walk.h"
#include "../../Utility/Utility.h"

#define PARTICLENUM 10		//パーティクルの数

void BaseEnemy::Init()
{
}

void BaseEnemy::Action()
{
	if (m_pState->GetStateType() == enemyDeath || !m_bAlive) { return; }
}

void BaseEnemy::Update(float _scrollX)
{
	if (!m_bAlive) { return; }
	m_pos += m_move;
	m_mat = Math::Matrix::CreateScale(m_scale, m_scale, 0) * Math::Matrix::CreateTranslation(m_pos.x - _scrollX, m_pos.y, 0);
}

void BaseEnemy::Draw()
{
	DrawUI();
	ParticleDraw();
	Math::Color col = { 1,1,1,1 };
	if (m_bDmg)col = { 1,0,0,1 };
	SHADER.m_spriteShader.SetMatrix(m_mat);
	SHADER.m_spriteShader.DrawTex(m_pState->GetTex(), 0, 0, 
		&Math::Rectangle(m_pState->GetAnimeCnt() * m_size, m_pState->GetStateType() * m_size, m_size, m_size), &col);
}

void BaseEnemy::Reset()
{
}

void BaseEnemy::CreateWalk()
{
	for (int i = m_particle.size(); i < PARTICLENUM; i++)
	{
		std::shared_ptr<BaseParticle> w = std::make_shared<Walk>();
		w->Init(this, m_fileNameP[Particle::walk]);
		m_particle.push_back(w);
	}
}

void BaseEnemy::ParticleUpdate(float _scrollX)
{
	std::vector<std::shared_ptr<BaseParticle>>::iterator it = m_particle.begin();
	while (it != m_particle.end())
	{
		(*it)->Update(_scrollX);
		if (!(*it)->GetAlive())
		{
			it = m_particle.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void BaseEnemy::ParticleDraw()
{
	std::vector<std::shared_ptr<BaseParticle>>::iterator it = m_particle.begin();
	while (it != m_particle.end())
	{
		(*it)->Draw();
		it++;
	}
}

void BaseEnemy::SetDmg(float _dmg)
{
	m_bDmg = true;
	m_hp -= _dmg;
	m_attackHitCnt++;
}

float BaseEnemy::GetAngleDeg(Math::Vector2 src, Math::Vector2 dest)
{
	float a, b, rad, deg;

	a = dest.x - src.x;
	b = dest.y - src.y;
	rad = atan2(b, a);

	deg = DirectX::XMConvertToDegrees(rad);

	if (deg < 0)
	{
		deg += 360;
	}
	return deg;
}

void BaseEnemy::InitUI()
{
	m_gaugeTex.Load("Texture/UI/bg.png");
	m_barTex.Load("Texture/UI/red.png");

	m_pHPBar = std::make_shared<EnemyHPBar>(&m_gaugeTex,&m_barTex);
}
