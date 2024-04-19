#include "map.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include "../utility/utility.h"

#define MapSize 64			//マップサイズ

void Map::Init()
{
	for (int i = 0; i < m_pos.size(); i++)
	{
		for (int j = 0; j < m_pos[i].size(); j++)
		{
			m_pos[i][j] = { j * 64.0f - SCREEN::width / Half,(i * 64.0f - SCREEN::height / Half) * Reverse };
		}
	}

	m_Size = MapSize;

	m_tex.Load("Texture/MapTile2.png");
}

void Map::Update(float _scrollX)
{
	for (int i = 0; i < m_pos.size(); i++)
	{
		for (int j = 0; j < m_pos[i].size(); j++)
		{
			m_mat[i][j] = Math::Matrix::CreateTranslation(m_pos[i][j].x - _scrollX, m_pos[i][j].y, 0);
		}
	}
}

void Map::Draw()
{
	for (int i = 0; i < m_pos.size(); i++)
	{
		for (int j = 0; j < m_pos[i].size(); j++)
		{
			switch (m_data[i][j])
			{
			case Block0:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(0, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block1:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block1, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block2:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block2, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block3:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block3, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block4:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block4, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block5:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block5, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block6:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block6, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block7:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block7, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block8:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block8, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block9:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block9, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;

			case Block10:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block10 - Block10, m_Size, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block11:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block11 - Block10, m_Size, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block12:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block12 - Block10, m_Size, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block13:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block13 - Block10, m_Size, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block14:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block14 - Block10, m_Size, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block15:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block15 - Block10, m_Size, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block16:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block16 - Block10, m_Size, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			case Block17:
				SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
				SHADER.m_spriteShader.DrawTex(&m_tex, 0, 0, &Math::Rectangle(m_Size * Block17 - Block10, m_Size, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
				break;
			default:
				break;
			}
		}
	}
}

void Map::MapSrc(int _i)
{
	//if (_i > HalfBlock10)
	//{
	//	SHADER.m_spriteShader.SetMatrix(m_mat[i][j]);
	//	SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, &Math::Rectangle(0, 0, m_Size, m_Size), &Math::Color(1, 1, 1, 1));
	//}
}

void Map::SetMapData(std::string _filenme)
{
	std::ifstream ifs(_filenme);

	std::string str, field;

	while (getline(ifs, str))
	{
		std::istringstream iss(str);

		std::vector<Math::Matrix> m;
		std::vector<Math::Vector2> p;
		std::vector<int> n;			

		while (getline(iss, field, ','))
		{
			Math::Matrix m1;
			Math::Vector2 p1;
			int n1 = stoi(field);

			m.push_back(m1);
			p.push_back(p1);
			n.push_back(n1);
		}
		m_mat.push_back(m);
		m_pos.push_back(p);
		m_data.push_back(n);
	}

	ifs.close();

	Init();
}

void Map::Release()
{
	m_data.clear();
	m_pos.clear();
	m_mat.clear();
}

int Map::GetHalfSize()
{
	return m_Size / Half;
}