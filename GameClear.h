#pragma once
#include "gameNode.h"

class GameClear : public gameNode
{
private:
	BYTE	CoolTime;


public:
	GameClear();
	~GameClear();

	HRESULT init();
	void release();
	void update();
	void render();

};