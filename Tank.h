#pragma once
#include "GameObject.h"
#include"Config.h"

class Tank : public GameObject
{
private:
	int hp;
	MoveDir moveDir;
public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

