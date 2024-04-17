#pragma once

#include "../BaseObject.h"

class Bullet:public BaseObject
{
public:
	Bullet(){ m_tex = nullptr; }
	~Bullet(){}

	void Init()override;
	void Action()override;
	void Update()override;
	void Draw()override;

	void SetPos(Math::Vector2 a_pos) { m_pos = a_pos; }
private:
};