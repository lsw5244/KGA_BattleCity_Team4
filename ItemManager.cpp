#include "ItemManager.h"
#include "Item.h"
void ItemManager::newItem()
{
	vecItems.push_back(new Item);
	vecItems.back()->Init(*playerTank, *enemyTankManager);
}

HRESULT ItemManager::Init()
{
	itemManager = this;
	eraseCount = 0;
	return S_OK;
}

void ItemManager::Update()
{
	for (vector<Item*>::iterator it = vecItems.begin();
		it != vecItems.end();)
	{
		if ((*it)->ItemUpdate()) 
		{
			SAFE_RELEASE((*it));
			it = vecItems.erase(it);
		}
		else {
			it++;
		}
	}
}

void ItemManager::Render(HDC hdc)
{
	for (vector<Item*>::iterator it = vecItems.begin();
		it != vecItems.end();
		it++)
	{
		(*it)->Render(hdc);
	}
}

void ItemManager::Release()
{
}

void ItemManager::Setdata(PlayerTank& playerTank, EnemyTankManager& enemyTankManager, TILE_INFO(*tileInfo)[TILE_COUNT])
{
	this->playerTank = &playerTank;
	this->enemyTankManager = &enemyTankManager;
	this->tileInfo = tileInfo;
}
