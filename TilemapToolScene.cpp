#include "TilemapToolScene.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT TilemapToolScene::Init()
{
    SetWindowSize(20, 20, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);

    sampleImage = ImageManager::GetSingleton()->AddImage("Image/SamlpTile.bmp",
        88, 88, SAMPLE_TILE_COUNT, SAMPLE_TILE_COUNT, true, RGB(255, 0, 255));
    bin = ImageManager::GetSingleton()->AddImage("Image/bin.bmp", 200, 200);
    if (sampleImage == nullptr)
    {
        cout << "Image/SamlpTile1.bmp 로드 실패!!" << endl;
        return E_FAIL;
    }

    // 왼쪽 상단 메인 영역 초기화
    for (int i = 0; i < TILE_COUNT; i++) {    // y축
        for (int j = 0; j < TILE_COUNT; j++) {    // x축 
            SetRect(&(tileInfo[i][j].selectRc),
                j * (TILE_SIZE * 2),
                i * (TILE_SIZE * 2),
                j * (TILE_SIZE * 2) + (TILE_SIZE * 2),
                i * (TILE_SIZE * 2) + (TILE_SIZE * 2));
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 2; l++) {
                    SetRect(&(tileInfo[i][j].rc[k][l]),
                        j * (TILE_SIZE * 2) + (l * (TILE_SIZE)),
                        i * (TILE_SIZE * 2) + (k * (TILE_SIZE)),
                        j * (TILE_SIZE * 2) + (l * (TILE_SIZE) + (TILE_SIZE)),
                        i * (TILE_SIZE * 2) + (k * (TILE_SIZE) + (TILE_SIZE)));
                    tileInfo[i][j].isDes[k][l] = true;
                    tileInfo[i][j].frameX[l] = l;
                    tileInfo[i][j].frameY[k] = k;
                    tileInfo[i][j].terrain = Terrain::Brick;
                }
            }
        }
    }

    // 오른쪽 상단 샘플 영역 초기화
    for (int i = 0; i < SAMPLE_TILE_COUNT; i++)    // y축
    {
        for (int j = 0; j < SAMPLE_TILE_COUNT; j++)    // x축
        {
            SetRect(&(sampleTileInfo[i][j].rc),
                TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE,
                i * TILE_SIZE,
                TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + j * TILE_SIZE + TILE_SIZE,
                i * TILE_SIZE + TILE_SIZE);

            sampleTileInfo[i][j].frameX = j;
            sampleTileInfo[i][j].frameY = i;
        }
    }

    // 선택된 타일
    selectedSampleTile.frameX = 0;
    selectedSampleTile.frameY = 0;
    selectedSampleTile.width = 0;
    selectedSampleTile.height = 0;
    mouseCheck = false;
    check = false;
    return S_OK;
}

