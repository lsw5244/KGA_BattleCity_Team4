#include "Item.h"
#include "Image.h"
#include "TimerManager.h"
HRESULT Item::Init(PlayerTank& playerTank)
{
	ImageManager::GetSingleton()->AddImage("Image/item/items.bmp", 96, 16, 6, 1, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/item/items.bmp");
	SetPlyaerRect(playerTank);
	srand((unsigned int)time(nullptr));

	aliveTime = renderTime = 0.0f;
	itemNum = rand() % 6;
	pos.x = 16 + ((rand() % 26) * 8);
	pos.y = 8 + ((rand() % 26) * 8)+1;
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
	aliveTime += TimerManager::GetSingleton()->GetDeltaTime();
	renderTime += TimerManager::GetSingleton()->GetDeltaTime();
	RECT rc;
	if (IntersectRect(&rc, &shape, playerRect))cout << "�浹" << endl;
	if (aliveTime >= 2.0f) {
		Release();
		return true;
	}
	return false;
}

void Item::Render(HDC hdc)
{
	if (renderTime <= 0.1f) {
		img->Render(hdc, pos.x, pos.y, itemNum, 0);
		
	} else if(renderTime >= 0.2f) renderTime = 0.0f;
}

void Item::Release()
{
}
