#pragma once
#include "GameEntity.h"
#include "Config.h"

class Tank;
class Image;
class PlayerTank;
class EnemyTankFactory;
class BattleScene : public GameEntity
{
private:
	// �÷��̾� ����
	Tank* enemyTank;
	EnemyTankFactory* enemyTankFactory[4];
	PlayerTank* playerTank;
	PlayerTank* playerTank1[10];

	// Ÿ�� ��������
	Image* sampleImage;
	// ��Ʋ ��׶���
	Image* battleBackGround;
	// ��� �̹���
	Image* backGround;

	bool addEnemy;

	TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT];

	HPEN pen, oPen;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// �����ε�
	void Release();

	void Load();
};