void TilemapToolScene::Update()
{
    mouse = g_ptMouse;
    RECT rect;
    GetClientRect(g_hWnd, &rect);
    view.x = rect.right - rect.left;
    view.y = rect.bottom - rect.top;
    if (view.x != TILEMAPTOOL_SIZE_X || view.y != TILEMAPTOOL_SIZE_Y) {
        view.x /= TILEMAPTOOL_SIZE_X;
        view.y /= TILEMAPTOOL_SIZE_Y;
        mouse.x /= view.x;
        mouse.y /= view.y;
    }

    // 샘플영역에서 샘플을 선택
    RECT sampleArea;
    sampleArea.left = TILEMAPTOOL_SIZE_X - sampleImage->GetWidth();
    sampleArea.right = TILEMAPTOOL_SIZE_X;
    sampleArea.top = 0;
    sampleArea.bottom = sampleImage->GetHeight();

    if (PtInRect(&(sampleArea), mouse))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON) && (!mouseCheck)) {
            mouseCheck = true;

            int posX = mouse.x - sampleArea.left;
            mousePos[0].x = posX / TILE_SIZE;
            int posY = mouse.y - sampleArea.top;
            mousePos[0].y = posY / TILE_SIZE;
        }

        if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON) && mouseCheck) {
            mouseCheck = false;

            int posX = mouse.x - sampleArea.left;
            mousePos[1].x = posX / TILE_SIZE;
            int posY = mouse.y - sampleArea.top;
            mousePos[1].y = posY / TILE_SIZE;

            selectedSampleTile.width = mousePos[0].x - mousePos[1].x;
            selectedSampleTile.height = mousePos[0].y - mousePos[1].y;

            if (selectedSampleTile.width < 0) {
                selectedSampleTile.width *= -1;
                selectedSampleTile.frameX = sampleTileInfo[mousePos[0].y][mousePos[0].x].frameX;
            } else {
                selectedSampleTile.frameX = sampleTileInfo[mousePos[1].y][mousePos[1].x].frameX;
            }
            if (selectedSampleTile.width % 2 == 0) selectedSampleTile.width++;
            if (selectedSampleTile.frameX % 2)  selectedSampleTile.frameX--;


            if (selectedSampleTile.height < 0) {
                selectedSampleTile.height *= -1;
                selectedSampleTile.frameY = sampleTileInfo[mousePos[0].y][mousePos[0].x].frameY;
            } else {
                selectedSampleTile.frameY = sampleTileInfo[mousePos[1].y][mousePos[1].x].frameY;
            }
            if (selectedSampleTile.height % 2 == 0) selectedSampleTile.height++;
            if (selectedSampleTile.frameY % 2) selectedSampleTile.frameY--;
            cout << selectedSampleTile.height << " " << selectedSampleTile.width << endl;

        }
    }
    // 메인영역에서 선택된 샘플 정보로 수정
    for (int yFrame = 0; yFrame < TILE_COUNT; yFrame++) {
        for (int xFrame = 0; xFrame < TILE_COUNT; xFrame++) {
            if (PtInRect(&(tileInfo[yFrame][xFrame].selectRc), mouse)) {
                if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON)) {
                    for (int height = 0; height < selectedSampleTile.height; height+=2) {
                        if (yFrame + (height/2) >= TILE_COUNT) break;
                        for (int width = 0; width < selectedSampleTile.width; width+=2) {
                            if (xFrame + (width/2) >= TILE_COUNT) break;
                            for (int tileNumY = 0; tileNumY < 2; tileNumY++) {
                                for (int tileNumX = 0; tileNumX < 2; tileNumX++) {
                                    tileInfo[yFrame + (height / 2)][xFrame + (width / 2)].frameX[tileNumX] = selectedSampleTile.frameX + tileNumX + width;
                                    tileInfo[yFrame + (height / 2)][xFrame + (width / 2)].frameY[tileNumY] = selectedSampleTile.frameY + tileNumY + height;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (KeyManager::GetSingleton()->IsOnceKeyDown('P')) 
    {
        check = true;
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp('P'))
    {
        check = false;
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp('S'))
    {
        Save();
    }

    if (KeyManager::GetSingleton()->IsOnceKeyUp('L'))
    {
        Load();
    }
}

void TilemapToolScene::Render(HDC hdc)
{
    // 메인 영역
    for (int i = 0; i < TILE_COUNT; i++) {
        for (int j = 0; j < TILE_COUNT; j++) {
            for (int tileNumY = 0; tileNumY < 2; tileNumY++) {
                for (int tileNumX = 0; tileNumX < 2; tileNumX++) { 
                    if (tileInfo[i][j].isDes[tileNumY][tileNumX]) {
                        sampleImage->Render(hdc,
                            tileInfo[i][j].rc[tileNumY][tileNumX].left + (TILE_SIZE / 2),
                            tileInfo[i][j].rc[tileNumY][tileNumX].top + (TILE_SIZE / 2),
                            tileInfo[i][j].frameX[tileNumX],
                            tileInfo[i][j].frameY[tileNumY]);
                        if (check) {
                            Rectangle(hdc,
                                tileInfo[i][j].rc[tileNumY][tileNumX].left,
                                tileInfo[i][j].rc[tileNumY][tileNumX].top,
                                tileInfo[i][j].rc[tileNumY][tileNumX].right,
                                tileInfo[i][j].rc[tileNumY][tileNumX].bottom);
                        }
                    }
                }
            }
        }
    }

    // 선택된 타일
    sampleImage->Render(
        hdc,
        TILEMAPTOOL_SIZE_X - 250,
        TILEMAPTOOL_SIZE_Y - 150,
        selectedSampleTile.frameX,
        selectedSampleTile.frameY,
        selectedSampleTile.width,
        selectedSampleTile.height,
        10.0f);

    // 샘플 영역
    sampleImage->Render(
        hdc,
        TILEMAPTOOL_SIZE_X - sampleImage->GetWidth() + sampleImage->GetWidth() / 2,
        sampleImage->GetHeight() / 2);
}

void TilemapToolScene::Release()
{
}

void TilemapToolScene::Save()
{
    int saveIndex;
    cout << "세이브할 맵의 번호를 입력하여 주십시오. : ";
    cin >> saveIndex;
    string saveFileName = "Save/saveMapData_" + to_string(saveIndex);
    saveFileName += ".map";


    HANDLE hFile = CreateFile(saveFileName.c_str(),
        GENERIC_WRITE,          // 읽기, 쓰기
        0, NULL,                // 공유, 보안 모드
        CREATE_ALWAYS,          // 파일 만들거나 읽을 때 옵션
        FILE_ATTRIBUTE_NORMAL,  // 파일 속성(읽기 전용, 숨김 등등)
        NULL);

    // 쓰기
    DWORD byteSize = sizeof(tagTile) * TILE_COUNT * TILE_COUNT;

    DWORD writtenByte;
    if (WriteFile(hFile,    // 파일 핸들
        tileInfo,       // 메모리 시작주소
        sizeof(tagTile) * TILE_COUNT * TILE_COUNT,  // 메모리 크기
        &writtenByte,   // 실제 쓰여진 파일 용량
        NULL) == false)          // ???
    {
        MessageBox(g_hWnd, "맵 데이터 저장에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
}

void TilemapToolScene::Load()
{
    int loadIndex;
    cout << "로드할 맵의 번호를 입력하여 주십시오. : ";
    cin >> loadIndex;
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
    if (ReadFile(hFile, tileInfo, sizeof(tagTile) * TILE_COUNT * TILE_COUNT,
        &readByte, NULL) == false)
    {
        MessageBox(g_hWnd, "맵 데이터 로드에 실패했습니다.", "에러", MB_OK);
    }

    CloseHandle(hFile);
}
