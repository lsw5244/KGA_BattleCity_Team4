#pragma once
#include "GameEntity.h"

class EnemyManager;
class Tank;
class Image;
class BattleScene : public GameEntity
{
private:
	// �÷��̾� ����
	Tank* enemyTank;

	// �� UFO
	EnemyManager* enemyMgr;

	// ��� �̹���
	Image* backGround;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// �����ε�
	void Release();
};

