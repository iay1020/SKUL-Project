#include "stdafx.h"
#include "CharacterState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;
JumpState* JumpState::instance;
FallState* FallState::instance;
DownJumpState* DownJumpState::instance;
DashState* DashState::instance;
JumpAttackState* JumpAttackState::instance;
Attack_A_State* Attack_A_State::instance;
Attack_B_State* Attack_B_State::instance;
Attack_C_State* Attack_C_State::instance;
Skill_A_State* Skill_A_State::instance;
Skill_B_State* Skill_B_State::instance;


// �������������������������������������������������������������������� ��� ����! �������������������������������������������������������������������������������������
IdleState * IdleState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new IdleState();
	}
	
	return instance;
}

void IdleState::Idle(Player * player)
{
	// ���� true�� ���̶�� �ִϸ��̼� ��ü ��ŸƮ
	if (player->get_Info().bool_V.now_Ani_Change)
	{
		player->set_Info()->ani_Changer("Idle", player->get_InputKey());
		player->set_Info()->img.ani->start();

		player->set_Info()->bool_V.now_Ani_Change = false;
	}

	// �÷��̾��� �Ʒ��� �� Ÿ���� ���ٸ� �߶� ���·� �ٲ��ش�.
	if (!DATAMANAGER->Collision_PlayerFall_Ground())
	{
		IdleState::Fall(player);  // �߶��Լ� ȣ��
	}

	// �����ִ� ���¿��� ������ �����ٸ� ���� �̵� ���·� �ٲ��ش�.
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		// inputKey�� �Է��� Ű�� �����Ѵ�.
		player->set_InputKey(PRESS_LEFT);
	
		// ĳ������ ������ �����Ѵ�.
		player->set_Info()->status.direction = DIRECTION_LEFT;
	
		// �̵�Ű�� ��� ������ ������ �� ���� true�� �ٲ��.
		player->set_Info()->bool_V.walking_Cheack = true;

		// ���� ���·� �ٲ۴�. (Idle ���¿��� Move�� ��ü������, Move �Լ��� ȣ���Ѵ�.)
		IdleState::Move(player);
	}
	
	// �����ִ� ���¿��� �������� �����ٸ� ������ �̵� ���·� �ٲ��ش�.
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		// inputKey�� �Է��� Ű�� �����Ѵ�.
		player->set_InputKey(PRESS_RIGHT);
	
		// ĳ������ ������ �����Ѵ�.
		player->set_Info()->status.direction = DIRECTION_RIGHT;
	
		// �̵�Ű�� ��� ������ ������ �� ���� true�� �ٲ��.
		player->set_Info()->bool_V.walking_Cheack = true;

		// ���� ���·� �ٲ۴�. (Idle ���¿��� Move�� ��ü������, Move �Լ��� ȣ���Ѵ�.) 
		IdleState::Move(player);
		
	}

	// �����ִ� ���¿��� �Ʒ� ����Ű�� ������ �����ٸ� �Ʒ� ������ �����Ѵ�.
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{

		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			// �Ʒ� Ÿ���� �����϶���
			if (DATAMANAGER->Collision_Player_FootHold_Down())
			{
				// ��¦ ������ �ϱ� ������ ���� ��ġ�� ���� �־��ش�.
				player->set_Info()->jump.jump_Value = PLAYER_DOWNJUMPPOWER;

				// ����, �߶� �ִϸ��̼����� ��ü�� ���� false�� �ٲ��ش�.
				player->set_Info()->bool_V.jump_Cheack = false;
				player->set_Info()->bool_V.fall_Cheack = false;

				// �Ʒ����� ���·� �̵� �Ѵ�.
				IdleState::DownJump(player);

			}
		}
	}
	


	// �����ִ� ���¿��� ������ �����ٸ� ���� ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		// ������ ��� �ߴٸ� ���� ī��Ʈ ����
		player->set_Info()->jump.Jump_Count--;

		// ���� ��ġ�� �־��ش�.
		player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

		// �������̶�� ture
		player->set_Info()->bool_V.jumping_Cheack = true;

		// ���� ����Ʈ�� ������ش�.
		DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Jump_Effect", "skul_Jump_Ani_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

		// Jump�Լ� ȣ��
		IdleState::Jump(player);
	}


	// �����ִ� ���¿��� ��ų�� �����ٸ� ��ų ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
	{
		// ��ų A�� �ִϸ��̼����� ��ü ���ش�.
		IdleState::Skill_A(player);
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{

	}


	// �����ִ� ���¿��� ����Ű�� �����ٸ� ���� ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// ���� A�� �ִϸ��̼����� ��ü ���ش�.
		IdleState::Attack_A(player);
	}


	// �����ִ� ���¿��� �뽬�� �����ٸ� �뽬 ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		// �뽬 Ƚ���� �ִٸ� �����Ѵ�. ( Ƚ���� �ϳ��� �ִٸ�)
		if (player->get_Info().dash.Dash_Count > 0)
		{
			// �뽬 Ƚ�� ����
			player->set_Info()->dash.Dash_Count--;
	
			// �뽬 ���� �ð� ����
			player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
	
			// �뽬���̶�� true�� �ٲ۴�.
			player->set_Info()->bool_V.dashing_Cheack = true;
	
			// �뽬 �ִϸ��̼� ��ü�� �ؾ� �ϴϱ� false��
			player->set_Info()->bool_V.dash_Cheack = false;

			// �뽬 ����Ʈ�� ����� �ش�.
			if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect","skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
			if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
	
			// �ִϸ��̼� ��ü�� ���� ��ȯ�� ���� Dash �Լ� ȣ��
			IdleState::Dash(player);
		}
	}

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void IdleState::Move(Player * player)
{
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// false��� walk �ִϸ��̼����� �ٲ��ش�.
		if (!player->get_Info().bool_V.walk_Cheack)
		{
			// �ִϸ��̼� ��ü
			player->set_Info()->ani_Changer("Move", player->get_InputKey());

			player->set_Info()->img.ani->start();

			// �ִϸ��̼� ��ü �� true (1���� �ٲٱ� ����)
			player->set_Info()->bool_V.walk_Cheack = true;
		}

		// ���¸� ����� �ٲ��ش�.
		player->set_State(MoveState::getInstance());
		player->get_State()->update(player);
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// false��� walk �ִϸ��̼����� �ٲ��ش�.
		if (!player->get_Info().bool_V.walk_Cheack)
		{

			// �ִϸ��̼� ��ü
			player->set_Info()->ani_Changer("Move", player->get_InputKey());

			player->set_Info()->img.ani->start();


			// �ִϸ��̼� ��ü �� true (1���� �ٲٱ� ����)
			player->set_Info()->bool_V.walk_Cheack = true;
		}

		// ���¸� ����� �ٲ��ش�.
		player->set_State(MoveState::getInstance());                
		player->get_State()->update(player); 
	}
}

void IdleState::Jump(Player * player)
{
	// ������ �ٲ���ٸ� �̹����� ��ü���ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// �ִϸ��̼� ��ü
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());

		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// �ִϸ��̼� ��ü
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());

		player->set_Info()->img.ani->start();
	}

	// ���¸� �ٽ� ���� ���·� ��ü
	player->set_State(JumpState::getInstance());
	player->get_State()->update(player);
}

void IdleState::Fall(Player * player)
{
	// ĳ������ ���⿡ ���� �߶� �ִϸ��̼��� �־��ְ� �߶� ���·� ��ü���ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{

		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{

		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	// �߶����� ��ü
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void IdleState::DownJump(Player * player)
{
	// ���� �ִϸ��̼����� ��ü �Ѵ�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
	
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());
		player->set_Info()->img.ani->start();

	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
	
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());
		player->set_Info()->img.ani->start();

	}
	
	// �Ʒ� ���� ���·� �̵��Ѵ�.
	player->set_State(DownJumpState::getInstance());
	player->get_State()->update(player);
}

void IdleState::Dash(Player * player)
{
	// ���⿡ �´� �뽬 �ִϸ��̼����� ��ü���ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		if (!player->get_Info().bool_V.dash_Cheack)
		{
		
			player->set_Info()->ani_Changer("Dash", player->get_InputKey());
			player->set_Info()->img.ani->start();

			player->set_Info()->bool_V.dash_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		if (!player->get_Info().bool_V.dash_Cheack)
		{
		
			player->set_Info()->ani_Changer("Dash", player->get_InputKey());
			player->set_Info()->img.ani->start();

			player->set_Info()->bool_V.dash_Cheack = true;
		}
	}

	// �ִϸ��̼� ��ü�� �����ٸ� Dash ���·� �ٲ��ش�.
	player->set_State(DashState::getInstance());
	player->get_State()->update(player);
}

