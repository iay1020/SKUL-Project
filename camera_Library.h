#pragma once
#include "stdafx.h"

// unsigned int Ÿ���� ������ 2�� ����
struct tag_U_INT
{
	unsigned int x;
	unsigned int y;
};

// ��� �ϱ� ���ϴ� Ÿ���� �ε����� ��Ƶд�.
class tag_FindTile
{
protected:
	tag_U_INT start_Index;		// ���� �ε���
	tag_U_INT end_Index;		// ������ �ε���
	tag_U_INT range;			// ��� �ϱ� ���ϴ� ���� 


public:
	tag_FindTile() {};
	~tag_FindTile() {};

	void init()
	{
		start_Index.x = start_Index.y = 0;
		end_Index.x = end_Index.y = 0;
		range.x = range.y = 0;

	}

	// �ε����� ã�´�. (��ǥ�� �޾ƿͼ� �� ��ǥ�� ��ġ�� �ε����� ���Ѵ�.)
	void Find_startIndex(float x, float y)
	{
		start_Index.x = x / TILE_SIZE_X;
		start_Index.y = y / TILE_SIZE_Y; 

		//cout << "start x : " << start_Index.x << endl;
		//cout << "start y : " << start_Index.y << endl;
		//cout << "=============================" << endl;
	}

	// �ε����� ã�´�. (��ǥ�� �޾ƿͼ� �� ��ǥ�� ��ġ�� �ε����� ���Ѵ�.)
	void Find_endIndex(float x, float y)
	{
		end_Index.x = (x + WINSIZEX) / TILE_SIZE_X;
		end_Index.y = (y + WINSIZEY) / TILE_SIZE_Y + 1;	// ȭ�� �Ʒ� �� ��¦ �� ������ ����ϱ� ���� ����ó��

		//cout << "end x : " << end_Index.x << endl;
		//cout << "end y : " << end_Index.y << endl;
		//cout << "=============================" << endl;
	}

	// ã�� ���ϴ� Ÿ���� ������ ���Ѵ�.
	void Find_Tile_Range()
	{
		range.x = unsigned int(end_Index.x - start_Index.x);	// ã�ƾ� �ϴ� x�� ����
		range.y = unsigned int(end_Index.y - start_Index.y);	// ã�ƾ� �ϴ� y�� ����

		//cout << "range x : " << range.x << endl;
		//cout << "range y : " << range.y << endl;
		//cout << "=============================" << endl;
	}

	// Ÿ���� ������ �޾ƿ´�.
	tag_U_INT get_Start_Index() { return start_Index; }		// ��ŸƮ �ε����� �޾ƿ´�.
	tag_U_INT get_End_Index() { return end_Index; }			// ���� �ε����� �޾ƿ´�.
	tag_U_INT get_Tile_Range() { return range; }			// ��� Ÿ�� ������ �޾ƿ´�.

};


// ī�޶��� ������ ��Ƶд�.
struct tag_Camera_INFO
{
	tag_U_INT		_world_Size;							// ���� ������
	tag_U_INT		_camera_Size;							// ī�޶� ������

	POINTFLOAT      _cameraXY;								// ī�޶� x, y ��ǥ

	tag_FindTile*			 _Find_Tile;		// ����� �ؾ� �ϴ� Ÿ���� ã���ش�.

	// �⺻ ���̽� ���� �Լ�
	void setting_Func()
	{
		// ī�޶��� ���̽� ��ǥ�� ������ش�. (�ʱ� ����)
		set_CameraXY(WINSIZEX / 2.f, WINSIZEY / 2.f, true);

		// Ÿ�� ã�� Ŭ����(ī�޶� ������)
		_Find_Tile = new tag_FindTile;
		_Find_Tile->init();

		// ���� ����� �����Ѵ�. (Ÿ�� ���� * Ÿ�� ������)
		_world_Size.x = IMAGEMANAGER->findImage("tutorial_BG_0")->getWidth();
		_world_Size.y = IMAGEMANAGER->findImage("tutorial_BG_0")->getHeight();

		// ī�޶� ����� �����Ѵ�.
		_camera_Size.x = WINSIZEX;
		_camera_Size.y = WINSIZEY;
	}



	// ī�޶� ���� �Լ�
	void set_World_Size(unsigned int x, unsigned int y) { _world_Size.x = x; _world_Size.y = y; }		// ���� ����� �����Ѵ�.
	void set_Camera_Size(unsigned int x, unsigned int y) { _camera_Size.x = x; _camera_Size.y = y; }	// ī�޶� ����� �����Ѵ�.
	void set_CameraX(float x) { _cameraXY.x = x; camera_Correction(); }									// ī�޶� x�� �����Ѵ�.
	void set_CameraY(float y) { _cameraXY.y = y; camera_Correction(); }									// ī�޶� y�� �����Ѵ�.
	void set_CameraXY(float x, float y, bool noCorrection)												// true�� ������ ����ó���� �����ϰ� �����Ѵ�.
	{
		// �Ű������� �̿��Ͽ� ī�޶� x, y�� ���Ѵ�.
		_cameraXY.x = x - (_camera_Size.x / 2);
		_cameraXY.y = y - (_camera_Size.y / 2);

		// true�� �־��ٸ� ����ó��
		if (noCorrection)	camera_Correction();
	};



	// ī�޶� ���� �Լ�	
	tag_U_INT get_World_Size() { return _world_Size; }						// ���� ����� �޾ƿ´�.
	tag_U_INT get_Camera_Size() { return _camera_Size; }					// ī�޶� ����� �޾ƿ´�.
	POINTFLOAT get_CameraXY() { return _cameraXY; }							// ī�޶��� x, y ��ǥ�� �޾ƿ´�.
	tag_FindTile* get_Find_Tile() { return _Find_Tile; }



	// ī�޶� ��� �Լ�
	void camera_Correction()												// ī�޶� ��ġ ����
	{
		// ī�޶� x, y�� ���� �Ѿ� ���� ��� ����
		if (_cameraXY.x < 0) _cameraXY.x = 0;
		if (_cameraXY.y < 0) _cameraXY.y = 0;
		if (_cameraXY.x + _camera_Size.x > _world_Size.x) _cameraXY.x = _world_Size.x - _camera_Size.x;
		if (_cameraXY.y + _camera_Size.y > _world_Size.y) _cameraXY.y = _world_Size.y - _camera_Size.y;
	};
		
	void find_Tile()														// ����� �ؾ� �ϴ� Ÿ���� ã�´�.
	{
		// ī�޶��� ��ǥ�� �̿��Ͽ� ���۰� ���� �ε����� ã�Ƴ���.
		_Find_Tile->Find_startIndex(_cameraXY.x, _cameraXY.y);
		_Find_Tile->Find_endIndex(_cameraXY.x, _cameraXY.y);
		_Find_Tile->Find_Tile_Range();
	};
};