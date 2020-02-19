#include "stdafx.h"
#include "Player.h"
#include "CharacterState.h" 


Player::Player()
{
	// 기본 플레이어 셋팅
	info.reset();
	info.set_Status("스컬", 100, 15, 0, DIRECTION_RIGHT, 1, 1);
	info.set_Pos(100, CAMERAMANAGER->Use_Func()->get_World_Size().y - 64 * 3, PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	info.set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
	info.img.ani->start();

	inputKey = PRESS_RIGHT;				// 오른쪽 애니메이션을 쓰고 있으니까
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
	state->update(this);							// 상태 업데이트
}

void Player::release()
{
}


