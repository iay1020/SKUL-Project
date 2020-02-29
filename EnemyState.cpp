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





// �������������������������������������������������������������������� ��� ����! �������������������������������������������������������������������������������������
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
	// �÷��̾�� �¾��� ���
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// �ǰ� �ִϸ��̼��� �־��ش�.
		IdleState_E::Hit(enemy);

	}

	// �ٴڿ� ���� ���� ��� �߶�
	if (!DATAMANAGER->enemy_find_Down_Gorund(enemy))
	{
		// �߶�����
		IdleState_E::Fall(enemy);
	}

	// ���� ���������̶��
	if (enemy->info_Address()->bool_V.next_Atk_Delay)
	{
		// �ĵ� ī��Ʈ
		enemy->info_Address()->oper.after_Delay_Cnt++;
	}

	// ī��Ʈ�� �����ߴٸ�
	if (enemy->info_Address()->oper.after_Delay <= enemy->info_Address()->oper.after_Delay_Cnt)
	{
		// ���� �����̸� ���ش�.
		enemy->info_Address()->bool_V.next_Atk_Delay = false;

		// ī��Ʈ �ʱ�ȭ
		enemy->info_Address()->oper.after_Delay_Cnt = 0;

	}


	// ���� �����̰� �ƴ� ���
	if (!enemy->info_Address()->bool_V.next_Atk_Delay)
	{

		// ���� ü����
		DATAMANAGER->enemy_Range_Check(enemy);

		// ���¿� ���� �Լ� ȣ��
		if (enemy->info_Address()->status.state != EnemyStateEnum::IDLE) enemy->call_StateFunc(enemy->info_Address()->status.state, this);
	}

}

void IdleState_E::Move(Enemy * enemy)
{
	// ���ʹ��� ���⿡ �´� �ִϸ��̼��� �־��ش�.
	enemy->info_Address()->ani_Changer("Walk");
	enemy->info_Address()->img.ani->start();
	


	// ���ʹ��� ���¸� ���� ���·� ��ü�Ѵ�.
	enemy->set_State(MoveState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void IdleState_E::Jump(Enemy * enemy)
{
}

void IdleState_E::Fall(Enemy * enemy)
{
	// �߶� �ִϸ��̼��� ���� ������ �ٷ� �߶� ���·� ��������ش�.
	enemy->set_State(FallState_E::getInstance());
	enemy->get_State()->update(enemy);
	
}

void IdleState_E::Hit(Enemy * enemy)
{
	// ���ʹ��� �ǰ� �̹����� �־��ش�.
	enemy->info_Address()->img_Changer();

	// ������ �����Ϸ��� true
	enemy->info_Address()->bool_V.lerping = true;

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void IdleState_E::Attack_A(Enemy * enemy)
{
	// �ִϸ��̼Ǹ� �־��ְ� ��ŸƮ�� ���� �ʴ´�.
	enemy->info_Address()->ani_Changer("Attack_A");
	enemy->info_Address()->img.ani->start();
	enemy->info_Address()->img.ani->stop();

	// ���� ���·� ��ü�Ѵ�.
	enemy->set_State(Attack_A_State_E::getInstance());
	enemy->get_State()->update(enemy);

}

void IdleState_E::Attack_B(Enemy * enemy)
{
	// �ִϸ��̼Ǹ� �־��ְ� ��ŸƮ�� ���� �ʴ´�.
	enemy->info_Address()->ani_Changer("Attack_B");
	enemy->info_Address()->img.ani->start();
	//enemy->info_Address()->img.ani->stop();

	// ����B ���·� ��ü�Ѵ�.
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








// �������������������������������������������������������������������� �̵� ����! �������������������������������������������������������������������������������������
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
	// �ٴڿ� ���� ���� ��� �߶�
	if (!DATAMANAGER->enemy_find_Down_Gorund(enemy))
	{
		// �߶�����
		MoveState_E::Fall(enemy);
	}
	
	// �÷��̾�� �¾��� ���
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// �ǰ� �ִϸ��̼��� �־��ش�.
		MoveState_E::Hit(enemy);
	
	}

	// ���ʹ� ������ ����
	if (DATAMANAGER->enemy_Find_Ground(enemy))
	{
		if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)  enemy->info_Address()->pos.center.x -= enemy->info_Address()->status.speed;
		if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT) enemy->info_Address()->pos.center.x += enemy->info_Address()->status.speed;
	}

	// ��Ʈ ����
	enemy->info_Address()->update_Rect();

	// ���� ü����
	DATAMANAGER->enemy_Range_Check(enemy);

	// ���¿� ���� �Լ� ȣ��
	if(enemy->info_Address()->status.state != EnemyStateEnum::WALK) enemy->call_StateFunc(enemy->info_Address()->status.state, this);

}

void MoveState_E::Jump(Enemy * enemy)
{
}

