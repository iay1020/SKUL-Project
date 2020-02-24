#pragma once
#include "Player.h"






// 캐릭터 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class CharacterState
{
public:
	virtual void Idle(Player* player)		= 0;
	virtual void Move(Player* player)		= 0;
	virtual void Jump(Player* player)		= 0;
	virtual void Fall(Player* player)		= 0;
	virtual void DownJump(Player* player)	= 0;
	virtual void Dash(Player* player)		= 0;
	virtual void JumpAttack(Player* player) = 0;
	virtual void Attack_A(Player* player)	= 0;
	virtual void Attack_B(Player* player)	= 0;
	virtual void Attack_C(Player* player)	= 0;
	virtual void Skill_A(Player* player)	= 0;
	virtual void Skill_B(Player* player)	= 0;
	virtual void update(Player* player)		= 0;

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
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
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
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
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
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
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
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
	virtual void update(Player* player);

};





// 아래 점프 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
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
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
	virtual void update(Player* player);
};






// 점프 공격 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class JumpAttackState : public CharacterState
{
	static JumpAttackState* instance;

public:
	static JumpAttackState* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
	virtual void update(Player* player);
};




// 기본공격 A 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class Attack_A_State : public CharacterState
{
	static Attack_A_State* instance;

public:
	static Attack_A_State* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
	virtual void update(Player* player);
};





// 기본공격 B 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class Attack_B_State : public CharacterState
{
	static Attack_B_State* instance;

public:
	static Attack_B_State* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
	virtual void update(Player* player);
};





// 기본공격 C 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class Attack_C_State : public CharacterState
{
	static Attack_C_State* instance;

public:
	static Attack_C_State* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
	virtual void update(Player* player);
};





// 스킬 A 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class Skill_A_State : public CharacterState
{
	static Skill_A_State* instance;

public:
	static Skill_A_State* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
	virtual void update(Player* player);
};





// 스킬 B 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class Skill_B_State : public CharacterState
{
	static Skill_B_State* instance;

public:
	static Skill_B_State* getInstance();

	virtual void Idle(Player* player);
	virtual void Move(Player* player);
	virtual void Jump(Player* player);
	virtual void Fall(Player* player);
	virtual void DownJump(Player* player);
	virtual void Dash(Player* player);
	virtual void JumpAttack(Player* player);
	virtual void Attack_A(Player* player);
	virtual void Attack_B(Player* player);
	virtual void Attack_C(Player* player);
	virtual void Skill_A(Player* player);
	virtual void Skill_B(Player* player);
	virtual void update(Player* player);
};