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

	// 공격 딜레이중이라면
	if (enemy->info_Address()->bool_V.next_Atk_Delay)
	{
		// 후딜 카운트
		enemy->info_Address()->oper.after_Delay_Cnt++;
	}

	// 카운트가 만족했다면
	if (enemy->info_Address()->oper.after_Delay <= enemy->info_Address()->oper.after_Delay_Cnt)
	{
		// 공격 딜레이를 꺼준다.
		enemy->info_Address()->bool_V.next_Atk_Delay = false;

		// 카운트 초기화
		enemy->info_Address()->oper.after_Delay_Cnt = 0;

	}


	// 공격 딜레이가 아닐 경우
	if (!enemy->info_Address()->bool_V.next_Atk_Delay)
	{

		// 상태 체인저
		DATAMANAGER->enemy_Range_Check(enemy);

		// 상태에 따른 함수 호출
		if (enemy->info_Address()->status.state != EnemyStateEnum::IDLE) enemy->call_StateFunc(enemy->info_Address()->status.state, this);
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
	// 에너미의 피격 이미지를 넣어준다.
	enemy->info_Address()->img_Changer();

	// 러프를 시작하려면 true
	enemy->info_Address()->bool_V.lerping = true;

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void IdleState_E::Attack_A(Enemy * enemy)
{
	// 애니메이션만 넣어주고 스타트는 하지 않는다.
	enemy->info_Address()->ani_Changer("Attack_A");
	enemy->info_Address()->img.ani->start();
	enemy->info_Address()->img.ani->stop();

	// 공격 상태로 교체한다.
	enemy->set_State(Attack_A_State_E::getInstance());
	enemy->get_State()->update(enemy);

}

void IdleState_E::Attack_B(Enemy * enemy)
{
	// 애니메이션만 넣어주고 스타트는 하지 않는다.
	enemy->info_Address()->ani_Changer("Attack_B");
	enemy->info_Address()->img.ani->start();
	//enemy->info_Address()->img.ani->stop();

	// 공격B 상태로 교체한다.
	enemy->set_State(Attack_B_State_E::getInstance());
	enemy->get_State()->update(enemy);

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

	// 에너미 움직임 연산
	if (DATAMANAGER->enemy_Find_Ground(enemy))
	{
		if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)  enemy->info_Address()->pos.center.x -= enemy->info_Address()->status.speed;
		if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT) enemy->info_Address()->pos.center.x += enemy->info_Address()->status.speed;
	}

	// 렉트 갱신
	enemy->info_Address()->update_Rect();

	// 상태 체인저
	DATAMANAGER->enemy_Range_Check(enemy);

	// 상태에 따라 함수 호출
	if(enemy->info_Address()->status.state != EnemyStateEnum::WALK) enemy->call_StateFunc(enemy->info_Address()->status.state, this);

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
	// 에너미의 피격 이미지를 넣어준다.
	enemy->info_Address()->img_Changer();

	// 러프를 시작하려면 true
	enemy->info_Address()->bool_V.lerping = true;

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void MoveState_E::Attack_A(Enemy * enemy)
{
	enemy->info_Address()->ani_Changer("Attack_A");

	enemy->info_Address()->img.ani->start();
	enemy->info_Address()->img.ani->stop();

	// 공격 상태로 교체한다.
	enemy->set_State(Attack_A_State_E::getInstance());
	enemy->get_State()->update(enemy);

}

