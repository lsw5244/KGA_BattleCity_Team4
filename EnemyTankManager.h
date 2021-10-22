#pragma once
#include "Config.h"

class EnemyTanks;
class PlayerTank;
class AmmoManager;
class ItemManager;
class EnemyTankManager
{
private:
	vector<EnemyTanks*> vecEnemyTank;
	int totalEnemyNum;

	bool stopTimeCheck;
	float stopTime;

	TILE_INFO(*tileInfo)[TILE_COUNT];
	PlayerTank* playerTank;
	AmmoManager* mgr;
	ItemManager* itemManager;

protected:
public:
	void NewEnemyTank(EnemyTanks* enemyTank, int posX, bool item = false);
	void SetVecEnemyTank();
	void SetData(TILE_INFO(*tileInfo)[TILE_COUNT], PlayerTank& playerTank, AmmoManager* mgr, ItemManager* itemManager);

	inline int GetEnemyTankVecSize() { return vecEnemyTank.size(); }
	void BoomItemUse();
	inline void TimeItemUse() { this->stopTimeCheck = true; }
	vector<EnemyTanks*> GetVecEnemyTanks() { return vecEnemyTank; }
	inline int GetTotalEnemyNum() { return totalEnemyNum; }

	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();


};

