#pragma once
#include "GameObject.h"
#include "Config.h"
#include "Image.h"
#include "ImageManager.h"
class EnemyTanks : public GameObject
{
private:
protected:
	void CollisionAndMove(MoveDir movedir);
	void PosReset(MoveDir movedir);
	TILE_INFO(*tileInfo)[TILE_COUNT];

	MoveDir movedir;
public:
	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }

	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

	EnemyTanks() {}
	virtual ~EnemyTanks();
};

