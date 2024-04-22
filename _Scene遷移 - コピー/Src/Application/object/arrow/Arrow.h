#pragma once

#include "../BaseObject.h"

class Arrow:public BaseObject
{
public:
	Arrow() { Init(); }
	~Arrow() { Release(); }

	void Action()override;
	void Update(float _scrollX)override;
	void Draw()override;
	void Release()override {}

	void SetPos(Math::Vector2 a_pos) { m_pos = a_pos; }
	void SetDir(int _dir) { m_dir = _dir; }//ƒvƒŒƒCƒ„[‚ÌŒü‚«‚É”ò‚Ô‚æ‚¤‚É‚·‚é
	void SetTex(KdTexture* _pTex) { m_pTex = _pTex; }

	bool GetContent()override { return true; }

	float GetDmg() { return abs(m_move.x); }

	int GetSpaceWidthImg(){ return 3; }
	int GetSpaceHeightImg(){ return 3; }
private:
	void Init()override;

	int m_dir;

	float m_angle;

	float m_accelerlation;

	KdTexture* m_pTex;
};