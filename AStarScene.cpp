#include "AStarScene.h"
#include "CommonFunction.h"

HRESULT AstarTile::Init()
{
	return E_NOTIMPL;
}

HRESULT AstarTile::Init(int idX, int idY)
{
	this->idX = idX;
	this->idY = idY;

	center.x = idX;// *ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);
	center.y = idY;// *ASTAR_TILE_SIZE + (ASTAR_TILE_SIZE / 2);

	rc.left = idX * ASTAR_TILE_SIZE;
	rc.top = idY * ASTAR_TILE_SIZE;
	rc.right = rc.left + ASTAR_TILE_SIZE;
	rc.bottom = rc.top + ASTAR_TILE_SIZE;

	F = 0.0f;	G = 0.0f;	H = 0.0f;

	type = AstarTileType::None;

	color = RGB(205, 255, 205);
	hBrush = CreateSolidBrush(color);

	hTypeBrush[AstarTileType::Start] = CreateSolidBrush(RGB(206, 9, 53));
	hTypeBrush[AstarTileType::Dest] = CreateSolidBrush(RGB(61, 209, 95));
	hTypeBrush[AstarTileType::Wall] = CreateSolidBrush(RGB(94, 94, 94));
	hTypeBrush[AstarTileType::Walkable] = CreateSolidBrush(RGB(194, 194, 194));
	hTypeBrush[AstarTileType::Curr] = CreateSolidBrush(RGB(255, 0, 255));
	hTypeBrush[AstarTileType::Closed] = CreateSolidBrush(RGB(0, 0, 0));
	hTypeBrush[AstarTileType::Path] = CreateSolidBrush(RGB(0, 255, 0));
	hTypeBrush[AstarTileType::None] = CreateSolidBrush(RGB(205, 255, 205));

	//HBRUSH hOldBrush;

	return S_OK;
}

void AstarTile::Update()
{
}

void AstarTile::Render(HDC hdc)
{
	hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	//FillRect(hdc, &rc, hBrush);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	char szTemp[128];
	wsprintf(szTemp, "F : %d", (int)F);
	TextOut(hdc, rc.left + 3, rc.top + 3, szTemp, strlen(szTemp));

	wsprintf(szTemp, "G : %d", (int)G);
	TextOut(hdc, rc.left + 3, rc.top + 23, szTemp, strlen(szTemp));

	wsprintf(szTemp, "H : %d", (int)H);
	TextOut(hdc, rc.left + 3, rc.top + 43, szTemp, strlen(szTemp));

	SelectObject(hdc, hOldBrush);
}

void AstarTile::Release()
{
	for (int i = 0; i < AstarTileType::End; i++)
	{
		DeleteObject(hTypeBrush[i]);
	}

	DeleteObject(hBrush);
}

void AstarTile::SetType(AstarTileType type)
{
	this->type = type;

	hBrush = hTypeBrush[type];
}

HRESULT AStarScene::Init()
{
	SetWindowSize(30, 30, TILEMAPTOOL_SIZE_X, TILEMAPTOOL_SIZE_Y);


	for (int i = 0; i < ASTAR_TILE_COUNT; i++)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)
		{
			map[i][j].Init(j, i);
		}
	}
	currTile = nullptr;

	return S_OK;
}

void AStarScene::Update()
{
	RECT astarArea = { 0, 0,
		ASTAR_TILE_COUNT * ASTAR_TILE_SIZE,
		ASTAR_TILE_COUNT * ASTAR_TILE_SIZE };

	if (PtInRect(&astarArea, g_ptMouse))
	{
		int idX = g_ptMouse.x / ASTAR_TILE_SIZE;
		int idY = g_ptMouse.y / ASTAR_TILE_SIZE;

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
			{
				map[startPoint.y][startPoint.x].SetType(AstarTileType::None);
				map[idY][idX].SetType(AstarTileType::Start);

				startPoint.x = idX;
				startPoint.y = idY;

				currTile = &(map[idY][idX]);
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
			{
				map[destPoint.y][destPoint.x].SetType(AstarTileType::None);
				map[idY][idX].SetType(AstarTileType::Dest);

				destPoint.x = idX;
				destPoint.y = idY;
			}
			else
			{
				map[idY][idX].SetType(AstarTileType::Wall);
			}
		}
		else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RBUTTON))
		{
			map[idY][idX].SetType(AstarTileType::None);
		}
	}

	// ����Ű ������ ��ã�� 1, 2 ���� ����
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		FindPath();
	}
}

