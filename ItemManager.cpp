#include "ItemManager.h"
#include "Item.h"
void ItemManager::newItem(PlayerTank& playerTank, EnemyTankManager& enemyTankManager, TILE_INFO(*tileInfo)[TILE_COUNT])
{
	this->tileInfo = tileInfo;
	vecItems.push_back(new Item);
	vecItems.back()->Init(playerTank, enemyTankManager);
}

HRESULT ItemManager::Init()
{
	vecItems.resize(5);
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
