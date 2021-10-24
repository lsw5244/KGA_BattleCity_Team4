#pragma once
#include "Config.h"

class PlayerStatus;
class PlayerTank;
class EnemyStatus;
class EnemyTankManager;
class StageManager;
class UIManager
{
private:
	PlayerStatus* playerStatus;
	EnemyStatus* enmeyStatus;

public:
	HRESULT Init();
	void SetData(PlayerTank* playerTank, StageManager* stageManager);
	void Update();
	void Render(HDC hdc);
	void Release();
};

