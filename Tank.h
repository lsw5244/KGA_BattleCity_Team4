#pragma once
#include "Config.h"
#include "GameObject.h"
#include "Ammo.h"

class Tank : public GameObject	// ��Ӱ���
{
public:
	TankType type;
	// 
	// GameObject ��� ����
	// ��ġ, ���, �̵��ӵ�

	// ��ü ��� ����
	// ���� (�� ���� ��ǥ)
	POINTFLOAT barrelEnd;
	float barrelSize;
	float barrelAngle;

	int ammoCount;
	Ammo* ammoPack;
	//Ammo ammo[ammoCount];

	MoveDir moveDir;

	bool isAlive;


public:
	HRESULT Init(TankType type);		// �θ�Ŭ������ �Լ� �� ����� �ٸ� ����
	void Update();		// �������̵��� �Ѵ�
	void Render(HDC hdc);
	void Release();

	void RotateBarrelAngle(float rotateAngle);
	void Fire();
	void Reload();
	void AutoMove();
	void ProcessInputKey();

	// �ǽ�3. ��ũ�� �����¿�(WASD)�� ����������.
	void Move(MoveDir dir);

	inline void SetBarrelAngle(float angle) { this->barrelAngle = angle; }
	inline void SetIsAlive(bool alive) { this->isAlive = alive; }

	Tank();
	~Tank();
};

