#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Ammo : public GameObject
{
private:
	MoveDir dir;
	bool isAlive;

	Image* boom_Effect;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	void Fire();
};

