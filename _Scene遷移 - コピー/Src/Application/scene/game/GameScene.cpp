#include "GameScene.h"
#include "../../object/player/Player.h"
#include "../../object/enemy/BaseEnemy.h"
#include "../../hit/Hit.h"
#include "../../map/Map.h"
#include "../../map/MapHit.h"
#include<vector>
#include "../../utility/utility.h"

int GameScene::Update()
{
	m_player->Action();
	m_enemy->Action();

	m_hit->BltEmyHit();	//�e�̓����蔻�肩�炷��
	m_hit->PlyEmyHit();

	m_mapHit->MapObjHit(m_map, m_player);
	m_mapHit->MapObjHit(m_map, m_enemy);

	m_player->Update();
	if (!m_player->GetbAlive())
	{
		return ChangeScene::result;
	}
	m_enemy->Update();
	m_map->Update();

	return ChangeScene::no;
}

void GameScene::Draw()
{
	m_map->Draw();
	m_enemy->Draw();
	m_player->Draw();
}

void GameScene::Init()
{
	bool bLoad = false;

	bLoad = m_playerTex.Load("Texture/player.png");
	_ASSERT_EXPR(bLoad, L"�v���C���[�摜�ǂݍ��݃G���[");

	bLoad = m_enemyTex.Load("Texture/enemy.png");
	_ASSERT_EXPR(bLoad, L"�G�l�~�[�摜�ǂݍ��݃G���[");

	bLoad = m_mapTex.Load("Texture/enemy.png");
	_ASSERT_EXPR(bLoad, L"�}�b�v�摜�ǂݍ��݃G���[");

	m_player = new Player;
	m_enemy = new BaseEnemy;
	m_hit = new Hit;
	m_map = new Map;
	m_mapHit = new MapHit;

	m_player->Init();
	m_enemy->Init();
	m_hit->Init();

	m_map->SetMapData(m_mapNme[0]);
	m_map->SetTexture(&m_playerTex);

	m_player->SetTexture(&m_playerTex);
	m_enemy->SetTexture(&m_enemyTex);

	((Player*)m_player)->SetOwner(this);
	m_hit->SetOwner(this);
}

void GameScene::Release()
{
	delete m_player;
	delete m_enemy;
	delete m_hit;
	delete m_map;
}