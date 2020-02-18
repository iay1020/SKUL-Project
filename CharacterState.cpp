#include "stdafx.h"
#include "CharacterState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;
JumpState* JumpState::instance;
FallState* FallState::instance;
DownJumpState* DownJumpState::instance;
DashState* DashState::instance;

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
	// �÷��̾��� �Ʒ��� �� Ÿ���� ���ٸ� �߶� ���·� �ٲ��ش�.
	if (!DATAMANAGER->Collision_PlayerFall_Ground())
	{
		Fall(player);  // �߶��Լ� ȣ��
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

		// Jump�Լ� ȣ��
		IdleState::Jump(player);
	}


	// �����ִ� ���¿��� ��ų�� �����ٸ� ��ų ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('A'))
	{

	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{

	}



	// �����ִ� ���¿��� �뽬�� �����ٸ� �뽬 ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{

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
			player->set_Info()->set_Ani("skul_Walk_NoWeapon", "skul_Walk_Left_NoWeapon");
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
			player->set_Info()->set_Ani("skul_Walk_NoWeapon", "skul_Walk_Right_NoWeapon");
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
		player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
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
		player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
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
		player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
		player->set_Info()->img.ani->start();

	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
		player->set_Info()->img.ani->start();

	}
	
	// �Ʒ� ���� ���·� �̵��Ѵ�.
	player->set_State(DownJumpState::getInstance());
	player->get_State()->update(player);
}

void IdleState::Dash(Player * player)
{
}

void IdleState::update(Player * player)
{
	Idle(player);

	KEYANIMANAGER->update();
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
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
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
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
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
	// �÷��̾��� �Ʒ��� �� Ÿ���� ���ٸ� �߶� ���·� �ٲ��ش�.
	if (!DATAMANAGER->Collision_PlayerFall_Ground())
	{
		Fall(player);  // �߶��Լ� ȣ��
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
			player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
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
			player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
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
		player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
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
}

void MoveState::update(Player * player)
{	
	Move(player);

	KEYANIMANAGER->update();
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
			Jump(player);
		}

		// ����Ű�� �ٽ� �����ٸ� (���� Ƚ���� �����ִٸ�)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// ���� ī��Ʈ�� ���� �����ְ�, ���� ��ġ ȸ��
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;
			}
		}
	}
}

void JumpState::Jump(Player * player)
{
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
			player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");

			// �̵����̶�� true
			player->set_Info()->bool_V.walking_Cheack = true;

			// �̵� + ���� ������ ���� Move ȣ��
			Move(player);
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// �Է�Ű ����
			player->set_InputKey(PRESS_RIGHT);

			// ���⿡ �´� �ִϸ��̼����� ��ü
			player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");

			// �̵����̶�� true
			player->set_Info()->bool_V.walking_Cheack = true;

			// �̵� + ���� ������ ���� Move ȣ��
			Move(player);
		}

		// ����Ű�� �ٽ� �����ٸ� (���� Ƚ���� �����ִٸ�)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// ���� ī��Ʈ�� ���� �����ְ�, ���� ��ġ ȸ��
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;
			}
		}
	
		// ���� ������ �����Ѵ�. ���� ��ġ�� 0 �̻��϶���
		if (player->get_Info().jump.jump_Value > 0)
		{
			// ���� ��ġ��ŭ ĳ������ y��ǥ�� ����.
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
		player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
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
}

