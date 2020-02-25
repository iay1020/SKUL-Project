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


	// �ν� ������ �÷��̾ �ִٸ� �÷��̾ �ִ� �������� �ɾ��.
	if (DATAMANAGER->find_Player(enemy))
	{
		// ���� ���� �����ȿ� �־ bool���� true�� �ٲ�� ���� ���·� �����Ѵ�.
		if (enemy->info_Address()->bool_V.attackCheck) Attack_A(enemy);

		// �ȴ� �ִϸ��̼��� �־��ش�.
		if (!enemy->info_Address()->bool_V.attackCheck) Move(enemy);
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
	// ���ʹ��� �ǰ� �ִϸ��̼��� �־��ش�.
	enemy->info_Address()->ani_Changer("Hit");
	enemy->info_Address()->img.ani->start();

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void IdleState_E::Attack_A(Enemy * enemy)
{
	// ���� ���·� ��ü�Ѵ�.
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

	// ���� �÷��̾ ���ʹ̰� �ٶ󺸴� ���⿡�� ������� ��쿡�� ��� ���·� �ٲ��ش�.
	if (DATAMANAGER->escape_Player(enemy))
	{
		Idle(enemy);
	}

	// �÷��̾ �νĹ��� �ۿ� �ִٸ� ��� ���·� �ٲ��ش�.
	if (!DATAMANAGER->find_Player(enemy))
	{
		Idle(enemy);
	}

	// �÷��̾ ���� ������ �ִٸ� ���� ���·� �ٲ��ش�.
	if (DATAMANAGER->find_Player(enemy))
	{
		if(enemy->info_Address()->bool_V.attackCheck)	Attack_A(enemy);
	}

	// ���ʹ� ������ ����
	if (DATAMANAGER->enemy_Find_Ground(enemy))
	{
		if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)  enemy->info_Address()->pos.center.x -= enemy->info_Address()->status.speed;
		if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT) enemy->info_Address()->pos.center.x += enemy->info_Address()->status.speed;
	}

	// ��Ʈ ����
	enemy->info_Address()->update_Rect();

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
	// ���ʹ��� �ǰ� �ִϸ��̼��� �־��ش�.
	enemy->info_Address()->ani_Changer("Hit");
	enemy->info_Address()->img.ani->start();

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);
}

void MoveState_E::Attack_A(Enemy * enemy)
{
	// �ϴ� ��� ���¿��� ���� ���·� ��ȯ
	enemy->info_Address()->ani_Changer("Idle");
	enemy->info_Address()->img.ani->start();

	// ���� ���·� ��ü�Ѵ�.
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
	// �߶� �ִϸ��̼��� ���� ������ �ٷ� �߶� ���·� ��������ش�.
	enemy->set_State(FallState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void HitState_E::Hit(Enemy * enemy)
{
	// �÷��̾�� ������ �ڽ��� �ٶ󺸴� ���� �������� ��¦ �з�����.
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// ���ʹ��� �ǰ� ��Ÿ���� ������.
		enemy->info_Address()->cool_Time.knockBack_Time++;

		if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)
		{
			// �ݴ�������� �̵��Ѵ�.
			if (DATAMANAGER->enemy_Move_Wall(enemy, EnemyDirection::RIGHT))
			{
				enemy->info_Address()->pos.center.x += ENEMYKNOCKBACK_RANGE;
			}
		}

		if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT)
		{
			// �ݴ�������� �̵��Ѵ�.
			if (DATAMANAGER->enemy_Move_Wall(enemy, EnemyDirection::LEFT))
			{
				enemy->info_Address()->pos.center.x -= ENEMYKNOCKBACK_RANGE;
			}
		}

		// ��Ʈ ����
		enemy->info_Address()->update_Rect();
	}

	// �ٴڿ� ���� ���� ��� �߶�
	if (!DATAMANAGER->enemy_find_Down_Gorund(enemy))
	{
		// �߶�����
		HitState_E::Fall(enemy);
	}

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
	// ���ʹ��� �ǰ� �ִϸ��̼��� �־��ش�.
	enemy->info_Address()->ani_Changer("Hit");
	enemy->info_Address()->img.ani->start();

	enemy->set_State(HitState_E::getInstance());
	enemy->get_State()->update(enemy);

}

void Attack_A_State_E::Attack_A(Enemy * enemy)
{
	// �÷��̾�� �¾��� ���
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// �ǰ� �ִϸ��̼��� �־��ش�.
		Attack_A_State_E::Hit(enemy);

	}

	// �÷��̾ �νĹ��� �ۿ� �ִٸ� ��� ���·� �ٲ��ش�.
	if (!DATAMANAGER->find_Attack_Range(enemy))
	{
		enemy->info_Address()->bool_V.attackCheck = false;
		enemy->info_Address()->cool_Time.attack_CoolTime_Cnt = 0;
	
		Idle(enemy);
	}

	// ���� ��Ÿ�ӱ��� ���� �ִϸ��̼��� ������� �ʴ´�.
	if (enemy->info_Address()->bool_V.attackCheck)	enemy->info_Address()->cool_Time.attack_CoolTime_Cnt++;
	
	if (enemy->info_Address()->cool_Time.attack_CoolTime <= enemy->info_Address()->cool_Time.attack_CoolTime_Cnt &&
		enemy->info_Address()->bool_V.attackCheck)
	{
		// �ִϸ��̼��� ����Ѵ�.
		enemy->info_Address()->ani_Changer("Attack_A");
		enemy->info_Address()->img.ani->start();
	
		// �ٽ� ���� �����ϰ� false�� �ٲ۴�.
		enemy->info_Address()->bool_V.attackCheck = false;

		// �ٽ� ���� �����ϰ� false�� �ٲ��ش�. (�÷��̾� ����)
		enemy->info_Address()->bool_V.Attack_Hit = false;
	
		// ��Ÿ�� �ʱ�ȭ
		enemy->info_Address()->cool_Time.attack_CoolTime_Cnt = 0;

		
	}
	
	

	// ���� �������� ��� ������ ��� ���·�
	if (enemy->info_Address()->img.ani->getFramePos().x == 688)
	{
		// ���ʹ� ���� ��Ʈ�� �׷��ش�.
		enemy->info_Address()->make_Attack_Rect();

		// ���ʹ��� ���� ��Ʈ�� �÷��̾ �¾Ҵ��� ����
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
