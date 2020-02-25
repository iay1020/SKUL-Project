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
	// 플레이어에게 맞았을 경우
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// 피격 애니메이션을 넣어준다.
		IdleState_E::Hit(enemy);

	}

	// 바닥에 땅이 없을 경우 추락
	if (!DATAMANAGER->enemy_find_Down_Gorund(enemy))
	{
		// 추락상태
		IdleState_E::Fall(enemy);
	}


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
	enemy->info_Address()->ani_Changer("Walk");
	enemy->info_Address()->img.ani->start();

	// 에너미의 상태를 무브 상태로 교체한다.
	enemy->set_State(MoveState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void IdleState_E::Jump(Enemy * enemy)
{
}

void IdleState_E::Fall(Enemy * enemy)
{
	// 추락 애니메이션이 없기 때문에 바로 추락 상태로 변경시켜준다.
	enemy->set_State(FallState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void IdleState_E::Hit(Enemy * enemy)
{
	// 에너미의 피격 애니메이션을 넣어준다.
	enemy->info_Address()->ani_Changer("Hit");
	enemy->info_Address()->img.ani->start();

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void IdleState_E::Attack_A(Enemy * enemy)
{
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
	// 바닥에 땅이 없을 경우 추락
	if (!DATAMANAGER->enemy_find_Down_Gorund(enemy))
	{
		// 추락상태
		MoveState_E::Fall(enemy);
	}

	// 플레이어에게 맞았을 경우
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// 피격 애니메이션을 넣어준다.
		MoveState_E::Hit(enemy);

	}

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
	// 추락 애니메이션이 없기 때문에 바로 추락 상태로 변경시켜준다.
	enemy->set_State(FallState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void MoveState_E::Hit(Enemy * enemy)
{
	// 에너미의 피격 애니메이션을 넣어준다.
	enemy->info_Address()->ani_Changer("Hit");
	enemy->info_Address()->img.ani->start();

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void MoveState_E::Attack_A(Enemy * enemy)
{
	// 일단 대기 상태에서 공격 상태로 전환
	enemy->info_Address()->ani_Changer("Idle");
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
	// 추락에 사용했던 변수 초기화
	enemy->info_Address()->pos.fall_Power = 0;

	// 피격 쿨타임 초기화
	enemy->info_Address()->cool_Time.knockBack_Time = 0;

	// 맞았다는 bool값 초기화
	enemy->info_Address()->bool_V.player_Attack_Hit = false;

	// 대기 애니메이션을 넣는다.
	enemy->info_Address()->ani_Changer("Idle");
	enemy->info_Address()->img.ani->start();

	// 대기 상태로 교체
	enemy->set_State(IdleState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void FallState_E::Move(Enemy * enemy)
{
}

void FallState_E::Jump(Enemy * enemy)
{
}

void FallState_E::Fall(Enemy * enemy)
{
	// 아래에 땅을 발견할때까지 추락한다.
	// 땅을 발견하면 Idle으로 교체
	if (DATAMANAGER->enemy_find_Down_Gorund(enemy))
	{
		FallState_E::Idle(enemy);
	}

	enemy->info_Address()->pos.center.y -= enemy->info_Address()->pos.fall_Power;
	enemy->info_Address()->pos.fall_Power -= ENEMY_GRAVITY;
	enemy->info_Address()->update_Rect();
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
	// 대기 애니메이션으로 교체
	enemy->info_Address()->ani_Changer("Idle");
	enemy->info_Address()->img.ani->start();

	// 대기 상태로 교체
	enemy->set_State(IdleState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void HitState_E::Move(Enemy * enemy)
{
}

void HitState_E::Jump(Enemy * enemy)
{
}

void HitState_E::Fall(Enemy * enemy)
{
	// 추락 애니메이션이 없기 때문에 바로 추락 상태로 변경시켜준다.
	enemy->set_State(FallState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void HitState_E::Hit(Enemy * enemy)
{
	// 플레이어에게 맞으면 자신이 바라보는 방향 뒤쪽으로 살짝 밀려난다.
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// 에너미의 피격 쿨타임을 돌린다.
		enemy->info_Address()->cool_Time.knockBack_Time++;

		if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)
		{
			// 반대방향으로 이동한다.
			if (DATAMANAGER->enemy_Move_Wall(enemy, EnemyDirection::RIGHT))
			{
				enemy->info_Address()->pos.center.x += ENEMYKNOCKBACK_RANGE;
			}
		}

		if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT)
		{
			// 반대방향으로 이동한다.
			if (DATAMANAGER->enemy_Move_Wall(enemy, EnemyDirection::LEFT))
			{
				enemy->info_Address()->pos.center.x -= ENEMYKNOCKBACK_RANGE;
			}
		}

		// 렉트 갱신
		enemy->info_Address()->update_Rect();
	}

	// 바닥에 땅이 없을 경우 추락
	if (!DATAMANAGER->enemy_find_Down_Gorund(enemy))
	{
		// 추락상태
		HitState_E::Fall(enemy);
	}

	// 에너미의 피격 시간이 끝났다면
	if (enemy->info_Address()->cool_Time.knockBack_Time >= ENEMYKNOCKBACK_TIME)
	{
		// 피격 쿨타임 초기화
		enemy->info_Address()->cool_Time.knockBack_Time = 0;

		// 맞았다는 bool값 초기화
		enemy->info_Address()->bool_V.player_Attack_Hit = false;

		HitState_E::Idle(enemy);
	}
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
	// 에너미의 피격 애니메이션을 넣어준다.
	enemy->info_Address()->ani_Changer("Hit");
	enemy->info_Address()->img.ani->start();

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void Attack_A_State_E::Attack_A(Enemy * enemy)
{
	// 플레이어에게 맞았을 경우
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// 피격 애니메이션을 넣어준다.
		Attack_A_State_E::Hit(enemy);

	}

	// 플레이어가 인식범위 밖에 있다면 대기 상태로 바꿔준다.
	if (!DATAMANAGER->find_Attack_Range(enemy))
	{
		enemy->info_Address()->bool_V.attackCheck = false;
		enemy->info_Address()->cool_Time.attack_CoolTime_Cnt = 0;
	
		Idle(enemy);
	}

	// 공격 쿨타임까지 공격 애니메이션을 재생하지 않는다.
	if (enemy->info_Address()->bool_V.attackCheck)	enemy->info_Address()->cool_Time.attack_CoolTime_Cnt++;
	
	if (enemy->info_Address()->cool_Time.attack_CoolTime <= enemy->info_Address()->cool_Time.attack_CoolTime_Cnt &&
		enemy->info_Address()->bool_V.attackCheck)
	{
		// 애니메이션을 재생한다.
		enemy->info_Address()->ani_Changer("Attack_A");
		enemy->info_Address()->img.ani->start();
	
		// 다시 공격 가능하게 false로 바꾼다.
		enemy->info_Address()->bool_V.attackCheck = false;

		// 다시 공격 가능하게 false로 바꿔준다. (플레이어 공격)
		enemy->info_Address()->bool_V.Attack_Hit = false;
	
		// 쿨타임 초기화
		enemy->info_Address()->cool_Time.attack_CoolTime_Cnt = 0;

		
	}
	
	

	// 공격 프레임이 모두 끝나면 대기 상태로
	if (enemy->info_Address()->img.ani->getFramePos().x == 688)
	{
		// 에너미 공격 렉트를 그려준다.
		enemy->info_Address()->make_Attack_Rect();

		// 에너미의 공격 렉트에 플레이어가 맞았는지 연산
		DATAMANAGER->enemy_Attack_Hit(enemy);

		Attack_A_State_E::Idle(enemy);

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
