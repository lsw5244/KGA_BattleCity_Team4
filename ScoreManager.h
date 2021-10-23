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

	bool playerIsDead;	// �÷��̾ �й����� ���
	int isStage = 1;		// ���� ��������

	inline void SetPlayerTank(PlayerTank& playerTank) { this->playerTank = &playerTank; }
	inline void SetEnemyTank(EnemyTankManager& enemyTank) { this->enemyTanks = &enemyTank; }
public:
	void Init();
	void Release();
	void Update(PlayerTank& playerTank, EnemyTankManager& enemyTank);
	void Render(HDC hdc);

	void SetData(PlayerTank& playerTank, EnemyTankManager& enemyTank);

	inline void SetPlayerIsDead(bool playerIsDead) { this->playerIsDead = playerIsDead; }
	inline bool GetPlayerIsDead() { return playerIsDead; }
	inline void AddIsStage() { if(isStage<2)this->isStage++; }
	inline int GetIsStage() { return isStage; }

	inline int GetTotalNormal() { return totalNormal; }
	inline int GetTotalFastMove() { return totalFastMove; }
	inline int GetTotalFastShoot() { return totalFastShoot; }
	inline int GetTotalBigTank() { return totalBigTank; }
	inline int GetTotalDestroy() { return totalDestroy; }
	inline int GetTotalScore() { return totalScore; }
	inline int GetPrevTotalScore() { return prevTotalScore; }

};

