#include "stdafx.h"
#include "Player.h"
#include "CharacterState.h" 


Player::Player()
{
	state->init();
	state = IdleState::getInstance();
}

void Player::set_State(CharacterState * state)
{
	this->state = state;
}

void Player::init()
{
}

void Player::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//set_State(MoveState::getInstance());
		state->Move(this, PRESS_LEFT);
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//set_State(MoveState::getInstance());
		state->Move(this, PRESS_RIGHT);
	}

	state->update(this);
}

void Player::release()
{
}


