#pragma once

#include "../PlayerPattern.h"

class PlayerJump :public PlayerPattern
{
public:
	PlayerJump() {}
	~PlayerJump(){ Release(); }

	void Update()override;

	int GetStateType()override { return playerJump; }

	int GetMaxAnimeNum() { return 1; }
};