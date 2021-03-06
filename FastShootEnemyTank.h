#pragma once
#include "EnemyTanks.h"
class FastShootEnemyTank : public EnemyTanks
{
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual ~FastShootEnemyTank() = default;
	void AutoFire() override;
};

