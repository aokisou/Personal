#pragma once

#include "../BaseObject.h"

class Bullet:public BaseObject
{
public:
	Bullet() { Init(); }
	~Bullet(){}

	void Action()override;
	void Update()override;
	void Draw()override;

	void SetPos(Math::Vector2 a_pos) { m_pos = a_pos; }
	void SetDir(int _dir) { m_dir = _dir; }//ƒvƒŒƒCƒ„[‚ÌŒü‚«‚É”ò‚Ô‚æ‚¤‚É‚·‚é
private:
	void Init()override;

	int m_dir;
};