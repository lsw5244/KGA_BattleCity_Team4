#include "Item.h"
#include "Image.h"
#include "TimerManager.h"
#include "EnemyTankManager.h"
#include "ItemManager.h"

HRESULT Item::Init(PlayerTank& playerTank, EnemyTankManager& enemyTankManager, ItemManager& itemManager)
{
	img = ImageManager::GetSingleton()->FindImage("Image/item/items.bmp");
	pointImage = ImageManager::GetSingleton()->FindImage("Image/Icon/Point.bmp");
	SetPlyaerRect(playerTank);
	SetPlyaer(playerTank);
	SetEnemyTankManager(enemyTankManager);
	SetItemManager(itemManager);
	srand((unsigned int)time(nullptr));
	pointImageRender = 0;
	collCheck = false;
	aliveTime = renderTime = 0.0f;
	itemNum = rand() % 6;
	pointImageTime = 0.0f;
	int posX;
	int posY;
	do {
		posX = rand() % 25;
		posY = rand() % 25;
	} while ((10 > posX < 15) && posY > 22);
	pos.x = 16 + ((posX + 1) * 8);
	pos.y = 8 + ((posY + 1) * 8);
	
	switch (itemNum) {
	case 0:
		itemState = ItemState::Barrier;
		break;
	case 1:
		itemState = ItemState::TimeStop;
		break;
	case 2:
		itemState = ItemState::Shovel;
		break;
	case 3:
		itemState = ItemState::Star;
		break;
	case 4:
		itemState = ItemState::Boom;
		break;
	case 5:
		itemState = ItemState::Life;
		break;
	}
	shape.left = pos.x - 7;
	shape.top = pos.y - 7;
	shape.right = pos.x + 7;
	shape.bottom = pos.y + 7;

	return S_OK;
}

bool Item::ItemUpdate()
{
	if (collCheck)
	{
		Release();
		return true;
	}
	aliveTime += TimerManager::GetSingleton()->GetDeltaTime();
	renderTime += TimerManager::GetSingleton()->GetDeltaTime();
	RECT rc;
	if (IntersectRect(&rc, &shape, playerRect))
	{
		switch (itemState) {
		case ItemState::Barrier:
			playerTank->ActiveBarrier();
			break;
		case ItemState::TimeStop:
			enemyTankManager->TimeItemUse();
			break;
		case ItemState::Shovel:
			itemManager->ActiveShove();
			break;
		case ItemState::Star:
			playerTank->LevelUp();
			break;
		case ItemState::Boom:
			enemyTankManager->BoomItemUse();
			break;
		case ItemState::Life:
			playerTank->LifeUp();
			break;
		}
		collCheck = true;
	}
	if (aliveTime >= 20 || collCheck) {
		pointImageRender = true;
		pointImageTime += TimerManager::GetSingleton()->GetDeltaTime();
		if (pointImageTime >= 0.4f) {
			Release();
			return true;
		}
	}
	return false;
}

void Item::Render(HDC hdc)
{
	if (!pointImageRender) {
		if (renderTime <= 0.1f) img->Render(hdc, pos.x, pos.y, itemNum, 0);
		else if (renderTime >= 0.2f) renderTime = 0.0f;
	}
	else {
		if (pointImageTime < 0.4f) {
			pointImage->Render(hdc, pos.x, pos.y, 4, 0);
		}
	}

}

void Item::Release()
{
}
