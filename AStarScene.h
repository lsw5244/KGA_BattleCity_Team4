#pragma once
#include "Config.h"
#include "GameEntity.h"

#define ASTAR_TILE_SIZE	64
#define	ASTAR_TILE_COUNT	12

enum AstarTileType
{
	Start, Dest, Wall, None, Walkable,
	Curr, Closed, Path, End
};

class AstarTile : public GameEntity
{
private:
	int idX, idY;
	RECT rc;
	POINTFLOAT center;

	float F;	// G + H
	float G;	// ��� ��忡�� ���� ������ �̵����
	float H;	// ���� ��忡�� ���������� ������

	AstarTile* parentTile;

	// Ÿ���� ������ ���� �ٸ� �������
	AstarTileType type;

	COLORREF color;
	HBRUSH hBrush;
	HBRUSH hTypeBrush[AstarTileType::End];
	HBRUSH hOldBrush;

public:
	virtual HRESULT Init() override;
	HRESULT Init(int idX, int idY);
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	int GetIdX() { return this->idX; }
	int GetIdY() { return this->idY; }

	void SetType(AstarTileType type);
	AstarTileType GetType() { return type; }

	void SetParentTile(AstarTile* parent) { this->parentTile = parent; }
	AstarTile* GetParentTile() { return this->parentTile; }

	void SetF(float f) { this->F = f; }
	float GetF() { return this->F; }
	void SetG(float g) { this->G = g; }
	float GetG() { return this->G; }
	void SetH(float h) { this->H = h; }
	float GetH() { return this->H; }

	POINTFLOAT GetCenter() { return this->center; }
};

class AStarScene : public GameEntity
{
private:
	AstarTile map[ASTAR_TILE_COUNT][ASTAR_TILE_COUNT];
	POINT startPoint;
	POINT destPoint;

	vector<AstarTile*>	openList;

	AstarTile* currTile;		// ���� ���� Ÿ��

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void FindPath();
	bool AddOpenList(AstarTile* currTile);
	AstarTile* GetMinFTile();
	void PrintPath();
};

