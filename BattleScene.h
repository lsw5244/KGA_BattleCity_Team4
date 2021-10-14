#pragma once
#include "GameEntity.h"

class Tank;
class Image;
class BattleScene : public GameEntity
{
private:
	// �÷��̾� ����
	Tank* enemyTank;

	// ��� �̹���
	Image* backGround;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// �����ε�
	void Release();
};

