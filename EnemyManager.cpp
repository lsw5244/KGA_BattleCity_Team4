#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
	enemyMaxCount = 10;

	// ������Ÿ�� : Enemy* �����͸� 10���� ����, ����
	vecEnemys.resize(enemyMaxCount);

	for (int i = 0; i < enemyMaxCount; i++)
	{
		vecEnemys[i] = new Enemy;
		vecEnemys[i]->Init();
		POINTFLOAT pos{ 100.0f + (i % 5) * 100.0f, 100.0f + (i / 5) * 80.0f };
		vecEnemys[i]->SetPos(pos);
	}

	// ������Ÿ�� : Enemy* ������ 10���� ������ �� �ִ� �޸𸮸� Ȯ��
	//vecEnemys.reserve(10);
	//int count = vecEnemys.size();

	//cout << "reserve count : " << count << endl;

	//for (int i = 0; i < 10; i++)
	//{
	//	vecEnemys.push_back(new Enemy);
	//	vecEnemys[i]->Init();
	//}

	//// ������ 10��¥�� �迭
	//for (int i = 0; i < 10; i++)
	//{
	//	enemy[i] = new Enemy;
	//	enemy[i]->Init();
	//	POINTFLOAT pos { 100.0f + (i % 5) * 100.0f, 100.0f + (i / 5) * 80.0f };
	//	enemy[i]->SetPos(pos);
	//}

	return S_OK;
}

void EnemyManager::Update()
{
	for (itEnemys = vecEnemys.begin();
		itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Update();
	}

	//for (int i = 0; i < enemyMaxCount; i++)
	//{
	//	vecEnemys[i]->Update();
	//}
}

void EnemyManager::Render(HDC hdc)
{
	for (itEnemys = vecEnemys.begin();
		itEnemys != vecEnemys.end(); itEnemys++)
	{
		(*itEnemys)->Render(hdc);
	}

	//for (int i = 0; i < enemyMaxCount; i++)
	//{
	//	vecEnemys[i]->Render(hdc);
	//}
}

void EnemyManager::Release()
{
	for (itEnemys = vecEnemys.begin();
		itEnemys != vecEnemys.end(); itEnemys++)
	{
		SAFE_RELEASE((*itEnemys));
	}
	vecEnemys.clear();

	//for (int i = 0; i < enemyMaxCount; i++)
	//{
	//	SAFE_RELEASE(vecEnemys[i]);
	//}
	//vecEnemys.clear();
}

void EnemyManager::AddEnemy(float posX, float posY)
{
}
