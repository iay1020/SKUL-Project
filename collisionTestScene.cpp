#include "stdafx.h"
#include "collisionTestScene.h"


collisionTestScene::collisionTestScene()
{
}


collisionTestScene::~collisionTestScene()
{
}

HRESULT collisionTestScene::init()
{
	//사각형 렉트 충돌
	_rect.left = 200;
	_rect.top = 200;
	_rect.right = 300;
	_rect.bottom = 300;
	
	_rectMove.left = 50;
	_rectMove.top = 50;
	_rectMove.right = 100;
	_rectMove.bottom = 100;

	//동그라미 충돌
	/*
	_cir.x = WINSIZEX / 2;
	_cir.y = WINSIZEY / 2;
	_cir.r = 100;

	_cirMove.x = 50;
	_cirMove.y = 50;
	_cirMove.r = 50;
	*/


	return S_OK;
}

void collisionTestScene::release()
{
}

void collisionTestScene::update()
{
	//사각형 충돌
	_rectMove.setCenterPos(_ptMouse.x, _ptMouse.y);
	
	if (isCollisionReaction(_rect, _rectMove))
	{
	
	}


	//동그라미 충돌
	/*
	_cirMove.x = _ptMouse.x;
	_cirMove.y = _ptMouse.y;

	if (isCollisionReaction(_cir, _cirMove))
	{

	}
	else
	{

	}
	*/
}

void collisionTestScene::render()
{
	//사각형
	_rect.render(getMemDC());
	_rectMove.render(getMemDC());

	//동그라미
	/*
	_cir.render(getMemDC());
	_cirMove.render(getMemDC());
	*/
}
