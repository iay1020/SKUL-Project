#include "stdafx.h"
#include "EnemyState.h"

IdleState_E* IdleState_E::instance;
MoveState_E* MoveState_E::instance;
JumpState_E* JumpState_E::instance;
FallState_E* FallState_E::instance;
HitState_E* HitState_E::instance;
Attack_A_State_E* Attack_A_State_E::instance;
Attack_B_State_E* Attack_B_State_E::instance;
Skill_A_State_E* Skill_A_State_E::instance;
Skill_B_State_E* Skill_B_State_E::instance;

IdleState_E * IdleState_E::getInstance()
{
	if (instance == nullptr)
	{
		instance = new IdleState_E();
	}

	return instance;
}

void IdleState_E::Idle(Enemy * enemy)
{
	// 인식 범위에 플레이어가 있다면 플레이어가 있는 방향으로 걸어간다.
}

void IdleState_E::Move(Enemy * enemy)
{
}

void IdleState_E::Jump(Enemy * enemy)
{
}

void IdleState_E::Fall(Enemy * enemy)
{
}

void IdleState_E::Hit(Enemy * enemy)
{
}

void IdleState_E::Attack_A(Enemy * enemy)
{
}

void IdleState_E::Attack_B(Enemy * enemy)
{
}

void IdleState_E::Skill_A(Enemy * enemy)
{
}

void IdleState_E::Skill_B(Enemy * enemy)
{
}

void IdleState_E::update(Enemy * enemy)
{
	IdleState_E::Idle(enemy);


}







MoveState_E * MoveState_E::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MoveState_E();
	}

	return instance;
}

void MoveState_E::Idle(Enemy * enemy)
{
}

void MoveState_E::Move(Enemy * enemy)
{
}

void MoveState_E::Jump(Enemy * enemy)
{
}

void MoveState_E::Fall(Enemy * enemy)
{
}

void MoveState_E::Hit(Enemy * enemy)
{
}

void MoveState_E::Attack_A(Enemy * enemy)
{
}

void MoveState_E::Attack_B(Enemy * enemy)
{
}

void MoveState_E::Skill_A(Enemy * enemy)
{
}

void MoveState_E::Skill_B(Enemy * enemy)
{
}

void MoveState_E::update(Enemy * enemy)
{
	Move(enemy);

}






JumpState_E * JumpState_E::getInstance()
{
	if (instance == nullptr)
	{
		instance = new JumpState_E();
	}

	return instance;
}

void JumpState_E::Idle(Enemy * enemy)
{
}

void JumpState_E::Move(Enemy * enemy)
{
}

void JumpState_E::Jump(Enemy * enemy)
{
}

void JumpState_E::Fall(Enemy * enemy)
{
}

void JumpState_E::Hit(Enemy * enemy)
{
}

void JumpState_E::Attack_A(Enemy * enemy)
{
}

void JumpState_E::Attack_B(Enemy * enemy)
{
}

void JumpState_E::Skill_A(Enemy * enemy)
{
}

void JumpState_E::Skill_B(Enemy * enemy)
{
}

void JumpState_E::update(Enemy * enemy)
{
	Jump(enemy);
}







FallState_E * FallState_E::getInstance()
{
	if (instance == nullptr)
	{
		instance = new FallState_E();
	}

	return instance;
}

void FallState_E::Idle(Enemy * enemy)
{
}

void FallState_E::Move(Enemy * enemy)
{
}

void FallState_E::Jump(Enemy * enemy)
{
}

void FallState_E::Fall(Enemy * enemy)
{
}

void FallState_E::Hit(Enemy * enemy)
{
}

void FallState_E::Attack_A(Enemy * enemy)
{
}

void FallState_E::Attack_B(Enemy * enemy)
{
}

void FallState_E::Skill_A(Enemy * enemy)
{
}

void FallState_E::Skill_B(Enemy * enemy)
{
}

void FallState_E::update(Enemy * enemy)
{
	Fall(enemy);
}







HitState_E * HitState_E::getInstance()
{
	if (instance == nullptr)
	{
		instance = new HitState_E();
	}

	return instance;
}

void HitState_E::Idle(Enemy * enemy)
{
}

