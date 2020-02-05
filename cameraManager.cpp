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
	//_worldImg = IMAGEMANAGER->addImage("worldMap", 200000, 300000);
	//_worldDC = _worldImg->getMemDC();

	_Find_Tile = new tag_FindTile;
	_Find_Tile->init();

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


void cameraManager::set_CameraXY(float x, float y, bool noCorrection)
{
	// �Ű������� �̿��Ͽ� ī�޶� x, y�� ���Ѵ�.
	_cameraXY.x = x - (_camera_Size.x / 2);
	_cameraXY.y = y - (_camera_Size.y / 2);

	// true�� �־��ٸ� ����ó��
	if (noCorrection)	camera_Correction();
	
}


void cameraManager::camera_Correction()
{
	// ī�޶� x, y�� ���� �Ѿ� ���� ��� ����
	if (_cameraXY.x < 0) _cameraXY.x = 0;
	if (_cameraXY.y < 0) _cameraXY.y = 0;
	if (_cameraXY.x + _camera_Size.x > _world_Size.x) _cameraXY.x = _world_Size.x - _camera_Size.x;
	if (_cameraXY.y + _camera_Size.y > _world_Size.y) _cameraXY.y = _world_Size.y - _camera_Size.y;
}

void cameraManager::find_Tile()
{
	// ī�޶��� ��ǥ�� �̿��Ͽ� ���۰� ���� �ε����� ã�Ƴ���.
	_Find_Tile->Find_startIndex(_cameraXY.x, _cameraXY.y);
	_Find_Tile->Find_endIndex(_cameraXY.x, _cameraXY.y);
	_Find_Tile->Find_Tile_Range();
}
