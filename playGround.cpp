#include "stdafx.h"
#include "playGround.h"

playGround::playGround()
{
}

playGround::~playGround()
{
}

HRESULT playGround::init()
{
	gameNode::init(true);

	_addImage.addImage_Func();			// 이미지를 추가한다. (나중에 로딩씬에서 처리 해야한다.)

	_sceneChanger = new sceneChanger;	// 동적할당	
	_sceneChanger->init();				// 기본 셋팅 초기화

	return S_OK;
}


void playGround::release()
{
	gameNode::release();
	_sceneChanger->release();	

}


void playGround::update()
{
	gameNode::update();

	_sceneChanger->update();	// 씬 체인저 업데이트

}

void playGround::render()
{
	//PatBlt(getMemDC(), 0, 0, worSizeX, worSizeY, WHITENESS);
	//==========================================================	

	_sceneChanger->render();

	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}