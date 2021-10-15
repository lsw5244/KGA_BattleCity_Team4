#include "PlayerTank.h"
#include "Image.h"
#include "Config.h"

int PlayerTank::CurrFrame(Image playerTank, int elapsedCount, int setCurr)
{
    if (elapsedCount == 2)
    {
        if (playerTank.GetCurrFrameX() % 2 == 0)
        {
            playerTank.SetCurrFrameX(setCurr);
        }
        else if (playerTank.GetCurrFrameX() % 2 != 0)
        {
            playerTank.SetCurrFrameX(setCurr - 1);
        }
        return 0;
    }
    return elapsedCount;
}

void PlayerTank::CollisionAndMove(MoveDir movedir)
{
    RECT rc;
    RECT bufferRc;
    POINTFLOAT bufferPos;
    bool check = false;

    bufferRc = shape;
    bufferPos = pos;
    if (movedir == MoveDir::Left) {
        pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    } else if (movedir == MoveDir::Right) {
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    } else if (movedir == MoveDir::Up) {
        pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    } else if (movedir == MoveDir::Down) {
        pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    shape.left = pos.x - 7;
    shape.top = pos.y - 6;
    shape.right = pos.x + 7;
    shape.bottom = pos.y + 7;
    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {
            if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc)) {
                check = true;
            }
        }
    }

    if (movedir == MoveDir::Left) {
        if (pos.x <= 16 + 6) check = true;
    }
    else if (movedir == MoveDir::Right) {
        if (pos.x >= 10 + 208) check = true;
    }
    else if (movedir == MoveDir::Up) {
        if (pos.y <= 16) check = true;
    }
    else if (movedir == MoveDir::Down) {
        if (pos.y >= 208 + 2) check = true;
    }
    if (check) {
        shape = bufferRc;
        pos = bufferPos;
    }

}

HRESULT PlayerTank::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/Player/Player3.bmp", 128, 76, 8, 4, true, RGB(255, 0, 255));
    playerTank = ImageManager::GetSingleton()->FindImage("Image/Player/Player3.bmp");
    pos.x = 16 + 8 ;
    pos.y = WIN_SIZE_Y - 16;

    moveSpeed = 50;

    return E_NOTIMPL;
}

void PlayerTank::Update()
{
    shape.left = pos.x - 7;
    shape.top = pos.y - 6;
    shape.right = pos.x + 7;
    shape.bottom = pos.y + 7;
    RECT rc;

    time += TimerManager::GetSingleton()->GetDeltaTime();
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
    {  
        CollisionAndMove(MoveDir::Up);
        elapsedCount++;
        elapsedCount = CurrFrame(*playerTank, elapsedCount, 1);
    } else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)) {
        CollisionAndMove(MoveDir::Down);
        elapsedCount++;
        elapsedCount = CurrFrame(*playerTank, elapsedCount, 5);
    } else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
        CollisionAndMove(MoveDir::Left);
        elapsedCount++;
        elapsedCount = CurrFrame(*playerTank, elapsedCount, 3);
    } else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
        CollisionAndMove(MoveDir::Right);
        elapsedCount++;
        elapsedCount = CurrFrame(*playerTank, elapsedCount, 7);
    }
}

void PlayerTank::Render(HDC hdc)
{

    if (KeyManager::GetSingleton()->IsStayKeyDown('8')) {
        Rectangle(hdc,
            shape.left,
            shape.top,
            shape.right,
            shape.bottom);
    }
    playerTank->Render(hdc, pos.x, pos.y, playerTank->GetCurrFrameX(), playerTank->GetCurrFrameY());
}

void PlayerTank::Release()
{

}
