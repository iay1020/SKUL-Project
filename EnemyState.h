#pragma once
#include "Enemy.h"


// 에너미 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class EnemyState
{
public:
	virtual void Idle(Enemy* enemy) = 0;
	virtual void Move(Enemy* enemy) = 0;
	virtual void Jump(Enemy* enemy) = 0;
	virtual void Fall(Enemy* enemy) = 0;
	virtual void Hit(Enemy* enemy) = 0;
	virtual void Attack_A(Enemy* enemy) = 0;
	virtual void Attack_B(Enemy* enemy) = 0;
	virtual void Skill_A(Enemy* enemy) = 0;
	virtual void Skill_B(Enemy* enemy) = 0;
	virtual void update(Enemy* enemy) = 0;

protected:
	void set_EnemyState(Enemy* enemy, EnemyState* state)
	{
		enemy->set_State(state);
	}

};







//대기 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class IdleState_E : public EnemyState
{
	static IdleState_E* instance;

public:
	static IdleState_E* getInstance();

	virtual void Idle(Enemy* enemy);
	virtual void Move(Enemy* enemy);
	virtual void Jump(Enemy* enemy);
	virtual void Fall(Enemy* enemy);
	virtual void Hit(Enemy* enemy);
	virtual void Attack_A(Enemy* enemy);
	virtual void Attack_B(Enemy* enemy);
	virtual void Skill_A(Enemy* enemy);
	virtual void Skill_B(Enemy* enemy);
	virtual void update(Enemy* enemy);

};






//이동 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class MoveState_E : public EnemyState
{
	static MoveState_E* instance;

public:
	static MoveState_E* getInstance();

	virtual void Idle(Enemy* enemy);
	virtual void Move(Enemy* enemy);
	virtual void Jump(Enemy* enemy);
	virtual void Fall(Enemy* enemy);
	virtual void Hit(Enemy* enemy);
	virtual void Attack_A(Enemy* enemy);
	virtual void Attack_B(Enemy* enemy);
	virtual void Skill_A(Enemy* enemy);
	virtual void Skill_B(Enemy* enemy);
	virtual void update(Enemy* enemy);

};






//점프 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class JumpState_E : public EnemyState
{
	static JumpState_E* instance;

public:
	static JumpState_E* getInstance();

	virtual void Idle(Enemy* enemy);
	virtual void Move(Enemy* enemy);
	virtual void Jump(Enemy* enemy);
	virtual void Fall(Enemy* enemy);
	virtual void Hit(Enemy* enemy);
	virtual void Attack_A(Enemy* enemy);
	virtual void Attack_B(Enemy* enemy);
	virtual void Skill_A(Enemy* enemy);
	virtual void Skill_B(Enemy* enemy);
	virtual void update(Enemy* enemy);

};






//추락 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class FallState_E : public EnemyState
{
	static FallState_E* instance;

public:
	static FallState_E* getInstance();

	virtual void Idle(Enemy* enemy);
	virtual void Move(Enemy* enemy);
	virtual void Jump(Enemy* enemy);
	virtual void Fall(Enemy* enemy);
	virtual void Hit(Enemy* enemy);
	virtual void Attack_A(Enemy* enemy);
	virtual void Attack_B(Enemy* enemy);
	virtual void Skill_A(Enemy* enemy);
	virtual void Skill_B(Enemy* enemy);
	virtual void update(Enemy* enemy);

};





//피격 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class HitState_E : public EnemyState
{
	static HitState_E* instance;

public:
	static HitState_E* getInstance();

	virtual void Idle(Enemy* enemy);
	virtual void Move(Enemy* enemy);
	virtual void Jump(Enemy* enemy);
	virtual void Fall(Enemy* enemy);
	virtual void Hit(Enemy* enemy);
	virtual void Attack_A(Enemy* enemy);
	virtual void Attack_B(Enemy* enemy);
	virtual void Skill_A(Enemy* enemy);
	virtual void Skill_B(Enemy* enemy);
	virtual void update(Enemy* enemy);

};







//기본 공격 A 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class Attack_A_State_E : public EnemyState
{
	static Attack_A_State_E* instance;

public:
	static Attack_A_State_E* getInstance();

	virtual void Idle(Enemy* enemy);
	virtual void Move(Enemy* enemy);
	virtual void Jump(Enemy* enemy);
	virtual void Fall(Enemy* enemy);
	virtual void Hit(Enemy* enemy);
	virtual void Attack_A(Enemy* enemy);
	virtual void Attack_B(Enemy* enemy);
	virtual void Skill_A(Enemy* enemy);
	virtual void Skill_B(Enemy* enemy);
	virtual void update(Enemy* enemy);

};






//기본 공격 B 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class Attack_B_State_E : public EnemyState
{
	static Attack_B_State_E* instance;

public:
	static Attack_B_State_E* getInstance();

	virtual void Idle(Enemy* enemy);
	virtual void Move(Enemy* enemy);
	virtual void Jump(Enemy* enemy);
	virtual void Fall(Enemy* enemy);
	virtual void Hit(Enemy* enemy);
	virtual void Attack_A(Enemy* enemy);
	virtual void Attack_B(Enemy* enemy);
	virtual void Skill_A(Enemy* enemy);
	virtual void Skill_B(Enemy* enemy);
	virtual void update(Enemy* enemy);

};







//스킬 A 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class Skill_A_State_E : public EnemyState
{
	static Skill_A_State_E* instance;

public:
	static Skill_A_State_E* getInstance();

	virtual void Idle(Enemy* enemy);
	virtual void Move(Enemy* enemy);
	virtual void Jump(Enemy* enemy);
	virtual void Fall(Enemy* enemy);
	virtual void Hit(Enemy* enemy);
	virtual void Attack_A(Enemy* enemy);
	virtual void Attack_B(Enemy* enemy);
	virtual void Skill_A(Enemy* enemy);
	virtual void Skill_B(Enemy* enemy);
	virtual void update(Enemy* enemy);

};








//스킬 B 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
class Skill_B_State_E : public EnemyState
{
	static Skill_B_State_E* instance;

public:
	static Skill_B_State_E* getInstance();

	virtual void Idle(Enemy* enemy);
	virtual void Move(Enemy* enemy);
	virtual void Jump(Enemy* enemy);
	virtual void Fall(Enemy* enemy);
	virtual void Hit(Enemy* enemy);
	virtual void Attack_A(Enemy* enemy);
	virtual void Attack_B(Enemy* enemy);
	virtual void Skill_A(Enemy* enemy);
	virtual void Skill_B(Enemy* enemy);
	virtual void update(Enemy* enemy);

};