void AStarScene::Render(HDC hdc)
{
	for (int i = 0; i < ASTAR_TILE_COUNT; i++)
	{
		for (int j = 0; j < ASTAR_TILE_COUNT; j++)
		{
			map[i][j].Render(hdc);
		}
	}
}

void AStarScene::Release()
{
}

void AStarScene::FindPath()
{
	if (AddOpenList(currTile))
	{
		currTile = GetMinFTile();
		currTile->SetType(AstarTileType::Curr);
	}
	else
	{
		// ��θ� ����Ѵ�.
		PrintPath();
	}
}

bool AStarScene::AddOpenList(AstarTile* currTile)
{
	int tempIdX, tempIdY;
	for (int i = -1; i <= 1; i += 2)	// ����
	{
		if (currTile->GetIdY() == 0 && i == -1)	continue;
		if (currTile->GetIdY() == ASTAR_TILE_COUNT - 1 && i == 1)	continue;

		tempIdY = currTile->GetIdY() + i;
		tempIdX = currTile->GetIdX();

		if (map[tempIdY][tempIdX].GetType() == AstarTileType::Dest)
		{
			map[destPoint.y][destPoint.x].SetParentTile(currTile);
			return false;
		}

		// �����¿��� ����� �̵��� �� �ִ� Ÿ���̸� ���¸���Ʈ�� �߰�
		if (map[tempIdY][tempIdX].GetType() == AstarTileType::None)// ||
			//map[tempIdY][tempIdX].GetType() == AstarTileType::Walkable)
		{
			map[tempIdY][tempIdX].SetType(AstarTileType::Walkable);
			map[tempIdY][tempIdX].SetParentTile(currTile);
			openList.push_back(&(map[tempIdY][tempIdX]));
		}
	}

	for (int j = -1; j <= 1; j += 2)	// �¿�
	{
		if (currTile->GetIdX() == 0 && j == -1)	continue;
		if (currTile->GetIdX() == ASTAR_TILE_COUNT - 1 && j == 1)	continue;

		tempIdX = currTile->GetIdX() + j;
		tempIdY = currTile->GetIdY();

		if (map[tempIdY][tempIdX].GetType() == AstarTileType::Dest)
		{
			map[destPoint.y][destPoint.x].SetParentTile(currTile);
			return false;
		}

		// �����¿��� ��尡 �̵��� �� �ִ� Ÿ���̸� ���¸���Ʈ�� �߰�
		if (map[tempIdY][tempIdX].GetType() == AstarTileType::None)// ||
			//map[tempIdY][tempIdX].GetType() == AstarTileType::Walkable)
		{
			map[tempIdY][tempIdX].SetType(AstarTileType::Walkable);
			map[tempIdY][tempIdX].SetParentTile(currTile);
			openList.push_back(&(map[tempIdY][tempIdX]));
		}
	}

	currTile->SetType(AstarTileType::Closed);

	return true;
}

AstarTile* AStarScene::GetMinFTile()
{
	float F, G, H;
	//int minI = INT_MAX;
	float minF = FLT_MAX;

	vector<AstarTile*>::iterator it = openList.begin();
	vector<AstarTile*>::iterator itTemp;
	for (; it != openList.end(); it++)
	{
		G = (*it)->GetParentTile()->GetG() + 10;
		(*it)->SetG(G);
		//float h = /*���� ��忡�� ������ �������� ���� ���*/
		H = GetDistance((*it)->GetCenter(),
			map[destPoint.y][destPoint.x].GetCenter()) * 10;
		(*it)->SetH(H);

		F = G + H;
		(*it)->SetF(F);

		if (minF > F)
		{
			minF = F;
			itTemp = it;
			//currTile = (*it);
		}
	}

	currTile = (*itTemp);
	openList.erase(itTemp);

	return currTile;
}

void AStarScene::PrintPath()
{
	AstarTile* currPathTile = &(map[destPoint.y][destPoint.x]);

	while (currPathTile != &(map[startPoint.y][startPoint.x]))
	{
		currPathTile->SetType(AstarTileType::Path);
		currPathTile = currPathTile->GetParentTile();
	}
}
