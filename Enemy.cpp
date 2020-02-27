#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	// �⺻ ���� �ʱ�ȭ

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
	// ���� ������Ʈ
	state->update(this);

	// ������ ���� ������ ���ʹ̰� ���Դ�.
	DATAMANAGER->skul_Attack_Range_Enemy(this);

	// ������ HP ����
	info.update_HP();

	
}

void Enemy::render(HDC getMemDC)
{
	// �ǰ����� �ƴҶ�
	if (!info.bool_V.player_Attack_Hit)
	{
		IMAGEMANAGER->findImage(info.img.imgName)->aniRender(getMemDC,
			info.pos.ani_Rc.left - CAMERAMANAGER->Use_Func()->get_CameraXY().x, info.pos.ani_Rc.top - CAMERAMANAGER->Use_Func()->get_CameraXY().y, info.img.ani);
	}
	// �ǰ����϶� 
	if (info.bool_V.player_Attack_Hit)
	{
		IMAGEMANAGER->findImage(info.img.imgName)->frameRender(getMemDC,
			info.pos.ani_Rc.left - CAMERAMANAGER->Use_Func()->get_CameraXY().x, info.pos.ani_Rc.top - CAMERAMANAGER->Use_Func()->get_CameraXY().y,
			info.img.curX, info.img.curY);
	}

	// hp ���
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
