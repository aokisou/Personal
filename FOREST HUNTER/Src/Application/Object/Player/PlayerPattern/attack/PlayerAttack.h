#pragma once

#include "../PlayerPattern.h"

class PlayerAttack :public PlayerPattern
{
public:
	PlayerAttack() {}
	~PlayerAttack() { Release(); }

	void Update()override;

	int GetStateType() override { return playerAttack; }

	int GetMaxAnimeNum() { return 5; }
private:
};