void MoveState_E::Fall(Enemy * enemy)
{
	// �߶� �ִϸ��̼��� ���� ������ �ٷ� �߶� ���·� ��������ش�.
	enemy->set_State(FallState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void MoveState_E::Hit(Enemy * enemy)
{
	// ���ʹ��� �ǰ� �̹����� �־��ش�.
	enemy->info_Address()->img_Changer();

	// ������ �����Ϸ��� true
	enemy->info_Address()->bool_V.lerping = true;

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void MoveState_E::Attack_A(Enemy * enemy)
{
	enemy->info_Address()->ani_Changer("Attack_A");

	enemy->info_Address()->img.ani->start();
	enemy->info_Address()->img.ani->stop();

	// ���� ���·� ��ü�Ѵ�.
	enemy->set_State(Attack_A_State_E::getInstance());
	enemy->get_State()->update(enemy);

}

void MoveState_E::Attack_B(Enemy * enemy)
{
	// �ִϸ��̼Ǹ� �־��ְ� ��ŸƮ�� ���� �ʴ´�.
	enemy->info_Address()->ani_Changer("Attack_B");
	enemy->info_Address()->img.ani->start();
	//enemy->info_Address()->img.ani->stop();

	// ����B ���·� ��ü�Ѵ�.
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







// �������������������������������������������������������������������� ���� ����! �������������������������������������������������������������������������������������
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








// �������������������������������������������������������������������� �߶� ����! �������������������������������������������������������������������������������������
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
	// �߶��� ����ߴ� ���� �ʱ�ȭ
	enemy->info_Address()->pos.fall_Power = 0;

	// �ǰ� ��Ÿ�� �ʱ�ȭ
	enemy->info_Address()->cool_Time.knockBack_Time = 0;

	// �¾Ҵٴ� bool�� �ʱ�ȭ
	enemy->info_Address()->bool_V.player_Attack_Hit = false;

	// ��� �ִϸ��̼��� �ִ´�.
	enemy->info_Address()->ani_Changer("Idle");
	enemy->info_Address()->img.ani->start();

	// ��� ���·� ��ü
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

	// �Ʒ��� ���� �߰��Ҷ����� �߶��Ѵ�.
	// ���� �߰��ϸ� Idle���� ��ü
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






// �������������������������������������������������������������������� �ǰ� ����! �������������������������������������������������������������������������������������
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
	// ��� �ִϸ��̼����� ��ü
	enemy->info_Address()->ani_Changer("Idle");
	enemy->info_Address()->img.ani->start();

	// ��� ���·� ��ü
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
	// �ǰ� ��Ÿ�� �ʱ�ȭ
	enemy->info_Address()->cool_Time.knockBack_Time = 0;

	// �¾Ҵٴ� bool�� �ʱ�ȭ
	enemy->info_Address()->bool_V.player_Attack_Hit = false;

	// �߶� �ִϸ��̼��� ���� ������ �ٷ� �߶� ���·� ��������ش�.
	enemy->set_State(FallState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void HitState_E::Hit(Enemy * enemy)
{
	// �÷��̾�� �¾Ҵٸ�
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// ���� ȣ��
		if(enemy->info_Address()->bool_V.lerping)	DATAMANAGER->Lerp_Enemy(enemy, ENEMYKNOCKBACKING_TIME, ENEMYKNOCKBACK_RANGE);

		// �ٴڿ� ���� ���� ��� �߶�
		if (!DATAMANAGER->enemy_find_Down_Gorund(enemy))
		{
			// �߶�����
			HitState_E::Fall(enemy);
		}
	}

	enemy->info_Address()->cool_Time.knockBack_Time++;

	// ���ʹ��� �ǰ� �ð��� �����ٸ�
	if (enemy->info_Address()->cool_Time.knockBack_Time >= ENEMYKNOCKBACK_TIME)
	{
		// �ǰ� ��Ÿ�� �ʱ�ȭ
		enemy->info_Address()->cool_Time.knockBack_Time = 0;
	
		// �¾Ҵٴ� bool�� �ʱ�ȭ
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






// �������������������������������������������������������������������� ����_A ����! �������������������������������������������������������������������������������������
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

	// ��� �ִϸ��̼����� ��ü
	enemy->info_Address()->ani_Changer("Idle");
	enemy->info_Address()->img.ani->start();

	// ��� ���·� ��ü
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
	// ���ʹ��� �ǰ� �̹����� �־��ش�.
	enemy->info_Address()->img_Changer();

	// ������ �����Ϸ��� true
	enemy->info_Address()->bool_V.lerping = true;

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void Attack_A_State_E::Attack_A(Enemy * enemy)
{
	

	// ���ʹ� ���� ����
	enemy->info_Address()->enemy_Attack_Pattern();

	// ���ʹ��� ���� ��Ʈ�� �÷��̾ �¾Ҵ��� ����
	DATAMANAGER->enemy_Attack_Hit(enemy);
	if (enemy->info_Address()->bool_V.lerping) DATAMANAGER->Lerp_Enemy(enemy, enemy->info_Address()->pos.lerp_Time, enemy->info_Address()->pos.lerp_Range);
	if (enemy->info_Address()->bool_V.atk_End) Attack_A_State_E::Idle(enemy);

	//// �÷��̾�� �¾��� ���
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// �ǰ� �ִϸ��̼��� �־��ش�.
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






// �������������������������������������������������������������������� ����_B ����! �������������������������������������������������������������������������������������
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

	// ��� ���·� ��ü
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
	// ���ʹ��� �ǰ� �̹����� �־��ش�.
	enemy->info_Address()->img_Changer();

	// ������ �����Ϸ��� true
	enemy->info_Address()->bool_V.lerping = true;

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void Attack_B_State_E::Attack_A(Enemy * enemy)
{
}

void Attack_B_State_E::Attack_B(Enemy * enemy)
{
	// ���ʹ� ���� ����
	enemy->info_Address()->enemy_Attack_Pattern();

	// ȭ���� �����.
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

	// ������ �����ٸ� �ٽ� ����
	if (enemy->info_Address()->bool_V.atk_End) Attack_B_State_E::Idle(enemy);

	//// �÷��̾�� �¾��� ���
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// �ǰ� �ִϸ��̼��� �־��ش�.
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






// �������������������������������������������������������������������� ��ų_A ����! �������������������������������������������������������������������������������������
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





// �������������������������������������������������������������������� ��ų_B ����! �������������������������������������������������������������������������������������
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
