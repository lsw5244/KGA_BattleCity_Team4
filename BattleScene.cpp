#include "BattleScene.h"
#include "Image.h"
#include "PlayerTank.h"
#include "Tank.h"
#include "CommonFunction.h"

#define POS 8

HRESULT BattleScene::Init()
{
    SetWindowSize(20, 20, WIN_SIZE_X, WIN_SIZE_Y);
    windowX = WIN_SIZE_X;
    windowY = WIN_SIZE_Y;
    sampleImage = ImageManager::GetSingleton()->AddImage("Image/SamlpTile.bmp",
        88, 88, SAMPLE_TILE_COUNT, SAMPLE_TILE_COUNT, true, RGB(255, 0, 255));

    battleBackGround = ImageManager::GetSingleton()->AddImage("Image/background.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    Load();

    playerTank = new PlayerTank;
    playerTank->Init();
    playerTank->SetTileInfo(tileInfo);

    return S_OK;
}

void BattleScene::Update()
{
    playerTank->Update();
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
                        if (KeyManager::GetSingleton()->IsStayKeyDown('0')) {
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

    
    
    playerTank->Render(hdc);
}

void BattleScene::Release()
{
}

void BattleScene::Load()
{
    {
        int loadIndex = 1;
        //cout << "�ε��� ���� ��ȣ�� �Է��Ͽ� �ֽʽÿ�. : ";
        //cin >> loadIndex;
        string loadFileName = "Save/saveMapData_" + to_string(loadIndex);
        loadFileName += ".map";

        HANDLE hFile = CreateFile(loadFileName.c_str(),
            GENERIC_READ,           // �б�, ����
            0, NULL,                // ����, ���� ���
            OPEN_EXISTING,          // ���� ����ų� ���� �� �ɼ�
            FILE_ATTRIBUTE_NORMAL,  // ���� �Ӽ�(�б� ����, ���� ���)
            NULL);

        // �б�
        DWORD readByte;
        if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_COUNT * TILE_COUNT,
            &readByte, NULL) == false)
        {
            MessageBox(g_hWnd, "�� ������ �ε忡 �����߽��ϴ�.", "����", MB_OK);
        }

        CloseHandle(hFile);
    }
}
