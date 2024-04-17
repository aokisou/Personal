#pragma once

#include "Pattern.h"

class PlayerDeath :public PlayerPattern
{
public:
	PlayerDeath() {}
	~PlayerDeath() { Release(); }

	void Update()override;

	int GetStateType() override{ return death; }
};