#pragma once
#include "GameObject.h"
#include"Config.h"

class EnemyTank;
class Tank : public GameObject
{
protected:
	int hp;
	MoveDir moveDir;

	vector<EnemyTank*> vecEnemyTanks;
	vector<EnemyTank*>::iterator itEnemyTanks;

	EnemyTankType enemyType;

	int enemyMaxCount;
	//enum class EnemyTankType { Normal, FastMove, QuickFire, Big, iNormal, iFastMove, iQuickFire, iBig, End };

	int nCount, fMCount, qFCount, bigCount, iNCount, iFMCount, iQFCount, iBigCount;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void AddEnemy(int nCount = 0, int fMCount = 0, int qFCount = 0, int bigCount = 0, int iNCount = 0, int iFMCount = 0, int iQFCount = 0, int iBigCount = 0);
};

