#include "stdafx.h"
#include "Player.h"
#include "CharacterState.h" 


Player::Player()
{
	// �⺻ �÷��̾� ����
	info.set_Status("����", 100, 15, 0, DIRECTION_RIGHT);
	info.set_Pos(100, CAMERAMANAGER->Use_Func()->get_World_Size().y - 64 * 3, PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	info.set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
	info.img.ani->start();

	inputKey = PRESS_EMPTY;				// �ƹ��͵� �Է¹��� ���� ����
	state = IdleState::getInstance();	// �⺻ ���´� Idle
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
		info.status.direction = DIRECTION_LEFT;		// ĳ������ ������ �����Ѵ�.

		inputKey = PRESS_LEFT;						// �Է��� Ű�� �����Ѵ�.
		state->Move(this);							// ���¸� Move�� �ٲ��ش�.
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		info.status.direction = DIRECTION_RIGHT;	// ĳ������ ������ �����Ѵ�.

		inputKey = PRESS_LEFT;						// �Է��� Ű�� �����Ѵ�.
		state->Idle(this);							// ���¸� Idle�� �ٲ��ش�.
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{

		inputKey = PRESS_RIGHT;						// �Է��� Ű�� �����Ѵ�.
		state->Move(this);							// ���¸� Move�� �ٲ��ش�.
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		inputKey = PRESS_RIGHT;						// �Է��� Ű�� �����Ѵ�.
		state->Idle(this);							// ���¸� Idle�� �ٲ��ش�.
	}

	state->update(this);							// ���� ������Ʈ
}

void Player::release()
{
}


