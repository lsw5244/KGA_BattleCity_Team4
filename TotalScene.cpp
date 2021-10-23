#include "TotalScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "PlayerTank.h"
#include "EnemyTankManager.h"
#include "BattleScene.h"
#include "ScoreManager.h"

HRESULT TotalScene::Init()
{
	SetWindowSize(300, 20, WIN_SIZE_X * 4, WIN_SIZE_Y * 4);
	windowX = WIN_SIZE_X, windowY = WIN_SIZE_Y;

	ImageManager::GetSingleton()->AddImage("Image/Text/HISocre.bmp", 140, 7, true, RGB(255, 0, 255));
	hiScore = ImageManager::GetSingleton()->FindImage("Image/Text/HISocre.bmp");

	for (int i = 0; i < 10; i++)
	{
		ImageManager::GetSingleton()->AddImage("Image/Text/Number_w.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
		wNumberImage[i] = ImageManager::GetSingleton()->FindImage("Image/Text/Number_w.bmp");
	}

	ImageManager::GetSingleton()->AddImage("Image/Text/Player1.bmp", 63, 7, true, RGB(255, 0, 255));
	player1 = ImageManager::GetSingleton()->FindImage("Image/Text/Player1.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Text/PTS.bmp", 22, 7, true, RGB(255, 0, 255));
	points = ImageManager::GetSingleton()->FindImage("Image/Text/PTS.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Text/ScoreNumber.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
	scoreNumber = ImageManager::GetSingleton()->FindImage("Image/Text/ScoreNumber.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Text/Stage_w.bmp", 37, 7, true, RGB(255, 0, 255));
	wStage = ImageManager::GetSingleton()->FindImage("Image/Text/Stage_w.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Enemy/Enemy.bmp", 128, 96, 8, 6, true, RGB(255, 0, 255));
	enemyTankImage = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Icon/Arrow.bmp", 8, 7, true, RGB(255, 0, 255));
	arrow = ImageManager::GetSingleton()->FindImage("Image/Icon/Arrow.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Text/TotalScore.bmp", 110, 10, true, RGB(255, 0, 255));
	totalScoreWord = ImageManager::GetSingleton()->FindImage("Image/Text/TotalScore.bmp");

	playerTank = new PlayerTank;

	enemyTanks = new EnemyTankManager;

	test = new BattleScene;
	
	return S_OK;
}

void TotalScene::Update()
{
	totalNormal = ScoreManager::GetSingleton()->GetTotalNormal();
	totalFastMove = ScoreManager::GetSingleton()->GetTotalFastMove();
	totalFastShoot = ScoreManager::GetSingleton()->GetTotalFastShoot();
	totalBigTank = ScoreManager::GetSingleton()->GetTotalBigTank();
	totalDestroy = ScoreManager::GetSingleton()->GetTotalDestroy();
	totalScore = ScoreManager::GetSingleton()->GetTotalScore();
	prevTotalScore = ScoreManager::GetSingleton()->GetPrevTotalScore();
	
}

void TotalScene::Render(HDC hdc)
{
	hiScore->Render(hdc, WIN_SIZE_X / 2, 20);	//고정
	wStage->Render(hdc, WIN_SIZE_X / 2 - 13, 36);	//고정
	for (int i = 0; i < 10; i++)
	{
		ScoreRender(hdc, i);
	}
	//wNumberImage[0]->Render(hdc, WIN_SIZE_X / 2 + 31, 36, 0, 0);	//스테이지 연결
	//
	//wNumberImage[1]->Render(hdc, WIN_SIZE_X / 2 - 21, 92, 0, 0);	//노멀 잡은 수
	//wNumberImage[2]->Render(hdc, WIN_SIZE_X / 2 - 21, 116, 0, 0);	//빠른놈 잡은 수
	//wNumberImage[3]->Render(hdc, WIN_SIZE_X / 2 - 21, 140, 0, 0);	//연사 잡은 수
	//wNumberImage[4]->Render(hdc, WIN_SIZE_X / 2 - 21, 164, 0, 0);	//왕탱 잡은 수

	//wNumberImage[5]->Render(hdc, WIN_SIZE_X / 2 - 76, 92, 0, 0);	//노멀 스코어
	//wNumberImage[6]->Render(hdc, WIN_SIZE_X / 2 - 76, 116, 0, 0);	//빠른놈 스코어
	//wNumberImage[7]->Render(hdc, WIN_SIZE_X / 2 - 76, 140, 0, 0);	//연사 스코어
	//wNumberImage[8]->Render(hdc, WIN_SIZE_X / 2 - 76, 164, 0, 0);	//왕탱 스코어
	player1->Render(hdc, WIN_SIZE_X / 2 - 74, 52);
	totalScoreWord->Render(hdc, WIN_SIZE_X / 2 - 25, 177);
	//wNumberImage[9]->Render(hdc, WIN_SIZE_X / 2 - 21, 178, 0, 0);	//종합 잡은 수

	for (int i = 0; i < 4; i++)
	{
		points->Render(hdc, WIN_SIZE_X / 2 - 54, 92 + (24 * i));
		enemyTankImage->Render(hdc, WIN_SIZE_X / 2, 92 + (24 * i), 0, i);
		arrow->Render(hdc, WIN_SIZE_X / 2 - 13, 92 + (24 * i));
	}
	
	if (prevTotalScore > 9)
	{
		if (999999 > prevTotalScore && prevTotalScore > 99999)
		{
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 90, 68, (prevTotalScore / 100000) % 5, ((prevTotalScore / 100000) / 5));
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 81, 68, ((prevTotalScore % 100000) / 10000) % 5, (((prevTotalScore / 100000) / 10000) / 5));
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 72, 68, (((prevTotalScore % 100000) % 10000) / 1000) % 5, (((prevTotalScore % 100000) % 10000) / 1000) / 5);
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 63, 68, ((((prevTotalScore % 100000) % 10000) % 1000) / 100) % 5, ((((prevTotalScore % 100000) % 10000) % 1000) / 100) / 5);
		}

		else if (99999 > prevTotalScore && prevTotalScore > 9999)
		{
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 81, 68, (prevTotalScore / 10000) % 5, ((prevTotalScore / 10000) / 5));
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 72, 68, ((prevTotalScore % 10000) / 1000) % 5, ((prevTotalScore % 10000) / 1000) / 5);
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 63, 68, (((prevTotalScore % 10000) % 1000) / 100) % 5, (((prevTotalScore % 10000) % 1000) / 100) / 5);
		}
		else if (9999 > prevTotalScore && prevTotalScore > 999)
		{
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 72, 68, (prevTotalScore / 1000) % 5, (prevTotalScore / 1000) / 5);
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 63, 68, ((prevTotalScore % 1000) / 100) % 5, ((prevTotalScore % 1000) / 100) / 5);
		}
		else if (999 > prevTotalScore && prevTotalScore > 99)
		{
			scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 63, 68, (prevTotalScore / 100) % 5, ((prevTotalScore / 100) / 5));
		}
		scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 54, 68, 0, 0);
	}
	scoreNumber->Render(hdc, WIN_SIZE_X / 2 - 45, 68, 0, 0);

}

