#pragma once
#include "Player.h"






// ĳ���� ���� �������������������������������������������������������������������������������������������������������
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





// �Ʒ� ���� ���� �������������������������������������������������������������������������������������������������������
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






// ���� ���� ���� �������������������������������������������������������������������������������������������������������
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




// �⺻���� A ���� �������������������������������������������������������������������������������������������������������
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





// �⺻���� B ���� �������������������������������������������������������������������������������������������������������
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





// �⺻���� C ���� �������������������������������������������������������������������������������������������������������
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





// ��ų A ���� �������������������������������������������������������������������������������������������������������
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





// ��ų B ���� �������������������������������������������������������������������������������������������������������
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