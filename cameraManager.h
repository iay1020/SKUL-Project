#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	HDC				_worldDC;							// ���� DC
	image*			_worldImg;							// ���� Img

	tag_U_INT		_world_Size;						// ���� ������
	tag_U_INT		_camera_Size;						// ī�޶� ������

	POINTFLOAT      _cameraXY;							// ī�޶� x, y ��ǥ

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
	void set_CameraXY(float x, float y);																// ī�޶��� x, y ��ǥ�� �����Ѵ�.

	// ī�޶� ���� �Լ�	
	tag_U_INT get_World_Size()	{ return _world_Size; }						// ���� ����� �޾ƿ´�.
	tag_U_INT get_Camera_Size() { return _camera_Size; }					// ī�޶� ����� �޾ƿ´�.
	POINTFLOAT get_CameraXY()	{ return _cameraXY; }						// ī�޶��� x, y ��ǥ�� �޾ƿ´�.

	// ī�޶� ��� �Լ�
	void camera_Correction();												// ī�޶� ��ġ ����

};

