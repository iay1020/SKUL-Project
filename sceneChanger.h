#pragma once
#include "gameNode.h"
#include "scene_Library.h" // 씬 관련 정보들이 저장 된 라이브러리

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

