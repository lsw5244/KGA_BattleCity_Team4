#pragma once
#include "GameEntity.h"

class Image;
class BattleScene : public GameEntity
{
private:

	// 배경 이미지
	Image* backGround;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// 오버로딩
	void Release();
};

