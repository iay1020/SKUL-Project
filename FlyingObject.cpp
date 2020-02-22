#include "stdafx.h"
#include "FlyingObject.h"

FlyingObject::FlyingObject()
{
}

FlyingObject::~FlyingObject()
{
}

void FlyingObject::Release()
{
	// 릴리즈 (터질 위험이 있으니 일단 주석)
	//while (vFlyingObj.size() != 0)
	//{
	//	delete vFlyingObj.begin()->img;
	//	delete vFlyingObj.begin()->ani;
	//	vFlyingObj.erase(vFlyingObj.begin);
	//}
}

void FlyingObject::update()
{
	// 투사체 이동 함수
	Move_FlyingObj();
}

void FlyingObject::render()
{
	// 투사체 오브젝트 출력
	Show_FlyingObj();
}

void FlyingObject::Create_FlyingObj(string imgName, string aniName, FLYINFOBJECT_TYPE type_V, float x, float y, float angle_V, float speed_V, bool Frame)
{
	// 투사체 오브젝트를 만든다.
	FlyingObjectInfo new_FlyingObj;
	new_FlyingObj.reset();
	new_FlyingObj.setting_Info(imgName, aniName, type_V, x, y, angle_V, speed_V, Frame);

	vFlyingObj.push_back(new_FlyingObj);

}

void FlyingObject::Move_FlyingObj()
{
	for (viFlyingObj = vFlyingObj.begin(); viFlyingObj != vFlyingObj.end();)
	{
		// 투사체 이동
		(*viFlyingObj).center.x += cosf((*viFlyingObj).angle) * (*viFlyingObj).speed;
		(*viFlyingObj).center.y += -sinf((*viFlyingObj).angle) * (*viFlyingObj).speed;

		// 투사체 삭제 카운트 증가
		(*viFlyingObj).Delete_Timer++;

		// 투사체 삭제 카운트 조건에 만족하면
		if ((*viFlyingObj).Delete_Timer >= (*viFlyingObj).get_Timer_Count())
		{
			viFlyingObj = vFlyingObj.erase(viFlyingObj);
		}

		// 만족하지 않는다면 다음으로
		else viFlyingObj++;
	}
}

void FlyingObject::Show_FlyingObj()
{
	// 카메라 좌표만큼 뺀 값을 담기 위해
	RECT tempRC;

	for (viFlyingObj = vFlyingObj.begin(); viFlyingObj != vFlyingObj.end(); ++viFlyingObj)
	{
	
		// 프레임 이미지가 아니라면
		if (!(*viFlyingObj).isFrame)
		{
			tempRC = (*viFlyingObj).rc;
			tempRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
			tempRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

			(*viFlyingObj).img->render(getMemDC(), tempRC.left, tempRC.top);
		}

		// 프레임 이미지라면 애니메이션이라는 뜻
		if ((*viFlyingObj).isFrame)
		{
			IMAGEMANAGER->findImage((*viFlyingObj).aniName)->aniRender(getMemDC(), 
				(*viFlyingObj).center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x, 
				(*viFlyingObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y,
				(*viFlyingObj).ani);

			cout << (*viFlyingObj).ani->getFramePos().x << endl;

		}
	}
}
