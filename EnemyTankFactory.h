#pragma once
#include "Config.h"
#include "GameObject.h"
#include <vector>
using namespace std;
class PlayerTank;
class EnemyTanks;
class EnemyTankFactory
{
private:
protected:
	virtual EnemyTanks* CreateEnemyTank() = 0;

public:
	vector<EnemyTanks*> vecEnemyTank;
	void NewEnemyTank(TILE_INFO(*tileInfo)[TILE_COUNT], PlayerTank& playerTank, int posX);
	void SetVecEnemyTanks(vector<EnemyTanks*> vecEnemyTank, int num);
	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;

	EnemyTankFactory() {}
	~EnemyTankFactory();
};

class NormalTankFactory : public EnemyTankFactory
{
	virtual EnemyTanks* CreateEnemyTank() override;

public:

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	NormalTankFactory() {}
	~NormalTankFactory();
};

class FastMoveTankFactory : public EnemyTankFactory
{
	virtual EnemyTanks* CreateEnemyTank() override;

public:

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	FastMoveTankFactory() {}
	~FastMoveTankFactory();
};

class FastShootTankFactory : public EnemyTankFactory
{
	virtual EnemyTanks* CreateEnemyTank() override;

public:

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	FastShootTankFactory() {}
	~FastShootTankFactory();
};

class BigTankFactory : public EnemyTankFactory
{
	virtual EnemyTanks* CreateEnemyTank() override;

public:

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	BigTankFactory() {}
	~BigTankFactory();
};

