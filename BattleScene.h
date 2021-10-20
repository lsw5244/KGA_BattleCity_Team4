#pragma once
#include "GameEntity.h"
#include "Config.h"

class Tank;
class Image;
class PlayerTank;
class EnemyTanks;
class EnemyTankFactory;
class AmmoManager;
class ItemManager;
class EnemyTankManager;
class BattleScene : public GameEntity
{
private:
	// 플레이어 로켓
	Tank* enemyTank;
	EnemyTankFactory* enemyTankFactory[4];
	PlayerTank* playerTank;

	vector<EnemyTanks*> vecEnemyTank[4];

	// 타일 샘플정보
	Image* sampleImage;
	// 배틀 백그라운드
	Image* battleBackGround;
	// 배경 이미지
	Image* backGround;

	ItemManager* itemManager;

	EnemyTankManager* enemyTankManager;

	TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT];

	HPEN pen, oPen;

	AmmoManager* ammoMgr;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// 오버로딩
	void Release();

	void Load();
};

