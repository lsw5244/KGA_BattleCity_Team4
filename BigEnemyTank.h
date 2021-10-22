#pragma once
#include "EnemyTanks.h"
class BigEnemyTank : public EnemyTanks
{
private:
	int bigTankFrame;
	bool renderChange;
public:
	HRESULT Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;

	void AutoFire() override;
};

