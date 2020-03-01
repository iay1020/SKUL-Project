#pragma once
#include "gameNode.h"
#include "DataManager.h"
#include "eventManager.h"

class Stage_2 : public gameNode
{
private:
	Player*				_skul;
	eventManager*		eventM;

public:
	Stage_2();
	~Stage_2();

	HRESULT init();
	void release();
	void update();
	void render();

	void testControl();

	void showRect(HDC getMemDC);

};