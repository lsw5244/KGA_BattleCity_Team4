#include "Ammo.h"
#include "Tank.h"
#include "Image.h"
#include "CommonFunction.h"

HRESULT Ammo::Init()
{
	//float x = 10.0f, y = 20.0f, h = 0.0f;
	//h = (float)sqrtf((x * x) + (y * y));


	pos.x = 0.0f;
	pos.y = 0.0f;

	bodySize = 21;

	shape.left = 0;
	shape.top = 0;
	shape.right = 0;
	shape.bottom = 0;

	moveSpeed = 8.0f;		// �ʴ� 15�ȼ� �̵�
	moveAngle = 0.0f;

	target = nullptr;

	isFire = false;
	//isAlive = true;

	ImageManager::GetSingleton()->AddImage("Image/bullet.bmp", bodySize, bodySize, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->FindImage("Image/bullet.bmp");
	if (img == nullptr)
	{
		return E_FAIL;
	}

	return S_OK;
}

void Ammo::Update()
{
	//if (isAlive == false)	return;

	if (isFire)
	{
		// Ÿ���� ���� ���� ���� ������ ����ȴ�.
		if (target)
		{
			float targetAngle = atan2f(-(target->GetPos().y - pos.y),
				(target->GetPos().x - pos.x));

			cout << "1. TargetAngle : " << targetAngle << endl;
			cout << "1. MoveAngle : " << moveAngle << endl << endl;

			float tempAngle;
			float ratio = 9.0f;
			if (GetDistance(target->GetPos(), pos) < 230.0f)
			{
				ratio = 3.0f;
			}
			if ((targetAngle - moveAngle) > PI)
			{
				tempAngle = ((targetAngle - PI2) - moveAngle) / ratio;
				cout << "2_1. tempAngle : " << tempAngle << endl;
			}
			else if ((targetAngle - moveAngle) < -PI)
			{
				tempAngle = ((targetAngle + PI2) - moveAngle) / ratio;
				cout << "2_2. tempAngle : " << tempAngle << endl;
			}
			else
			{
				tempAngle = (targetAngle - moveAngle) / ratio;
				cout << "2_0. tempAngle : " << tempAngle << endl;
			}

			moveAngle += tempAngle;
			if (moveAngle > PI2)
			{
				moveAngle -= PI2;
			}
			else if (moveAngle < -PI2)
			{
				moveAngle += PI2;
			}

			cout << "2. TargetAngle : " << targetAngle << endl;
			cout << "2. MoveAngle : " << moveAngle << endl << endl;


			//RotateToTarget(target->GetPos());
		}

		pos.x += cos(moveAngle) * moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();		// �����Ӵ� �̵��Ÿ� -> �ð� �� �̵��Ÿ�
		pos.y -= sin(moveAngle) * moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();

		shape.left = pos.x - (bodySize / 2.0f);
		shape.top = pos.y - (bodySize / 2.0f);
		shape.right = pos.x + (bodySize / 2.0f);
		shape.bottom = pos.y + (bodySize / 2.0f);

		// Ÿ�ٰ��� �浹Ȯ��
		if (CheckCollision())
		{
			isFire = false;
			target->SetIsAlive(false);
		}

		// ȭ���� ������� Ȯ��
		if (shape.left > WIN_SIZE_X || shape.right < 0 ||
			shape.top > WIN_SIZE_Y || shape.bottom < 0)
		{
			isFire = false;
		}
	}
}

void Ammo::RotateToTarget(POINTFLOAT targetPos)
{
	if (!isFire) return;

	float toTargetAngle = moveAngle -
		atan2(-(targetPos.y - pos.y), targetPos.x - pos.x);

	if (toTargetAngle > PI)
	{
		toTargetAngle = -(PI * 2 - toTargetAngle);
	}
	else if (toTargetAngle < -PI)
	{
		toTargetAngle = PI * 2 + toTargetAngle;
	}

	if (toTargetAngle > 0)
	{
		moveAngle -= DEGREE_TO_RADIAN(5.0f);
	}
	else
	{
		moveAngle += DEGREE_TO_RADIAN(5.0f);
	}
}

void Ammo::SetIsFire(bool fire)
{
	this->isFire = fire;
}

void Ammo::Render(HDC hdc)
{
	//if (isAlive == false)	return;

	if (isFire)
	{
		img->Render(hdc, pos.x, pos.y);
		//Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Ammo::Release()
{
}

bool Ammo::CheckCollision()
{
	// ��� �̻��ϰ� �� ��ũ�� �浹�ߴ��� �Ǵ��ұ�?

	if (!target)	return false;

	// �� ���� ��ǥ�� �Ÿ� ���
	POINTFLOAT ammoPos = pos;
	POINTFLOAT targetPos = target->GetPos();

	float distance = sqrtf((ammoPos.x - targetPos.x) * (ammoPos.x - targetPos.x)
		+ (ammoPos.y - targetPos.y) * (ammoPos.y - targetPos.y));

	// �������� �� ���
	float ammoRadius = bodySize / 2.0f;
	float targetRadius = target->GetBodySize() / 2.0f;

	float sum = ammoRadius + targetRadius;

	// �� (�������� ���� �� ũ�� �浹)
	if (distance < sum)
		return true;

	return false;
}

Ammo::Ammo()
{
}

Ammo::~Ammo()
{
}
