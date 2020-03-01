#pragma once
#include "gameNode.h"
#include "DataManager.h"
#include "eventManager.h"

class Stage_1 : public gameNode
{
private:
	Player*				_skul;
	eventManager*		eventM;

public:
	Stage_1();
	~Stage_1();

	HRESULT init();
	void release();
	void update();
	void render();

	void testControl();

	void showRect(HDC getMemDC);

};