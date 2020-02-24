#pragma once
#include "Enemy.h"


// ���ʹ� ���� �������������������������������������������������������������������������������������������������������
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







//��� ���� �������������������������������������������������������������������������������������������������������
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






//�̵� ���� �������������������������������������������������������������������������������������������������������
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






//���� ���� �������������������������������������������������������������������������������������������������������
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






//�߶� ���� �������������������������������������������������������������������������������������������������������
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





//�ǰ� ���� �������������������������������������������������������������������������������������������������������
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







//�⺻ ���� A ���� �������������������������������������������������������������������������������������������������������
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






//�⺻ ���� B ���� �������������������������������������������������������������������������������������������������������
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







//��ų A ���� �������������������������������������������������������������������������������������������������������
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








//��ų B ���� �������������������������������������������������������������������������������������������������������
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