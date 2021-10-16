#include "EnemyTank.h"
#include "Image.h"
#include "Tank.h"

HRESULT EnemyTank::Init()
{
    haveItem = false;
    enemyTank = new Image;

    switch (enemyTankType)
    {
    case EnemyTankType::Normal:
        enemyTank->Init("Image/Enemy/Enemy.BMP", 128, 112, 8, 7, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(0);
        moveSpeed = 30;
        break;
    case EnemyTankType::FastMove:
        enemyTank->Init("Image/Enemy/Enemy.BMP", 128, 112, 8, 7, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(1);
        moveSpeed = 60;
        break;
    case EnemyTankType::QuickFire:
        enemyTank->Init("Image/Enemy/Enemy.BMP", 128, 112, 8, 7, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(2);
        moveSpeed = 30;
        break;
    case EnemyTankType::Big:
        enemyTank->Init("Image/Enemy/Enemy.BMP", 128, 112, 8, 7, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(3);
        moveSpeed = 30;
        break;
    case EnemyTankType::iNormal:
        enemyTank->Init("Image/Enemy/Enemy_Item.BMP", 128, 128, 8, 8, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(0);
        moveSpeed = 30;
        haveItem = true;
        break;
    case EnemyTankType::iFastMove:
        enemyTank->Init("Image/Enemy/Enemy_Item.BMP", 128, 128, 8, 8, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(2);
        moveSpeed = 60;
        haveItem = true;
        break;
    case EnemyTankType::iQuickFire:
        enemyTank->Init("Image/Enemy/Enemy_Item.BMP", 128, 128, 8, 8, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(4);
        moveSpeed = 30;
        haveItem = true;
        break;
    case EnemyTankType::iBig:
        enemyTank->Init("Image/Enemy/Enemy_Item.BMP", 128, 128, 8, 8, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(6);
        moveSpeed = 30;
        haveItem = true;
        break;
    }

    pos.x = 100;
    pos.y = 100;

    moveDir = Down;

    return S_OK;
}

void EnemyTank::Update()
{
    elapsedCount++;

    if (elapsedCount == 10)
        //if (elapsedCount == 0.2f)
    {
        if (haveItem)
        {
            if (enemyTank->GetCurrFrameY() % 2 == 0)
            {
                enemyTank->SetCurrFrameY(enemyTank->GetCurrFrameY() + 1);
            }
            else if (enemyTank->GetCurrFrameY() % 2 != 0)
            {
                enemyTank->SetCurrFrameY(enemyTank->GetCurrFrameY() - 1);
            }
        }
        elapsedCount = 0;
    }



    if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_LEFT) /*&& pos.x > 0*/)
    {
        moveDir = Left;
        Move(MoveDir::Left);
    }
    else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_RIGHT) /*&& pos.x < WIN_SIZE_X*/)
    {
        moveDir = Right;
        Move(MoveDir::Right);
    }
    else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_UP) /*&& pos.y > 0*/)
    {
        moveDir = Up;
        Move(MoveDir::Up);
    }
    else if (Singleton<KeyManager>::GetSingleton()->IsStayKeyDown(VK_DOWN) /*&& pos.y < WIN_SIZE_Y*/)
    {
        moveDir = Down;
        Move(MoveDir::Down);
    }
}

void EnemyTank::Render(HDC hdc)
{

    enemyTank->Render(hdc, pos.x, pos.y, enemyTank->GetCurrFrameX(), enemyTank->GetCurrFrameY());
}

void EnemyTank::Release()
{
    for (int i = 0; i < 8; i++)
    {
        SAFE_RELEASE(enemyTank);
    }
}

void EnemyTank::Move(MoveDir dir)
{
    switch (dir)
    {
    case Left:
        pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();

        elapsedCount2++;
        if (elapsedCount2 == 2)
        {
            if (enemyTank->GetCurrFrameX() % 2 == 0)
            {
                enemyTank->SetCurrFrameX(3);
            }
            else if (enemyTank->GetCurrFrameX() % 2 != 0)
            {
                enemyTank->SetCurrFrameX(2);
            }
            elapsedCount2 = 0;
        }
        break;
    case Right:
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();

        elapsedCount2++;
        if (elapsedCount2 == 2)
        {
            if (enemyTank->GetCurrFrameX() % 2 == 0)
            {
                enemyTank->SetCurrFrameX(7);
            }
            else if (enemyTank->GetCurrFrameX() % 2 != 0)
            {
                enemyTank->SetCurrFrameX(6);
            }
            elapsedCount2 = 0;
        }
        break;
    case Up:
        pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();

        elapsedCount2++;
        if (elapsedCount2 == 2)
        {
            if (enemyTank->GetCurrFrameX() % 2 == 0)
            {
                enemyTank->SetCurrFrameX(1);
            }
            else if (enemyTank->GetCurrFrameX() % 2 != 0)
            {
                enemyTank->SetCurrFrameX(0);
            }
            elapsedCount2 = 0;
        }
        break;
    case Down:
        pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();

        elapsedCount2++;
        if (elapsedCount2 == 2)
        {
            if (enemyTank->GetCurrFrameX() % 2 == 0)
            {
                enemyTank->SetCurrFrameX(5);
            }
            else if (enemyTank->GetCurrFrameX() % 2 != 0)
            {
                enemyTank->SetCurrFrameX(4);
            }
            elapsedCount2 = 0;
        }
        break;
    }

}
