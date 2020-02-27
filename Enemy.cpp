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

	// 스컬의 공격 범위에 에너미가 들어왔다.
	DATAMANAGER->skul_Attack_Range_Enemy(this);

	// 스컬의 HP 셋팅
	info.update_HP();

	
}

void Enemy::render(HDC getMemDC)
{
	// 피격중이 아닐때
	if (!info.bool_V.player_Attack_Hit)
	{
		IMAGEMANAGER->findImage(info.img.imgName)->aniRender(getMemDC,
			info.pos.ani_Rc.left - CAMERAMANAGER->Use_Func()->get_CameraXY().x, info.pos.ani_Rc.top - CAMERAMANAGER->Use_Func()->get_CameraXY().y, info.img.ani);
	}
	// 피격중일때 
	if (info.bool_V.player_Attack_Hit)
	{
		IMAGEMANAGER->findImage(info.img.imgName)->frameRender(getMemDC,
			info.pos.ani_Rc.left - CAMERAMANAGER->Use_Func()->get_CameraXY().x, info.pos.ani_Rc.top - CAMERAMANAGER->Use_Func()->get_CameraXY().y,
			info.img.curX, info.img.curY);
	}

	// hp 출력
	if (info.bool_V.im_Hit)
	{
		info.hp.img_HP_BG->render(getMemDC, info.hp.rc_HP_BG.left - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
			info.hp.rc_HP_BG.top - CAMERAMANAGER->Use_Func()->get_CameraXY().y);

		info.hp.img_HP_Back->render(getMemDC, info.hp.rc_HP_Back.left - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
			info.hp.rc_HP_Back.top - CAMERAMANAGER->Use_Func()->get_CameraXY().y,
			0, 0, info.hp.rc_HP_Back.right - info.hp.rc_HP_Back.left, info.hp.img_HP_Back->getHeight());

		info.hp.img_HP_Front->render(getMemDC, info.hp.rc_HP_Front.left - CAMERAMANAGER->Use_Func()->get_CameraXY().x
			, info.hp.rc_HP_Front.top - CAMERAMANAGER->Use_Func()->get_CameraXY().y,
			0, 0, info.hp.rc_HP_Front.right - info.hp.rc_HP_Front.left, info.hp.img_HP_Front->getHeight());
	}

	RECT temp_AniRC = info.pos.find_Range_Rc;
	temp_AniRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_AniRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_AniRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	temp_AniRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	RECT temp_HitRange_Rc = info.pos.hit_Range_Rc;
	temp_HitRange_Rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_HitRange_Rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_HitRange_Rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	temp_HitRange_Rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	RECT temp_Attack_Rc = info.pos.Attack_Rc;
	temp_Attack_Rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_Attack_Rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	temp_Attack_Rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	temp_Attack_Rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

	if(KEYMANAGER->isToggleKey('0'))	Rectangle(getMemDC, temp_AniRC);
	if(KEYMANAGER->isToggleKey('9'))	Rectangle(getMemDC, temp_HitRange_Rc);
	if (KEYMANAGER->isToggleKey('8'))	Rectangle(getMemDC, temp_Attack_Rc);
}
