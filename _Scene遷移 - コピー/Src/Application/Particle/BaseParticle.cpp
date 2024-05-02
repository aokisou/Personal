#include "BaseParticle.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/BaseEnemy.h"

void BaseParticle::Init(BaseObject* _obj, std::string _file)
{
	m_pOwner = _obj;
	m_tex.Load(_file);
}

void BaseParticle::Release()
{
}