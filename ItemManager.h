#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "PlayerTank.h"
class Item;
class ItemManager : public  GameEntity
{
private:
	vector<Item*> vecItems;
	vector<Item*>::iterator it;
	int eraseCount;
	TILE_INFO(*tileInfo)[TILE_COUNT];

protected:

public:
	void newItem(PlayerTank& playerTank, TILE_INFO(*tileInfo)[TILE_COUNT]);
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

