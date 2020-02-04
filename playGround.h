#pragma once
#include "gameNode.h"
#include "Size_Library.h" // ������ ���� ���̺귯��

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

// WINSIZEX = 1600		// ������ ������
// WINSIZEY = 900
// WORLDSIZE = 4800		// ���� ������
// WORLDSIZE = 3600