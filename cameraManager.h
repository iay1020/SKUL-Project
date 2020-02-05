#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	HDC				_worldDC;							// 월드 DC
	image*			_worldImg;							// 월드 Img

	tag_U_INT		_world_Size;						// 월드 사이즈
	tag_U_INT		_camera_Size;						// 카메라 사이즈

	POINTFLOAT      _cameraXY;							// 카메라 x, y 좌표

public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// 카메라 설정 함수
	void set_World_Size(unsigned int x, unsigned int y)	 { _world_Size.x = x; _world_Size.y = y; }		// 월드 사이즈를 저장한다.
	void set_Camera_Size(unsigned int x, unsigned int y) { _camera_Size.x = x; _camera_Size.y = y; }	// 카메라 사이즈를 저장한다.
	void set_CameraXY(float x, float y);																// 카메라의 x, y 좌표를 설정한다.

	// 카메라 겟터 함수	
	tag_U_INT get_World_Size()	{ return _world_Size; }						// 월드 사이즈를 받아온다.
	tag_U_INT get_Camera_Size() { return _camera_Size; }					// 카메라 사이즈를 받아온다.
	POINTFLOAT get_CameraXY()	{ return _cameraXY; }						// 카메라의 x, y 좌표를 받아온다.

	// 카메라 기능 함수
	void camera_Correction();												// 카메라 위치 보정

};

