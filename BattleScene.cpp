#include "BattleScene.h"
#include "Image.h"
#include "PlayerTank.h"
#include "Tank.h"
#include "CommonFunction.h"
#include "EnemyTankFactory.h"
#include "EnemyTanks.h"
#include "AmmoManager.h"
#include "ItemManager.h"
#include "EnemyTankManager.h"
#include "UIManager.h"
#include "StageManager.h"
#include "ScoreManager.h"

#define POS 8
#define NormalTank enemyTankFactory[0]->CreateEnemyTank()
#define FastTank enemyTankFactory[1]->CreateEnemyTank()
#define ShootTank enemyTankFactory[2]->CreateEnemyTank()
#define BigTank enemyTankFactory[3]->CreateEnemyTank()

HRESULT BattleScene::Init()
{
    {
        ImageManager::GetSingleton()->AddImage("Image/SamlpTile.bmp", 88, 88, SAMPLE_TILE_COUNT, SAMPLE_TILE_COUNT, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);
        ImageManager::GetSingleton()->AddImage("Image/Player/Player3.bmp", 128, 76, 8, 4, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Enemy/Enemy.bmp", 128, 96, 8, 6, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Enemy/Enemy_Item.bmp", 128, 128, 8, 8, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Effect/Spawn_Effect.bmp", 64, 16, 4, 1, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Effect/Boom_Effect.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Effect/EnemyTankBoom.bmp", 160, 32, 5, 1, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Effect/Shield.bmp", 32, 16, 2, 1, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Down.bmp", 3, 4, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Left.bmp", 4, 3, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Right.bmp", 4, 3, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Up.bmp", 3, 4, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Icon/Icon_Enemy.bmp", 8, 8, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Icon/player1Life.bmp", 16, 16, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/item/items.bmp", 96, 16, 6, 1, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/Text/Number.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
        ImageManager::GetSingleton()->AddImage("Image/loading.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    }
    //이미지 초기화

    SetWindowSize(300, 20, WIN_SIZE_X*4, WIN_SIZE_Y*4);
    windowX = WIN_SIZE_X , windowY = WIN_SIZE_Y;
    // 화면 비율 조정

    sampleImage = ImageManager::GetSingleton()->FindImage("Image/SamlpTile.bmp");
    // 맵 이미지 불러오기

    battleBackGround = ImageManager::GetSingleton()->FindImage("Image/background.bmp");
    // 배틀신 배경 불러오기

    // 플레이어 이미지 저장

    ScoreManager::GetSingleton()->Init();
    Load();

    playerTank = new PlayerTank;
    playerTank->Init();

    enemyTankFactory[0] = new NormalTankFactory;
    enemyTankFactory[1] = new FastShootTankFactory;
    enemyTankFactory[2] = new FastMoveTankFactory;
    enemyTankFactory[3] = new BigTankFactory;

    enemyTankManager = new EnemyTankManager;
    enemyTankManager->Init();

    ammoManager = new AmmoManager;
    ammoManager->AmmoImageInit();
    ammoManager->SetTileInfo(tileInfo);
    ammoManager->SetPlayerTank(playerTank);
    ammoManager->SetVecEnemyTank(enemyTankManager->GetVecEnemyTanks());
    ammoManager->Init();

    itemManager = new ItemManager;
    itemManager->Init();

    stageManager = new StageManager;
    stageManager->Init();

    uIManager = new UIManager;
    uIManager->Init(*playerTank, *enemyTankManager);
 
    itemManager->Setdata(*playerTank, *enemyTankManager, tileInfo);
    playerTank->SetData(tileInfo, ammoManager, itemManager);
    enemyTankManager->SetData(tileInfo, *playerTank, ammoManager, itemManager);

    stageManager->SetData(enemyTankManager, playerTank, ammoManager, tileInfo);

    ScoreManager::GetSingleton()->SetData(*playerTank, *enemyTankManager);

    return S_OK;
}

void BattleScene::Update()
{
    enemyTankManager->Update();
    playerTank->Update();
    ammoManager->Update();
    itemManager->Update();
    uIManager->Update(*playerTank, *enemyTankManager);

    ScoreManager::GetSingleton()->Update(*playerTank, *enemyTankManager);
    stageManager->Update();
}

void BattleScene::Render(HDC hdc)
{
    battleBackGround->Render(hdc, battleBackGround->GetWidth() / 2, battleBackGround->GetHeight() / 2);
    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {

            if (tileInfo[i][j].isDes[0][0] == false && tileInfo[i][j].isDes[0][1] == false &&
                tileInfo[i][j].isDes[1][0] == false && tileInfo[i][j].isDes[1][1] == false)
                tileInfo[i][j].terrain = Terrain::Empty;

            for (int tileNumY = 0; tileNumY < 2; tileNumY++) {
                for (int tileNumX = 0; tileNumX < 2; tileNumX++) {
                    if (tileInfo[i][j].isDes[tileNumY][tileNumX]) {
                        if (tileInfo[i][j].terrain != Terrain::Forest)
                        sampleImage->Render(hdc,
                            tileInfo[i][j].rc[tileNumY][tileNumX].left + (TILE_SIZE / 2),
                            tileInfo[i][j].rc[tileNumY][tileNumX].top + (TILE_SIZE / 2),
                            tileInfo[i][j].frameX[tileNumX],
                            tileInfo[i][j].frameY[tileNumY]);
                        if (KeyManager::GetSingleton()->IsStayKeyDown('0') && tileInfo[i][j].terrain != Terrain::Empty) {
                            Rectangle(hdc,
                                tileInfo[i][j].selectRc.left,
                                tileInfo[i][j].selectRc.top,
                                tileInfo[i][j].selectRc.right,
                                tileInfo[i][j].selectRc.bottom);
                        }
                        if (KeyManager::GetSingleton()->IsStayKeyDown('9')) {
                            if (tileInfo[i][j].terrain == Terrain::Brick) {
                                pen = (HPEN)CreateSolidBrush(RGB(185, 122, 87));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::IronBrick) {
                                pen = (HPEN)CreateSolidBrush(RGB(195, 195, 195));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Water) {
                                pen = (HPEN)CreateSolidBrush(RGB(0, 162, 232));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Forest) {
                                pen = (HPEN)CreateSolidBrush(RGB(34, 177, 76));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Soild) {
                                pen = (HPEN)CreateSolidBrush(RGB(127, 127, 127));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Base) {
                                pen = (HPEN)CreateSolidBrush(RGB(200, 191, 231));
                            }
                            else if (tileInfo[i][j].terrain == Terrain::Empty) {
                                pen = (HPEN)CreateSolidBrush(RGB(30, 30, 30));
                            }
                            if (tileInfo[i][j].isDes[tileNumY][tileNumX] == false) pen = (HPEN)CreateSolidBrush(RGB(0, 0, 0));
                            oPen = (HPEN)SelectObject(hdc, pen);
                            Rectangle(hdc,
                                tileInfo[i][j].rc[tileNumY][tileNumX].left,
                                tileInfo[i][j].rc[tileNumY][tileNumX].top,
                                tileInfo[i][j].rc[tileNumY][tileNumX].right,
                                tileInfo[i][j].rc[tileNumY][tileNumX].bottom);
                            SelectObject(hdc, oPen);
                            DeleteObject(pen);
                        }

                    }
                }
            }
        }
    }
    // 숲타일 제외 모두 렌더

    enemyTankManager->Render(hdc);
    playerTank->Render(hdc);
    ammoManager->Render(hdc);

    itemManager->Render(hdc);
    uIManager->Render(hdc);
    stageManager->Render(hdc);
    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {
            for (int tileNumY = 0; tileNumY < 2; tileNumY++) {
                for (int tileNumX = 0; tileNumX < 2; tileNumX++) {
                    if (tileInfo[i][j].terrain == Terrain::Forest)
                    sampleImage->Render(hdc,
                        tileInfo[i][j].rc[tileNumY][tileNumX].left + (TILE_SIZE / 2),
                        tileInfo[i][j].rc[tileNumY][tileNumX].top + (TILE_SIZE / 2),
                        tileInfo[i][j].frameX[tileNumX],
                        tileInfo[i][j].frameY[tileNumY]);
                }
            }
        }
    }
    // 숲타일 렌더
}

void BattleScene::Release()
{
    SAFE_RELEASE(ammoManager);
}

int BattleScene::Load()
{
    {
        int loadIndex = ScoreManager::GetSingleton()->GetIsStage();
        string loadFileName = "Save/saveMapData_" + to_string(loadIndex);
        loadFileName += ".map";

        HANDLE hFile = CreateFile(loadFileName.c_str(),
            GENERIC_READ,           // 읽기, 쓰기
            0, NULL,                // 공유, 보안 모드
            OPEN_EXISTING,          // 파일 만들거나 읽을 때 옵션
            FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등등)
            NULL);

        // 읽기
        DWORD readByte;
        if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_COUNT * TILE_COUNT,
            &readByte, NULL) == false)
        {
            MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
        }

        CloseHandle(hFile);
        return loadIndex;
    }
}
