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
	// �Ű������� �̿��Ͽ� ī�޶� x, y�� ���Ѵ�.
	_cameraXY.x = x - _camera_Size.x;
	_cameraXY.y = y - _camera_Size.y;

	// ī�޶� ������� �Ѿ�� ����ó���� �Ѵ�.
	camera_Correction();
}


void cameraManager::camera_Correction()
{
	// ī�޶� x, y�� ���� �Ѿ� ���� ��� ����
	if (_cameraXY.x < 0) _cameraXY.x = 0;
	if (_cameraXY.y < 0) _cameraXY.y = 0;
	if(_cameraXY.x)
}
