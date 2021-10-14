#pragma once
#include "GameEntity.h"

class Tank;
class Image;
class BattleScene : public GameEntity
{
private:
	// 플레이어 로켓
	Tank* enemyTank;

	// 배경 이미지
	Image* backGround;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// 오버로딩
	void Release();
};

