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

	RECT bufferRc;
	POINTFLOAT bufferPos;
	TILE_INFO(*tileInfo)[TILE_COUNT];
public:

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }
};

