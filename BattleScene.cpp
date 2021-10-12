#include "BattleScene.h"
#include "Image.h"
#include "Tank.h"
#include "EnemyManager.h"

HRESULT BattleScene::Init()
{

	return S_OK;
}

void BattleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		SceneManager::GetSingleton()->ChangeScene("≈∏¿Ã∆≤æ¿");
		return;
	}


}

void BattleScene::Render(HDC hdc)
{

}

void BattleScene::Release()
{
	SAFE_RELEASE(enemyMgr);
}
