#pragma once
#include "Config.h"
#include "GameObject.h"
#include "PlayerTank.h"
class EnemyTankManager;
class Item : public GameObject
{
private:
	enum class ItemState { Barrier, TimeStop, Shovel, Star, Boom, Life };
	EnemyTankManager* enemyTankManager;
	PlayerTank* playerTank;
	RECT* playerRect;
	ItemState itemState;
	float aliveTime;
	float renderTime;
	int itemNum;
	bool collCheck; 
	inline void SetPlyaerRect(PlayerTank& playerTank) { this->playerRect = playerTank.GetRect(); }
	inline void SetPlyaer(PlayerTank& playerTank) { this->playerTank = &playerTank; }
	inline void SetEnemyTankManager(EnemyTankManager& enemyTankManager) { this->enemyTankManager = &enemyTankManager; }

protected:
public:
	HRESULT Init(PlayerTank& playerTank, EnemyTankManager& enemyTankManager);
	bool ItemUpdate();
	void Render(HDC hdc);
	void Release();
};

