#pragma once
#include "stdafx.h"

// unsigned short Ÿ���� ������ 2�� ����
struct tag_U_Short
{
	unsigned short x;
	unsigned short y;
};



// ī�޶� ���꿡 ����ϴ� ����
struct tag_Camera_Operation
{
	unsigned int _TILE_COUNT_X;		// x Ÿ���� ����
	unsigned int _TILE_COUNT_Y;		// y Ÿ���� ����
};


// ��� �ϱ� ���ϴ� Ÿ���� �ε����� ��Ƶд�.
class tag_FindTile
{
protected:
	tag_U_Short start_Index;		// ���� �ε���
	tag_U_Short end_Index;			// ������ �ε���
	tag_U_Short range;				// ��� �ϱ� ���ϴ� ���� 

public:
	tag_FindTile() {};
	~tag_FindTile() {};

	void reset()
	{
		start_Index.x = start_Index.y = 0;
		end_Index.x = end_Index.y = 0;
		range.x = range.y = 0;
	}

	// �ε����� ã�´�. (��ǥ�� �޾ƿͼ� �� ��ǥ�� ��ġ�� �ε����� ���Ѵ�.)
	void Find_startIndex(float x, float y)
	{
		start_Index.x = unsigned short(x / TILE_SIZE_X);
		start_Index.y = unsigned short(y / TILE_SIZE_Y);

		// ����ó��
		start_Index.x < 0 ? start_Index.x = 0 : start_Index.x;
		start_Index.y < 0 ? start_Index.y = 0 : start_Index.y;
	}

	// �ε����� ã�´�. (��ǥ�� �޾ƿͼ� �� ��ǥ�� ��ġ�� �ε����� ���Ѵ�.)
	void Find_endIndex(float x, float y, unsigned short tile_CntX, unsigned short tile_CntY)
	{
		end_Index.x = unsigned short((x + WINSIZEX) / TILE_SIZE_X);
		end_Index.y = unsigned short((y + WINSIZEY) / TILE_SIZE_Y + 1);			// ȭ�� �Ʒ� �� ��¦ �� ������ ����ϱ� ���� ����ó��

		// ����ó��
		end_Index.x + 1 > tile_CntX ?
			end_Index.x = tile_CntX - 1 : end_Index.x;
		end_Index.y + 1 > tile_CntY ?
			end_Index.y = tile_CntY - 1 : end_Index.y;
	}

	// ã�� ���ϴ� Ÿ���� ������ ���Ѵ�.
	void Find_Tile_Range()
	{
		range.x = unsigned short(end_Index.x - start_Index.x);	// ã�ƾ� �ϴ� x�� ����
		range.y = unsigned short(end_Index.y - start_Index.y);	// ã�ƾ� �ϴ� y�� ����
	}

	// Ÿ���� ������ �޾ƿ´�.
	tag_U_Short get_Start_Index() { return start_Index; }		// ��ŸƮ �ε����� �޾ƿ´�.
	tag_U_Short get_End_Index() { return end_Index; }			// ���� �ε����� �޾ƿ´�.
	tag_U_Short get_Tile_Range() { return range; }				// ��� Ÿ�� ������ �޾ƿ´�.

};


// ī�޶��� ������ ��Ƶд�.
struct tag_Camera_INFO
{
	tag_U_Short				_world_Size;					// ���� ������
	tag_U_Short				_camera_Size;					// ī�޶� ������

	POINTFLOAT				_cameraXY;						// ī�޶� x, y ��ǥ
	tag_Camera_Operation	_operation;						// ī�޶� ���� ���� 

	tag_FindTile*			_Find_Tile;						// ����� �ؾ� �ϴ� Ÿ���� ã���ش�.


