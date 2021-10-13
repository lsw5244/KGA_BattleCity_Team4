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
        break;
    case EnemyTankType::FastMove:
        enemyTank->Init("Image/Enemy/Enemy.BMP", 128, 112, 8, 7, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(1);
        break;
    case EnemyTankType::QuickFire:
        enemyTank->Init("Image/Enemy/Enemy.BMP", 128, 112, 8, 7, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(2);
        break;
    case EnemyTankType::Big:
        enemyTank->Init("Image/Enemy/Enemy.BMP", 128, 112, 8, 7, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(3);
        break;
    case EnemyTankType::iNormal:
        enemyTank->Init("Image/Enemy/Enemy_Item.BMP", 128, 128, 8, 8, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(0);
        haveItem = true;
        break;
    case EnemyTankType::iFastMove:
        enemyTank->Init("Image/Enemy/Enemy_Item.BMP", 128, 128, 8, 8, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(2);
        haveItem = true;
        break;
    case EnemyTankType::iQuickFire:
        enemyTank->Init("Image/Enemy/Enemy_Item.BMP", 128, 128, 8, 8, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(4);
        haveItem = true;
        break;
    case EnemyTankType::iBig:
        enemyTank->Init("Image/Enemy/Enemy_Item.BMP", 128, 128, 8, 8, true, RGB(255, 0, 255));
        enemyTank->SetCurrFrameY(6);
        haveItem = true;
        break;
    }


    //for (int i = 0; i < 4; i++)
    //{
    //    enemyTank[i] = new Image;
    //    enemyTank[i]->Init("Image/Enemy/Enemy.BMP", 512, 448, 8, 7, true, RGB(255, 0, 255));
    //    enemyTank[i]->SetCurrFrameY(i);
    //}
    //for (int i = 4; i < 8; i++)
    //{
    //    enemyTank[i] = new Image;
    //    enemyTank[i]->Init("Image/Enemy/Enemy_Item.BMP", 512, 512, 8, 8, true, RGB(255, 0, 255));
    //    enemyTank[i]->SetCurrFrameY((i - 4) * 2);
    //}

    pos.x = 100;
    pos.y = 100;

    moveSpeed = 1;

    moveDir = Down;

    elapsedCount = 0;

    return S_OK;
}

void EnemyTank::Update()
{
    elapsedCount++;

    if (elapsedCount == 5)
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
        //for (int i = 4; i < 8; i++)
        //{
        //    if(enemyTank[i]->GetCurrFrameY() % 2 == 0)
        //        enemyTank[i]->SetCurrFrameY((i - 4) * 2 + 1);
        //    else if(enemyTank[i]->GetCurrFrameY() % 2 != 0)
        //        enemyTank[i]->SetCurrFrameY((i - 4) * 2);
        //}
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
    for (int i = 0; i < 8; i++)
    {
        switch (moveDir)
        {
        case Left:
            enemyTank->SetCurrFrameX(2);
            break;
        case Right:
            enemyTank->SetCurrFrameX(6);
            break;
        case Up:
            enemyTank->SetCurrFrameX(0);
            break;
        case Down:
            enemyTank->SetCurrFrameX(4);
            break;
        }

    }
 
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
            pos.x -= moveSpeed;
            break;
        case Right: 
            pos.x += moveSpeed; 
            break;
        case Up: 
            pos.y -= moveSpeed; 
            break;
        case Down: 
            pos.y += moveSpeed; 
            break;
        }

}
