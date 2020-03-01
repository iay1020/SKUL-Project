#include "stdafx.h"
#include "GameOver.h"

GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

HRESULT GameOver::init()
{
	CoolTime = 0;

	return S_OK;
}

void GameOver::release()
{
}

void GameOver::update()
{
	EFFECTMANAGER->update();
	CoolTime++;

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && CoolTime > 100)
	{
		DATAMANAGER->Delete_Enemy();
		DATAMANAGER->Delete__flyObject();
		
		SCENEMANAGER->changeScene("Stage_0");
	}
}

void GameOver::render()
{
	IMAGEMANAGER->findImage("gameOver")->render(getMemDC(), 0, 0);
}
