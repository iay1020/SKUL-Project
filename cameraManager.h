#pragma once
#include "singletonBase.h"
#include "camera_Library.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	//HDC				_worldDC;							// ���� DC 
	//image*			_worldImg;							// ���� Img

	tag_U_INT		_world_Size;						// ���� ������
	tag_U_INT		_camera_Size;						// ī�޶� ������

	POINTFLOAT      _cameraXY;							// ī�޶� x, y ��ǥ

	tag_FindTile*   _Find_Tile;							// ����� �ؾ� �ϴ� Ÿ���� ã���ش�.
	
public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// ī�޶� ���� �Լ�
	void set_World_Size(unsigned int x, unsigned int y)	 { _world_Size.x = x; _world_Size.y = y; }		// ���� ����� �����Ѵ�.
	void set_Camera_Size(unsigned int x, unsigned int y) { _camera_Size.x = x; _camera_Size.y = y; }	// ī�޶� ����� �����Ѵ�.
	void set_CameraXY(float x, float y, bool noCorrection = false);										// true�� ������ ����ó���� �����ϰ� �����Ѵ�.
	void set_CameraX(float x) {	_cameraXY.x = x; camera_Correction(); }									// ī�޶� x�� �����Ѵ�.
	void set_CameraY(float y) { _cameraXY.y = y; camera_Correction(); }									// ī�޶� y�� �����Ѵ�.

	// ī�޶� ���� �Լ�	
	tag_U_INT get_World_Size()	{ return _world_Size; }						// ���� ����� �޾ƿ´�.
	tag_U_INT get_Camera_Size() { return _camera_Size; }					// ī�޶� ����� �޾ƿ´�.
	POINTFLOAT get_CameraXY()	{ return _cameraXY; }						// ī�޶��� x, y ��ǥ�� �޾ƿ´�.
	//HDC get_WorldDC()			{ return _worldDC; }						// ����DC�� �޾ƿ´�.
	//image* get_WorldImg()		{ return _worldImg; }						// ����Img�� �޾ƿ´�.
	tag_FindTile* get_Find_Tile() {	return _Find_Tile; }

	// ī�޶� ��� �Լ�
	void camera_Correction();												// ī�޶� ��ġ ����
	void find_Tile();														// ����� �ؾ� �ϴ� Ÿ���� ã�´�.

};