void IdleState::JumpAttack(Player * player)
{
}

void IdleState::Attack_A(Player * player)
{
	// ���� A �ִϸ��̼����� ��ü
	player->set_Info()->ani_Changer("Attack_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// ���� A ���·� ��ü���ش�.
	player->set_State(Attack_A_State::getInstance());
	player->get_State()->update(player);
}

void IdleState::Attack_B(Player * player)
{
}

void IdleState::Attack_C(Player * player)
{
}

void IdleState::Skill_A(Player * player)
{

	// ��ų A�� �ִϸ��̼����� ��ü
	player->set_Info()->ani_Changer("Skill_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// ��ų A ���·� ��ü 
	player->set_State(Skill_A_State::getInstance());
	player->get_State()->update(player);

}

void IdleState::Skill_B(Player * player)
{
}

void IdleState::update(Player * player)
{
	IdleState::Idle(player);

	//KEYANIMANAGER->update();
}





// �������������������������������������������������������������������� �̵� ����! �������������������������������������������������������������������������������������
MoveState * MoveState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new MoveState;
	}

	return instance;
}

void MoveState::Idle(Player * player)
{
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// false��� idle �ִϸ��̼����� �ٲ��ش�.
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			// �ִϸ��̼� ��ü
			player->set_Info()->ani_Changer("Idle", player->get_InputKey());
			player->set_Info()->img.ani->start();

			// �ִϸ��̼� ��ü �� true (1���� �ٲٱ� ����)
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// false��� idle �ִϸ��̼����� �ٲ��ش�.
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			// �ִϸ��̼� ��ü
			player->set_Info()->ani_Changer("Idle", player->get_InputKey());
			player->set_Info()->img.ani->start();

			// �ִϸ��̼� ��ü �� true (1���� �ٲٱ� ����)
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	// ���¸� ���� �ٲ��ش�.
	player->set_State(IdleState::getInstance());
	player->get_State()->update(player);
}

void MoveState::Move(Player * player)
{
	// ���� true�� ���̶�� �ִϸ��̼� ��ü ��ŸƮ
	if (player->get_Info().bool_V.now_Ani_Change)
	{
		player->set_Info()->ani_Changer("Move", player->get_InputKey());
		player->set_Info()->img.ani->start();

		player->set_Info()->bool_V.now_Ani_Change = false;
	}

	// �÷��̾��� �Ʒ��� �� Ÿ���� ���ٸ� �߶� ���·� �ٲ��ش�.
	if (!DATAMANAGER->Collision_PlayerFall_Ground())
	{
		MoveState::Fall(player);  // �߶��Լ� ȣ��
	}

	if (player->get_InputKey() == PRESS_LEFT)
	{
		// ĳ���� ���� ���� ����� ����
		if (!DATAMANAGER->Collision_Player_Wall())
		{
			// �÷��̾ �������� �̵� (�̵����̶��)
			if (player->get_Info().bool_V.walking_Cheack)  player->set_Info()->pos.center.x -= PLAYER_SPEED;
		}

		// �÷��̾ ���� Ű�� �Է� �Ѵٸ� ���� �Լ��� ȣ���Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			// ���� Ƚ���� �����ִٸ�
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// ���� Ƚ���� ���� �Ѵ�.
				player->set_Info()->jump.Jump_Count--;


				// ����Ű�� �����ٸ� true�� �ٲ��ش�.
				player->set_Info()->bool_V.jumping_Cheack = true;

				// ���� ����Ʈ�� ������ش�.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Jump_Effect", "skul_Jump_Ani_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);


				// ���� �ִϸ��̼� ��ü�� ���� Jump�Լ� ȣ��
				MoveState::Jump(player);
			}
		}

		// ����Ű�� ���ٸ� ��� ���·� ���ư����Ѵ�.
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			// �̵��� ���� �Ʊ� ������ false�� �ٲ��ش�.
			player->set_Info()->bool_V.walking_Cheack = false;
			player->set_Info()->bool_V.walk_Cheack = false;
			player->set_Info()->bool_V.idle_Cheack = false;

			// ��� �̹����� �ٲٱ� ���� Idle�Լ� ȣ��
			MoveState::Idle(player);
		}

		// �̵� ���¿��� �뽬�� �����ٸ� �뽬 ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			// �뽬 Ƚ���� �ִٸ� �����Ѵ�. ( Ƚ���� �ϳ��� �ִٸ�)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// �뽬 Ƚ�� ����
				player->set_Info()->dash.Dash_Count--;
		
				// �뽬 ���� �ð� ����
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// �뽬���̶�� true�� �ٲ۴�.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// �뽬 �ִϸ��̼� ��ü�� �ؾ� �ϴϱ� false��
				player->set_Info()->bool_V.dash_Cheack = false;

				// �뽬 ����Ʈ�� ����� �ش�.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// �ִϸ��̼� ��ü�� ���� ��ȯ�� ���� Dash �Լ� ȣ��
				MoveState::Dash(player);
			}
		}

		// �̵� ���¿��� ������ �����ٸ� ���� ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			MoveState::Attack_A(player);
		}

		// �̵� ���¿��� ��ų AŰ�� �����ٸ�, ��ų �ִϸ��̼����� ��ü�Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			MoveState::Skill_A(player);
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// ĳ���� ���� ���� ����� ����
		if (!DATAMANAGER->Collision_Player_Wall())
		{
			// �÷��̾ ���������� �̵� (�̵����̶��)
			if (player->get_Info().bool_V.walking_Cheack) player->set_Info()->pos.center.x += PLAYER_SPEED;
		}

		// �÷��̾ ���� Ű�� �Է� �Ѵٸ� ���� �Լ��� ȣ���Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			// ���� Ƚ���� �����ִٸ�
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// ���� Ƚ���� ���� �Ѵ�.
				player->set_Info()->jump.Jump_Count--;

				// ����Ű�� �����ٸ� true�� �ٲ��ش�.
				player->set_Info()->bool_V.jumping_Cheack = true;

				// ���� ����Ʈ�� ������ش�.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Jump_Effect", "skul_Jump_Ani_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

				// ���� �ִϸ��̼� ��ü�� ���� Jump�Լ� ȣ��
				MoveState::Jump(player);
			}
		}

		// ������Ű�� ���ٸ� ��� ���·� ���ư����Ѵ�.
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			// �̵��� ���� �Ʊ� ������ false�� �ٲ��ش�.
			player->set_Info()->bool_V.walking_Cheack = false;
			player->set_Info()->bool_V.walk_Cheack = false;
			player->set_Info()->bool_V.idle_Cheack = false;

			// ��� �̹����� �ٲٱ� ���� Idle�Լ� ȣ��
			MoveState::Idle(player);
		}

		// �̵� ���¿��� �뽬�� �����ٸ� �뽬 ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			
			// �뽬 Ƚ���� �ִٸ� �����Ѵ�. ( Ƚ���� �ϳ��� �ִٸ�)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// �뽬 Ƚ�� ����
				player->set_Info()->dash.Dash_Count--;
		
				// �뽬 ���� �ð� ����
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// �뽬���̶�� true�� �ٲ۴�.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// �뽬 �ִϸ��̼� ��ü�� �ؾ� �ϴϱ� false��
				player->set_Info()->bool_V.dash_Cheack = false;

				// �뽬 ����Ʈ�� ����� �ش�.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// �ִϸ��̼� ��ü�� ���� ��ȯ�� ���� Dash �Լ� ȣ��
				MoveState::Dash(player);
			}
		}

		// �̵� ���¿��� ������ �����ٸ� ���� ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			MoveState::Attack_A(player);
		}

		// �̵� ���¿��� ��ų AŰ�� �����ٸ�, ��ų �ִϸ��̼����� ��ü�Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			MoveState::Skill_A(player);
		}
	}

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void MoveState::Jump(Player * player)
{
	if (player->get_InputKey() == PRESS_LEFT)
	{
		if (!player->get_Info().bool_V.jump_Cheack)
		{
			// ���� �ִϸ��̼��� �־��ش�.
			//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
			player->set_Info()->ani_Changer("Jump", player->get_InputKey());
			player->set_Info()->img.ani->start();

			// ���� ������ ���� �־��ش�.
			player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

			// ���������� �ٲ۴�.
			player->set_Info()->bool_V.jumping_Cheack = true;

			// ���� �ִϸ��̼� ��ü ������ true
			player->set_Info()->bool_V.jump_Cheack = true;
		}

		// ���� ����Ű���� ���� ���ٸ�
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			// �� �̻� �̵��� ���� �ʴ´ٴ� ��
			player->set_Info()->bool_V.walking_Cheack = false;
		}

		// �ٸ� ����Ű�� �����ٸ�
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			// �Է�ġ�� �������ش�.
			player->set_InputKey(PRESS_RIGHT);

			// �ٽ� �̹����� �ޱ� ���� false�� �ٲ��ش�.
			player->set_Info()->bool_V.jump_Cheack = false;

			// �Լ��� ����� �Ѵ�.
			MoveState::Jump(player);
		}

		// ���� ���·� �ٲ��ش�.
		player->set_State(JumpState::getInstance());
		player->get_State()->update(player);
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		if (!player->get_Info().bool_V.jump_Cheack)
		{
			// ���� �ִϸ��̼��� �־��ش�.
			//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
			player->set_Info()->ani_Changer("Jump", player->get_InputKey());
			player->set_Info()->img.ani->start();

			// ���� ������ ���� �־��ش�.
			player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

			// ���������� �ٲ۴�.
			player->set_Info()->bool_V.jump_Cheack = true;
		}

		// ���� ����Ű���� ���� ���ٸ�
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			// �� �̻� �̵��� ���� �ʴ´ٴ� ��
			player->set_Info()->bool_V.walking_Cheack = false;
		}

		// �ٸ� ����Ű�� �����ٸ�
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			// �Է�ġ�� �������ش�.
			player->set_InputKey(PRESS_LEFT);

			// �ٽ� �̹����� �ޱ� ���� false�� �ٲ��ش�.
			player->set_Info()->bool_V.jump_Cheack = false;

			// �Լ��� ����� �Ѵ�.
			MoveState::Jump(player);
		}

		// ���� ���·� �ٲ��ش�.
		player->set_State(JumpState::getInstance());
		player->get_State()->update(player);
	}
}