void HitState_E::Move(Enemy * enemy)
{
}

void HitState_E::Jump(Enemy * enemy)
{
}

void HitState_E::Fall(Enemy * enemy)
{
}

void HitState_E::Hit(Enemy * enemy)
{
}

void HitState_E::Attack_A(Enemy * enemy)
{
}

void HitState_E::Attack_B(Enemy * enemy)
{
}

void HitState_E::Skill_A(Enemy * enemy)
{
}

void HitState_E::Skill_B(Enemy * enemy)
{
}

void HitState_E::update(Enemy * enemy)
{
	Hit(enemy);
}







Attack_A_State_E * Attack_A_State_E::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Attack_A_State_E();
	}

	return instance;
}

void Attack_A_State_E::Idle(Enemy * enemy)
{
}

void Attack_A_State_E::Move(Enemy * enemy)
{
}

void Attack_A_State_E::Jump(Enemy * enemy)
{
}

void Attack_A_State_E::Fall(Enemy * enemy)
{
}

void Attack_A_State_E::Hit(Enemy * enemy)
{
}

void Attack_A_State_E::Attack_A(Enemy * enemy)
{
}

void Attack_A_State_E::Attack_B(Enemy * enemy)
{
}

void Attack_A_State_E::Skill_A(Enemy * enemy)
{
}

void Attack_A_State_E::Skill_B(Enemy * enemy)
{
}

void Attack_A_State_E::update(Enemy * enemy)
{
	Attack_A(enemy);

}







Attack_B_State_E * Attack_B_State_E::getInstance()
{

	if (instance == nullptr)
	{
		instance = new Attack_B_State_E();
	}

	return instance;
}

void Attack_B_State_E::Idle(Enemy * enemy)
{
}

void Attack_B_State_E::Move(Enemy * enemy)
{
}

void Attack_B_State_E::Jump(Enemy * enemy)
{
}

void Attack_B_State_E::Fall(Enemy * enemy)
{
}

void Attack_B_State_E::Hit(Enemy * enemy)
{
}

void Attack_B_State_E::Attack_A(Enemy * enemy)
{
}

void Attack_B_State_E::Attack_B(Enemy * enemy)
{
}

void Attack_B_State_E::Skill_A(Enemy * enemy)
{
}

void Attack_B_State_E::Skill_B(Enemy * enemy)
{
}

void Attack_B_State_E::update(Enemy * enemy)
{
	Attack_B(enemy);

}







Skill_A_State_E * Skill_A_State_E::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Skill_A_State_E();
	}

	return instance;
}

void Skill_A_State_E::Idle(Enemy * enemy)
{
}

void Skill_A_State_E::Move(Enemy * enemy)
{
}

void Skill_A_State_E::Jump(Enemy * enemy)
{
}

void Skill_A_State_E::Fall(Enemy * enemy)
{
}

void Skill_A_State_E::Hit(Enemy * enemy)
{
}

void Skill_A_State_E::Attack_A(Enemy * enemy)
{
}

void Skill_A_State_E::Attack_B(Enemy * enemy)
{
}

void Skill_A_State_E::Skill_A(Enemy * enemy)
{
}

void Skill_A_State_E::Skill_B(Enemy * enemy)
{
}

void Skill_A_State_E::update(Enemy * enemy)
{
	Skill_A(enemy);

}






Skill_B_State_E * Skill_B_State_E::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Skill_B_State_E();
	}

	return instance;
}

void Skill_B_State_E::Idle(Enemy * enemy)
{
}

void Skill_B_State_E::Move(Enemy * enemy)
{
}

void Skill_B_State_E::Jump(Enemy * enemy)
{
}

void Skill_B_State_E::Fall(Enemy * enemy)
{
}

void Skill_B_State_E::Hit(Enemy * enemy)
{
}

void Skill_B_State_E::Attack_A(Enemy * enemy)
{
}

void Skill_B_State_E::Attack_B(Enemy * enemy)
{
}

void Skill_B_State_E::Skill_A(Enemy * enemy)
{
}

void Skill_B_State_E::Skill_B(Enemy * enemy)
{
}

void Skill_B_State_E::update(Enemy * enemy)
{
	Skill_B(enemy);

}
