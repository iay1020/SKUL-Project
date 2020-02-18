#pragma once
#include "Player.h"






// 캐릭터 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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





// 대기 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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





// 이동 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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





// 점프 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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





// 추락 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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





// 대쉬 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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