	// �⺻ ���̽� ���� �Լ�
	void setting_Func()
	{
		// ī�޶��� ���̽� ��ǥ�� ������ش�. (�ʱ� ����)
		set_CameraXY(WINSIZEX / 2.f, WINSIZEY / 2.f, true);

		// Ÿ�� ã�� Ŭ����(ī�޶� ������)
		_Find_Tile = new tag_FindTile;
		_Find_Tile->reset();

		// ���� ����� �����Ѵ�. (Ÿ�� ���� * Ÿ�� ������)
		_world_Size.x = TILE_COUNT_X * TILE_SIZE_X;
		_world_Size.y = TILE_COUNT_Y * TILE_SIZE_Y;

		// ī�޶� ����� �����Ѵ�.
		_camera_Size.x = WINSIZEX;
		_camera_Size.y = WINSIZEY;

		// ���� Ÿ���� ������ �����Ѵ�. (�� �Ŀ� Ÿ���� ũ�⸦ �ø� ��쿡�� �� ���� �������ش�.)
		_operation._TILE_COUNT_X = TILE_COUNT_X;
		_operation._TILE_COUNT_Y = TILE_COUNT_Y;
	}



	// ī�޶� ���� �Լ�
	void set_World_Size(unsigned short x, unsigned short y) { _world_Size.x = x; _world_Size.y = y; }		// ���� ����� �����Ѵ�.
	void set_Camera_Size(unsigned short x, unsigned short y) { _camera_Size.x = x; _camera_Size.y = y; }	// ī�޶� ����� �����Ѵ�.
	void set_CameraX(float x) { _cameraXY.x = x; camera_Correction(); }									// ī�޶� x�� �����Ѵ�.
	void set_CameraY(float y) { _cameraXY.y = y; camera_Correction(); }									// ī�޶� y�� �����Ѵ�.
	void set_CameraXY(float x, float y, bool noCorrection)												// true�� ������ ����ó���� �����ϰ� �����Ѵ�.
	{
		// �Ű������� �̿��Ͽ� ī�޶� x, y�� ���Ѵ�.
		_cameraXY.x = x - (_camera_Size.x / 2);
		_cameraXY.y = y - (_camera_Size.y / 2) - 200;

		// true�� �־��ٸ� ����ó��
		if (noCorrection)	camera_Correction();
	};
	void set_Tile_CountX(int tileCountX) { _operation._TILE_COUNT_X = tileCountX; }
	void set_Tile_CountY(int tileCountY) { _operation._TILE_COUNT_Y = tileCountY; }
	



	// ī�޶� ���� �Լ�	
	tag_U_Short get_World_Size() { return _world_Size; }						// ���� ����� �޾ƿ´�.
	tag_U_Short get_Camera_Size() { return _camera_Size; }						// ī�޶� ����� �޾ƿ´�.
	POINTFLOAT get_CameraXY() { return _cameraXY; }								// ī�޶��� x, y ��ǥ�� �޾ƿ´�.
	tag_FindTile* get_Find_Tile() { return _Find_Tile; }						// ī�޶� �ȿ� �ִ� Ÿ���� ã�´�.
	tag_Camera_Operation get_Camera_Operation() { return _operation; }			// ī�޶� ���� ���� �ҷ�����


	// ī�޶� ��� �Լ�
	void camera_Correction()													// ī�޶� ��ġ ����
	{
		// ī�޶� x, y�� ���� �Ѿ� ���� ��� ����
		if (_cameraXY.x < 0) _cameraXY.x = 0;
		if (_cameraXY.y < 0) _cameraXY.y = 0;
		if (_cameraXY.x + _camera_Size.x > _world_Size.x) _cameraXY.x = _world_Size.x - _camera_Size.x;
		if (_cameraXY.y + _camera_Size.y - 200 > _world_Size.y) _cameraXY.y = _world_Size.y - _camera_Size.y;
	};
		
	// �Ű������� Ÿ���� ������ X, Y�� �޾ƿ´�.
	void find_Tile(unsigned short tile_CntX, unsigned short tile_CntY)		// ����� �ؾ� �ϴ� Ÿ���� ã�´�.
	{
		// ī�޶��� ��ǥ�� �̿��Ͽ� ���۰� ���� �ε����� ã�Ƴ���.
		_Find_Tile->Find_startIndex(_cameraXY.x, _cameraXY.y);
		_Find_Tile->Find_endIndex(_cameraXY.x, _cameraXY.y, tile_CntX, tile_CntY);
		_Find_Tile->Find_Tile_Range();
	};
};