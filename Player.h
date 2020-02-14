#pragma once

class CharacterState;

class Player
{
private:
	CharacterState* state;

public:
	Player();

	void set_State(CharacterState* state);
	void init();
	void update();
	void release();


	
};





//class CharacterState;
////class IdleState;
////class MoveState;
//
//class Player
//{
//private:
//	CharacterState* state;
//
//public:
//	Player();
//	~Player();
//
//	void init() { state = new IdleState(this); }
//	void update()
//	{
//		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
//		{
//			state = new MoveState(this);
//		}
//		else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
//		{
//			state = new MoveState(this);
//		}
//		else
//		{
//			state = new IdleState(this);
//		}
//
//		state->update();
//	}
//	void release() {}
//	
//};