void MoveState::Fall(Player * player)
{
	// ĳ������ ���⿡ ���� �߶� �ִϸ��̼��� �־��ְ� �߶� ���·� ��ü���ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		//player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		//player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	// �߶����� ��ü
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void MoveState::DownJump(Player * player)
{
}

void MoveState::Dash(Player * player)
{
	// ���⿡ �´� �뽬 �ִϸ��̼����� ��ü���ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		if (!player->get_Info().bool_V.dash_Cheack)
		{
			//player->set_Info()->set_Ani("skul_Dash", "skul_Dash_Left");
			player->set_Info()->ani_Changer("Dash", player->get_InputKey());
			player->set_Info()->img.ani->start();

			player->set_Info()->bool_V.dash_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		if (!player->get_Info().bool_V.dash_Cheack)
		{
			//player->set_Info()->set_Ani("skul_Dash", "skul_Dash_Right");
			player->set_Info()->ani_Changer("Dash", player->get_InputKey());
			player->set_Info()->img.ani->start();

			player->set_Info()->bool_V.dash_Cheack = true;
		}
	}

	// �ִϸ��̼� ��ü�� �����ٸ� Dash ���·� �ٲ��ش�.
	player->set_State(DashState::getInstance());
	player->get_State()->update(player);

}

void MoveState::JumpAttack(Player * player)
{
}

void MoveState::Attack_A(Player * player)
{
	// ���� A �ִϸ��̼����� ��ü 
	player->set_Info()->ani_Changer("Attack_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// ���� A ���·� �ٲ��ش�.
	player->set_State(Attack_A_State::getInstance());
	player->get_State()->update(player);
}

void MoveState::Attack_B(Player * player)
{
}

void MoveState::Attack_C(Player * player)
{
}

void MoveState::Skill_A(Player * player)
{

	// ��ų A�� �ִϸ��̼����� ��ü
	player->set_Info()->ani_Changer("Skill_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// ��ų A ���·� ��ü 
	player->set_State(Skill_A_State::getInstance());
	player->get_State()->update(player);

}

void MoveState::Skill_B(Player * player)
{
}

void MoveState::update(Player * player)
{	
	MoveState::Move(player);

	//KEYANIMANAGER->update();
}




// �������������������������������������������������������������������� ���� ����! �������������������������������������������������������������������������������������
JumpState * JumpState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new JumpState();
	}

	return instance;
}

void JumpState::Idle(Player * player)
{
}

void JumpState::Move(Player * player)
{
	// �̵����� ��� ����
	if (player->get_Info().bool_V.walking_Cheack)
	{
		// ĳ���� ���� ���� ����� ����
		if (!DATAMANAGER->Collision_Player_Wall())
		{
			// �ش� �������� �̵��Ѵ�.
			if (player->get_InputKey() == PRESS_LEFT)
			{
				player->set_Info()->pos.center.x -= PLAYER_SPEED;
			}

			if (player->get_InputKey() == PRESS_RIGHT)
			{
				player->set_Info()->pos.center.x += PLAYER_SPEED;
			}
		}

		// ���� ������ ���ش�.
		// ���� ������ �����Ѵ�. ���� ��ġ�� 0 �̻��϶���
		if (player->get_Info().jump.jump_Value > 0)
		{
			// ���� ��ġ��ŭ ĳ������ y��ǥ�� ����.
			if (!DATAMANAGER->Collision_PlayerJump_Ground())
			player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

			// ���� ��ġ�� �߷¸�ŭ ����. (�ִ� �߶� �ӵ����� Ŭ����)
			if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED)
			{
				player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;
			}
		}

		// ���� ��ġ�� 0 ���϶�� �߶� ���·� �ٲ���Ѵ�.
		else
		{
			// ������ ���� ���̴�.
			player->set_Info()->bool_V.jumping_Cheack = false;
		
			// �߶� ����
			player->set_Info()->bool_V.falling_Cheack = true;
		
			// Fall�Լ� ȣ��
			JumpState::Fall(player);
		}

		// ���� Ű�� ���ٸ�
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			// �� �̻� �̵��� ���ϵ��� false ���� �־��ش�.
			player->set_Info()->bool_V.walking_Cheack = false;

			// ���� �Է¶� �ִϸ��̼� ��ü�� ���� flase�� �ٲ��ش�.
			player->set_Info()->bool_V.jump_Cheack = false;

			// �̵��� �����ٸ� �ٸ� ������ �ϱ� ���� Jump�� ���ư���.
			JumpState::Jump(player);
		}

		// ����Ű�� �ٽ� �����ٸ� (���� Ƚ���� �����ִٸ�)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// ���� ����Ʈ�� ������ش�.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Double_Jump_Effect", "skul_Double_Jump_Ani_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

				// ���� ī��Ʈ�� ���� �����ְ�, ���� ��ġ ȸ��
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;
			}
		}

		// ���� ���¿��� �뽬�� �����ٸ� �뽬 ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			
			// �뽬 Ƚ���� �ִٸ� �����Ѵ�. ( Ƚ���� �ϳ��� �ִٸ�)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// �뽬 Ƚ�� ����
				player->set_Info()->dash.Dash_Count--;
		
				// �뽬 ���� �ð� ����
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// �뽬���̶�� true�� �ٲ۴�.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// �뽬 �ִϸ��̼� ��ü�� �ؾ� �ϴϱ� false��
				player->set_Info()->bool_V.dash_Cheack = false;

				// �뽬 ����Ʈ�� ����� �ش�.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// �ִϸ��̼� ��ü�� ���� ��ȯ�� ���� Dash �Լ� ȣ��
				JumpState::Dash(player);
			}
		}

		// ���� ���¿��� ������ �����ٸ� ���� ���� ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			// �ִϸ��̼� ��ü�� ���� JumpAttack �Լ� ȣ��
			JumpState::JumpAttack(player);
		}

		// �̵� ���¿��� ��ų AŰ�� �����ٸ�, ��ų �ִϸ��̼����� ��ü�Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			JumpState::Skill_A(player);
		}
	}
}

