#pragma once
#include "Config.h"
#include "GameEntity.h"

class Image;
class PlayerTank;
class EnemyTankManager;
class BattleScene;
class TotalScene : public GameEntity
{
private:
	Image* hiScore;
	Image* wNumberImage[10];
	Image* player1;
	Image* points;
	Image* scoreNumber;
	Image* wStage;
	Image* totalScoreWord;
	Image* enemyTankImage;
	Image* arrow;
	PlayerTank* playerTank;
	EnemyTankManager* enemyTanks;

	Image* gameOver;
	float gameOverPos;
	
	Image* gameClear;
	float gameClearPos;


	BattleScene* test;
	
	int stageNum;

	int totalNormal;
	int totalFastMove;
	int totalFastShoot;
	int totalBigTank;
	int totalDestroy;
	int totalScore;
	int prevTotalScore;

	float nextSceneTime;
	float sceneChangeTime;

	inline void SetPlayerTank(PlayerTank& playerTank) { this->playerTank = &playerTank; }
	inline void SetEnemyTank(EnemyTankManager& enemyTank) { this->enemyTanks = &enemyTank; }

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void ScoreRender(HDC hdc, int i);
};

