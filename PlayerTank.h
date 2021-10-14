#pragma once
#include "Tank.h"

class Image;
class PlayerTank : public  Tank
{
private:
	Image* playerTank;
	
	int Level;
	int elapsedCount;
	
	bool isFire;
public:

	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
};