void JumpState::Jump(Player * player)
{
	// ���� true�� ���̶�� �ִϸ��̼� ��ü ��ŸƮ
	if (player->get_Info().bool_V.now_Ani_Change)
	{
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());
		player->set_Info()->img.ani->start();

		player->set_Info()->bool_V.now_Ani_Change = false;
	}

	// ���� ��� �̵����̶�� true��
	if (player->get_Info().bool_V.walking_Cheack) Move(player);

	// �÷��̾ �̵������� ������
	if (!player->get_Info().bool_V.walking_Cheack)
	{
		// ���� ����Ű�� ������ �ִϸ��̼� ��ü �� Jump�Լ� ȣ�� �� Move�� �����ش�.
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			// �Է�Ű ����
			player->set_InputKey(PRESS_LEFT);

			// ���⿡ �´� �ִϸ��̼����� ��ü
			//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
			player->set_Info()->ani_Changer("Jump", player->get_InputKey());

			// �̵����̶�� true
			player->set_Info()->bool_V.walking_Cheack = true;

			// �̵� + ���� ������ ���� Move ȣ��
			JumpState::Move(player);
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// �Է�Ű ����
			player->set_InputKey(PRESS_RIGHT);

			// ���⿡ �´� �ִϸ��̼����� ��ü
			//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
			player->set_Info()->ani_Changer("Jump", player->get_InputKey());

			// �̵����̶�� true
			player->set_Info()->bool_V.walking_Cheack = true;

			// �̵� + ���� ������ ���� Move ȣ��
			JumpState::Move(player);
		}

		// ����Ű�� �ٽ� �����ٸ� (���� Ƚ���� �����ִٸ�)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// ���� ����Ʈ�� ������ش�.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Double_Jump_Effect", "skul_Double_Jump_Ani_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

				// ���� ī��Ʈ�� ���� �����ְ�, ���� ��ġ ȸ��
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;
			}
		}

		// ���� ���¿��� �뽬�� �����ٸ� �뽬 ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			
			// �뽬 Ƚ���� �ִٸ� �����Ѵ�. ( Ƚ���� �ϳ��� �ִٸ�)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// �뽬 Ƚ�� ����
				player->set_Info()->dash.Dash_Count--;
		
				// �뽬 ���� �ð� ����
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// �뽬���̶�� true�� �ٲ۴�.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// �뽬 �ִϸ��̼� ��ü�� �ؾ� �ϴϱ� false��
				player->set_Info()->bool_V.dash_Cheack = false;

				// �뽬 ����Ʈ�� ����� �ش�.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// �ִϸ��̼� ��ü�� ���� ��ȯ�� ���� Dash �Լ� ȣ��
				JumpState::Dash(player);
			}
		}

		// ���� ���¿��� ������ �����ٸ� ���� ���� ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			// �ִϸ��̼� ��ü�� ���� JumpAttack �Լ� ȣ��
			JumpState::JumpAttack(player);
		}

		// �̵� ���¿��� ��ų AŰ�� �����ٸ�, ��ų �ִϸ��̼����� ��ü�Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			JumpState::Skill_A(player);
		}

		// ���� ������ �����Ѵ�. ���� ��ġ�� 0 �̻��϶���
		if (player->get_Info().jump.jump_Value > 0)
		{
			// ���� ��ġ��ŭ ĳ������ y��ǥ�� ����.
			if (!DATAMANAGER->Collision_PlayerJump_Ground())
			player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

			// ���� ��ġ�� �߷¸�ŭ ����. (�ִ� �߶� �ӵ����� Ŭ����)
			if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED)
			{
				player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;
			}
		}

		// ���� ��ġ�� 0 ���϶�� �߶� ���·� �ٲ���Ѵ�.
		else
		{
			// ������ ���� ���̴�.
			player->set_Info()->bool_V.jumping_Cheack = false;
		
			// �߶� ����
			player->set_Info()->bool_V.falling_Cheack = true;
		
			// Fall�Լ� ȣ��
			JumpState::Fall(player);
		}
	}

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void JumpState::Fall(Player * player)
{
	// ���⿡ �´� �߶� �̹����� �־��ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		//player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		//player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	// �߶� ���·� �̵��Ѵ�.
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void JumpState::DownJump(Player * player)
{
}

void JumpState::Dash(Player * player)
{
	// ���⿡ �´� �뽬 �ִϸ��̼����� ��ü���ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		if (!player->get_Info().bool_V.dash_Cheack)
		{
			//player->set_Info()->set_Ani("skul_Dash", "skul_Dash_Left");
			player->set_Info()->ani_Changer("Dash", player->get_InputKey());
			player->set_Info()->img.ani->start();

			player->set_Info()->bool_V.dash_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		if (!player->get_Info().bool_V.dash_Cheack)
		{
			//player->set_Info()->set_Ani("skul_Dash", "skul_Dash_Right");
			player->set_Info()->ani_Changer("Dash", player->get_InputKey());
			player->set_Info()->img.ani->start();

			player->set_Info()->bool_V.dash_Cheack = true;
		}
	}

	// �ִϸ��̼� ��ü�� �����ٸ� Dash ���·� �ٲ��ش�.
	player->set_State(DashState::getInstance());
	player->get_State()->update(player);
}

void JumpState::JumpAttack(Player * player)
{
	// �������� �ִϸ��̼����� ��ü���ش�.
	player->set_Info()->ani_Changer("JumpAttack", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// �������� ���·� �ٲ��ش�.
	player->set_State(JumpAttackState::getInstance());
	player->get_State()->update(player);
}

void JumpState::Attack_A(Player * player)
{
}

void JumpState::Attack_B(Player * player)
{
}

void JumpState::Attack_C(Player * player)
{
}

void JumpState::Skill_A(Player * player)
{

	// ��ų A�� �ִϸ��̼����� ��ü
	player->set_Info()->ani_Changer("Skill_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// ��ų A ���·� ��ü 
	player->set_State(Skill_A_State::getInstance());
	player->get_State()->update(player);

}

void JumpState::Skill_B(Player * player)
{
}

void JumpState::update(Player * player)
{
	JumpState::Jump(player);

	//KEYANIMANAGER->update();
}





// �������������������������������������������������������������������� �߶� ����! �������������������������������������������������������������������������������������
FallState * FallState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new FallState();
	}

	return instance;
}

void FallState::Idle(Player * player)
{

	// ���⿡ ���� �ٸ� ��� �ִϸ��̼��� �־��ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			// ��� �ִϸ��̼����� ��ü
			//player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
			player->set_Info()->ani_Changer("Idle", player->get_InputKey());
			player->set_Info()->img.ani->start();

			// ��ü�� �ߴٸ� true
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			// ��� �ִϸ��̼����� ��ü
			//player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
			player->set_Info()->ani_Changer("Idle", player->get_InputKey());
			player->set_Info()->img.ani->start();

			// ��ü�� �ߴٸ� true
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	// ��� ���·� �ٲ��ش�.
	player->set_State(IdleState::getInstance());
	player->get_State()->update(player);
}

void FallState::Move(Player * player)
{
	// ĳ���� ���� ���� ����� ����
	if (!DATAMANAGER->Collision_Player_Wall())
	{
		// �̵����̶�� �ε� ������ �Ѵ�.
		if (player->get_InputKey() == PRESS_LEFT)
		{
			player->set_Info()->pos.center.x -= PLAYER_SPEED;
		}

		if (player->get_InputKey() == PRESS_RIGHT)
		{
			player->set_Info()->pos.center.x += PLAYER_SPEED;
		}
	}

	// ���� ���� ������� �߶� ���¿��� ����������.

	if (DATAMANAGER->Collision_PlayerFall_Ground())
	{
		//// ī�޶� ��ġ ����
		CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);
		
		// ��Ʈ ����
		player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		player->update_Ani_Rect();
		
		// ������ ���� �� ������ ���� ��� �ʱ�ȭ
		//player->set_Info()->bool_Value_Reset();
		player->set_Info()->bool_State_Reset();

		player->set_Info()->jump.jump_Value = 0;
		
		// ���� ��ġ �ʱ�ȭ
		player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;
		
		// Idle �ִϸ��̼� ��ü�� ���� ȣ��
		FallState::Idle(player);
	}

	// �߶�����
	player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

	// ���� ��ġ�� �߷¸�ŭ ����. (�ִ� �߶� �ӵ����� Ŭ����)
	if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED)
	{
		player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;
	}

	// ���� ����Ű�� ���ٸ� �� �̻� �̵����� �ʴ´�.
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		// �̵����� �ƴ϶�� false
		player->set_Info()->bool_V.walking_Cheack = false;

		// �ٸ� ������ �Է� �� �߶� �ִϸ��̼� ��ü�� ���� false��
		player->set_Info()->bool_V.fall_Cheack = false;

		// �̵��� �������� �ٸ� ������ ���� Fall �Լ� ȣ��
		FallState::Fall(player);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		// �̵����� �ƴ϶�� false
		player->set_Info()->bool_V.walking_Cheack = false;

		// �ٸ� ������ �Է� �� �߶� �ִϸ��̼� ��ü�� ���� false��
		player->set_Info()->bool_V.fall_Cheack = false;

		// �̵��� �������� �ٸ� ������ ���� Fall �Լ� ȣ��
		FallState::Fall(player);
	}

	// ����Ű�� �ٽ� �����ٸ� (���� Ƚ���� �����ִٸ�)
	if (KEYMANAGER->isOnceKeyDown('C'))
	{

		if (player->get_Info().jump.Jump_Count > 0)
		{
			// ���� ����Ʈ�� ������ش�.
			DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Double_Jump_Effect", "skul_Double_Jump_Ani_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

			// ���� ī��Ʈ�� ���� �����ְ�, ���� ��ġ ȸ��
			player->set_Info()->jump.Jump_Count--;
			player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

			// ���� �ִϸ��̼� ��ü�� ���� ȣ��
			FallState::Jump(player);
		}
	}

	// �߶� ���¿��� �뽬�� �����ٸ� �뽬 ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
	
		// �뽬 Ƚ���� �ִٸ� �����Ѵ�. ( Ƚ���� �ϳ��� �ִٸ�)
		if (player->get_Info().dash.Dash_Count > 0)
		{
			// �߶� ���¿��� �뽬�� ����ϸ� �߶� ��ġ�� �����Ѵ�.
			player->set_Info()->jump.jump_Value = 0;
	
			// �뽬 Ƚ�� ����
			player->set_Info()->dash.Dash_Count--;
	
			// �뽬 ���� �ð� ����
			player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
	
			// �뽬���̶�� true�� �ٲ۴�.
			player->set_Info()->bool_V.dashing_Cheack = true;
	
			// �뽬 �ִϸ��̼� ��ü�� �ؾ� �ϴϱ� false��
			player->set_Info()->bool_V.dash_Cheack = false;

			// �뽬 ����Ʈ�� ����� �ش�.
			if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
			if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
	
			// �ִϸ��̼� ��ü�� ���� ��ȯ�� ���� Dash �Լ� ȣ��
			FallState::Dash(player);
		}
	}

	// �߶� ���¿��� ����Ű�� ������ ���� ���� ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// ���� ���� �ִϸ��̼����� �ٲٱ� ���� �Լ� ȣ��
		FallState::JumpAttack(player);
	}

	// �̵� ���¿��� ��ų AŰ�� �����ٸ�, ��ų �ִϸ��̼����� ��ü�Ѵ�.
	if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
	{
		FallState::Skill_A(player);
	}

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void FallState::Jump(Player * player)
{
	// ���⿡ ���� �´� ���� �ִϸ��̼����� �ٲ��ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// �ִϸ��̼� ��ü + ����
		//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());

		player->set_Info()->img.ani->start();

		// ���� �ִϸ��̼��� �ٲ�ٸ� true (�ߺ� ��ü ����)
		player->set_Info()->bool_V.jump_Cheack = true;

		// ���������� �ٲ��ش�.
		player->set_Info()->bool_V.jumping_Cheack = true;

		// �߶����� �ƴϹǷ� flase
		player->set_Info()->bool_V.falling_Cheack = false;

		// ���� ���·� �ٲ��ش�.
		player->set_State(JumpState::getInstance());
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// �ִϸ��̼� ��ü + ����
		//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());

		player->set_Info()->img.ani->start();

		// ���� �ִϸ��̼��� �ٲ�ٸ� true (�ߺ� ��ü ����)
		player->set_Info()->bool_V.jump_Cheack = true;

		// ���������� �ٲ��ش�.
		player->set_Info()->bool_V.jumping_Cheack = true;

		// �߶����� �ƴϹǷ� flase
		player->set_Info()->bool_V.falling_Cheack = false;

		// ���� ���·� �ٲ��ش�.
		player->set_State(JumpState::getInstance());
	}
}

