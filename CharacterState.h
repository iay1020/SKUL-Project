#pragma once
#include "Player.h"
#include "CharacterState_Library.h"

class CharacterState
{
public:
	virtual void Idle(Player* player) = 0;
	virtual void Move(Player* player, InputKey Key) = 0;
	virtual void update(Player* player) = 0;

protected:
	InputKey inputKey;

protected:
	void set_PlayerState(Player* player, CharacterState* state)
	{
		player->set_State(state);
	}
};

class IdleState : public CharacterState
{
	static IdleState* instance;

public:
	static IdleState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player, InputKey Key);
	virtual void update(Player* player);
	
};

class MoveState : public CharacterState
{
	static MoveState* instance;

public:
	static MoveState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player, InputKey Key);
	virtual void update(Player* player);

};





//class Player;
//
//// 상태 종류
//enum STATE
//{
//	STATE_IDLE,
//	STATE_WALK
//};
//
//// 상태 인터페이스
//class CharacterState
//{
//protected:
//	Player* me;
//
//public:
//	CharacterState(Player* owner = nullptr) { me = owner; }
//	virtual ~CharacterState() {} // 소멸자
//	virtual void handleInput() {}
//	virtual void update() {}
//};
//
//// 상태별 클래스 만들기
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