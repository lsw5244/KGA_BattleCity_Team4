#include "UIManager.h"
#include "PlayerStatus.h"
#include "EnemyStatus.h"

HRESULT UIManager::Init(PlayerTank& playerTank, EnemyTankManager& enemyTank)
{
    playerStatus = new PlayerStatus;
    playerStatus->Init(playerTank);

    enmeyStatus = new EnemyStatus;
    enmeyStatus->Init(enemyTank);
    return S_OK;
}

void UIManager::Update(PlayerTank& playerTank, EnemyTankManager& enemyTank)
{
    playerStatus->Update(playerTank);
    enmeyStatus->Update(enemyTank);
}

void UIManager::Render(HDC hdc)
{
    playerStatus->Render(hdc);
    enmeyStatus->Render(hdc);
}

void UIManager::Release()
{
}
