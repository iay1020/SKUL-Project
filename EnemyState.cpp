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





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 대기 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	if (DATAMANAGER->find_Player(enemy))
	{
		// 만약 공격 범위안에 있어서 bool값이 true로 바뀌면 공격 상태로 가야한다.
		if (enemy->info_Address()->bool_V.attackCheck) Attack_A(enemy);

		// 걷는 애니메이션을 넣어준다.
		if (!enemy->info_Address()->bool_V.attackCheck) Move(enemy);
	}

}

void IdleState_E::Move(Enemy * enemy)
{
	// 에너미의 방향에 맞는 애니메이션을 넣어준다.
	if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)
	{
		enemy->info_Address()->ani_Changer("Walk");
		enemy->info_Address()->img.ani->start();

	}

	if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT)
	{
		enemy->info_Address()->ani_Changer("Walk");
		enemy->info_Address()->img.ani->start();

	}

	// 에너미의 상태를 무브 상태로 교체한다.
	enemy->set_State(MoveState_E::getInstance());
	enemy->get_State()->update(enemy);
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
	// 공격 애니메이션을 넣어준다.
	enemy->info_Address()->ani_Changer("Attack_A");
	enemy->info_Address()->img.ani->start();

	// 공격 상태로 교체한다.
	enemy->set_State(Attack_A_State_E::getInstance());
	enemy->get_State()->update(enemy);

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








// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 이동 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	enemy->info_Address()->ani_Changer("Idle");
	enemy->info_Address()->img.ani->start();

	enemy->set_State(IdleState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void MoveState_E::Move(Enemy * enemy)
{
	// 만약 플레이어가 에너미가 바라보는 방향에서 사라졌을 경우에는 대기 상태로 바꿔준다.
	if (DATAMANAGER->escape_Player(enemy))
	{
		Idle(enemy);
	}

	// 플레이어가 인식범위 밖에 있다면 대기 상태로 바꿔준다.
	if (!DATAMANAGER->find_Player(enemy))
	{
		Idle(enemy);
	}

	// 플레이어가 공격 범위에 있다면 공격 상태로 바꿔준다.
	if (DATAMANAGER->find_Player(enemy))
	{
		if(enemy->info_Address()->bool_V.attackCheck)	Attack_A(enemy);
	}

	// 에너미 움직임 연산
	if (DATAMANAGER->enemy_Find_Ground(enemy))
	{
		if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)  enemy->info_Address()->pos.center.x -= enemy->info_Address()->status.speed;
		if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT) enemy->info_Address()->pos.center.x += enemy->info_Address()->status.speed;
	}

	// 렉트 갱신
	enemy->info_Address()->update_Rect();

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
	// 공격 애니메이션을 넣어준다.
	enemy->info_Address()->ani_Changer("Attack_A");
	enemy->info_Address()->img.ani->start();

	// 공격 상태로 교체한다.
	enemy->set_State(Attack_A_State_E::getInstance());
	enemy->get_State()->update(enemy);

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







// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 점프 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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








// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 추락 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 피격 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 공격_A 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 대기 애니메이션으로 교체
	enemy->info_Address()->ani_Changer("Idle");
	enemy->info_Address()->img.ani->start();

	// 대기 상태로 교체
	enemy->set_State(IdleState_E::getInstance());
	enemy->get_State()->update(enemy);

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
	//// 공격 쿨타임까지 공격 애니메이션을 재생하지 않는다.
	//if (enemy->info_Address()->bool_V.attackCheck)	enemy->info_Address()->cool_Time.attack_CoolTime_Cnt++;
	//
	//if (enemy->info_Address()->cool_Time.attack_CoolTime <= enemy->info_Address()->cool_Time.attack_CoolTime_Cnt)
	//{
	//	// 애니메이션을 재생한다.
	//	enemy->info_Address()->img.ani->start();
	//
	//	// 다시 공격 가능하게 false로 바꾼다.
	//	enemy->info_Address()->bool_V.attackCheck = false;
	//
	//	// 쿨타임 초기화
	//	enemy->info_Address()->cool_Time.attack_CoolTime_Cnt = 0;
	//}

	// 공격 프레임이 모두 끝나면 대기 상태로
	if (enemy->info_Address()->img.ani->getFramePos().x == 688)
	{
		// 다시 공격 가능하게 false로 바꾼다.
		enemy->info_Address()->bool_V.attackCheck = false;

		Idle(enemy);

	}

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






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 공격_B 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 스킬_A 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 스킬_B 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
