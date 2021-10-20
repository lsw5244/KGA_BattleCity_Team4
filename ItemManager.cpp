#include "ItemManager.h"
#include "Item.h"
void ItemManager::newItem(PlayerTank& playerTank)
{
	vecItems.push_back(new Item);
	vecItems.back()->Init(playerTank);
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
			vecItems.erase(it);
			if (it == vecItems.end())break;
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
