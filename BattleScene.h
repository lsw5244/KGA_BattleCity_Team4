#pragma once
#include "GameEntity.h"

class Image;
class BattleScene : public GameEntity
{
private:

	// ��� �̹���
	Image* backGround;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);	// �����ε�
	void Release();
};

