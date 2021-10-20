#pragma once
#include "EnemyTanks.h"
class FastShootEnemyTank : public EnemyTanks
{
public:
	HRESULT Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	void AutoFire() override;
};

