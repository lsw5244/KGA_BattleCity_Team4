#pragma once
#include "Tank.h"

class EnemyTanks;
class Image;
class AmmoManager;
class PlayerTank : public  GameObject
{
private:
	vector<EnemyTanks*> vecEnemyTank;
	Image* playerTank;
	int Level;
	int elapsedCount;
	bool isFire;

	int life;
	bool isBarrier;
	MoveDir moveDir;
	TILE_INFO(*tileInfo)[TILE_COUNT];

	AmmoManager* ammoMgr;

	int CurrFrame(Image playerTank, int elapsedCount, int setCurr);
	void CollisionAndMove(MoveDir movedir);
	void PosReset(MoveDir movedir);

	Image* shieldEffect;
	float shieldEffectTime;
	float shieldEffectDelay;

	Image* spawnEffect;
	float spawnEffectTime;
	int spawnEffectFrameX;
	int spawnEffectCount;
	bool spawnFrameUp;

	bool SpawnEffect();
	bool ShieldEffect();

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void LevelUp();
	inline void LifeUp() { if(life < 2) this->life++; }
	inline void ActiveBarrier() { this->shieldEffectTime = 0.0f; }
	inline void isHit();

	inline void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank) { this->vecEnemyTank = vecEnemyTank; }
	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }
	inline RECT* GetRect() { return &shape; }
	inline int GetLife() { return life; }
	inline void SetAmmoMgr(AmmoManager* mgr) { ammoMgr = mgr; }

};

