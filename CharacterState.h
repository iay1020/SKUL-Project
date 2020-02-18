#pragma once
#include "Player.h"






// ฤณธฏลอ ป๓ลย กแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแ
class CharacterState
{
public:
	virtual void Idle(Player* player)		= 0;
	virtual void Move(Player* player)		= 0;
	virtual void Jump(Player* player)		= 0;
	virtual void Fall(Player* player)		= 0;
	virtual void DownJump(Player* player)	= 0;
	virtual void Dash(Player* player)		= 0;
	virtual void update(Player* player)		= 0;
	
protected:

protected:
	void set_PlayerState(Player* player, CharacterState* state)
	{
		player->set_State(state);
	}
};





// ด๋ฑโ ป๓ลย กแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแ
class IdleState : public CharacterState
{
	static IdleState* instance;

public:
	static IdleState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);
	
};





// ภฬตฟ ป๓ลย กแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแ
class MoveState : public CharacterState
{
	static MoveState* instance;

public:
	static MoveState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);

};





// มกวม ป๓ลย กแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแ
class JumpState : public CharacterState
{
	static JumpState* instance;

public:
	static JumpState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);

};





// ร฿ถ๔ ป๓ลย กแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแ
class FallState : public CharacterState
{
	static FallState* instance;

public:
	static FallState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);

};





// พฦทก มกวม ป๓ลย กแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแ
class DownJumpState : public CharacterState
{
	static DownJumpState* instance;

public:
	static DownJumpState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);

};




// ด๋ฝฌ ป๓ลย กแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแกแ
class DashState : public CharacterState
{
	static DashState* instance;

public:
	static DashState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void update(Player* player);
};



//class Player;
//
//// ป๓ลย มพท๙
//enum STATE
//{
//	STATE_IDLE,
//	STATE_WALK
//};
//
//// ป๓ลย ภฮลอฦไภฬฝบ
//class CharacterState
//{
//protected:
//	Player* me;
//
//public:
//	CharacterState(Player* owner = nullptr) { me = owner; }
//	virtual ~CharacterState() {} // ผาธ๊ภฺ
//	virtual void handleInput() {}
//	virtual void update() {}
//};
//
//// ป๓ลยบฐ ลฌทกฝบ ธธต้ฑโ
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