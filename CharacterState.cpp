#include "stdafx.h"
#include "CharacterState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;
JumpState* JumpState::instance;
FallState* FallState::instance;

// �������������������������������������������������������������������� ��� ���� �������������������������������������������������������������������������������������
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


	// �����ִ� ���¿��� ������ �����ٸ� ���� ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
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
}

void IdleState::Fall(Player * player)
{
}

void IdleState::update(Player * player)
{
	Idle(player);

	KEYANIMANAGER->update();
}





// �������������������������������������������������������������������� �̵� ���� �������������������������������������������������������������������������������������
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
}

void MoveState::Move(Player * player)
{
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// �÷��̾ �������� �̵� (�̵����̶��)
		if(player->get_Info().bool_V.walking_Cheack) player->set_Info()->pos.center.x -= PLAYER_SPEED;

		// �÷��̾ ���� Ű�� �Է� �Ѵٸ� ���� �Լ��� ȣ���Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			// ����Ű�� �����ٸ� true�� �ٲ��ش�.
			player->set_Info()->bool_V.jumping_Cheack = true;

			// ���� �ִϸ��̼� ��ü�� ���� Jump�Լ� ȣ��
			MoveState::Jump(player);
		}

		// ����Ű�� ���ٸ� ��� ���·� ���ư����Ѵ�.
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			// �̵��� ���� �Ʊ� ������ false�� �ٲ��ش�.
			player->set_Info()->bool_V.walking_Cheack = false;
			player->set_Info()->bool_V.idle_Cheack = false;

			// ��� �̹����� �ٲٱ� ���� Idle�Լ� ȣ��
			MoveState::Idle(player);
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// �÷��̾ ���������� �̵� (�̵����̶��)
		if (player->get_Info().bool_V.walking_Cheack) player->set_Info()->pos.center.x += PLAYER_SPEED;

		// �÷��̾ ���� Ű�� �Է� �Ѵٸ� ���� �Լ��� ȣ���Ѵ�.
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			// ����Ű�� �����ٸ� true�� �ٲ��ش�.
			player->set_Info()->bool_V.jumping_Cheack = true;

			// ���� �ִϸ��̼� ��ü�� ���� Jump�Լ� ȣ��
			MoveState::Jump(player);
		}

		// ������Ű�� ���ٸ� ��� ���·� ���ư����Ѵ�.
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			// �̵��� ���� �Ʊ� ������ false�� �ٲ��ش�.
			player->set_Info()->bool_V.walking_Cheack = false;
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
			player->set_Info()->bool_V.jump_Cheack = true;
		}

		// ���� ����Ű���� ���� ���ٸ�
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			// ���� �����߿� �ٸ� ����Ű�� ������ �ٸ� �̹����� ��ü�ؾ� �ϴϱ� false��
			player->set_Info()->bool_V.jump_Cheack = false;
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
			// ���� �����߿� �ٸ� ����Ű�� ������ �ٸ� �̹����� ��ü�ؾ� �ϴϱ� false��
			player->set_Info()->bool_V.jump_Cheack = false;
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
	}
}

void MoveState::Fall(Player * player)
{
}

void MoveState::update(Player * player)
{	
	Move(player);

	KEYANIMANAGER->update();
}




// �������������������������������������������������������������������� ���� ���� �������������������������������������������������������������������������������������
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
	// �ش� �������� �̵��Ѵ�.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		player->set_Info()->pos.center.x -= PLAYER_SPEED;
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		player->set_Info()->pos.center.x += PLAYER_SPEED;
	}

	// ���� ������ ���ش�.
	// ���� ������ �����Ѵ�. ���� ��ġ�� 0 �̻��϶���
	if (player->get_Info().jump.jump_Value > 0)
	{
		// ���� ��ġ��ŭ ĳ������ y��ǥ�� ����.
		player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

		// ���� ��ġ�� �߷¸�ŭ ����.
		player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;
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
	}

	// ����Ű�� �ٲ�ٸ� �ִϸ��̼� ��ü (�̹����� ���� �����ϸ� �ȵȴ�. �״�� �����ϰ� �ϴ� ���?)
}

void JumpState::Jump(Player * player)
{
	// ���� ��� �̵����̶�� true��
	if (player->get_Info().bool_V.walking_Cheack) Move(player);


	// ���� ������ �����Ѵ�. ���� ��ġ�� 0 �̻��϶���
	if (player->get_Info().jump.jump_Value > 0)
	{
		// ���� ��ġ��ŭ ĳ������ y��ǥ�� ����.
		player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

		// ���� ��ġ�� �߷¸�ŭ ����.
		player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

		// �ٽ� ������ ���� ó������ ����������.
		player->set_State(IdleState::getInstance());
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
}

void JumpState::update(Player * player)
{
	Jump(player);

	KEYANIMANAGER->update();
}





// �������������������������������������������������������������������� �߶� ���� �������������������������������������������������������������������������������������
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
}

void FallState::Move(Player * player)
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

	// �߶� ������ ���� �� ó������ ������.


	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void FallState::Jump(Player * player)
{
}

void FallState::Fall(Player * player)
{
	// �̵����̶�� �̵� ������ �Ѵ�.
	if (player->get_Info().bool_V.walking_Cheack) Move(player);
	// �׷��� �ʴٸ� �߶� ���길 �Ѵ�.
	else
	{
		// �߶�����
		player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;
		player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

		// ī�޶� ��ġ ����
		CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

		// ��Ʈ ����
		player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		player->update_Ani_Rect();

		// ó������ �ǵ�����.
	}
}

void FallState::update(Player * player)
{
	Fall(player);

	KEYANIMANAGER->update();
}
