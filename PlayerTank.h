#pragma once
#include "Tank.h"

class EnemyTanks;
class Image;
class AmmoManager;
class PlayerStatus;
class PlayerTank : public  GameObject
{
private:
	vector<EnemyTanks*> vecEnemyTank[4];
	Image* playerTank;
	int Level;
	int elapsedCount;
	bool isFire;
	float time;
	int life;
	MoveDir moveDir;
	TILE_INFO(*tileInfo)[TILE_COUNT];

	AmmoManager* ammoMgr;
	PlayerStatus* playerStatus;

	int CurrFrame(Image playerTank, int elapsedCount, int setCurr);
	void CollisionAndMove(MoveDir movedir);
	void PosReset(MoveDir movedir);

	Image* spawnEffect;
	float effectTime;
	int effectFrameX;
	int effectCount;
	bool frameUp;
	bool SpawnEffect();

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	inline void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank, int num) { this->vecEnemyTank[num] = vecEnemyTank; }
	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }
	inline RECT* GetRect() { return &shape; }
	inline void SetAmmoMgr(AmmoManager* mgr) { ammoMgr = mgr; }

};

