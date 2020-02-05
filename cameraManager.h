#pragma once
#include "singletonBase.h"
#include "camera_Library.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	tag_Camera_INFO*			 _camera;			// 카메라에서 쓰는 변수가 들어있다.
	
public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	tag_Camera_INFO* Use_Func() { return _camera; }	// 카메라 관련 기능을 이용한다.
};

