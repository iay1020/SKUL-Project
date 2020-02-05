#pragma once
#include "gameNode.h"
#include "scene_Library.h"

class sceneChanger : public gameNode
{
private:
	tagSceneFunc	_sceneFunc;	// scene의 함수 모음 변수

public:
	sceneChanger();
	~sceneChanger();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

