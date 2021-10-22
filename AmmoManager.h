#pragma once
#include "Config.h"
#include "GameEntity.h"

class Ammo;
class PlayerTank;
class EnemyTanks;
#define PLAYER_MAX_AMMO_COUNT 2
class AmmoManager : public GameEntity
{
private:
	vector<Ammo*> vecEnemyAmmos;
	vector<Ammo*>::iterator it;
	vector<EnemyTanks*> vecEnemys;

	int enemyMaxAmmoCount = 30;

	Ammo* playerAmmos[PLAYER_MAX_AMMO_COUNT];

	TILE_INFO(*tileInfo)[TILE_COUNT];

	PlayerTank* playerTank;

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void AmmoImageInit();
	void Fire(MoveDir dir, POINTFLOAT pos, TankType type, bool isFastAmmo = false, int maxAmmo = 1);
	void SetTileInfoAndEnemyVec();

	void SetTileInfo(TILE_INFO(*info)[TILE_COUNT]) { this->tileInfo = info; }
	inline void SetPlayerTank(PlayerTank* tank) { playerTank = tank; }
	inline void SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank) { this->vecEnemys = vecEnemyTank; }

	void PlayerAmmoPowerUp();
	void PlayerAmmoPowerDown();

};

