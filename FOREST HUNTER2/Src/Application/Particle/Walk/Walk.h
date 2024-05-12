#pragma once

#include "../BaseParticle.h"

class Walk :public BaseParticle
{
public:
	Walk(){}
	~Walk(){}

	void Update(float _scrollX)override;
	void Draw()override;
};