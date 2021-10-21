#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class PlayerTank;
class EnemyTanks;
class Ammo : public GameObject
{
private:
	MoveDir dir;
	bool isAlive;
	bool renderBoomEffect;
	bool showCollider;

	float sec;

	int boomEffectFrameX;

	Image* boomEffect;

	TILE_INFO(*tileInfo)[TILE_COUNT];

	TILE_INFO* hitTile1;
	TILE_INFO* hitTile2;

	bool isHit;

	RECT gameSceneRect;

	TankType type;

	PlayerTank* playerTank;
	vector<EnemyTanks*> vecEnemys;
	vector<EnemyTanks*>::iterator it;
public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void Fire(MoveDir dir, POINTFLOAT pos);
	void DestroyAmmo();

	void SetTileInfo(TILE_INFO(*info)[TILE_COUNT]) { this->tileInfo = info; }

	void AmmoHitCheck();
	void DestroyWall(int i, int j);
	void DestroyWall(TILE_INFO* tileInfo);
	void DestroyWall(TILE_INFO* tileInfo1, TILE_INFO* tileinfo2);
	void IronWallHitDestroyWall(TILE_INFO* tileInfo);
	void DestroyBase(int i, int j);

	inline bool GetIsAlive() { return isAlive; }
	inline bool GetRenderBoomEffect() { return renderBoomEffect; }
	inline void SetType(TankType type) { this->type = type; }
	inline void SetPlayerTank(PlayerTank* tank) { playerTank = tank; }
	inline void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank) { this->vecEnemys = vecEnemyTank; }

	bool CollisionEnter(RECT rc1, RECT rc2);
};