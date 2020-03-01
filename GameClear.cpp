#include "stdafx.h"
#include "GameClear.h"

GameClear::GameClear()
{
}

GameClear::~GameClear()
{
}

HRESULT GameClear::init()
{
	BYTE	CoolTime;

	return S_OK;
}

void GameClear::release()
{
}

void GameClear::update()
{
	EFFECTMANAGER->update();
	CoolTime++;

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && CoolTime > 100)
	{
		DATAMANAGER->Delete_Enemy();
		DATAMANAGER->Delete__flyObject();

		SCENEMANAGER->changeScene("Intro");
	}
}

void GameClear::render()
{
	IMAGEMANAGER->findImage("clearGame")->render(getMemDC(), 0, 0);

}
