#pragma once
#include "GameEntity.h"
#include "Config.h"

class Tank;
class Image;
class PlayerTank;
class BattleScene : public GameEntity
{
private:
	// �÷��̾� ����
	Tank* enemyTank;

	PlayerTank* playerTank;

	// Ÿ�� ��������
	Image* sampleImage;
	// ��Ʋ ��׶���
	Image* battleBackGround;
	// ��� �̹���
	Image* backGround;

	

	TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT];

	HPEN pen, oPen;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// �����ε�
	void Release();

	void Load();
};

