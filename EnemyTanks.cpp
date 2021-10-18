#include "EnemyTanks.h"

void EnemyTanks::CollisionAndMove(MoveDir movedir)
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
    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {
            if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc)) {
                check = true;
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

void EnemyTanks::PosReset(MoveDir movedir)
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

int EnemyTanks::CurrFrame(Image enemyTank, int* elapsedCount, int setCurr)
{
    if (*elapsedCount == 2)
    {
        if (enemyTank.GetCurrFrameX() % 2 == 0)
        {
            enemyTank.SetCurrFrameX(setCurr);
        }
        else if (enemyTank.GetCurrFrameX() % 2 != 0)
        {
            enemyTank.SetCurrFrameX(setCurr - 1);
        }
        return 0;
    }
    return *elapsedCount;
}

MoveDir EnemyTanks::AutoMove(MoveDir moveDir, POINTFLOAT pos)
{
    int randomValue = rand();
    RECT rc;
    RECT bufferRc1 = shape;
    RECT bufferRc2 = shape;
    POINTFLOAT bufferPos1 = pos;
    POINTFLOAT bufferPos2 = pos;
    bool check1 = true;
    bool check2 = true;

    if (moveDir == MoveDir::Up || moveDir == MoveDir::Down) {
        bufferPos1.x -= 1;
        bufferPos2.x += 1;
        bufferRc1.top = bufferPos1.y - 7;
        bufferRc1.left = (bufferPos1.x - 1) - 8;
        bufferRc1.bottom = bufferPos1.y + 7;
        bufferRc1.right = (bufferPos1.x - 1) + 8;

        bufferRc2.top = bufferPos2.y - 7;
        bufferRc2.left = (bufferPos2.x + 1) - 8;
        bufferRc2.bottom = bufferPos2.y + 7;
        bufferRc2.right = (bufferPos2.x + 1) + 8;
    }
    else if (moveDir == MoveDir::Right || moveDir == MoveDir::Left) {
        bufferPos1.y -= 1;
        bufferPos2.y += 1;
        bufferRc1.top = (bufferPos1.y - 1) - 8;
        bufferRc1.left = bufferPos1.x - 7;
        bufferRc1.bottom = (bufferPos1.y - 1) + 8;
        bufferRc1.right = bufferPos1.x + 7;

        bufferRc2.top = (bufferPos2.y + 1) - 8;
        bufferRc2.left = bufferPos2.x - 7;
        bufferRc2.bottom = (bufferPos2.y + 1) + 8;
        bufferRc2.right = bufferPos2.x + 7;
    }

    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {
            if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &bufferRc1, &tileInfo[i][j].selectRc)) {
                check1 = false;
            }
            if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &bufferRc2, &tileInfo[i][j].selectRc)) {
                check2 = false;
            }
        }
    }
    if (moveDir == MoveDir::Left || moveDir == MoveDir::Right) {
        if (bufferPos1.y <= 16) check1 = false;
        if (bufferPos2.y >= 208 + 1) check2 = false;
    } else if (moveDir == MoveDir::Up || moveDir == MoveDir::Down) {
        if (bufferPos1.x <= 16 + 8) check1 = false;
        if (bufferPos2.x >= 208 + 9) check2 = false;
    }


    cout << check1 << " " << check2 << endl;
    if (check1 || check2) {
        if (moveDir == MoveDir::Up || moveDir == MoveDir::Down) {
            if (check1 && check2) {
                if (randomValue % 2) {
                    return  MoveDir::Right;
                }
                else {
                    return MoveDir::Left;
                }
            }
            else {
                if (check1) return MoveDir::Left;
                if (check2) return MoveDir::Right;
            }
        }
        else if (moveDir == MoveDir::Right || moveDir == MoveDir::Left) {
            if (check1 && check2) {
                if (randomValue % 2) {
                    return MoveDir::Up;
                }
                else {
                    return MoveDir::Down;
                }
            }
            else {
                if (check1) return MoveDir::Up;
                if (check2) return MoveDir::Down;
            }
        }
    }
    return moveDir;
}

HRESULT EnemyTanks::TankInit()
{
    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;
    movedir = MoveDir::Down;
    elapsedCount = 0;
    return S_OK;
}


EnemyTanks::~EnemyTanks()
{
}
