#include "PlayerTank.h"
#include "Image.h"
#include "Config.h"

int CurrFrame(Image playerTank, int elapsedCount, int setCurr) {
    if (elapsedCount == 2)
    {
        if (playerTank.GetCurrFrameX() % 2 == 0)
        {
            playerTank.SetCurrFrameX(setCurr);
        }
        else if (playerTank.GetCurrFrameX() % 2 != 0)
        {
            playerTank.SetCurrFrameX(setCurr -1);
        }
        return 0;
    }
    return elapsedCount;
}

HRESULT PlayerTank::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/Player/Player.bmp", 128, 64, 8, 4, true, RGB(255, 0, 255));
    playerTank = ImageManager::GetSingleton()->FindImage("Image/Player/Player.bmp");
    pos.x = 16 + 8 ;
    pos.y = WIN_SIZE_Y - 16;

    moveSpeed = 50;

    return E_NOTIMPL;
}

void PlayerTank::Update()
{
    shape.left = pos.x - (16 / 2) + 2;
    shape.top = pos.y - (16 / 2) + 2;
    shape.right = pos.x + (16 / 2) - 2;
    shape.bottom = pos.y + (16 / 2) - 2;
    RECT rc;

    time += TimerManager::GetSingleton()->GetDeltaTime();
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
    {  
        bufferRc = shape;
        bufferPos = pos;
        pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
        shape.left = pos.x - (16 / 2) + 2;
        shape.top = pos.y - (16 / 2) + 2;
        shape.right = pos.x + (16 / 2) - 2;
        shape.bottom = pos.y + (16 / 2) - 2;
        for (int i = 0; i < TILE_COUNT; i++) {
            for (int j = 0; j < TILE_COUNT; j++) {
                if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc) ||
                    pos.y <= 16) {
                    shape = bufferRc;
                    pos = bufferPos;
                };
            }
        }
        elapsedCount++;
        elapsedCount = CurrFrame(*playerTank, elapsedCount, 1);
    } else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)) {
        bufferRc = shape;
        bufferPos = pos;
        pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
        shape.left = pos.x - (16 / 2) + 2;
        shape.top = pos.y - (16 / 2) + 2;
        shape.right = pos.x + (16 / 2) - 2;
        shape.bottom = pos.y + (16 / 2) - 2;
        for (int i = 0; i < TILE_COUNT; i++) {
            for (int j = 0; j < TILE_COUNT; j++) {
                if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc) ||
                    pos.y >= 208+2) {
                    shape = bufferRc;
                    pos = bufferPos;
                };
            }
        }
        elapsedCount++;
        elapsedCount = CurrFrame(*playerTank, elapsedCount, 5);
    } else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
        bufferRc = shape;
        bufferPos = pos;
        pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
        shape.left = pos.x - (16 / 2) + 2;
        shape.top = pos.y - (16 / 2) + 2;
        shape.right = pos.x + (16 / 2) - 2;
        shape.bottom = pos.y + (16 / 2) - 2;
        for (int i = 0; i < TILE_COUNT; i++) {
            for (int j = 0; j < TILE_COUNT; j++) {
                if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc) ||
                    pos.x <= 16+6) {
                    shape = bufferRc;
                    pos = bufferPos;
                };
            }
        }
        elapsedCount++;
        elapsedCount = CurrFrame(*playerTank, elapsedCount, 3);
    } else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
        bufferRc = shape;
        bufferPos = pos;
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
        shape.left = pos.x - (16 / 2) + 2;
        shape.top = pos.y - (16 / 2) + 2;
        shape.right = pos.x + (16 / 2) - 2;
        shape.bottom = pos.y + (16 / 2) - 2;
        for (int i = 0; i < TILE_COUNT; i++) {
            for (int j = 0; j < TILE_COUNT; j++) {
                if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc) ||
                    pos.x >= 10+208) {
                    shape = bufferRc;
                    pos = bufferPos;
                };
            }
        }
        elapsedCount++;
        elapsedCount = CurrFrame(*playerTank, elapsedCount, 7);
    }



    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {
            if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc)) {
                cout << "Ãæµ¹";
            };
        }
    }
}

void PlayerTank::Render(HDC hdc)
{

    playerTank->Render(hdc, pos.x, pos.y, playerTank->GetCurrFrameX(), playerTank->GetCurrFrameY());
    if (KeyManager::GetSingleton()->IsStayKeyDown('8')) {
        Rectangle(hdc,
            shape.left,
            shape.top,
            shape.right,
            shape.bottom);
    }
}

void PlayerTank::Release()
{
}
