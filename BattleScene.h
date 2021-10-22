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
class BattleScene : public GameEntity
{
private:
	// �÷��̾� ����
	Tank* enemyTank;
	EnemyTankFactory* enemyTankFactory[4];
	PlayerTank* playerTank;

	// Ÿ�� ��������
	Image* sampleImage;
	// ��Ʋ ��׶���
	Image* battleBackGround;
	// ��� �̹���
	Image* backGround;

	ItemManager* itemManager;

	EnemyTankManager* enemyTankManager;

	TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT];

	HPEN pen, oPen;

	AmmoManager* ammoManager;

	UIManager* uIManager;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// �����ε�
	void Release();

	void Load();
};

