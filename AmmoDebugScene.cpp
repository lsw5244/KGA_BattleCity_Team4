#include "AmmoDebugScene.h"
#include "CommonFunction.h"
HRESULT AmmoDebugScene::Init()
{
    SetWindowSize(10, 10, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);

    ammo = new Ammo;
    ammo->Init();
    return S_OK;
}

void AmmoDebugScene::Update()
{
    ammo->Update();
}

void AmmoDebugScene::Render(HDC hdc)
{
    //Rectangle(hdc, 10, 10, 20, 20);

    ammo->Render(hdc);
}

void AmmoDebugScene::Release()
{
    SAFE_RELEASE(ammo);
}
