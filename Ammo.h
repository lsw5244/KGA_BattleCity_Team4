#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Ammo : public GameObject
{
private:
	MoveDir dir;
	bool isAlive;
	bool renderBoomEffect;
	bool showCollider;

	float sec;

	Image* boomEffect;

	TILE_INFO(*tileInfo)[TILE_COUNT];

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
};

