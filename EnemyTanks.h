#pragma once
#include "GameObject.h"
#include "Config.h"
#include "Image.h"
#include "ImageManager.h"
#include <tuple>

class EnemyTanks : public GameObject
{
private:
protected:
	void CollisionAndMove(MoveDir moveDir);
	void PosReset(MoveDir moveDir);
	void TankUpdate();
	int CurrFrame(Image enemyTank, int* elapsedCount, int setCurr);
	tuple<MoveDir, bool> AutoMove(MoveDir moveDir, POINTFLOAT pos);
	TILE_INFO(*tileInfo)[TILE_COUNT];
	MoveDir movedir;
	int elapsedWay;
	int elapsedCount;
	float time;
	Image* spawnEffect;
	float effectTime;
	int effectFrameX;
	int effectCount;
	bool frameUp;
	bool SpawnEffect();

public:
	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }

	HRESULT TankInit();
	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

	EnemyTanks() {}
	virtual ~EnemyTanks();
};

