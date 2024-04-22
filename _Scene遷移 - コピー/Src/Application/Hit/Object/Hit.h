#pragma once

class GameScene;

class Hit
{
public:
	Hit(){ m_pOwner = nullptr; }
	~Hit(){}

	void PlyEmyHit();
	void ArrEmyHit();

	void SetOwner(GameScene* _pOwner) { m_pOwner = _pOwner; }
private:
	GameScene* m_pOwner;
};