#pragma once
#include "gameNode.h"
#include "mapTool_Library.h"	// ���� ���� ������ ����Ǿ� �ִ� ���̺귯��

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

