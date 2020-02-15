#include "stdafx.h"
#include "Player.h"
#include "CharacterState.h" 


Player::Player()
{
	// 기본 플레이어 셋팅
	info.set_Status("스컬", 100, 15, 0, DIRECTION_RIGHT);
	info.set_Pos(100, CAMERAMANAGER->Use_Func()->get_World_Size().y - 64 * 3, PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	info.set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
	info.img.ani->start();

	inputKey = PRESS_EMPTY;				// 아무것도 입력받지 않은 상태
	state = IdleState::getInstance();	// 기본 상태는 Idle
}

void Player::set_State(CharacterState * state)
{
	this->state = state;
}

void Player::set_InputKey(InputKey key)
{
	this->inputKey = key;
}

void Player::init()
{
}

void Player::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		info.status.direction = DIRECTION_LEFT;		// 캐릭터의 방향을 저장한다.

		inputKey = PRESS_LEFT;						// 입력한 키를 저장한다.
		state->Move(this);							// 상태를 Move로 바꿔준다.
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		info.status.direction = DIRECTION_RIGHT;	// 캐릭터의 방향을 저장한다.

		inputKey = PRESS_LEFT;						// 입력한 키를 저장한다.
		state->Idle(this);							// 상태를 Idle로 바꿔준다.
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{

		inputKey = PRESS_RIGHT;						// 입력한 키를 저장한다.
		state->Move(this);							// 상태를 Move로 바꿔준다.
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		inputKey = PRESS_RIGHT;						// 입력한 키를 저장한다.
		state->Idle(this);							// 상태를 Idle로 바꿔준다.
	}

	state->update(this);							// 상태 업데이트
}

void Player::release()
{
}


