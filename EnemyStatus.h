#pragma once
#include "EnemyTanks.h"

class Image;
class EnemyTankManager;
class EnemyStatus
{
private:
	Image* enemyNumIcon;

	EnemyTankManager* enemyTanks;

	int totalEnmey;
	inline void SetEnemyTank(EnemyTankManager& enemyTank) { this->enemyTanks = &enemyTank; }
public:
	HRESULT Init(EnemyTankManager& enemyTank);
	void Update(EnemyTankManager& enemyTank);
	void Render(HDC hdc);
	void Release();
};

