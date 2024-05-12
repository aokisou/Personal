#include "BaseParticle.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/BaseEnemy.h"

void BaseParticle::Init(BaseObject* _obj, std::string _file)
{
	bool bLoad = false;
	m_pos = {_obj->GetFuturePos()};
	m_move = { rand() % 3 + 1.5f * -_obj->GetDir(), (float)(rand() % 3)};
	m_size = 1;
	m_cnt = rand() % 30 + 10;
	m_bAlive = true;
	m_pOwner = _obj;
	bLoad = m_tex.Load(_file);
	_ASSERT_EXPR(bLoad, "パーティクル画像読み取りエラー");
}

void BaseParticle::Release()
{
}