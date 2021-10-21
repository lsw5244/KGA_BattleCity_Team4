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
protected:
public:
	void NewEnemyTank(EnemyTanks* enemyTank, TILE_INFO(*tileInfo)[TILE_COUNT], PlayerTank& playerTank, int posX, AmmoManager* mgr, bool item = false);
	vector<EnemyTanks*> GetVecEnemyTanks() { return vecEnemyTank; }
	void SetVecEnemyTank();
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline int GetTotalEnemyNum() { return totalEnemyNum; }
};

