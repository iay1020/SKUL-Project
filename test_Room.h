#pragma once
#include "gameNode.h"
#include "DataManager.h"
//#include "CharacterState.h"
//#include "Player.h"

class test_Room : public gameNode
{
private:
	short				loopSpeed[5];

	Player*				_skul;

public:
	test_Room();
	~test_Room();

	HRESULT init();
	void release();
	void update();
	void render();

	void testControl();

	void showRect(HDC getMemDC);

};

