#include "PlayerTank.h"
#include "Image.h"
#include "Config.h"

HRESULT PlayerTank::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/Player/Player.bmp", 128, 64, 8, 4, true, RGB(255, 0, 255));
    playerTank = ImageManager::GetSingleton()->FindImage("Image/Player/Player.bmp");
    pos.x = 50;
    pos.y = WIN_SIZE_Y;

    moveSpeed = 50;

    return E_NOTIMPL;
}

void PlayerTank::Update()
{
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
    {  
        pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
        elapsedCount++;
    
        if (elapsedCount == 2)
        {
         if (playerTank->GetCurrFrameX() % 2 == 0)
        {
            playerTank->SetCurrFrameX(1);
        }
        else if (playerTank->GetCurrFrameX() % 2 != 0)
        {
            playerTank->SetCurrFrameX(0);
        }
           elapsedCount = 0;
        }
       
       
        
    }
    
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
    {
        
        pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
        elapsedCount++;
        if (elapsedCount == 2)
        {
            if (playerTank->GetCurrFrameX() % 2 == 0)
            {
                playerTank->SetCurrFrameX(5);
            }
            else if (playerTank->GetCurrFrameX() % 2 != 0)
            {
                playerTank->SetCurrFrameX(4);
            }
            elapsedCount = 0;
        }



    }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
    {
        pos.x -= moveSpeed* TimerManager::GetSingleton()->GetDeltaTime();
        elapsedCount++;
        if (elapsedCount == 2)
        {
            if (playerTank->GetCurrFrameX() % 2 == 0)
            {
                playerTank->SetCurrFrameX(3);
            }
            else if (playerTank->GetCurrFrameX() % 2 != 0)
            {
                playerTank->SetCurrFrameX(2);
            }
            elapsedCount = 0;
        }



    }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
    {
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
        elapsedCount++;
        if (elapsedCount == 2)
        {
            if (playerTank->GetCurrFrameX() % 2 == 0)
            {
                playerTank->SetCurrFrameX(7);
            }
            else if (playerTank->GetCurrFrameX() % 2 != 0)
            {
                playerTank->SetCurrFrameX(6);
            }
            elapsedCount = 0;
        }



    }
}

void PlayerTank::Render(HDC hdc)
{
    playerTank->Render(hdc, pos.x, pos.y, playerTank->GetCurrFrameX(), playerTank->GetCurrFrameY());
}

void PlayerTank::Release()
{
}