void MoveState_E::Attack_B(Enemy * enemy)
{
	// 애니메이션만 넣어주고 스타트는 하지 않는다.
	enemy->info_Address()->ani_Changer("Attack_B");
	enemy->info_Address()->img.ani->start();
	//enemy->info_Address()->img.ani->stop();

	// 공격B 상태로 교체한다.
	enemy->set_State(Attack_B_State_E::getInstance());
	enemy->get_State()->update(enemy);

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
	// 피격 쿨타임 초기화
	enemy->info_Address()->cool_Time.knockBack_Time = 0;

	// 맞았다는 bool값 초기화
	enemy->info_Address()->bool_V.player_Attack_Hit = false;

	// 추락 애니메이션이 없기 때문에 바로 추락 상태로 변경시켜준다.
	enemy->set_State(FallState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void HitState_E::Hit(Enemy * enemy)
{
	// 플레이어에게 맞았다면
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// 선형 호출
		if(enemy->info_Address()->bool_V.lerping)	DATAMANAGER->Lerp_Enemy(enemy, ENEMYKNOCKBACKING_TIME, ENEMYKNOCKBACK_RANGE);

		// 바닥에 땅이 없을 경우 추락
		if (!DATAMANAGER->enemy_find_Down_Gorund(enemy))
		{
			// 추락상태
			HitState_E::Fall(enemy);
		}
	}

	enemy->info_Address()->cool_Time.knockBack_Time++;

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
	enemy->info_Address()->bool_V.atk_End = false;
	enemy->info_Address()->state_ReSet();

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
	// 에너미의 피격 이미지를 넣어준다.
	enemy->info_Address()->img_Changer();

	// 러프를 시작하려면 true
	enemy->info_Address()->bool_V.lerping = true;

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void Attack_A_State_E::Attack_A(Enemy * enemy)
{
	

	// 에너미 공격 패턴
	enemy->info_Address()->enemy_Attack_Pattern();

	// 에너미의 공격 렉트에 플레이어가 맞았는지 연산
	DATAMANAGER->enemy_Attack_Hit(enemy);
	if (enemy->info_Address()->bool_V.lerping) DATAMANAGER->Lerp_Enemy(enemy, enemy->info_Address()->pos.lerp_Time, enemy->info_Address()->pos.lerp_Range);
	if (enemy->info_Address()->bool_V.atk_End) Attack_A_State_E::Idle(enemy);

	//// 플레이어에게 맞았을 경우
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// 피격 애니메이션을 넣어준다.
		Attack_A_State_E::Hit(enemy);

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
	enemy->info_Address()->reset_Attack_Bool();
	enemy->info_Address()->state_ReSet();

	// 대기 상태로 교체
	enemy->set_State(IdleState_E::getInstance());
	enemy->get_State()->update(enemy);

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
	// 에너미의 피격 이미지를 넣어준다.
	enemy->info_Address()->img_Changer();

	// 러프를 시작하려면 true
	enemy->info_Address()->bool_V.lerping = true;

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void Attack_B_State_E::Attack_A(Enemy * enemy)
{
}

void Attack_B_State_E::Attack_B(Enemy * enemy)
{
	// 에너미 공격 패턴
	enemy->info_Address()->enemy_Attack_Pattern();

	// 화살을 만든다.
	if (enemy->info_Address()->bool_V.make_Arrow)
	{
		if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)
			DATAMANAGER->flyObj_Manager_Address()->Create_FlyingObj("archer_Arrow_Left", "archer_Arrow_Left_Ani",
				FLYINFOBJECT_TYPE::ARROW, FLYINGOBJECT_DIRECTION::LEFT, enemy->info_Address()->pos.center.x - 45, enemy->info_Address()->pos.center.y - 22, 
				3.14f, ARROW_SPEED, enemy->info_Address()->status.attack, true);

		if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT)
			DATAMANAGER->flyObj_Manager_Address()->Create_FlyingObj("archer_Arrow_Right", "archer_Arrow_Right_Ani",
				FLYINFOBJECT_TYPE::ARROW, FLYINGOBJECT_DIRECTION::RIGHT, enemy->info_Address()->pos.center.x + 45, enemy->info_Address()->pos.center.y - 22, 
				0, ARROW_SPEED, enemy->info_Address()->status.attack, true);

		enemy->info_Address()->bool_V.make_Arrow = false;
	}

	// 공격이 끝났다면 다시 대기로
	if (enemy->info_Address()->bool_V.atk_End) Attack_B_State_E::Idle(enemy);

	//// 플레이어에게 맞았을 경우
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// 피격 애니메이션을 넣어준다.
		Attack_B_State_E::Hit(enemy);

	}

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
