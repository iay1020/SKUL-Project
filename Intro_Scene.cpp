#include "stdafx.h"
#include "Intro_Scene.h"

Intro_Scene::Intro_Scene()
{
}

Intro_Scene::~Intro_Scene()
{
}

HRESULT Intro_Scene::init()
{
	Intro_BG_0 = new image;
	Intro_BG_0 = IMAGEMANAGER->findImage("intro_BG_0");
	Intro_BG_1 = new image;
	Intro_BG_1 = IMAGEMANAGER->findImage("intro_BG_1");
	Intro_BG_2 = new image;
	Intro_BG_2 = IMAGEMANAGER->findImage("intro_BG_2");

	for (int i = 0; i < 2; ++i)
	{
		Loop[i] = 0;
	}

	skul = new animation;
	skul = KEYANIMANAGER->findAnimation("intro_Skul");
	skul->start();

	Intro_Tile = new image;
	Intro_Tile = IMAGEMANAGER->findImage("intro_Title");

	alpha = 0;

	return S_OK;
}

void Intro_Scene::release()
{
}

void Intro_Scene::update()
{
	Loop[1] += 2;

	KEYANIMANAGER->update();

	if (alpha < 255)
	{
		alpha++;
	}

	if (alpha == 255)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			SCENEMANAGER->changeScene("Stage_0");
		}
	}
}

void Intro_Scene::render()
{
	RECT rc = RectMake(0, 0, 3392, 960);
	Intro_BG_0->loopRender(getMemDC(), &rc, Loop[0], 0);
	Intro_BG_1->loopRender(getMemDC(), &rc, Loop[1], 0);
	Intro_BG_2->render(getMemDC(), 0, 0);

	IMAGEMANAGER->findImage("intro_Skul")->aniRender(getMemDC(), WINSIZEX / 2 - 100, WINSIZEY / 2 + 105, skul);

	//Intro_Tile->render(getMemDC(), WINSIZEX / 2 - 250, 50);
	Intro_Tile->alphaRender(getMemDC(), WINSIZEX / 2 - 250, 50, alpha);

}