void FallState::Fall(Player * player)
{
	// ���� true�� ���̶�� �ִϸ��̼� ��ü ��ŸƮ
	if (player->get_Info().bool_V.now_Ani_Change)
	{
		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();

		player->set_Info()->bool_V.now_Ani_Change = false;
	}

	// �߶� ���� �ִϸ��̼����� ��ü�ϴ� ���� (���� �߶� �ִϸ��̼� �߿���)
	if (player->get_Info().img.imgName == "skul_Fall" ||
		player->get_Info().img.imgName == "skul_Fall_NoHead")
	{

		// �������� 2�� ���ϴ� ���� (�����Ӱ����� ũ�Ⱑ 160�̹Ƿ�, 0 = 0, 160 = 1, 320 = 2�� ������ ��ġ�� ����Ų��.)
		if (player->get_Info().img.ani->getFramePos().x >= 320)
		{
			// ���䰡 ��� �޷��ŷ��� �ϱ� ������ ���� �ִϸ��̼����� ��ü�Ѵ�.
			if (player->get_InputKey() == PRESS_LEFT)
			{
				//player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
				player->set_Info()->ani_Changer("Falling", player->get_InputKey());
				player->set_Info()->img.ani->start();
			}

			if (player->get_InputKey() == PRESS_RIGHT)
			{
				//player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
				player->set_Info()->ani_Changer("Falling", player->get_InputKey());
				player->set_Info()->img.ani->start();
			}
		}
	}

	// �̵����̶�� �̵� ������ �Ѵ�.
	if (player->get_Info().bool_V.walking_Cheack) Move(player);

	// �̵����� �ƴ϶��
	if (!player->get_Info().bool_V.walking_Cheack)
	{
		// ����Ű�� �����ٸ�
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			// �ش� ����Ű ����
			player->set_InputKey(PRESS_LEFT);

			// �ش� �������� �ִϸ��̼� ��ü
			//player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
			player->set_Info()->ani_Changer("Falling", player->get_InputKey());
			player->set_Info()->img.ani->start();
			
			// ĳ���� ���� ���� ����� ����
			if (!DATAMANAGER->Collision_Player_Wall())
			{
				// �̵����̶�� true
				player->set_Info()->bool_V.walking_Cheack = true;

				// �̵� + �߶� ������ ���� Jall�Լ� �ٽ� ȣ��
				FallState::Fall(player);
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// �ش� ����Ű ����
			player->set_InputKey(PRESS_RIGHT);

			// �ش� �������� �ִϸ��̼� ��ü
			//player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
			player->set_Info()->ani_Changer("Falling", player->get_InputKey());
			player->set_Info()->img.ani->start();

			// ĳ���� ���� ���� ����� ����
			if (!DATAMANAGER->Collision_Player_Wall())
			{
				// �̵����̶�� true
				player->set_Info()->bool_V.walking_Cheack = true;

				// �̵� + �߶� ������ ���� Jall�Լ� �ٽ� ȣ��
				FallState::Fall(player);
			}
		}

		// ����Ű�� �ٽ� �����ٸ� (���� Ƚ���� �����ִٸ�)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{

			if (player->get_Info().jump.Jump_Count > 0)
			{
				// ���� ����Ʈ�� ������ش�.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Double_Jump_Effect", "skul_Double_Jump_Ani_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

				// ���� ī��Ʈ�� ���� �����ְ�, ���� ��ġ ȸ��
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

				// ���� �ִϸ��̼� ��ü�� ���� ȣ��
				FallState::Jump(player);
			}
		}

		// �߶� ���¿��� �뽬�� �����ٸ� �뽬 ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
		
			// �뽬 Ƚ���� �ִٸ� �����Ѵ�. ( Ƚ���� �ϳ��� �ִٸ�)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// �߶� ���¿��� �뽬�� ����ϸ� �߶� ��ġ�� �����Ѵ�.
				player->set_Info()->jump.jump_Value = 0;
		
				// �뽬 Ƚ�� ����
				player->set_Info()->dash.Dash_Count--;
		
				// �뽬 ���� �ð� ����
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// �뽬���̶�� true�� �ٲ۴�.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// �뽬 �ִϸ��̼� ��ü�� �ؾ� �ϴϱ� false��
				player->set_Info()->bool_V.dash_Cheack = false;

				// �뽬 ����Ʈ�� ����� �ش�.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// �ִϸ��̼� ��ü�� ���� ��ȯ�� ���� Dash �Լ� ȣ��
				FallState::Dash(player);
			}
		}

		// �߶� ���¿��� ����Ű�� ������ ���� ���� ���·� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			// ���� ���� �ִϸ��̼����� �ٲٱ� ���� �Լ� ȣ��
			FallState::JumpAttack(player);
		}

		// �̵� ���¿��� ��ų AŰ�� �����ٸ�, ��ų �ִϸ��̼����� ��ü�Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			FallState::Skill_A(player);
		}
		
		// ���� ���� ������� �߶� ���¿��� ����������.
		if (DATAMANAGER->Collision_PlayerFall_Ground())
		{

			// ī�޶� ��ġ ����
			CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

			// ��Ʈ ����
			player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
			player->update_Ani_Rect();

			// ������ ���� �� ������ ���� ��� �ʱ�ȭ
			//player->set_Info()->bool_Value_Reset();
			player->set_Info()->bool_State_Reset();

			player->set_Info()->jump.jump_Value = 0;

			// ���� ��ġ �ʱ�ȭ
			player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;

			// Idle �ִϸ��̼� ��ü�� ���� ȣ��
			FallState::Idle(player);
		}

		// �߶�����
		player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

		// ���� ��ġ�� �߷¸�ŭ ����. (�ִ� �߶� �ӵ����� Ŭ����)
		if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED)
		{
			player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;
		}

	}

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void FallState::DownJump(Player * player)
{
}

