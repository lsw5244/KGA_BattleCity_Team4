#pragma once
#include "Config.h"

class EnemyTanks;
class PlayerTank;
class AmmoManager;
class EnemyTankManager
{
private:
	vector<EnemyTanks*> vecEnemyTank;
	int totalEnemyNum;

	bool stopTimeCheck;
	float stopTime;
protected:
public:
	void NewEnemyTank(EnemyTanks* enemyTank, TILE_INFO(*tileInfo)[TILE_COUNT], PlayerTank& playerTank, int posX, AmmoManager* mgr, bool item = false);
	void SetVecEnemyTank();
	
	void BoomItemUse();
	inline void TimeItemUse() { this->stopTimeCheck = true; }
	vector<EnemyTanks*> GetVecEnemyTanks() { return vecEnemyTank; }
	inline int GetTotalEnemyNum() { return totalEnemyNum; }

	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();


};

