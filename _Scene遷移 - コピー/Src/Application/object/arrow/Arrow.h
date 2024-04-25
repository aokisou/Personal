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

	void SetPos(Math::Vector2 _pos) { m_pos = _pos; }
	void SetScale(float _scale) { m_scale = _scale; }
	void SetDir(int _dir) { m_dir = _dir; }//ÉvÉåÉCÉÑÅ[ÇÃå¸Ç´Ç…îÚÇ‘ÇÊÇ§Ç…Ç∑ÇÈ
	void SetTex(KdTexture* _pTex) { m_pTex = _pTex; }

	bool GetContent()override { return true; }

	float GetDmg() { return abs(m_move.x); }

	int GetSpaceWidthImg(){ return (int)(2 * m_scale); }
	int GetSpaceHeightImg(){ return (int)(6 * m_scale); }
private:
	void Init()override;

	int m_dir;

	float m_angle;

	float m_accelerlation;

	KdTexture* m_pTex;
};