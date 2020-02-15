#include "stdafx.h"
#include "CharacterState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;
JumpState* JumpState::instance;
FallState* FallState::instance;

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 대기 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
IdleState * IdleState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new IdleState();
	}

	return instance;
}

void IdleState::Idle(Player * player)
{
	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();

	// 멈춰있는 상태에서 점프를 눌렀다면 점프 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		player->set_State(JumpState::getInstance());
	}



	// 멈춰있는 상태에서 스킬을 눌렀다면 스킬 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('A'))
	{

	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{

	}



	// 멈춰있는 상태에서 대쉬를 눌렀다면 대쉬 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{

	}
}

void IdleState::Move(Player * player)
{
	player->set_Info()->bool_V.idle_Cheack = false;

	if (player->get_InputKey() == PRESS_LEFT)
	{

		// false라면 walk 애니메이션으로 바꿔준다.
		if (!player->get_Info().bool_V.walk_Cheack)
		{
			// 애니메이션 교체
			player->set_Info()->set_Ani("skul_Walk_NoWeapon", "skul_Walk_Left_NoWeapon");
			player->set_Info()->img.ani->start();

			// 애니메이션 교체 후 true (1번만 바꾸기 위해)
			player->set_Info()->bool_V.walk_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{

		// false라면 walk 애니메이션으로 바꿔준다.
		if (!player->get_Info().bool_V.walk_Cheack)
		{
			// 애니메이션 교체
			player->set_Info()->set_Ani("skul_Walk_NoWeapon", "skul_Walk_Right_NoWeapon");
			player->set_Info()->img.ani->start();

			// 애니메이션 교체 후 true (1번만 바꾸기 위해)
			player->set_Info()->bool_V.walk_Cheack = true;
		}
	}

	// 상태를 무브로 바꿔준다.
	player->set_State(MoveState::getInstance());
}

void IdleState::Jump(Player * player)
{
}

void IdleState::Fall(Player * player)
{
}

void IdleState::update(Player * player)
{
	Idle(player);

	KEYANIMANAGER->update();
}





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 이동 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
MoveState * MoveState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MoveState;
	}

	return instance;
}

void MoveState::Idle(Player * player)
{
	// 다음 이동 상태 애니메이션을 위해 bool값 초기화
	player->set_Info()->bool_V.walk_Cheack = false;

	if (player->get_InputKey() == PRESS_LEFT)
	{
		// false라면 idle 애니메이션으로 바꿔준다.
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			cout << "왼쪽 애니 교체" << endl;
			// 애니메이션 교체
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
			player->set_Info()->img.ani->start();

			// 애니메이션 교체 후 true (1번만 바꾸기 위해)
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// false라면 idle 애니메이션으로 바꿔준다.
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			cout << "오른쪽 애니 교체" << endl;
			// 애니메이션 교체
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
			player->set_Info()->img.ani->start();

			// 애니메이션 교체 후 true (1번만 바꾸기 위해)
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	// 상태를 대기로 바꿔준다.
	player->set_State(IdleState::getInstance());
}

void MoveState::Move(Player * player)
{
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// 플레이어가 왼쪽으로 이동
		player->set_Info()->pos.center.x -= PLAYER_SPEED;

		// 플레이어가 점프 키를 입력 한다면 점프 상태로 바꿔준다.

		// 플레이어가 공격 키를 입력 한다면 상태를 바꿔준다.

	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// 플레이어가 오른쪽으로 이동
		player->set_Info()->pos.center.x += PLAYER_SPEED;

		// 플레이어가 점프 키를 입력 한다면 점프 상태로 바꿔준다.

		// 플레이어가 공격 키를 입력 한다면 상태를 바꿔준다.

	}

	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void MoveState::Jump(Player * player)
{
}

void MoveState::Fall(Player * player)
{
}

void MoveState::update(Player * player)
{	
	Move(player);

	KEYANIMANAGER->update();
}




// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 점프 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
JumpState * JumpState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new JumpState();
	}

	return instance;
}

void JumpState::Idle(Player * player)
{
}

void JumpState::Move(Player * player)
{
}

void JumpState::Jump(Player * player)
{
	// 점프 수치를 받고 점프 수치가 0으로 변할때 추락 상태로 변경 시킨다.
	if (player->get_InputKey() == PRESS_LEFT)
	{

	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{

	}

}

void JumpState::Fall(Player * player)
{
}

void JumpState::update(Player * player)
{
	Jump(player);

	KEYANIMANAGER->update();
}





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 추락 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
FallState * FallState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new FallState();
	}

	return instance;
}

void FallState::Idle(Player * player)
{
}

void FallState::Move(Player * player)
{
}

void FallState::Jump(Player * player)
{
}

void FallState::Fall(Player * player)
{
}

void FallState::update(Player * player)
{
}
