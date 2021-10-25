#include "ScoreManager.h"
#include "EnemyTankManager.h"
#include "Config.h"
void ScoreManager::Init()
{
	totalNormal = 0;
	totalFastMove = 0;
	totalFastShoot = 0;
	totalBigTank = 0;
	totalDestroy = 0;
	itemBonusPoint = 0;
	playerIsDead = false;
}

void ScoreManager::Release()
{

}

void ScoreManager::Update(PlayerTank& playerTank, EnemyTankManager& enemyTank)
{
	totalNormal = enemyTank.GetTotalNormal();
	totalFastMove = enemyTank.GetTotalFastMove();
	totalFastShoot = enemyTank.GetTotalFastShoot();
	totalBigTank = enemyTank.GetTotalBigTank();
	itemBonusPoint = enemyTank.GetItemBonusPoint();

	if (KeyManager::GetSingleton()->IsOnceKeyDown('M'))
	{
		totalNormal++;
		totalScore += 100;	
		prevTotalScore += 100;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('N'))
	{
		totalFastMove++;
		totalScore += 200;
		prevTotalScore += 200;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('B'))
	{
		totalFastShoot++;
		totalScore += 300;
		prevTotalScore += 300;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('V'))
	{
		totalBigTank++;
		totalScore += 400;
		prevTotalScore += 400;
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))
	{
		itemBonusPoint++;
		totalScore += 500;
		prevTotalScore += 500;
	}
	totalDestroy = totalNormal + totalFastMove + totalFastShoot + totalBigTank;

	if (totalScore > 20000)		totalScore = totalScore - 20000;
	if (prevTotalScore > 1000000) prevTotalScore = prevTotalScore - 1000000;

	//cout << totalNormal << " / " << totalFastMove << " / " << totalFastShoot << " / " 
	//	<< totalBigTank << " / " << totalDestroy << " / "  << itemBonusPoint << " / " 
	//	<< totalScore << " / " << prevTotalScore << endl;

}

void ScoreManager::Render(HDC hdc)
{
}

void ScoreManager::SetData(PlayerTank& playerTank, EnemyTankManager& enemyTank)
{
	SetPlayerTank(playerTank);
	SetEnemyTank(enemyTank);
}
