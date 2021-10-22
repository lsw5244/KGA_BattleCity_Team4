#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "PlayerTank.h"
#include "EnemyTankManager.h"
class Item;
class ItemManager : public  GameEntity
{
private:
	vector<Item*> vecItems;
	vector<Item*>::iterator it;
	ItemManager* itemManager;
	int eraseCount;

	TILE_INFO(*tileInfo)[TILE_COUNT];
	PlayerTank* playerTank;
	EnemyTankManager* enemyTankManager;

protected:

public:
	void newItem();
	void Setdata(PlayerTank& playerTank, EnemyTankManager& enemyTankManager, TILE_INFO(*tileInfo)[TILE_COUNT]);
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

