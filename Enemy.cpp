#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	// 기본 상태 초기화

}

void Enemy::set_State(EnemyState* state)
{
	this->state = state;
}

void Enemy::init()
{
}

void Enemy::update()
{
	// 상태 업데이트
	state->update(this);

}

void Enemy::render(HDC getMemDC)
{
	IMAGEMANAGER->findImage(info.img.imgName)->aniRender(getMemDC, 
		info.pos.ani_Rc.left - CAMERAMANAGER->Use_Func()->get_CameraXY().x, info.pos.ani_Rc.top - CAMERAMANAGER->Use_Func()->get_CameraXY().y, info.img.ani);

	RECT temp_AniRC = info.pos.ani_Rc;
	temp_AniRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_AniRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_AniRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	temp_AniRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	RECT temp_HitRange_Rc = info.pos.hit_Range_Rc;
	temp_HitRange_Rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_HitRange_Rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_HitRange_Rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	temp_HitRange_Rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	if(KEYMANAGER->isToggleKey('0'))	Rectangle(getMemDC, temp_AniRC);
	if(KEYMANAGER->isToggleKey('9'))	Rectangle(getMemDC, temp_HitRange_Rc);
}
