#pragma once
#include "Config.h"
#include "Singleton.h"

class PlayerTank;
class EnemyTankManager;
class ScoreManager : public Singleton<ScoreManager>
{
private:
	PlayerTank* playerTank;
	EnemyTankManager* enemyTanks;

	int totalNormal;
	int totalFastMove;
	int totalFastShoot;
	int totalBigTank;
	int totalDestroy;
	int itemBonusPoint;
	int totalScore;
	int prevTotalScore;

	inline void SetPlayerTank(PlayerTank& playerTank) { this->playerTank = &playerTank; }
	inline void SetEnemyTank(EnemyTankManager& enemyTank) { this->enemyTanks = &enemyTank; }
public:
	void Init(PlayerTank& playerTank, EnemyTankManager& enemyTank);
	void Release();
	void Update(PlayerTank& playerTank, EnemyTankManager& enemyTank);
	void Render(HDC hdc);

	inline int GetTotalNormal() { return totalNormal; }
	inline int GetTotalFastMove() { return totalFastMove; }
	inline int GetTotalFastShoot() { return totalFastShoot; }
	inline int GetTotalBigTank() { return totalBigTank; }
	inline int GetTotalDestroy() { return totalDestroy; }
	inline int GetTotalScore() { return totalScore; }
	inline int GetPrevTotalScore() { return prevTotalScore; }

};

