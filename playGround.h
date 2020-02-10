#pragma once
#include "gameNode.h"
#include "sceneChanger.h"
#include "addImage.h"

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

class playGround : public gameNode
{
private:
	sceneChanger*	_sceneChanger;	// �� ��ȯ�� ����Ѵ�.

	tagAddImage		_addImage;	// �̹����� �߰� �Ѵ�. (���߿� �ε������� �̵� �ؾ��Ѵ�)
	
public:
	playGround();
	~playGround();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

// WINSIZEX = 1600		// ������ ������
// WINSIZEY = 960
// WORLDSIZE = 4800		// ���� ������
// WORLDSIZE = 3600