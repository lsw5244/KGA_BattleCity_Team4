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
class UIManager;
class StageManager;
class BattleScene : public GameEntity
{
private:
	// 플레이어 로켓
	Tank* enemyTank;
	EnemyTankFactory* enemyTankFactory[4];
	PlayerTank* playerTank;

	// 타일 샘플정보
	Image* sampleImage;
	// 배틀 백그라운드
	Image* battleBackGround;
	// 배경 이미지
	Image* backGround;

	ItemManager* itemManager;

	StageManager* stageManager;
	EnemyTankManager* enemyTankManager;

	TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT];

	HPEN pen, oPen;

	AmmoManager* ammoManager;

	UIManager* uIManager;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// 오버로딩
	void Release();

	int Load();
};

