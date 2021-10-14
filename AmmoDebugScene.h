#pragma once
#include	 "GameEntity.h"
#include "Ammo.h"

class AmmoDebugScene : public GameEntity
{
private:
	Ammo* ammo;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

