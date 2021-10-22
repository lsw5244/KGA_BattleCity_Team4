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
	int elapsedCount;
	bool isFire;

	int life;
	bool isBarrier;
	MoveDir moveDir;
	TILE_INFO(*tileInfo)[TILE_COUNT];

	AmmoManager* ammoMgr;

	void SetFrame();
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

	
	Image* deadEffect;
	float deadEffecttime;
	int deadEffectfreamX;
	bool isdead;

	int Level;
	int maxAmmo;
	float ammoSpeed;

	bool fastAmmoReady;

	bool SpawnEffect();
	bool ShieldEffect();

	TankType type;
public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void LevelUp();
	inline void LifeUp() { if(life < 2) this->life++; }
	inline void ActiveBarrier() { this->shieldEffectTime = 0.0f; }
	inline void Setisdead(bool isdead) { if(shieldEffectTime >= 10.0f)this->isdead = isdead;}

	inline void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank) { this->vecEnemyTank = vecEnemyTank; }
	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }
	inline RECT* GetRect() { return &shape; }
	inline int GetLife() { return life; }
	inline void SetAmmoMgr(AmmoManager* mgr) { ammoMgr = mgr; }
	inline void SetFastAmmoReady(bool ready) { fastAmmoReady = ready; }

};

