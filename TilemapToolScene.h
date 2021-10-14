#pragma once
#include "Config.h"
#include "GameEntity.h"

//enum class Terrain {
//	Brick, IronBrick, Water, Forest, Soild, Empty,
//	Base, BaseDes,
//	End
//};


//#define TILE_COUNT	(26)
typedef struct tagSampleTile
{
	RECT rc;
	int frameX, frameY;
	int width, height;
} SAMPLE_TILE_INFO;
//
//typedef struct tagTile
//{
//	Terrain terrain;
//	RECT selectRc;
//	RECT rc[2][2];
//	int frameX[2];
//	int frameY[2];
//	bool isDes[2][2];
//} TILE_INFO;

class Image;
class TilemapToolScene : public GameEntity
{
private:
	HPEN pen, oPen;

	SAMPLE_TILE_INFO sampleTileInfo[SAMPLE_TILE_COUNT][SAMPLE_TILE_COUNT];
	TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT];
	Image* sampleImage;
	Image* bin;
	SAMPLE_TILE_INFO selectedSampleTile;

	bool check;
	bool mouseCheck;
	POINT mousePos[2];
	POINTFLOAT view;
	POINT mouse;

	void SetTerrain(TILE_INFO* tileInfo, int x, int y);

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Save();
	void Load();

};

