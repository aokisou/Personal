#pragma once

#include "../PlayerPattern.h"

class PlayerGetHit :public PlayerPattern
{
public:
	PlayerGetHit() {}
	~PlayerGetHit() { Release(); }

	void Update()override;

	int GetStateType() override { return playerGetHit; }

	int GetMaxAnimeNum() { return 2; }
private:
};