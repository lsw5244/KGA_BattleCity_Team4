#pragma once
#include "EnemyTanks.h"

class Image;
class EnemyTankManager;
class StageManager;
class EnemyStatus
{
private:
	Image* enemyNumIcon;
	StageManager* stageManager;

	int totalEnmey;
public:
	inline void SetData(StageManager* stageManager) { this->stageManager = stageManager; }
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

