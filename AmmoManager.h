#pragma once
#include "Config.h"
#include "GameEntity.h"

class GameObject;
class Ammo;
class AmmoManager : public GameEntity
{
private:
	vector<Ammo*> vecAmmos;
	vector<Ammo*>::iterator itAmmos;

	int ammoMaxCount;

	GameObject* owner;		// ����� ���� ��ĳ���� ���

	/*
		GameObject

		Enemy			Tank

		Orc		Dragon		Warrior ...
	*/

public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void Fire();

	inline void SetOwner(GameObject* owner) { this->owner = owner; }
};

