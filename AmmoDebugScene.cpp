#include "AmmoDebugScene.h"

HRESULT AmmoDebugScene::Init()
{
    ammo = new Ammo;
    
    return S_OK;
}

void AmmoDebugScene::Update()
{
    ammo->Update();
}

void AmmoDebugScene::Render(HDC hdc)
{
    ammo->Render(hdc);
}

void AmmoDebugScene::Release()
{
    SAFE_RELEASE(ammo);
}
