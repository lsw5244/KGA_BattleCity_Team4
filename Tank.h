#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

class EnemyTank;
class Image;
class Tank : public GameObject
{
protected:
	int hp;
	MoveDir moveDir;

	Image* spawnEffect;

	vector<EnemyTank*> vecEnemyTanks;
	vector<EnemyTank*>::iterator itEnemyTanks;

	EnemyTankType enemyType;

	int enemyMaxCount, addEnemyCount, destEnemyCount;

	int onMapEnemyCount;

	float spawnTimer;

	bool spawnTank;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void AddEnemy(EnemyTankType enemyType, int addEnemyNum);
};

