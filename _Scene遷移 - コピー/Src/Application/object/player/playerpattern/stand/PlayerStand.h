#pragma once

#include "../PlayerPattern.h"

class PlayerStand :public PlayerPattern
{
public:
	PlayerStand() {}
	~PlayerStand() { Release(); }

	void Update()override;

	int GetStateType() override { return playerStand; }
private:
};