#pragma once
#include "singletonBase.h"
#include "camera_Library.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	tag_Camera_INFO*			 _camera;			// ī�޶󿡼� ���� ������ ����ִ�.
	
public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	tag_Camera_INFO* Use_Func() { return _camera; }	// ī�޶� ���� ����� �̿��Ѵ�.
};

