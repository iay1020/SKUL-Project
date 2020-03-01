#pragma once
#include "gameNode.h"


class Intro_Scene : public gameNode
{
private:
	image* Intro_BG_0;
	image* Intro_BG_1;
	image* Intro_BG_2;

	short Loop[2];

	animation* skul;

	image* Intro_Tile;

	BYTE alpha;


public:
	Intro_Scene();
	~Intro_Scene();

	HRESULT init();
	void release();
	void update();
	void render();

};