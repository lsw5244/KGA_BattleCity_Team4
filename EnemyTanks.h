#pragma once
#include "GameObject.h"
#include "Config.h"
#include "Image.h"
#include "ImageManager.h"
class EnemyTanks : public GameObject
{
private:
protected:
	void CollisionAndMove(MoveDir moveDir);
	void PosReset(MoveDir moveDir);
	int CurrFrame(Image enemyTank, int* elapsedCount, int setCurr);
	MoveDir AutoMove(MoveDir moveDir, POINTFLOAT pos);
	TILE_INFO(*tileInfo)[TILE_COUNT];
	MoveDir movedir;
	int elapsedCount;
	float time;

public:
	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }

	virtual HRESULT TankInit();
	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

	EnemyTanks() {}
	virtual ~EnemyTanks();
};

