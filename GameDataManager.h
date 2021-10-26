#pragma once
#include "Config.h"
#include "Singleton.h"

class GameDataManager : public Singleton<GameDataManager> {
private:
	TILE_INFO tileInfo[TILE_COUNT][TILE_COUNT];

	bool playerIsDead;		// �÷��̾ �й����� ���
	int isStage = 1;		// ���� ��������
	int isScoreStage = 1;	// ��Ż������ ǥ������ �������� �ѹ�
	int playerLife = 2;		// �÷��̾� ������
	int playerLevel = 0;	// �÷��̾� ����
public:

	inline void Release() {  }

	inline void SetPlayerLife(int playerLife) { this->playerLife = playerLife; }
	inline int GetPlayerLife() { return playerLife; }

	inline void SetPlayerLevel(int playerLevel) { this->playerLevel = playerLevel; }
	inline int GetPlayerLevel() { return playerLevel; }

	inline void SetPlayerIsDead(bool playerIsDead) { this->playerIsDead = playerIsDead; }
	inline bool GetPlayerIsDead() { return playerIsDead; }

	inline void SetStage(int stageNum) { this->isStage = stageNum; }
	inline void AddIsStage() { if (isStage < 11)this->isStage++; }
	inline int GetIsStage() { return isStage; }

	inline void SetScoreStage(int stageNum) { this->isScoreStage = stageNum; }
	inline int GetScoreStage() { return isScoreStage; }

	inline void SetTileInfo(TILE_INFO tileInfo, int y, int x) { this->tileInfo[y][x] = tileInfo; }
	inline TILE_INFO GetTileInfo(int y, int x) { return tileInfo[y][x]; }
};
