#pragma once
#include "EnemyTanks.h"
class FastMoveEnemyTank : public EnemyTanks
{
public:
	HRESULT Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
};

