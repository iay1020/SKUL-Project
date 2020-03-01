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
	vFlyingObj.clear();
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

void FlyingObject::Create_FlyingObj(string imgName, string aniName, FLYINFOBJECT_TYPE type_V, FLYINGOBJECT_DIRECTION dir,
	float x, float y, float angle_V, float speed_V, int atk_V, bool Frame)
{
	// 투사체 오브젝트를 만든다.
	FlyingObjectInfo new_FlyingObj;
	new_FlyingObj.reset();
	new_FlyingObj.setting_Info(imgName, aniName, type_V, dir, x, y, angle_V, speed_V, atk_V ,Frame);

	vFlyingObj.push_back(new_FlyingObj);

}

void FlyingObject::Move_FlyingObj()
{
	for (viFlyingObj = vFlyingObj.begin(); viFlyingObj != vFlyingObj.end();)
	{
		// 투사체의 타입이 스컬의 머리이고, 벽을 발견하면 반대 각도로 바꿔준다. 또한 중력을 추가해서 떨어지도록 한다. 추락중으로 바꿔준다.
		if ((*viFlyingObj).type == FLYINFOBJECT_TYPE::SKUL_HEAD)
		{
			// 추락중이지 않을때
			if (!(*viFlyingObj).isFalling && !(*viFlyingObj).isHit)
			{
				// 벽을 발견하면 각도를 반대각도로 바꿔주고, 중력을 추가하여 떨어지도록 한다. 또한 추락중으로 바꿔준다.
				if(DATAMANAGER->Collision_FlyingObject_Wall(&(*viFlyingObj)))
				{
					// 투사체의 방향에 따라 다른 연산
					if ((*viFlyingObj).dir == FLYINGOBJECT_DIRECTION::LEFT)
					{
						(*viFlyingObj).angle = 0;								// 반대 각도로 바꿔준다.
						(*viFlyingObj).speed = 5;
						(*viFlyingObj).isFalling = true;						// 추락중으로 바꿔준다.

						(*viFlyingObj).isHit = true;							// 이 투사체는 충돌이 끝났다.

						// 투사체와 충돌한 벽에 이펙트를 만든다.
						EFFECTMANAGER->play("throw_Head_Effect_R",
							(*viFlyingObj).center.x - 10 - CAMERAMANAGER->Use_Func()->get_CameraXY().x, 
							(*viFlyingObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
					}
					

					else if ((*viFlyingObj).dir == FLYINGOBJECT_DIRECTION::RIGHT)
					{
						(*viFlyingObj).angle = 3.14;							// 반대 각도로 바꿔준다.
						(*viFlyingObj).speed = 5;
						(*viFlyingObj).isFalling = true;						// 추락중으로 바꿔준다.

						(*viFlyingObj).isHit = true;							// 이 투사체는 충돌이 끝났다.

						// 투사체와 충돌한 벽에 이펙트를 만든다.
						EFFECTMANAGER->play("throw_Head_Effect_L", 
							(*viFlyingObj).center.x + 40 - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
							(*viFlyingObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);

					}
				}
			}

			// 투사체의 타입이 스컬의 머리이고, 추락중이며 땅을 발견하면 스피드를 없애버린다. 또한 애니메이션을 끈다.
			if ((*viFlyingObj).isFalling)
			{
				// 땅을 만나기 전까지는 중력을 받아 떨어진다.
				if (!DATAMANAGER->Collision_FlyingObject_Ground(&(*viFlyingObj))) (*viFlyingObj).gravity += FLYINGOBJECT_GRAVITY;

				// 땅을 만나면 추락 연산을 모두 종료하고 애니메이션을 멈춰준다.
				if (DATAMANAGER->Collision_FlyingObject_Ground(&(*viFlyingObj)))
				{
					(*viFlyingObj).speed = 0;
					(*viFlyingObj).gravity = 0;
					(*viFlyingObj).ani->stop();

				}
			}
		}

		//// 화살의 경우
		//if ((*viFlyingObj).type == FLYINFOBJECT_TYPE::ARROW)
		//{
		//	// 아직 충돌하지 않은 화살일때
		//	if (!(*viFlyingObj).isHit)
		//	{
		//		// 스컬과 충돌 했을 경우
		//
		//		
		//		// 투사체의 방향에 따라 다른 연산
		//		if ((*viFlyingObj).dir == FLYINGOBJECT_DIRECTION::LEFT)
		//		{
		//			(*viFlyingObj).isHit = true;							// 이 투사체는 충돌이 끝났다.
		//
		//			// 화살이 스컬과 충돌하면 이펙트를 만든다.
		//			EFFECTMANAGER->play("throw_Head_Effect_R",
		//				(*viFlyingObj).center.x - 10 - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
		//				(*viFlyingObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
		//		}
		//
		//
		//		 if ((*viFlyingObj).dir == FLYINGOBJECT_DIRECTION::RIGHT)
		//		{
		//			(*viFlyingObj).isHit = true;							// 이 투사체는 충돌이 끝났다.
		//
		//			// 화살이 스컬과 충돌하면 이펙트를 만든다.
		//			EFFECTMANAGER->play("throw_Head_Effect_L",
		//				(*viFlyingObj).center.x + 40 - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
		//				(*viFlyingObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
		//
		//		}
		//	}
		//
		//}

		// 투사체 이동
		(*viFlyingObj).center.x += cosf((*viFlyingObj).angle) * (*viFlyingObj).speed;
		(*viFlyingObj).center.y += -sinf((*viFlyingObj).angle) * (*viFlyingObj).speed + (*viFlyingObj).gravity;

		// 렉트 갱신
		(*viFlyingObj).update_Rect();

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
		// 카메라 보정
		tempRC = (*viFlyingObj).rc;
		tempRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		tempRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		tempRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		tempRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	
		// 프레임 이미지가 아니라면
		if (!(*viFlyingObj).isFrame)
		{
			(*viFlyingObj).img->render(getMemDC(), tempRC.left, tempRC.top);
		}

		// 프레임 이미지라면 애니메이션이라는 뜻
		if ((*viFlyingObj).isFrame)
		{
			IMAGEMANAGER->findImage((*viFlyingObj).aniName)->aniRender(getMemDC(), 
				(*viFlyingObj).center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x, 
				(*viFlyingObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y,
				(*viFlyingObj).ani);

		}
	}
}
