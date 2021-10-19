#include "BattleScene.h"
#include "Image.h"
#include "PlayerTank.h"
#include "Tank.h"
#include "CommonFunction.h"
#include "EnemyTankFactory.h"
#include "AmmoManager.h"
#define POS 8

HRESULT BattleScene::Init()
{
    SetWindowSize(300, 20, WIN_SIZE_X*4, WIN_SIZE_Y*4);
    windowX = WIN_SIZE_X , windowY = WIN_SIZE_Y;
    // 화면 비율 조정

    sampleImage = ImageManager::GetSingleton()->AddImage("Image/SamlpTile.bmp",
        88, 88, SAMPLE_TILE_COUNT, SAMPLE_TILE_COUNT, true, RGB(255, 0, 255));
    // 맵 이미지 불러오기

    battleBackGround = ImageManager::GetSingleton()->AddImage("Image/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    Load();
    // 배틀신 배경 불러오기

    ImageManager::GetSingleton()->AddImage("Image/Player/Player3.bmp", 128, 76, 8, 4, true, RGB(255, 0, 255));
    // 플레이어 이미지 저장

    ImageManager::GetSingleton()->AddImage("Image/Enemy/Enemy.bmp", 128, 96, 8, 6, true, RGB(255, 0, 255));
    // 적 탱크 이미지 저장

    ImageManager::GetSingleton()->AddImage("Image/Enemy/Enemy_Item.bmp", 128, 128, 8, 8, true, RGB(255, 0, 255));
    // 적 아이템 탱크 이미지 저장

    ammoMgr = new AmmoManager;
    ammoMgr->SetTileInfo(tileInfo);
    ammoMgr->Init();

    playerTank = new PlayerTank;
    playerTank->Init();
    playerTank->SetTileInfo(tileInfo);
    playerTank->SetAmmoMgr(ammoMgr);

    enemyTankFactory[0] = new NormalTankFactory;
    enemyTankFactory[1] = new FastShootTankFactory;
    enemyTankFactory[2] = new FastMoveTankFactory;
    enemyTankFactory[3] = new BigTankFactory;
    
    enemyTankFactory[0]->NewEnemyTank(tileInfo, *playerTank, 1);
    enemyTankFactory[1]->NewEnemyTank(tileInfo, *playerTank, 2);
    enemyTankFactory[2]->NewEnemyTank(tileInfo, *playerTank, 3);
    enemyTankFactory[3]->NewEnemyTank(tileInfo, *playerTank, 1);

    for (int i = 0; i < 4; i++)playerTank->SetVecEnemyTank(enemyTankFactory[i]->vecEnemyTank, i);

    addEnemy = true;

    return S_OK;
}

void BattleScene::Update()
{
    for (int i = 0; i < 4; i++) {
        enemyTankFactory[i]->Update();
    }

    playerTank->Update();
    ammoMgr->Update();
}

void BattleScene::Render(HDC hdc)
{
    battleBackGround->Render(hdc, battleBackGround->GetWidth() / 2, battleBackGround->GetHeight() / 2);
    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {

            if (tileInfo[i][j].isDes[0][0] == false &&
                tileInfo[i][j].isDes[0][1] == false &&
                tileInfo[i][j].isDes[1][0] == false &&
                tileInfo[i][j].isDes[1][1] == false)
                tileInfo[i][j].terrain = Terrain::Empty;
            for (int tileNumY = 0; tileNumY < 2; tileNumY++) {
                for (int tileNumX = 0; tileNumX < 2; tileNumX++) {
                    if (tileInfo[i][j].isDes[tileNumY][tileNumX]) {
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
                                tileInfo[i][j].rc[tileNumY][tileNumX].top ,
                                tileInfo[i][j].rc[tileNumY][tileNumX].right,
                                tileInfo[i][j].rc[tileNumY][tileNumX].bottom );
                            SelectObject(hdc, oPen);
                            DeleteObject(pen);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        enemyTankFactory[i]->Render(hdc);
    }

    //enemyTank->Render(hdc);
    playerTank->Render(hdc);
    ammoMgr->Render(hdc);
}

void BattleScene::Release()
{
    for (int i = 0; i < 4; i++) {
        enemyTankFactory[i]->Release();
    }
    SAFE_RELEASE(ammoMgr);
}

void BattleScene::Load()
{
    {
        int loadIndex = 1;
        //cout << "로드할 맵의 번호를 입력하여 주십시오. : ";
        //cin >> loadIndex;
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
    }
}
