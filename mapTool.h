#pragma once
#include "gameNode.h"
#include "mapTool_Library.h"	// 맵툴 관련 정보가 저장되어 있는 라이브러리

class mapTool : public gameNode
{
private:

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

