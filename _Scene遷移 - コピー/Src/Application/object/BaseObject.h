#pragma once

class BaseObject
{
public:
	BaseObject() {}
	virtual ~BaseObject() {}

	virtual void Init() = 0;
	virtual void Action() = 0;
	virtual void Update(float _scrollX) = 0;
	virtual void Draw() = 0;
	virtual void Release() = 0;
	virtual void Reset() = 0;

	//���l
	Math::Vector2 GetPos() { return m_pos; }
	Math::Vector2 GetFuturePos() { return m_pos + m_move; }
	Math::Vector2 GetMovePow() { return m_move; }
	float GetHalfSize();

	//�摜�̃X�y�[�X
	virtual int GetSpaceWidthImg() { return 0; }
	virtual int GetSpaceHeightImg() { return 0; }

	virtual void MapHitX(float _posX, float _moveX);
	virtual void MapHitY(float _posY, float _moveY, bool _b);

	//�����t���O
	void SetFalseAlive() { m_bAlive = false; }
	bool GetAlive() { return m_bAlive; }

	//�����蔻��̎��ɒe���}�b�v�Ɠ������������
	virtual bool GetContent() { return false; }

protected:

	Math::Vector2 m_pos = {};
	Math::Vector2 m_move = {};
	Math::Matrix m_mat = {};
	
	int m_dir = 0;

	//�摜�T�C�Y
	int m_size = 0;
	//�摜�g�嗦
	float m_scale = 0.0f;

	bool m_bAlive = false;
private:
};