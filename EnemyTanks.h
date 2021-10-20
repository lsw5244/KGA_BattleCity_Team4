#pragma once
#include "GameObject.h"
#include "Config.h"
#include "Image.h"
#include "ImageManager.h"
#include <tuple>
#include "PlayerTank.h"

class EnemyTanks : public GameObject
{
private:
protected:
	vector<EnemyTanks*> vecEnemyTanks[4];

	void CollisionAndMove(MoveDir moveDir);
	void PosReset(MoveDir moveDir);
	void TankUpdate();

	int itemTankImg(int num);
	float itemTime;
	int itemfraemY;

	int CurrFrame(Image enemyTank, int* elapsedCount, int setCurr);
	tuple<MoveDir, bool> AutoMove(MoveDir moveDir, POINTFLOAT pos);
	TILE_INFO(*tileInfo)[TILE_COUNT];
	bool spawnColl;		// ������ �ٸ� ��ũ�� �����ִ��� ����
	bool itemTank;		// �������� �����ϰ� �ִ� ��ũ���� ����

	RECT* playerRect;
	MoveDir movedir;
	int elapsedWay;
	int elapsedCount;
	float time;

	Image* spawnEffect;
	float effectTime;
	int effectFrameX;
	int effectCount;
	bool frameUp;
	bool SpawnEffect();

public:
	inline void SetTileInfo(TILE_INFO(*tileInfo)[TILE_COUNT]) { this->tileInfo = tileInfo; }
	void SetPlyaerRect(PlayerTank& playerTank) { this->playerRect = playerTank.GetRect(); }

	HRESULT TankInit(int posX, bool item);
	virtual HRESULT Init() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;
	virtual void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank, int num) = 0;
	inline RECT GetRect() { return this->shape; }

	EnemyTanks() {}
	virtual ~EnemyTanks();
};