void FallState::Dash(Player * player)
{
	// ���⿡ �´� �뽬 �ִϸ��̼����� ��ü���ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		if (!player->get_Info().bool_V.dash_Cheack)
		{
			//player->set_Info()->set_Ani("skul_Dash", "skul_Dash_Left");
			player->set_Info()->ani_Changer("Dash", player->get_InputKey());
			player->set_Info()->img.ani->start();

			player->set_Info()->bool_V.dash_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		if (!player->get_Info().bool_V.dash_Cheack)
		{
			//player->set_Info()->set_Ani("skul_Dash", "skul_Dash_Right");
			player->set_Info()->ani_Changer("Dash", player->get_InputKey());
			player->set_Info()->img.ani->start();

			player->set_Info()->bool_V.dash_Cheack = true;
		}
	}

	// �ִϸ��̼� ��ü�� �����ٸ� Dash ���·� �ٲ��ش�.
	player->set_State(DashState::getInstance());
	player->get_State()->update(player);
}

void FallState::JumpAttack(Player * player)
{
	// �������� �ִϸ��̼����� ��ü���ش�.
	player->set_Info()->ani_Changer("JumpAttack", player->get_InputKey());
	player->set_Info()->img.ani->start();


	// �������� ���·� �ٲ��ش�.
	player->set_State(JumpAttackState::getInstance());
	player->get_State()->update(player);
}

void FallState::Attack_A(Player * player)
{
}

void FallState::Attack_B(Player * player)
{
}

void FallState::Attack_C(Player * player)
{
}

void FallState::Skill_A(Player * player)
{

	// ��ų A�� �ִϸ��̼����� ��ü
	player->set_Info()->ani_Changer("Skill_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// ��ų A ���·� ��ü 
	player->set_State(Skill_A_State::getInstance());
	player->get_State()->update(player);

}

void FallState::Skill_B(Player * player)
{
}

void FallState::update(Player * player)
{
	FallState::Fall(player);

	KEYANIMANAGER->update();
}





// �������������������������������������������������������������������� �Ʒ� ���� ����! �������������������������������������������������������������������������������������
DownJumpState * DownJumpState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new DownJumpState();
	}

	return instance;
}

void DownJumpState::Idle(Player * player)
{
}

void DownJumpState::Move(Player * player)
{
}

void DownJumpState::Jump(Player * player)
{
	// ���� ��ġ��ŭ ĳ���͸� ���� �÷��ְ�, �߷¸�ŭ ��ġ�� �����Ѵ�.
	player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;
	player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

}

void DownJumpState::Fall(Player * player)
{
	// �߶� �ִϸ��̼� ��ü
	if (!player->get_Info().bool_V.fall_Cheack)
	{
		if (player->get_InputKey() == PRESS_LEFT)
		{
			//player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
			player->set_Info()->ani_Changer("Fall", player->get_InputKey());
			player->set_Info()->img.ani->start();

		}

		if (player->get_InputKey() == PRESS_RIGHT)
		{
			//player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
			player->set_Info()->ani_Changer("Fall", player->get_InputKey());
			player->set_Info()->img.ani->start();

		}

		player->set_Info()->bool_V.fall_Cheack = true;
	}

	// ���� ��ġ��ŭ �Ʒ��� ��������.
	player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;
	player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

	// ���� ���� ��ġ�� ���� ��Ʈ�� ������ �߶� ���·� �ٲ��ش�.
	if (DATAMANAGER->Collision_Player_FootHold())
	{
		// �߶� ���·� ����
		player->set_State(FallState::getInstance());
		player->get_State()->update(player);
	}
}

void DownJumpState::DownJump(Player * player)
{
	// ���� ��ġ�� �����ִٸ� ���� ������ �Ѵ�.
	if (player->get_Info().jump.jump_Value > 0)	Jump(player);

	// �Ʒ��� ��������.
	if (player->get_Info().jump.jump_Value <= 0) Fall(player);

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void DownJumpState::Dash(Player * player)
{
}

void DownJumpState::JumpAttack(Player * player)
{
}

void DownJumpState::Attack_A(Player * player)
{
}

void DownJumpState::Attack_B(Player * player)
{
}

void DownJumpState::Attack_C(Player * player)
{
}

void DownJumpState::Skill_A(Player * player)
{
}

void DownJumpState::Skill_B(Player * player)
{
}

void DownJumpState::update(Player * player)
{
	DownJumpState::DownJump(player);

	KEYANIMANAGER->update();
}






// �������������������������������������������������������������������� �뽬 ����! �������������������������������������������������������������������������������������
DashState * DashState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new DashState();
	}

	return instance;
}

