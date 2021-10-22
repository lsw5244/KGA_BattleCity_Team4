#pragma once
#include "Tank.h"

class EnemyTanks;
class Image;
class AmmoManager;
class ItemManager;
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
	ItemManager* itemManager;
	AmmoManager* ammoManager;

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

	bool fastAmmoReady;

	void SetFrame();
	bool SpawnEffect();
	bool ShieldEffect();

	bool SuperPlayerMode;
	TankType type;
public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void LevelUp();
	void PlayerTankReset();
	void SetData(TILE_INFO(*tileInfo)[TILE_COUNT], AmmoManager* mgr, ItemManager* itemManager);

	inline void LifeUp() { if(life < 10) this->life++; }
	inline void ActiveBarrier() { this->shieldEffectTime = 0.0f; }
	inline void Setisdead(bool isdead) { if(shieldEffectTime >= 10.0f)this->isdead = isdead;}

	inline void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank) { this->vecEnemyTank = vecEnemyTank; }
	inline RECT* GetRect() { return &shape; }
	inline int GetLife() { return life; }
	inline void SetFastAmmoReady(bool ready) { fastAmmoReady = ready; }

};

