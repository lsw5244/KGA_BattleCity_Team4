#pragma once
#include "EnemyTanks.h"
class NormalEnemyTank : public EnemyTanks
{
public:
	void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank, int num) override;
	HRESULT Init() override;
	void Update() override;
	void Render(HDC hdc) override;
	void Release() override;
};

