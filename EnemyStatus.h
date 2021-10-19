#pragma once
#include "EnemyTanks.h"

class Image;
class EnemyStatus : public EnemyTanks
{
private:
	Image* enemyNumIcon;

public:
	HRESULT Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	void EnemyIconRender(HDC hdc, int enemyNum);
};

