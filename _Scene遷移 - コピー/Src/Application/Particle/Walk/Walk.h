#pragma once

#include "../BaseParticle.h"

class Walk :public BaseParticle
{
public:
	Walk(){}
	~Walk(){}

	void Update()override;
	void Draw()override;
};