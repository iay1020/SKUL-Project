#pragma once
#include "gameNode.h"
#include "DataManager.h"
#include "eventManager.h"


class Stage_0 : public gameNode
{
private:
	Player*				_skul;
	eventManager*		eventM;

public:
	Stage_0();
	~Stage_0();

	HRESULT init();
	void release();
	void update();
	void render();

	void testControl();

	void showRect(HDC getMemDC);

};