void JumpState::update(Player * player)
{
	Jump(player);

	KEYANIMANAGER->update();
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
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
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
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
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
		player->set_Info()->bool_V.idle_Cheack = false;
		player->set_Info()->bool_V.walk_Cheack = false;
		player->set_Info()->bool_V.walking_Cheack = false;
		player->set_Info()->bool_V.jump_Cheack = false;
		player->set_Info()->bool_V.jumping_Cheack = false;
		player->set_Info()->bool_V.fall_Cheack = false;
		player->set_Info()->bool_V.falling_Cheack = false;
		player->set_Info()->jump.jump_Value = 0;
		
		// ���� ��ġ �ʱ�ȭ
		player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;
		
		// Idle �ִϸ��̼� ��ü�� ���� ȣ��
		Idle(player);
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
		Fall(player);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		// �̵����� �ƴ϶�� false
		player->set_Info()->bool_V.walking_Cheack = false;

		// �ٸ� ������ �Է� �� �߶� �ִϸ��̼� ��ü�� ���� false��
		player->set_Info()->bool_V.fall_Cheack = false;

		// �̵��� �������� �ٸ� ������ ���� Fall �Լ� ȣ��
		Fall(player);
	}

	// ����Ű�� �ٽ� �����ٸ� (���� Ƚ���� �����ִٸ�)
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (player->get_Info().jump.Jump_Count > 0)
		{
			// ���� ī��Ʈ�� ���� �����ְ�, ���� ��ġ ȸ��
			player->set_Info()->jump.Jump_Count--;
			player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

			// ���� �ִϸ��̼� ��ü�� ���� ȣ��
			Jump(player);
		}
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
		player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
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
		player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
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
	// �߶� ���� �ִϸ��̼����� ��ü�ϴ� ���� (���� �߶� �ִϸ��̼� �߿���)
	if (player->get_Info().img.imgName == "skul_Fall")
	{

		// �������� 2�� ���ϴ� ���� (�����Ӱ����� ũ�Ⱑ 160�̹Ƿ�, 0 = 0, 160 = 1, 320 = 2�� ������ ��ġ�� ����Ų��.)
		if (player->get_Info().img.ani->getFramePos().x >= 320)
		{
			// ���䰡 ��� �޷��ŷ��� �ϱ� ������ ���� �ִϸ��̼����� ��ü�Ѵ�.
			if (player->get_InputKey() == PRESS_LEFT)
			{
				player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
				player->set_Info()->img.ani->start();
			}

			if (player->get_InputKey() == PRESS_RIGHT)
			{
				player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
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
			player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
			player->set_Info()->img.ani->start();
			
			// ĳ���� ���� ���� ����� ����
			if (!DATAMANAGER->Collision_Player_Wall())
			{
				// �̵����̶�� true
				player->set_Info()->bool_V.walking_Cheack = true;

				// �̵� + �߶� ������ ���� Jall�Լ� �ٽ� ȣ��
				Fall(player);
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// �ش� ����Ű ����
			player->set_InputKey(PRESS_RIGHT);

			// �ش� �������� �ִϸ��̼� ��ü
			player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
			player->set_Info()->img.ani->start();

			// ĳ���� ���� ���� ����� ����
			if (!DATAMANAGER->Collision_Player_Wall())
			{
				// �̵����̶�� true
				player->set_Info()->bool_V.walking_Cheack = true;

				// �̵� + �߶� ������ ���� Jall�Լ� �ٽ� ȣ��
				Fall(player);
			}
		}

		// ����Ű�� �ٽ� �����ٸ� (���� Ƚ���� �����ִٸ�)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// ���� ī��Ʈ�� ���� �����ְ�, ���� ��ġ ȸ��
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

				// ���� �ִϸ��̼� ��ü�� ���� ȣ��
				Jump(player);
			}
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
			player->set_Info()->bool_V.idle_Cheack = false;
			player->set_Info()->bool_V.walk_Cheack = false;
			player->set_Info()->bool_V.walking_Cheack = false;
			player->set_Info()->bool_V.jump_Cheack = false;
			player->set_Info()->bool_V.jumping_Cheack = false;
			player->set_Info()->bool_V.fall_Cheack = false;
			player->set_Info()->bool_V.falling_Cheack = false;
			player->set_Info()->jump.jump_Value = 0;

			// ���� ��ġ �ʱ�ȭ
			player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;

			// Idle �ִϸ��̼� ��ü�� ���� ȣ��
			Idle(player);
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
}

void FallState::update(Player * player)
{
	Fall(player);

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

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();

	// �ٽ� DownJump�Լ��� ���ư���.
	DownJump(player);
}

void DownJumpState::Fall(Player * player)
{
	// �߶� �ִϸ��̼� ��ü
	if (!player->get_Info().bool_V.fall_Cheack)
	{
		if (player->get_InputKey() == PRESS_LEFT)
		{
			player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
			player->set_Info()->img.ani->start();

		}

		if (player->get_InputKey() == PRESS_RIGHT)
		{
			player->set_Info()->set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
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

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();


	// ������ ������ �ʾҴٸ� �ݺ�
	DownJump(player);
}

void DownJumpState::DownJump(Player * player)
{
	// ���� ��ġ�� �����ִٸ� ���� ������ �Ѵ�.
	if (player->get_Info().jump.jump_Value > 0)	Jump(player);

	// �Ʒ��� ��������.
	if (player->get_Info().jump.jump_Value <= 0) Fall(player);
}

void DownJumpState::Dash(Player * player)
{
}

void DownJumpState::update(Player * player)
{
	DownJump(player);

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
}

void DashState::Move(Player * player)
{
}

void DashState::Jump(Player * player)
{
}

void DashState::Fall(Player * player)
{
}

void DashState::DownJump(Player * player)
{
}

void DashState::Dash(Player * player)
{
}

void DashState::update(Player * player)
{
	Dash(player);

	KEYANIMANAGER->update();
}


