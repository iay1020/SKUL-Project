#pragma once

class CharacterState;

class Player
{
protected:
	CharacterState* state;		// 플레이어 상태
	InputKey		inputKey;	// 플레이어 입력 키
	CharacterInfo	info;		// 플레이어 스테이터스

public:
	Player();

	// ■■■■■■■■■■■■■■■ Set ■■■■■■■■■■■■■■■■■
	// IdleState, WalkState, JumpState, FallState
	void set_State(CharacterState* state);
	void set_InputKey(InputKey key);
	CharacterInfo* set_Info() { return &info; }
	void update_Pos(int idx, int idy) { info.pos.center.x = idx * TILE_SIZE_X; info.pos.center.y = idy * TILE_SIZE_Y; }			// 인덱스를 이용하여 좌표 갱신	
	void update_Rect(short sizeX, short sizeY) { info.update_Rect(sizeX, sizeY); }												// 렉트 갱신
	void update_Ani_Rect() { info.update_Ani_Rect(); }																			// 애니 렉트 갱신

	// ■■■■■■■■■■■■■■■ Get ■■■■■■■■■■■■■■■■■
	CharacterState* get_State() { return state; }
	InputKey get_InputKey() { return inputKey; }
	CharacterInfo get_Info() { return info; }

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

