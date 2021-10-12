#include "TitleScene.h"
#include "Config.h"
#include "Image.h"
#include "Button.h"
#include "ButtonFunction.h"

HRESULT TitleScene::Init()
{
	// Ÿ��Ʋ������ ����� UI �̹����� �ε��س���.
	ImageManager::GetSingleton()->AddImage("Image/button.bmp", 122, 62, 1, 2);

	ImageManager::GetSingleton()->AddImage("Image/bin.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/bin.bmp");

	btnFunction = new ButtonFunction();

	btnGotoBattle = new Button();
	btnGotoBattle->Init(100, 100);
	// ��ư�� ��� ����(�Լ� �����Ϳ� Ư���Լ� �ּҼ��� : ���̵�)
	// �Ű����� (� ������, � �ε�����)
	arg = new ArgumentFuncPtr;
	arg->sceneName = "������";
	arg->loadingSceneName = "�ε���";
	btnGotoBattle->SetFunc(&ButtonFunction::ChangeScene, btnFunction, arg);

	btnQuitProgram = new Button();
	btnQuitProgram->Init(WIN_SIZE_X - 100, 100);
	// ��ư�� ��� ����(�Լ� �����Ϳ� Ư���Լ� �ּҼ��� : �ݱ�)
	btnQuitProgram->SetFunc(&ButtonFunction::QuitProgram, btnFunction);

	return S_OK;
}

void TitleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene("������", "�ε���");
		return;
	}

	if (btnGotoBattle)
		btnGotoBattle->Update();
	if (btnQuitProgram)
		btnQuitProgram->Update();
}

void TitleScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);

	if (btnGotoBattle)
		btnGotoBattle->Render(hdc);
	if (btnQuitProgram)
		btnQuitProgram->Render(hdc);
}

void TitleScene::Release()
{
	SAFE_RELEASE(btnGotoBattle);
	SAFE_RELEASE(btnQuitProgram);
	SAFE_DELETE(btnFunction);
	SAFE_DELETE(arg);
}
