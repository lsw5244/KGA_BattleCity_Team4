#include "UIManager.h"
#include "PlayerStatus.h"
#include "EnemyStatus.h"
#include "Config.h"

HRESULT UIManager::Init()
{
    playerStatus = new PlayerStatus;
    playerStatus->Init();
    enmeyStatus = new EnemyStatus;
    enmeyStatus->Init();
    return S_OK;
}

void UIManager::SetData(PlayerTank* playerTank, StageManager* stageManager)
{
    playerStatus->SetData(playerTank);
    enmeyStatus->SetData(stageManager);
}

void UIManager::Update()
{
    playerStatus->Update();
    enmeyStatus->Update();
}

void UIManager::Render(HDC hdc)
{
    playerStatus->Render(hdc);
    enmeyStatus->Render(hdc);
}

void UIManager::Release()
{
    SAFE_DELETE(playerStatus);
    SAFE_DELETE(enmeyStatus);
}
