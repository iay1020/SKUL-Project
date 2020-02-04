#pragma once
#include "gameNode.h"
#include "scene_Library.h" // �� ���� �������� ���� �� ���̺귯��

class sceneChanger : public gameNode
{
private:
	tagSceneFunc	_sceneFunc;	// scene�� �Լ� ���� ����

public:
	sceneChanger();
	~sceneChanger();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

