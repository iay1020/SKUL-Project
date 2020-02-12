#pragma once
#include "stdafx.h"

// unsigned short 타입의 정보를 2개 저장
struct tag_U_Short
{
	unsigned short x;
	unsigned short y;
};



// 카메라 연산에 사용하는 변수
struct tag_Camera_Operation
{
	unsigned int _TILE_COUNT_X;		// x 타일의 갯수
	unsigned int _TILE_COUNT_Y;		// y 타일의 갯수
};


// 출력 하기 원하는 타일의 인덱스를 담아둔다.
class tag_FindTile
{
protected:
	tag_U_Short start_Index;		// 시작 인덱스
	tag_U_Short end_Index;			// 마지막 인덱스
	tag_U_Short range;				// 출력 하기 원하는 범위 

public:
	tag_FindTile() {};
	~tag_FindTile() {};

	void reset()
	{
		start_Index.x = start_Index.y = 0;
		end_Index.x = end_Index.y = 0;
		range.x = range.y = 0;
	}

	// 인덱스를 찾는다. (좌표를 받아와서 그 좌표가 위치한 인덱스를 구한다.)
	void Find_startIndex(float x, float y)
	{
		start_Index.x = unsigned short(x / TILE_SIZE_X);
		start_Index.y = unsigned short(y / TILE_SIZE_Y);

		// 예외처리
		start_Index.x < 0 ? start_Index.x = 0 : start_Index.x;
		start_Index.y < 0 ? start_Index.y = 0 : start_Index.y;
	}

	// 인덱스를 찾는다. (좌표를 받아와서 그 좌표가 위치한 인덱스를 구한다.)
	void Find_endIndex(float x, float y, unsigned short tile_CntX, unsigned short tile_CntY)
	{
		end_Index.x = unsigned short((x + WINSIZEX) / TILE_SIZE_X);
		end_Index.y = unsigned short((y + WINSIZEY) / TILE_SIZE_Y + 1);			// 화면 아래 쪽 살짝 빈 공간을 출력하기 위한 예외처리

		// 예외처리
		end_Index.x + 1 > tile_CntX ?
			end_Index.x = tile_CntX - 1 : end_Index.x;
		end_Index.y + 1 > tile_CntY ?
			end_Index.y = tile_CntY - 1 : end_Index.y;
	}

	// 찾기 원하는 타일의 범위를 구한다.
	void Find_Tile_Range()
	{
		range.x = unsigned short(end_Index.x - start_Index.x);	// 찾아야 하는 x의 갯수
		range.y = unsigned short(end_Index.y - start_Index.y);	// 찾아야 하는 y의 갯수
	}

	// 타일의 범위를 받아온다.
	tag_U_Short get_Start_Index() { return start_Index; }		// 스타트 인덱스를 받아온다.
	tag_U_Short get_End_Index() { return end_Index; }			// 엔드 인덱스를 받아온다.
	tag_U_Short get_Tile_Range() { return range; }				// 출력 타일 범위를 받아온다.

};


// 카메라의 변수를 모아둔다.
struct tag_Camera_INFO
{
	tag_U_Short				_world_Size;					// 월드 사이즈
	tag_U_Short				_camera_Size;					// 카메라 사이즈

	POINTFLOAT				_cameraXY;						// 카메라 x, y 좌표
	tag_Camera_Operation	_operation;						// 카메라 연산 변수 

	tag_FindTile*			_Find_Tile;						// 출력을 해야 하는 타일을 찾아준다.


	// 기본 베이스 세팅 함수
	void setting_Func()
	{
		// 카메라의 베이스 좌표를 만들어준다. (초기 셋팅)
		set_CameraXY(WINSIZEX / 2.f, WINSIZEY / 2.f, true);

		// 타일 찾는 클래스(카메라 범위만)
		_Find_Tile = new tag_FindTile;
		_Find_Tile->reset();

		// 월드 사이즈를 저장한다. (타일 갯수 * 타일 사이즈)
		_world_Size.x = TILE_COUNT_X * TILE_SIZE_X;
		_world_Size.y = TILE_COUNT_Y * TILE_SIZE_Y;

		// 카메라 사이즈를 저장한다.
		_camera_Size.x = WINSIZEX;
		_camera_Size.y = WINSIZEY;

		// 현재 타일의 갯수를 저장한다. (이 후에 타일의 크기를 늘릴 경우에는 이 값을 수정해준다.)
		_operation._TILE_COUNT_X = TILE_COUNT_X;
		_operation._TILE_COUNT_Y = TILE_COUNT_Y;
	}



	// 카메라 설정 함수
	void set_World_Size(unsigned short x, unsigned short y) { _world_Size.x = x; _world_Size.y = y; }		// 월드 사이즈를 저장한다.
	void set_Camera_Size(unsigned short x, unsigned short y) { _camera_Size.x = x; _camera_Size.y = y; }	// 카메라 사이즈를 저장한다.
	void set_CameraX(float x) { _cameraXY.x = x; camera_Correction(); }									// 카메라 x를 수정한다.
	void set_CameraY(float y) { _cameraXY.y = y; camera_Correction(); }									// 카메라 y를 수정한다.
	void set_CameraXY(float x, float y, bool noCorrection)												// true를 넣으면 예외처리를 제외하고 세팅한다.
	{
		// 매개변수를 이용하여 카메라 x, y를 구한다.
		_cameraXY.x = x - (_camera_Size.x / 2);
		_cameraXY.y = y - (_camera_Size.y / 2);

		// true를 넣었다면 예외처리
		if (noCorrection)	camera_Correction();
	};
	void set_Tile_CountX(int tileCountX) { _operation._TILE_COUNT_X = tileCountX; }
	void set_Tile_CountY(int tileCountY) { _operation._TILE_COUNT_Y = tileCountY; }
	



	// 카메라 겟터 함수	
	tag_U_Short get_World_Size() { return _world_Size; }						// 월드 사이즈를 받아온다.
	tag_U_Short get_Camera_Size() { return _camera_Size; }						// 카메라 사이즈를 받아온다.
	POINTFLOAT get_CameraXY() { return _cameraXY; }								// 카메라의 x, y 좌표를 받아온다.
	tag_FindTile* get_Find_Tile() { return _Find_Tile; }						// 카메라 안에 있는 타일을 찾는다.
	tag_Camera_Operation get_Camera_Operation() { return _operation; }			// 카메라 연산 변수 불러오기


	// 카메라 기능 함수
	void camera_Correction()													// 카메라 위치 보정
	{
		// 카메라 x, y가 맵을 넘어 갔을 경우 보정
		if (_cameraXY.x < 0) _cameraXY.x = 0;
		if (_cameraXY.y < 0) _cameraXY.y = 0;
		if (_cameraXY.x + _camera_Size.x > _world_Size.x) _cameraXY.x = _world_Size.x - _camera_Size.x;
		if (_cameraXY.y + _camera_Size.y > _world_Size.y) _cameraXY.y = _world_Size.y - _camera_Size.y;
	};
		
	// 매개변수로 타일의 사이즈 X, Y를 받아온다.
	void find_Tile(unsigned short tile_CntX, unsigned short tile_CntY)		// 출력을 해야 하는 타일을 찾는다.
	{
		// 카메라의 좌표를 이용하여 시작과 끝의 인덱스를 찾아낸다.
		_Find_Tile->Find_startIndex(_cameraXY.x, _cameraXY.y);
		_Find_Tile->Find_endIndex(_cameraXY.x, _cameraXY.y, tile_CntX, tile_CntY);
		_Find_Tile->Find_Tile_Range();
	};
};