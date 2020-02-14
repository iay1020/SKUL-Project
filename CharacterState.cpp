#include "stdafx.h"
#include "CharacterState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;

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
}

void IdleState::Move(Player * player, InputKey Key)
{
	player->set_State(MoveState::getInstance());
	
}

void IdleState::update(Player * player)
{
	cout << "Idle : ���" << endl;
}

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
}

void MoveState::Move(Player * player, InputKey Key)
{
	*inputKey = Key;
}

void MoveState::update(Player * player)
{
	if (*inputKey == PRESS_LEFT)   cout << "Left : �̵�" << endl;
	if (*inputKey == PRESS_RIGHT)  cout << "Right : �̵�" << endl;
	if (*inputKey == PRESS_EMPTY)  cout << "���� �������" << endl;

	*inputKey = PRESS_EMPTY;

	player->set_State(IdleState::getInstance());
}


