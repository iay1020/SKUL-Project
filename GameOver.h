#pragma once
#include "gameNode.h"

class GameOver : public gameNode
{
private:
	BYTE	CoolTime;


public:
	GameOver();
	~GameOver();

	HRESULT init();
	void release();
	void update();
	void render();

};