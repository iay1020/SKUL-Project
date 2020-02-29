#pragma once
#include "gameNode.h"


class FlyingObject : public gameNode
{
private:
	vector<FlyingObjectInfo>				vFlyingObj;		// ����ü ����
	vector<FlyingObjectInfo>::iterator		viFlyingObj;	// ����ü ���� �ݺ���

public:
	FlyingObject();
	~FlyingObject();

	void Release();
	void update();
	void render();

	// ����ü ���� �Լ� (�Ű����� : �̹����̸�, ����x, ����y, ����, ���ǵ�, �̹����� ���������� �ƴ���)
	void Create_FlyingObj(string imgName, string aniName, FLYINFOBJECT_TYPE type_V, FLYINGOBJECT_DIRECTION dir,
		float x, float y, float angle_V, float speed_V, int atk_V, bool Frame = false);

	// ����ü �̵� �Լ�
	void Move_FlyingObj();

	// ����ü ��� �Լ�
	void Show_FlyingObj();

	// ����ü ���� �ּ�
	vector<FlyingObjectInfo>* get_vFlyingObj_Address() { return &vFlyingObj; }

};