void DashState::Idle(Player * player)
{
	// ��� �ִϸ��̼����� ��ü �� ��� ���·� �̵�
	if (player->get_InputKey() == PRESS_LEFT)
	{
		//player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
		player->set_Info()->ani_Changer("Idle", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		//player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
		player->set_Info()->ani_Changer("Idle", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	player->set_State(IdleState::getInstance());
	player->get_State()->Idle(player);
}

void DashState::Move(Player * player)
{
}

void DashState::Jump(Player * player)
{
}

void DashState::Fall(Player * player)
{
	// ���⿡ �´� �߶� �̹����� �־��ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		//player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		//player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();
	}

	// �߶� ���·� �̵��Ѵ�.
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void DashState::DownJump(Player * player)
{
}

void DashState::Dash(Player * player)
{
	// �뽬���϶��� ����
	if (player->get_Info().bool_V.dashing_Cheack) DATAMANAGER->Lerp_Player();

	// �뽬���� �ƴҶ�
	if (!player->get_Info().bool_V.dashing_Cheack)
	{
		// �Ʒ� ���� ���ٸ� �߶� �Լ� ȣ��
		if (!DATAMANAGER->Collision_PlayerFall_Ground())
		{
			DashState::Fall(player);
		}
		
		// �Ʒ� ���� �ִٸ� ��� �Լ� ȣ��
		if (DATAMANAGER->Collision_PlayerFall_Ground())
		{
			player->set_Info()->bool_V.idle_Cheack = false;
		
			// ���� ��ġ �ʱ�ȭ
			player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;
			player->set_Info()->jump.jump_Value = 0;
			
			DashState::Idle(player);
		}
	}
	
}

void DashState::JumpAttack(Player * player)
{
}

void DashState::Attack_A(Player * player)
{
}

void DashState::Attack_B(Player * player)
{
}

void DashState::Attack_C(Player * player)
{
}

void DashState::Skill_A(Player * player)
{
}

void DashState::Skill_B(Player * player)
{
}

void DashState::update(Player * player)
{
	DashState::Dash(player); 

}




// �������������������������������������������������������������������� ���� ���� ����! �������������������������������������������������������������������������������������
JumpAttackState * JumpAttackState::getInstance()
{
	if (instance == nullptr)
	{
		instance = new JumpAttackState();
	}

	return instance;
}

void JumpAttackState::Idle(Player * player)
{
	// ���ݷ�Ʈ �ʱ�ȭ
	player->set_Info()->pos.Attack_RC = { 0,0,0,0 };

	// ��� �ִϸ��̼����� ��ü�Ѵ�.
	player->set_Info()->ani_Changer("Idle", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// ��� �� ���� �ʱ�ȭ
	player->set_Info()->jump.jump_Value = 0;
	player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;
	player->set_Info()->jump.jump_Attack_Count = 0;

	player->set_Info()->bool_Value_Reset();

	// ��� ���·� ��ü
	player->set_State(IdleState::getInstance());
	player->get_State()->update(player);
}

void JumpAttackState::Move(Player * player)
{
	if (player->get_Info().jump.jump_Value < 0)
	{
		player->set_Info()->bool_V.jumping_Cheack = false;
		player->set_Info()->bool_V.falling_Cheack = true;

		// �Ʒ��� Ÿ���� ������ �߶��� ���߰� ��� �ִϸ��̼����� �ٲ��ش�.
		if (DATAMANAGER->Collision_PlayerFall_Ground() &&
			player->get_Info().bool_V.falling_Cheack &&
			!player->get_Info().bool_V.jumping_Cheack) Idle(player);
	}

	// ���� ����Ű�� ���� ��쿡�� �̵� bool ���� false��
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		player->set_Info()->bool_V.walking_Cheack = false;

		JumpAttackState::JumpAttack(player);
	}

	// ����Ű�� �°� �÷��̾ �̵������ش�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// ���� ������ �̵����� �ʵ��� �Ѵ�.
		if (!DATAMANAGER->Collision_Player_Wall()) player->set_Info()->pos.center.x -= PLAYER_SPEED;
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// ���� ������ �̵����� �ʵ��� �Ѵ�.
		if (!DATAMANAGER->Collision_Player_Wall()) player->set_Info()->pos.center.x += PLAYER_SPEED;
	}

	player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;
	if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED) player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void JumpAttackState::Jump(Player * player)
{
}

void JumpAttackState::Fall(Player * player)
{
	// ���� ��Ʈ �ʱ�ȭ
	player->set_Info()->pos.Attack_RC = { 0, 0, 0, 0 };

	// �������� ī��Ʈ �ʱ�ȭ
	player->set_Info()->jump.jump_Attack_Count = 0;

	// �߶��� �ִϸ��̼����� �ٲ��ش�.
	player->set_Info()->ani_Changer("Falling", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// �߶� ���·� �ٲ��ش�.
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void JumpAttackState::DownJump(Player * player)
{
}

void JumpAttackState::Dash(Player * player)
{
}

void JumpAttackState::JumpAttack(Player * player)
{
	if (player->get_Info().jump.jump_Value < 0)
	{
		player->set_Info()->bool_V.jumping_Cheack = false;
		player->set_Info()->bool_V.falling_Cheack = true;

		// �Ʒ��� Ÿ���� ������ �߶��� ���߰� ��� �ִϸ��̼����� �ٲ��ش�.
		if (DATAMANAGER->Collision_PlayerFall_Ground() &&
			player->get_Info().bool_V.falling_Cheack &&
			!player->get_Info().bool_V.jumping_Cheack) Idle(player);
	}

	// ���� �̵����̶��
	if (player->get_Info().bool_V.walking_Cheack) Move(player);

	// �̵������� �ʴٸ� �׳� �߶� ���길
	if (!player->get_Info().bool_V.walking_Cheack)
	{
		// ���� �̵�Ű�� ������ ��쿡�� bool���� �ٲ��ش�.
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			player->set_InputKey(PRESS_LEFT);

			player->set_Info()->bool_V.walking_Cheack = true;

			// �̵��� ���� �ؾ� �ϱ� ������ ��ȣ��
			JumpAttackState::JumpAttack(player);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			player->set_InputKey(PRESS_RIGHT);

			player->set_Info()->bool_V.walking_Cheack = true;

			// �̵��� ���� �ؾ� �ϱ� ������ ��ȣ��
			JumpAttackState::JumpAttack(player);
		}

		player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;
		if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED) player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

		// ī�޶� ��ġ ����
		CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

		// ��Ʈ ����
		player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		player->update_Ani_Rect();
	}

	// ���� ���� ���͹���
	player->set_Info()->jump.jump_Attack_Count++;

	// ���� ��Ʈ�� ������ش�.
	if (player->get_InputKey() == PRESS_LEFT && player->get_Info().img.ani->getFramePos().x == 320)		player->set_Info()->create_Attack_Rect(player->get_InputKey());
	else if (player->get_InputKey() == PRESS_RIGHT && player->get_Info().img.ani->getFramePos().x == 160)	player->set_Info()->create_Attack_Rect(player->get_InputKey());
	else player->set_Info()->pos.Attack_RC = { 0,0,0,0 };

	// ���� ������ �����ϸ� ���� �ð��� ���� �� �߶��� �ִϸ��̼����� �ٲ��.
	if (player->get_Info().jump.jump_Attack_Count >= PLAYER_JUMPATTACK_COOLTIME) Fall(player);
}

void JumpAttackState::Attack_A(Player * player)
{
}

void JumpAttackState::Attack_B(Player * player)
{
}

void JumpAttackState::Attack_C(Player * player)
{
}

void JumpAttackState::Skill_A(Player * player)
{
}

void JumpAttackState::Skill_B(Player * player)
{
}

void JumpAttackState::update(Player * player)
{
	JumpAttackState::JumpAttack(player);

	//KEYANIMANAGER->update();
}





// �������������������������������������������������������������������� �⺻���� A! �������������������������������������������������������������������������������������
Attack_A_State * Attack_A_State::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Attack_A_State();
	}

	return instance;
}

void Attack_A_State::Idle(Player * player)
{
	// ���� ��Ʈ �ʱ�ȭ
	player->set_Info()->pos.Attack_RC = { 0, 0, 0, 0 };

	// ���� ������ ���� ���� bool �ʱ�ȭ
	player->set_Info()->bool_V.Attack_Success = false;

	// ����ߴ� ���� �ʱ�ȭ
	player->set_Info()->bool_State_Reset();

	// ��� �ִϸ��̼��� �־��ش�.
	player->set_Info()->ani_Changer("Idle", player->get_InputKey());
	player->get_Info().img.ani->start();

	// ��� ���·� �ٲ��ش�.
	player->set_State(IdleState::getInstance());
	player->get_State()->update(player);
}

void Attack_A_State::Move(Player * player)
{
}

void Attack_A_State::Jump(Player * player)
{
}

void Attack_A_State::Fall(Player * player)
{
}

void Attack_A_State::DownJump(Player * player)
{
}

void Attack_A_State::Dash(Player * player)
{
}

void Attack_A_State::JumpAttack(Player * player)
{
}

void Attack_A_State::Attack_A(Player * player)
{
	// ���� �̵����� bool ���� �����ִٸ� ���� �����δ�.
	if (player->get_Info().bool_V.walking_Cheack)
	{
		if (player->get_InputKey() == PRESS_LEFT)
		{
			player->set_Info()->pos.center.x -= PLAYER_SPEED * 3;

			// �ѹ��� ���������ϱ� ������ false�� �ٲ��ش�.
			player->set_Info()->bool_V.walking_Cheack = false;
		}

		if (player->get_InputKey() == PRESS_RIGHT)
		{
			player->set_Info()->pos.center.x += PLAYER_SPEED * 3;

			// �ѹ��� ���������ϱ� ������ false�� �ٲ��ش�.
			player->set_Info()->bool_V.walking_Cheack = false;
		}

		// ī�޶� ��ġ ����
		CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

		// ��Ʈ ����
		player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		player->update_Ani_Rect();
	}

	// ���� ���� A�� �����Ű�� �ִ� ���߿� XŰ�� �����ٸ� (+ ���� Attack_B�� bool���� true�� �ȵ�����)
	{
		if (KEYMANAGER->isOnceKeyDown('X') && !player->get_Info().bool_V.next_Attack_B)
		{
			player->set_Info()->bool_V.next_Attack_B = true;
		}
	}

	// ���� ���� �������϶� ��Ʈ ���� �� �� �������϶� ����
	if (player->get_Info().img.ani->getFramePos().x == 2 * 160)
	{
		// ���� ��Ʈ�� ������ش�.
		player->set_Info()->create_Attack_Rect(player->get_InputKey());
	}
	else player->set_Info()->pos.Attack_RC = { 0,0,0,0 };


	// ���� �ִϸ��̼��� ������ �������϶�
	if (player->get_Info().img.ani->getFramePos().x == 640)
	{
		// ���� ���� B�� bool���� ���� �ִٸ� ���� B �ִϸ��̼����� ��ü �Ϸ� ����.
		if(player->get_Info().bool_V.next_Attack_B) Attack_B(player);
	
		// �ƴ϶�� ��� �ִϸ��̼��� �־��ش�.
		else Idle(player);
	}
}

