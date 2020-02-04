#pragma once
#include "gameNode.h"
#include "sceneChanger.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

struct _tagPlayer
{
	POINTFLOAT center;
	RECT	   rc;
};

class playGround : public gameNode
{
private:
	sceneChanger* _sceneChanger;	// 씬 전환을 담당한다.
	
	image*	bg[3];

	HDC		_worDC;
	image*	_worImg;

	_tagPlayer _player;

	int worSizeX, worSizeY;

	float cameraX, cameraY;
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

// WINSIZEX = 1600		// 윈도우 사이즈
// WINSIZEY = 900
// WORLDSIZE = 4800		// 월드 사이즈
// WORLDSIZE = 3600