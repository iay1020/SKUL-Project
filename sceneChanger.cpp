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
	_sceneFunc.addScene();	// ¾ÀÀ» Ãß°¡ ÇÑ´Ù.
	_sceneFunc.changeScene("mapTool");	// Ã³À½ ½ÃÀÛÇÒ ¾ÀÀ» °ñ¶óÁØ´Ù.

	return S_OK;
}

void sceneChanger::release()
{
}

void sceneChanger::update()
{
	SCENEMANAGER->update();
}

void sceneChanger::render()
{
	SCENEMANAGER->render();
}
