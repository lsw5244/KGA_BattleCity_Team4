#include "TotalScene.h"
#include "CommonFunction.h"
#include "Image.h"
#include "ScoreManager.h"
#include "TimerManager.h"
#include "SceneManager.h"

HRESULT TotalScene::Init()
{
	SetWindowSize(300, 20, WIN_SIZE_X * 4, WIN_SIZE_Y * 4);
	windowX = WIN_SIZE_X, windowY = WIN_SIZE_Y;

	hiScore = ImageManager::GetSingleton()->FindImage("Image/Text/HISocre.bmp");

	for (int i = 0; i < 10; i++)
	{
		wNumberImage[i] = ImageManager::GetSingleton()->FindImage("Image/Text/Number_w.bmp");
	}
	player1 = ImageManager::GetSingleton()->FindImage("Image/Text/Player1.bmp");
	points = ImageManager::GetSingleton()->FindImage("Image/Text/PTS.bmp");
	scoreNumber = ImageManager::GetSingleton()->FindImage("Image/Text/ScoreNumber.bmp");
	wStage = ImageManager::GetSingleton()->FindImage("Image/Text/Stage_w.bmp");
	enemyTankImage = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	arrow = ImageManager::GetSingleton()->FindImage("Image/Icon/Arrow.bmp");
	totalScoreWord = ImageManager::GetSingleton()->FindImage("Image/Text/TotalScore.bmp");
	gameOver = ImageManager::GetSingleton()->FindImage("Image/Title/ScoreGameOver.bmp");
	gameClear = ImageManager::GetSingleton()->FindImage("Image/Title/GameClear.bmp");

	gameOverPos = WIN_SIZE_Y + (gameOver->GetHeight() / 2);
	gameClearPos = WIN_SIZE_Y + (gameClear->GetHeight() / 2);
	nextSceneTime = 0;
	sceneChangeTime = 3;
	stageNum = ScoreManager::GetSingleton()->GetIsStage();
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


	nextSceneTime += TimerManager::GetSingleton()->GetDeltaTime();
	if (ScoreManager::GetSingleton()->GetPlayerIsDead()) {	// 플레이어 사망시
		if (nextSceneTime > sceneChangeTime) {
			if (gameOverPos > WIN_SIZE_Y / 2) {
				gameOverPos -= 80 * TimerManager::GetSingleton()->GetDeltaTime();
			}
		}
		if (nextSceneTime > sceneChangeTime + 3) {
			if (ScoreManager::GetSingleton()->GetPlayerIsDead()) {
				ScoreManager::GetSingleton()->SetStage(1);
				SceneManager::GetSingleton()->ChangeScene("TitleScene");
			}
		}
	}
	else if (!ScoreManager::GetSingleton()->GetPlayerIsDead()) {
		if (stageNum != 11) {
			if (nextSceneTime > sceneChangeTime) {		// 스테이지 클리어후 다음스테이지 전환
				if (!ScoreManager::GetSingleton()->GetPlayerIsDead()) {
					SceneManager::GetSingleton()->ChangeScene("BattleScene");
				}
			}
		}
		else {	// 10스테이지 클리어 했을 경우
			if (nextSceneTime > sceneChangeTime) {
				if (gameClearPos > WIN_SIZE_Y / 2) {
					gameClearPos -= 80 * TimerManager::GetSingleton()->GetDeltaTime();
				}
			}
			if (nextSceneTime > sceneChangeTime + 4) {	
				ScoreManager::GetSingleton()->SetStage(1);
				SceneManager::GetSingleton()->ChangeScene("TitleScene");
			}
		}
	}
}

void TotalScene::Render(HDC hdc)
{
	if (nextSceneTime > sceneChangeTime) {
		gameOver->Render(hdc, WIN_SIZE_X / 2, gameOverPos);
		gameClear->Render(hdc, WIN_SIZE_X / 2, gameClearPos);
		return;
	}

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
	//
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
