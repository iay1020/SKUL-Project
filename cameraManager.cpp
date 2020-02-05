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
	// 매개변수를 이용하여 카메라 x, y를 구한다.
	_cameraXY.x = x - (_camera_Size.x / 2);
	_cameraXY.y = y - (_camera_Size.y / 2);

	// true를 넣었다면 예외처리
	if (noCorrection)	camera_Correction();
	
}


void cameraManager::camera_Correction()
{
	// 카메라 x, y가 맵을 넘어 갔을 경우 보정
	if (_cameraXY.x < 0) _cameraXY.x = 0;
	if (_cameraXY.y < 0) _cameraXY.y = 0;
	if (_cameraXY.x + _camera_Size.x > _world_Size.x) _cameraXY.x = _world_Size.x - _camera_Size.x;
	if (_cameraXY.y + _camera_Size.y > _world_Size.y) _cameraXY.y = _world_Size.y - _camera_Size.y;
}

void cameraManager::find_Tile()
{
	// 카메라의 좌표를 이용하여 시작과 끝의 인덱스를 찾아낸다.
	_Find_Tile->Find_startIndex(_cameraXY.x, _cameraXY.y);
	_Find_Tile->Find_endIndex(_cameraXY.x, _cameraXY.y);
	_Find_Tile->Find_Tile_Range();
}
