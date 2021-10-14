#pragma once
#include "Config.h"
#include "GameObject.h"

class Image;
class Ammo : public GameObject
{
private:
	MoveDir dir;
	bool isAlive;
	bool renderBoomEffect;

	float sec;

	bool isFire;

	float moveAngle;

	Image* boomEffect;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();

	inline void SetIsFire(bool fire) { this->isFire = fire; };
	inline bool GetIsFire() { return this->isFire; }

	inline void SetMoveAngle(float angle) { this->moveAngle = angle; }

	void Fire(MoveDir dir, POINTFLOAT pos);
	void DestroyAmmo();
};

