#pragma once
#include "Tank.h"

class Image;
class PlayerTank : public  Tank
{
private:
	Image* playerTank;
	int Level;
	int elapsedCount;
	bool isFire;
	float time;


	TILE_INFO(*tileInfo)[TILE_COUNT];

	int CurrFrame(Image playerTank, int elapsedCount, int setCurr);
	void CollisionAndMove(MoveDir movedir);
	void PosReset(MoveDir movedir);


public:

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }
};

