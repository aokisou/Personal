#pragma once

#include "../BaseScene.h"

class Result :public BaseScene
{
public:
	Result(int _fps) { m_maxFps = _fps;}
	~Result() { Release(); }

	int Update()override;
	void Draw()override;
	void Init()override;

private:
	void Release()override;
};