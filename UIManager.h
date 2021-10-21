#pragma once
#include "Config.h"

class PlayerStatus;
class PlayerTank;
class EnemyStatus;
class EnemyTankManager;
class UIManager
{
private:
	PlayerStatus* playerStatus;
	EnemyStatus* enmeyStatus;

public:
	HRESULT Init(PlayerTank& playerTank, EnemyTankManager& enemyTank);
	void Update(PlayerTank& playerTank, EnemyTankManager& enemyTank);
	void Render(HDC hdc);
	void Release();
};

