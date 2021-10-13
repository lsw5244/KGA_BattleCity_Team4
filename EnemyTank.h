#pragma once
#include "Tank.h"

class Image;
class EnemyTank : public Tank
{
private:
	Image* enemyTank;

	EnemyTankType enemyTankType;

	int elapsedCount;

	bool haveItem;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Move(MoveDir dir);

	inline void SetMoveDir(MoveDir moveDir) { this->moveDir = moveDir; }
	inline void SetEnemyTankType(EnemyTankType enemyTankType) {	this->enemyTankType = enemyTankType; }
};

