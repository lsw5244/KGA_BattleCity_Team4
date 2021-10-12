#pragma once
#include "Config.h"
#include "GameEntity.h"

enum class Terrain { Brick, IronBrick, Water, End };

#define TILE_SIZE	(8 / 2)
#define TILE_COUNT	(26)
#define SAMPLE_TILE_COUNT	(11*2)

typedef struct tagSampleTile
{
	RECT rc;
	int frameX, frameY;
	int width, height;
} SAMPLE_TILE_INFO;

typedef struct tagTile
{
	Terrain terrain;
	RECT selectRc;
	RECT rc[2][2];
	int frameX[2];
	int frameY[2];
	bool isDes[2][2];

} TILE_INFO;

class Image;
class TilemapToolScene : public GameEntity
{
private:
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

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void Save(int saveIndex = 0);
	void Load(int loadIndex = 0);

};

