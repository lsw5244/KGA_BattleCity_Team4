#include "TitleScene.h"
#include "Config.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunction.h"
HRESULT TitleScene::Init()
{
	// 타이틀씬에서 사용할 UI 이미지도 로드해놓자.
	ImageManager::GetSingleton()->AddImage("Image/Title/background.bmp", 256, 224);
	backGround = ImageManager::GetSingleton()->FindImage("Image/Title/background.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Title/Title.bmp", 256, 224);
	titleBackGround = ImageManager::GetSingleton()->FindImage("Image/Title/Title.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Title/PlayerSelect.bmp", 30, 15, 2, 1, true, RGB(255,0,255));
	plyaerSelect = ImageManager::GetSingleton()->FindImage("Image/Title/PlayerSelect.bmp");
	arg = new ArgumentFuncPtr;
	arg->sceneName = "전투씬";
	arg->loadingSceneName = "로딩씬";
	
	Player_1p = true;
	selectFrame = 0;
	titlePos.x = 256 / 2;
	titlePos.y = 224 * 2;
	selectPos.y = -10;
	selectPos.x = 75;
	// 버튼의 기능 셋팅(함수 포인터에 특정함수 주소설정 : 닫기)

	time = 0.0f;
	return S_OK;
}

void TitleScene::Update()
{
	time += TimerManager::GetSingleton()->GetDeltaTime();
	if (titlePos.y > 224 / 2) {
		titlePos.y -= (100 * TimerManager::GetSingleton()->GetDeltaTime());
		if (KeyManager::GetSingleton()->IsOnceKeyDown('Z')) titlePos.y = 224 / 2;
	
	} else {
		titlePos.y = 224 / 2;

		if (time > 0.1f) {
			time = 0.0f;
			selectFrame ? selectFrame = 0 : selectFrame = 1;
		}

		if (Player_1p) {
			selectPos.y = 130;
		}
		else {
			selectPos.y = 147;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP) || KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
		{
			Player_1p = !Player_1p;
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('Z')) {
			SceneManager::GetSingleton()->ChangeScene("전투씬", "로딩씬");
			return;
		}
	}


}

void TitleScene::Render(HDC hdc)
{
	backGround->Render(hdc, backGround->GetWidth() / 2, backGround->GetHeight() / 2);
	titleBackGround->Render(hdc, titlePos.x, titlePos.y);
	plyaerSelect->Render(hdc, selectPos.x, selectPos.y, selectFrame, 0);
}

void TitleScene::Release()
{
	SAFE_DELETE(btnFunction);
	SAFE_DELETE(arg);
}
