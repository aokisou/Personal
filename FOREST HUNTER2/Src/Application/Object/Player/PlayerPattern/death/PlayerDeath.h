#pragma once

#include "../PlayerPattern.h"

class PlayerDeath :public PlayerPattern
{
public:
	PlayerDeath() {}
	~PlayerDeath() { Release(); }

	void Update()override;

	int GetStateType() override{ return playerDeath; }

	int GetMaxAnimeNum() { return 9; }
};