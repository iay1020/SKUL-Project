#pragma once
#include "gameNode.h"

class collisionTestScene : public gameNode
{
private:
	MYRECT _rect;
	MYRECT _rectMove;

	MYCIRCLE _cir;
	MYCIRCLE _cirMove;
public:
	collisionTestScene();
	~collisionTestScene();

	HRESULT init();
	void release();
	void update();
	void render();

};

