#include "PlayerTank.h"
#include "Image.h"
#include "Config.h"
#include "EnemyTanks.h"
#include "AmmoManager.h"
#include "CommonFunction.h"

void PlayerTank::SetFrame()
{
    if (moveDir == MoveDir::Up) {
        if (elapsedCount == 0) elapsedCount = 1;
        else elapsedCount = 0;
    }
    if (moveDir == MoveDir::Left) {
        if (elapsedCount == 2) elapsedCount = 3;
        else elapsedCount = 2;
    }
    if (moveDir == MoveDir::Down) {
        if (elapsedCount == 4) elapsedCount = 5;
        else elapsedCount = 4;
    }
    if (moveDir == MoveDir::Right) {
        if (elapsedCount == 6) elapsedCount = 7;
        else elapsedCount = 6;
    }

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

    for (int i = GetPosCount(pos.y, -2, false); i < GetPosCount(pos.y, 2, false); i++) {
        for (int j = GetPosCount(pos.x, -2, true); j < GetPosCount(pos.x, 2, true); j++) {
            if (!(tileInfo[i][j].terrain == Terrain::Empty) && IntersectRect(&rc, &shape, &tileInfo[i][j].selectRc)) {
                check = true;
            }

            for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
                it != vecEnemyTank.end();
                it++)
            {
                RECT enemyRect = (*it)->GetRect();
                if (IntersectRect(&rc, &shape, &enemyRect)) check = true;

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
    spawnEffectTime += TimerManager::GetSingleton()->GetDeltaTime();

    if (spawnEffectTime >= 0.25)
    {
        if (spawnEffectCount != 12)
        {
            if (spawnEffectFrameX == 3)
            {
                spawnFrameUp = false;
            }
            else if (spawnEffectFrameX == 0)
            {
                spawnFrameUp = true;
            }
            switch (spawnFrameUp)
            {
            case true:
                spawnEffectFrameX++;
                break;
            case false:
                spawnEffectFrameX--;
                break;

            }
            spawnEffect->SetCurrFrameX(spawnEffectFrameX);

            spawnEffectCount++;
        }
        spawnEffectTime = 0;
    }

    if (spawnEffectCount == 12) return false;
    return true;
}

bool PlayerTank::ShieldEffect()
{
   if (shieldEffectTime < 7.0f)
   {
       shieldEffectTime += TimerManager::GetSingleton()->GetDeltaTime();
       shieldEffectDelay += TimerManager::GetSingleton()->GetDeltaTime();
       if (shieldEffectDelay < 0.1f)
       {
           return true;
       }
       if (shieldEffect->GetCurrFrameX() == 1)
       {
           shieldEffect->SetCurrFrameX(0);
       }
       else if (shieldEffect->GetCurrFrameX() == 0)
       {
           shieldEffect->SetCurrFrameX(1);
       }
       shieldEffectDelay = 0.0f;
       return true;
   } else {
       return false;
   }
}

HRESULT PlayerTank::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/Effect/Spawn_Effect.bmp", 64, 16, 4, 1, true, RGB(255, 0, 255));
    spawnEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Spawn_Effect.bmp");
    spawnEffectFrameX = 3;
    spawnEffectCount = 0;

    ImageManager::GetSingleton()->AddImage("Image/Player/Player3.bmp", 128, 76, 8, 4, true, RGB(255, 0, 255));
    playerTank = ImageManager::GetSingleton()->FindImage("Image/Player/Player3.bmp");
    pos.x = 16 + 8;
    pos.y = WIN_SIZE_Y - 16;

    ImageManager::GetSingleton()->AddImage("Image/Effect/Shield.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
    shieldEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Shield.bmp");
    shieldEffectDelay = 0.0f;

    ImageManager::GetSingleton()->AddImage("Image/Effect/EnemyTankBoom.bmp", 160, 32, 5, 1, true, RGB(255, 0, 255));
    deadEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/EnemyTankBoom.bmp");
    deadEffecttime = 0.0f;
    deadEffectfreamX = 0;
    isdead = false;

    moveDir = MoveDir::Up;
    type = TankType::Player;

    moveSpeed = 50;
    shape.left = pos.x - 8;
    shape.top = pos.y - 8;
    shape.right = pos.x + 8;
    shape.bottom = pos.y + 8;

    isBarrier = false;
    fastAmmoReady = true;
    life = 2;
    Level = 0;
    return S_OK;
}

void PlayerTank::Update()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_PRIOR))
    {
        life++;
    }
    else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NEXT))
    {
        life--;
    }
    RECT rc;
    SpawnEffect();
    if (SpawnEffect() == false)
    {
        // time += TimerManager::GetSingleton()->GetDeltaTime();
        if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
        {
            moveDir = MoveDir::Up;
            PosReset(MoveDir::Up);
            CollisionAndMove(MoveDir::Up);
            SetFrame();
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN)) {
            moveDir = MoveDir::Down;
            PosReset(MoveDir::Down);
            CollisionAndMove(MoveDir::Down);
            SetFrame();
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT)) {
            moveDir = MoveDir::Left;
            PosReset(MoveDir::Left);
            CollisionAndMove(MoveDir::Left);
            SetFrame();
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT)) {
            moveDir = MoveDir::Right;
            PosReset(MoveDir::Right);
            CollisionAndMove(MoveDir::Right);
            SetFrame();
        }

        if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
        {
            switch (moveDir)
            {
            case MoveDir::Left:
                ammoMgr->Fire(moveDir, { (float)shape.left, pos.y }, type, fastAmmoReady);
                break;
            case MoveDir::Right:
                ammoMgr->Fire(moveDir, { (float)shape.right, pos.y }, type, fastAmmoReady);
                break;
            case MoveDir::Up:
                ammoMgr->Fire(moveDir, { pos.x, (float)shape.top }, type, fastAmmoReady);
                break;
            case MoveDir::Down:
                ammoMgr->Fire(moveDir, { pos.x, (float)shape.bottom }, type, fastAmmoReady);
                break;
            }
        }
    }

    if (isdead == true)
    {
        deadEffecttime += TimerManager::GetSingleton()->GetDeltaTime();
        cout << deadEffecttime;
        if (deadEffecttime >= 0.05)
        {
            deadEffectfreamX++;
            deadEffecttime = 0.0f;
            if (deadEffectfreamX >= 5)
            {
                if (life > 0)
                {
                deadEffectfreamX = 0;
                    life--;
                 pos.x = 16 + 8;
                    pos.y = WIN_SIZE_Y - 16;
                    isdead = false;
                 spawnEffectTime = 0.0f;
                 spawnEffectFrameX = 0;
                 spawnEffectCount = 0;
                 shieldEffectTime = 0.0f;
                 shieldEffectDelay = 0.0f;
                }
                
            }
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
                 playerTank->Render(hdc, pos.x, pos.y, elapsedCount, Level);
            }
     else
          {
                spawnEffect->Render(hdc, pos.x, pos.y, spawnEffect->GetCurrFrameX(), 0);
          }
    if (ShieldEffect() == true && SpawnEffect() == false)
             {
                shieldEffect->Render(hdc, pos.x, pos.y, shieldEffect->GetCurrFrameX(), 0);
             }

    if (isdead == true)

    {
        deadEffect->Render(hdc, pos.x, pos.y, deadEffectfreamX, 0);
    }
    
}

void PlayerTank::Release()
{

}

void PlayerTank::LevelUp()
{
    if (Level < 3) Level++;
    if (Level == 1);
    if (Level == 2);
    if (Level == 3);
}

