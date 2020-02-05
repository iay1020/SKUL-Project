#include "stdafx.h"
#include "cameraManager.h"

cameraManager::cameraManager()
{
}

cameraManager::~cameraManager()
{
}

HRESULT cameraManager::init()
{
	return S_OK;
}

void cameraManager::release()
{
}

void cameraManager::update()
{
}

void cameraManager::render()
{
}


void cameraManager::set_CameraXY(float x, float y)
{
	// 매개변수를 이용하여 카메라 x, y를 구한다.
	_cameraXY.x = x - _camera_Size.x;
	_cameraXY.y = y - _camera_Size.y;

	// 카메라가 월드맵을 넘어갈때 예외처리를 한다.
	camera_Correction();
}


void cameraManager::camera_Correction()
{
	// 카메라 x, y가 맵을 넘어 갔을 경우 보정
	if (_cameraXY.x < 0) _cameraXY.x = 0;
	if (_cameraXY.y < 0) _cameraXY.y = 0;
	if(_cameraXY.x)
}
