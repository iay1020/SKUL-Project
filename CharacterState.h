#pragma once
#include "Player.h"






// ĳ���� ���� �������������������������������������������������������������������������������������������������������
class CharacterState
{
public:
	virtual void Idle(Player* player)	= 0;
	virtual void Move(Player* player)   = 0;
	virtual void Jump(Player* player)   = 0;
	virtual void Fall(Player* player)   = 0;
	virtual void Dash(Player* player)   = 0;
	virtual void update(Player* player) = 0;
	
protected:

protected:
	void set_PlayerState(Player* player, CharacterState* state)
	{
		player->set_State(state);
	}
};





// ��� ���� �������������������������������������������������������������������������������������������������������
class IdleState : public CharacterState
{
	static IdleState* instance;

public:
	static IdleState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);
	
};





// �̵� ���� �������������������������������������������������������������������������������������������������������
class MoveState : public CharacterState
{
	static MoveState* instance;

public:
	static MoveState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);

};





// ���� ���� �������������������������������������������������������������������������������������������������������
class JumpState : public CharacterState
{
	static JumpState* instance;

public:
	static JumpState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);

};





// �߶� ���� �������������������������������������������������������������������������������������������������������
class FallState : public CharacterState
{
	static FallState* instance;

public:
	static FallState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);


};





// �뽬 ���� �������������������������������������������������������������������������������������������������������
class DashState : public CharacterState
{
	static DashState* instance;

public:
	static DashState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);
};



//class Player;
//
//// ���� ����
//enum STATE
//{
//	STATE_IDLE,
//	STATE_WALK
//};
//
//// ���� �������̽�
//class CharacterState
//{
//protected:
//	Player* me;
//
//public:
//	CharacterState(Player* owner = nullptr) { me = owner; }
//	virtual ~CharacterState() {} // �Ҹ���
//	virtual void handleInput() {}
//	virtual void update() {}
//};
//
//// ���º� Ŭ���� �����
//class IdleState : public CharacterState
//{
//public:
//	IdleState(Player* owner = nullptr) { this->me = owner; }
//	virtual void handleInput()
//	{
//
//	}
//
//	virtual void update()
//	{
//		cout << "Idle" << endl;
//	}
//
//};
//
//class MoveState : public CharacterState
//{
//public:
//	MoveState(Player*  owner = nullptr) {	this->me = owner; }
//	virtual void handleInput()
//	{
//
//	}
//	virtual void update()
//	{
//		cout << "Move" << endl;
//	}
//};
//