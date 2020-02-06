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

	_addImage.addImage_Func();			// �̹����� �߰��Ѵ�. (���߿� �ε������� ó�� �ؾ��Ѵ�.)

	_sceneChanger = new sceneChanger;	// �����Ҵ�	
	_sceneChanger->init();				// �⺻ ���� �ʱ�ȭ

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

	_sceneChanger->update();	// �� ü���� ������Ʈ

}

void playGround::render()
{
	//PatBlt(getMemDC(), 0, 0, worSizeX, worSizeY, WHITENESS);
	//==========================================================	

	_sceneChanger->render();

	//===========================================================
	_backBuffer->render(getHDC(), 0, 0);
}