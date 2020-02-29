#pragma once
#include "gameNode.h"


class FlyingObject : public gameNode
{
private:
	vector<FlyingObjectInfo>				vFlyingObj;		// 투사체 벡터
	vector<FlyingObjectInfo>::iterator		viFlyingObj;	// 투사체 벡터 반복자

public:
	FlyingObject();
	~FlyingObject();

	void Release();
	void update();
	void render();

	// 투사체 생성 함수 (매개변수 : 이미지이름, 중점x, 중점y, 각도, 스피드, 이미지가 프레임인지 아닌지)
	void Create_FlyingObj(string imgName, string aniName, FLYINFOBJECT_TYPE type_V, FLYINGOBJECT_DIRECTION dir,
		float x, float y, float angle_V, float speed_V, int atk_V, bool Frame = false);

	// 투사체 이동 함수
	void Move_FlyingObj();

	// 투사체 출력 함수
	void Show_FlyingObj();

	// 투사체 벡터 주소
	vector<FlyingObjectInfo>* get_vFlyingObj_Address() { return &vFlyingObj; }

};