void TotalScene::Release()
{
}

void TotalScene::ScoreRender(HDC hdc, int i)
{
	switch (i)
	{
	case 0:
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 + 31, 36, 0, 0);
		break;
	case 1:
		if (totalNormal > 9)
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 92, (totalNormal / 10) % 5, ((totalNormal / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 92, (totalNormal % 10) % 5, ((totalNormal % 10) / 5));
		break;
	case 2:
		if (totalFastMove > 9)
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 116, (totalFastMove / 10) % 5, ((totalFastMove / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 116, (totalFastMove % 10) % 5, ((totalFastMove % 10) / 5));
		break;
	case 3:
		if (totalFastShoot > 9)
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 140, (totalFastShoot / 10) % 5, ((totalFastShoot / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 140, (totalFastShoot % 10) % 5, ((totalFastShoot % 10) / 5));
		break;
	case 4:
		if (totalBigTank > 9)
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 164, (totalBigTank / 10) % 5, ((totalBigTank / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 164, (totalBigTank % 10) % 5, ((totalBigTank % 10) / 5));
		break;
	case 5:
		if (totalNormal > 9)
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 103, 92, (totalNormal / 10) % 5, ((totalNormal / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 94, 92, (totalNormal % 10) % 5, ((totalNormal % 10) / 5));
		if (totalNormal > 0);
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 85, 92, 0, 0);
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 76, 92, 0, 0);
		}
		break;
	case 6:
		if (totalFastMove * 2 > 9)
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 103, 116, (totalFastMove * 2 / 10) % 5, ((totalFastMove * 2 / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 94, 116, (totalFastMove * 2 % 10) % 5, ((totalFastMove * 2 % 10) / 5));
		if (totalFastMove > 0);
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 85, 116, 0, 0);
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 76, 116, 0, 0);
		}
		break;
	case 7:
		if (totalFastShoot * 3 > 9)
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 103, 140, (totalFastShoot * 3 / 10) % 5, ((totalFastShoot * 3 / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 94, 140, (totalFastShoot * 3 % 10) % 5, ((totalFastShoot * 3 % 10) / 5));
		if (totalFastShoot > 0);
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 85, 140, 0, 0);
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 76, 140, 0, 0);
		}
		break;
	case 8:
		if (totalBigTank * 4 > 9)
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 103, 164, (totalBigTank * 4 / 10) % 5, ((totalBigTank * 4 / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 94, 164, (totalBigTank * 4 % 10) % 5, ((totalBigTank * 4 % 10) / 5));
		if (totalBigTank > 0);
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 85, 164, 0, 0);
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 76, 164, 0, 0);
		}
		break;
	case 9:
		if (totalDestroy > 9)
		{
			wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 29, 178, (totalDestroy / 10) % 5, ((totalDestroy / 10) / 5));
		}
		wNumberImage[i]->Render(hdc, WIN_SIZE_X / 2 - 21, 178, (totalDestroy % 10) % 5, ((totalDestroy % 10) / 5));
		break;
	}
}
