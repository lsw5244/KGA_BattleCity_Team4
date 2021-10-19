#include "PlayerTank.h"
#include "Image.h"
#include "Config.h"
#include "EnemyTanks.h"

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
    }
    else if (movedir == MoveDir::Right) {
        pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    else if (movedir == MoveDir::Up) {
        pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }
    else if (movedir == MoveDir::Down) {
        pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
    }

    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;

    int xCount = (((int)pos.x - 16) / 8) % 26;
    int yCount = (((int)pos.y - 8) / 8) % 26;
    int xMinCount = xCount - 2;
    int xMaxCount = xCount + 2;
    int yMinCount = yCount - 2;
    int yMaxCount = yCount + 2;
    if (xMinCount < 0) xMinCount = 0;
    if (xMaxCount > 26) xMaxCount = 26;
    if (yMinCount < 0) yMinCount = 0;
    if (yMaxCount > 26) yMaxCount = 26;

    for (int i = yMinCount; i < yMaxCount; i++) {
        for (int j = xMinCount; j < xMaxCount; j++) {
            if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc)) {
                check = true;
            }
            for (int i = 0; i < 4; i++) {
                for (vector<EnemyTanks*>::iterator it = vecEnemyTank[i].begin();
                    it != vecEnemyTank[i].end();
                    it++)
                {
                    RECT enemyRect = (*it)->GetRect();
                    if (IntersectRect(&rc, &shape, &enemyRect)) check = true;
                }
            }
        }
    }

    if (movedir == MoveDir::Left) {
        if (pos.x <= 16 + 8) check = true;
    }
    else if (movedir == MoveDir::Right) {
        if (pos.x >= 208 + 9) check = true;
    }
    else if (movedir == MoveDir::Up) {
        if (pos.y <= 16) check = true;
    }
    else if (movedir == MoveDir::Down) {
        if (pos.y >= 208 + 1) check = true;
    }
    if (check) {
        shape = bufferRc;
        pos = bufferPos;
    }
}

void PlayerTank::PosReset(MoveDir movedir)
{
    int posCount = 0;
    if (movedir == MoveDir::Left || movedir == MoveDir::Right) {
        int posY = ((int)pos.y - 8) % 8;
        for (float posNum = pos.y; posNum >= 8; posNum -= 8) posCount++;
        if (posY <= 3) {
            pos.y = (posCount - 1) * 8;
            pos.y += 8;
        }
        else {
            pos.y = (posCount - 1) * 8;
            pos.y += 16;
        }
    }
    else if (movedir == MoveDir::Up || movedir == MoveDir::Down) {
        int posX = ((int)pos.x - 16) % 8;
        for (float posNum = pos.x; posNum >= 8; posNum -= 8) posCount++;

        if (posX <= 3) {
            pos.x = (posCount - 1) * 8;
            pos.x += 8;
        }
        else {
            pos.x = (posCount - 1) * 8;
            pos.x += 16;
        }
    }
    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;
}

bool PlayerTank::SpawnEffect()
{
    effectTime += TimerManager::GetSingleton()->GetDeltaTime();

    if (effectTime >= 0.25)
    {
        if (effectCount != 12)
        {
            if (effectFrameX == 3)
            {
                frameUp = false;
            }
            else if (effectFrameX == 0)
            {
                frameUp = true;
            }
            switch (frameUp)
            {
            case true:
                effectFrameX++;
                break;
            case false:
                effectFrameX--;
                break;

            }
            spawnEffect->SetCurrFrameX(effectFrameX);

            effectCount++;
        }
        effectTime = 0;
    }

    if (effectCount == 12) return false;
}

HRESULT PlayerTank::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/Effect/Spawn_Effect.bmp", 64, 16, 4, 1, true, RGB(255, 0, 255));
    spawnEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Spawn_Effect.bmp");
    effectFrameX = 3;
    effectCount = 0;

    ImageManager::GetSingleton()->AddImage("Image/Player/Player3.bmp", 128, 76, 8, 4, true, RGB(255, 0, 255));
    playerTank = ImageManager::GetSingleton()->FindImage("Image/Player/Player3.bmp");
    pos.x = 16 + 8;
    pos.y = WIN_SIZE_Y - 16;

    


    moveSpeed = 50;
    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;
    return S_OK;
}

void PlayerTank::Update()
{
    RECT rc;
    SpawnEffect();
    if (SpawnEffect() == false)
    {
        time += TimerManager::GetSingleton()->GetDeltaTime();
        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
        {
            PosReset(MoveDir::Up);
            CollisionAndMove(MoveDir::Up);
            elapsedCount++;
            elapsedCount = CurrFrame(*playerTank, elapsedCount, 1);
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)) {
            PosReset(MoveDir::Down);
            CollisionAndMove(MoveDir::Down);
            elapsedCount++;
            elapsedCount = CurrFrame(*playerTank, elapsedCount, 5);
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
            PosReset(MoveDir::Left);
            CollisionAndMove(MoveDir::Left);
            elapsedCount++;
            elapsedCount = CurrFrame(*playerTank, elapsedCount, 3);
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
            PosReset(MoveDir::Right);
            CollisionAndMove(MoveDir::Right);
            elapsedCount++;
            elapsedCount = CurrFrame(*playerTank, elapsedCount, 7);
        }
    }
}

void PlayerTank::Render(HDC hdc)
{

    if (KeyManager::GetSingleton()->IsStayKeyDown(TANK_COLLIDER_DEBUG)) {
        Rectangle(hdc,
            shape.left,
            shape.top,
            shape.right,
            shape.bottom);
    }
    if (SpawnEffect() == false)
    {
        playerTank->Render(hdc, pos.x, pos.y, playerTank->GetCurrFrameX(), playerTank->GetCurrFrameY());
    }
    else
    {
        spawnEffect->Render(hdc, pos.x, pos.y, spawnEffect->GetCurrFrameX(), 0);
    }
}

void PlayerTank::Release()
{

}
