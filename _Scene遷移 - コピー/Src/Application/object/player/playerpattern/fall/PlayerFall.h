#pragma once

#include "../PlayerPattern.h"

class PlayerFall :public PlayerPattern
{
public:
	PlayerFall() {}
	~PlayerFall() { Release(); }

	void Update()override;

	int GetStateType() override { return playerFall; }

	int GetMaxAnimeNum() { return 1; }
private:
};