#include "stdafx.h"
#include "sceneChanger.h"

sceneChanger::sceneChanger()
{
}

sceneChanger::~sceneChanger()
{
}

HRESULT sceneChanger::init()
{
	_sceneFunc.addScene();	// ���� �߰� �Ѵ�.
	_sceneFunc.changeScene("mapTool");	// ó�� ������ ���� ����ش�.

	return S_OK;
}

void sceneChanger::release()
{
}

void sceneChanger::update()
{
	_sceneFunc.TEST_SceneChange();
	SCENEMANAGER->update();
}

void sceneChanger::render()
{
	SCENEMANAGER->render();
}