void Attack_A_State::Attack_B(Player * player)
{
	// ���� ������ �����ϰ� bool�� �ʱ�ȭ
	player->set_Info()->bool_V.Attack_Success = false;

	// ���� B �ִϸ��̼����� ��ü���ش�.
	player->set_Info()->ani_Changer("Attack_B", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// ���� B ���·� ��ü���ش�.
	player->set_State(Attack_B_State::getInstance());
	player->get_State()->update(player);
}

void Attack_A_State::Attack_C(Player * player)
{
}

void Attack_A_State::Skill_A(Player * player)
{
}

void Attack_A_State::Skill_B(Player * player)
{
}

void Attack_A_State::update(Player * player)
{
	Attack_A_State::Attack_A(player);

}






// �������������������������������������������������������������������� �⺻���� B! �������������������������������������������������������������������������������������
Attack_B_State * Attack_B_State::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Attack_B_State();
	}

	return instance;
}

void Attack_B_State::Idle(Player * player)
{
	// ���� ��Ʈ �ʱ�ȭ
	player->set_Info()->pos.Attack_RC = { 0, 0, 0, 0 };

	// ����� ���� �ʱ�ȭ
	player->set_Info()->bool_State_Reset();

	player->set_Info()->bool_V.next_Attack_B = false;

	// ��� �ִϸ��̼����� ��ü ���ش�.
	player->set_Info()->ani_Changer("Idle", player->get_InputKey());

	// ��� ���·� �ٲ��ش�.
	player->set_State(IdleState::getInstance());
	player->get_State()->update(player);
}

void Attack_B_State::Move(Player * player)
{
}

void Attack_B_State::Jump(Player * player)
{
}

void Attack_B_State::Fall(Player * player)
{
}

void Attack_B_State::DownJump(Player * player)
{
}

void Attack_B_State::Dash(Player * player)
{
}

void Attack_B_State::JumpAttack(Player * player)
{
}

void Attack_B_State::Attack_A(Player * player)
{
}

void Attack_B_State::Attack_B(Player * player)
{
	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();

	// ���� ���� �������϶� ��Ʈ ���� �� �� �������϶� ����
	if (player->get_Info().img.ani->getFramePos().x == 2 * 160)
	{
		// ���� ��Ʈ�� ������ش�.
		player->set_Info()->create_Attack_Rect(player->get_InputKey());
	}
	else player->set_Info()->pos.Attack_RC = { 0,0,0,0 };

	// ���� �ִϸ��̼��� ������ �������϶�
	if (player->get_Info().img.ani->getFramePos().x == 640)
	{
		// ��� ���·� ���ư���.
		Attack_B_State::Idle(player);
	}
}

void Attack_B_State::Attack_C(Player * player)
{
}

void Attack_B_State::Skill_A(Player * player)
{
}

void Attack_B_State::Skill_B(Player * player)
{
}

void Attack_B_State::update(Player * player)
{
	Attack_B_State::Attack_B(player);

}






// �������������������������������������������������������������������� �⺻���� C! �������������������������������������������������������������������������������������
Attack_C_State * Attack_C_State::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Attack_C_State();
	}

	return instance;
}

void Attack_C_State::Idle(Player * player)
{
}

void Attack_C_State::Move(Player * player)
{
}

void Attack_C_State::Jump(Player * player)
{
}

void Attack_C_State::Fall(Player * player)
{
}

void Attack_C_State::DownJump(Player * player)
{
}

void Attack_C_State::Dash(Player * player)
{
}

void Attack_C_State::JumpAttack(Player * player)
{
}

void Attack_C_State::Attack_A(Player * player)
{
}

void Attack_C_State::Attack_B(Player * player)
{
}

void Attack_C_State::Attack_C(Player * player)
{
}

void Attack_C_State::Skill_A(Player * player)
{
}

void Attack_C_State::Skill_B(Player * player)
{
}

void Attack_C_State::update(Player * player)
{
}






// �������������������������������������������������������������������� ��ų A! �������������������������������������������������������������������������������������
Skill_A_State * Skill_A_State::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Skill_A_State();
	}

	return instance;
}

void Skill_A_State::Idle(Player * player)
{
	// �Ұ� �ʱ�ȭ
	player->set_Info()->bool_State_Reset();

	// ��� �ִϸ��̼����� ��ü
	player->set_Info()->ani_Changer("Idle", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// ��� ���·� ��ü
	player->set_State(IdleState::getInstance());
	player->get_State()->update(player);
}

void Skill_A_State::Move(Player * player)
{
}

void Skill_A_State::Jump(Player * player)
{
}

void Skill_A_State::Fall(Player * player)
{
}

void Skill_A_State::DownJump(Player * player)
{
}

void Skill_A_State::Dash(Player * player)
{
}

void Skill_A_State::JumpAttack(Player * player)
{
}

void Skill_A_State::Attack_A(Player * player)
{
}

void Skill_A_State::Attack_B(Player * player)
{
}

void Skill_A_State::Attack_C(Player * player)
{
}

void Skill_A_State::Skill_A(Player * player)
{
	// ������ �Ӹ� ��ġ���� ��Ʈ�� �����Ͽ� �ٶ󺸴� �������� �����ش�. (�Ӹ��� ��Ʈ ���� �Լ� ȣ��)
	// ������ �Ӹ��� �ѹ��� ���ư��� �Ѵ�. �Ѱ��� ������ ���ÿ� bool���� �ٲ��ش�.
	// ������ �Ӹ��� �ٽ� �ݰų�, ���� �ð��� �ڳ��� bool���� false�� �ٲ��.
	if (!player->get_Info().bool_V.useing_Skill_A)
	{
		// ������ �Ӹ��� �������ش�. (���⿡ ���� �ٸ� �̹���, �ٸ� ����)
		if (player->get_InputKey() == PRESS_RIGHT)
		{
			DATAMANAGER->flyObj_Manager_Address()->Create_FlyingObj("skul_Skill_Head", "skill_Head_R", 
				FLYINFOBJECT_TYPE::SKUL_HEAD, FLYINGOBJECT_DIRECTION::RIGHT,
				player->get_Info().pos.center.x, player->get_Info().pos.center.y - 20,
				0.f, PLAYER_HEAD_SPEED, 40, true);
		}

		if (player->get_InputKey() == PRESS_LEFT)
		{
			DATAMANAGER->flyObj_Manager_Address()->Create_FlyingObj("skul_Skill_Head", "skill_Head_L", 
				FLYINFOBJECT_TYPE::SKUL_HEAD, FLYINGOBJECT_DIRECTION::LEFT,
				player->get_Info().pos.center.x, player->get_Info().pos.center.y - 20,
				3.14f, PLAYER_HEAD_SPEED, 40, true);
		}

		// ��ų�� ��������� true
		player->set_Info()->bool_V.useing_Skill_A = true;
	}

	// ������ �Ӹ��� ������ �ִϸ��̼��� ������ ���� �Ӹ��� ���� �ִϸ��̼� Ÿ������ ��ü �� ��� ���·�
	if (player->get_Info().img.ani->getFramePos().x == 480)
	{
		// ���� �ʱ�ȭ (��ų�� ���� �� ��� -> �߶����� �Ѿ ���)
		player->set_Info()->jump.jump_Value = 0;

		player->set_Info()->type.skul_Type = SKUL_TYPE::SKUL_WEAPON_NOHEAD;
		Skill_A_State::Idle(player);
	}

}

void Skill_A_State::Skill_B(Player * player)
{
}

void Skill_A_State::update(Player * player)
{
	Skill_A_State::Skill_A(player);

	//KEYANIMANAGER->update();
}






// �������������������������������������������������������������������� ��ų B! �������������������������������������������������������������������������������������
Skill_B_State * Skill_B_State::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Skill_B_State();
	}

	return instance;
}

void Skill_B_State::Idle(Player * player)
{
}

void Skill_B_State::Move(Player * player)
{
}

void Skill_B_State::Jump(Player * player)
{
}

void Skill_B_State::Fall(Player * player)
{
}

void Skill_B_State::DownJump(Player * player)
{
}

void Skill_B_State::Dash(Player * player)
{
}

void Skill_B_State::JumpAttack(Player * player)
{
}

void Skill_B_State::Attack_A(Player * player)
{
}

void Skill_B_State::Attack_B(Player * player)
{
}

void Skill_B_State::Attack_C(Player * player)
{
}

void Skill_B_State::Skill_A(Player * player)
{
}

void Skill_B_State::Skill_B(Player * player)
{
}

void Skill_B_State::update(Player * player)
{
}


