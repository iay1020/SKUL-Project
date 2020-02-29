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

void Enemy::call_StateFunc(EnemyStateEnum state_, EnemyState * state)
{
	
	switch (state_)
	{
	case EnemyStateEnum::IDLE:
		state->Idle(this);

		break;

	case EnemyStateEnum::WALK:
		state->Move(this);

		break;

	case EnemyStateEnum::FALL:
		state->Fall(this);

		break;

	case EnemyStateEnum::HIT:
		state->Hit(this);

		break;

	case EnemyStateEnum::ATK_A:
		state->Attack_A(this);

		break;

	case EnemyStateEnum::ATK_B:
		state->Attack_B(this);

		break;

	case EnemyStateEnum::SKILL_A:
		state->Skill_A(this);

		break;

	case EnemyStateEnum::SKILL_B:
		state->Skill_B(this);

		break;


	}
	
}

void Enemy::init()
{
}

void Enemy::update()
{
	// ���� ������Ʈ
	state->update(this);

	// ����ü�� �ǰ� �ߴ���
	DATAMANAGER->Collision_Skul_Head_Enemy(this);

	// ���� ��Ʈ ������Ʈ
	info.make_Attack_Range();

	// ������ ���� ������ ���ʹ̰� ���Դ�.
	DATAMANAGER->skul_Attack_Range_Enemy(this);

	// ���ʹ��� HP ����
	info.update_HP();

	
}

void Enemy::render(HDC getMemDC)
{
	RECT temp_AniRC = info.pos.find_Range_Rc;
	temp_AniRC = DATAMANAGER->minus_CameraPos(temp_AniRC);
	RECT temp_HitRange_Rc = info.pos.hit_Range_Rc;
	temp_HitRange_Rc = DATAMANAGER->minus_CameraPos(temp_HitRange_Rc);
	RECT temp_Attack_Rc = info.pos.Attack_Rc;
	temp_Attack_Rc = DATAMANAGER->minus_CameraPos(temp_Attack_Rc);
	RECT attack_Range_T = info.pos.attack_Range_Rc;
	attack_Range_T = DATAMANAGER->minus_CameraPos(attack_Range_T);
	RECT long_Attack_Reange_T = info.pos.long_Attack_Ranger_RC;
	long_Attack_Reange_T = DATAMANAGER->minus_CameraPos(long_Attack_Reange_T);

	if (KEYMANAGER->isToggleKey('0'))	Rectangle(getMemDC, temp_AniRC);
	if (KEYMANAGER->isToggleKey('6'))	Rectangle(getMemDC, long_Attack_Reange_T);
	if (KEYMANAGER->isToggleKey('8'))	Rectangle(getMemDC, temp_Attack_Rc);
	if (KEYMANAGER->isToggleKey('9'))	Rectangle(getMemDC, temp_HitRange_Rc);
	if (KEYMANAGER->isToggleKey('7'))	Rectangle(getMemDC, attack_Range_T);

	// �ǰ����� �ƴҶ�
	if (!info.bool_V.player_Attack_Hit)
	{
		IMAGEMANAGER->findImage(info.img.imgName)->aniRender(getMemDC,
			info.pos.ani_Rc.left - CAMERAMANAGER->Use_Func()->get_CameraXY().x, info.pos.ani_Rc.top - CAMERAMANAGER->Use_Func()->get_CameraXY().y, info.img.ani);
	}
	// �ǰ����϶� 
	if (info.bool_V.player_Attack_Hit)
	{
		// �з����� ���ʹ��� �Ӹ� ���� �������� ����ö󰣴�.
		info.pos.damege_Center.x = info.pos.center.x;
		info.pos.damege_Center.y -= 1;

		// ������ ���
		char HitDmg[20];
		sprintf_s(HitDmg, 20, "%d", info.status.show_Attack);
		if (info.bool_V.Critical_Hit) SetTextColor(getMemDC, RGB(255, 0, 0));
		TextOut(getMemDC, info.pos.damege_Center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
			info.pos.damege_Center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y,
			HitDmg, strlen(HitDmg));

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
}
