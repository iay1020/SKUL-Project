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
	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();

	// �����ִ� ���¿��� ������ �����ٸ� ���� ���·� �ٲ��ش�.
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		player->set_State(JumpState::getInstance());
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
}

void IdleState::Move(Player * player)
{
	player->set_Info()->bool_V.idle_Cheack = false;

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
	}

	// ���¸� ����� �ٲ��ش�.
	player->set_State(MoveState::getInstance());
}

void IdleState::Jump(Player * player)
{
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
	// ���� �̵� ���� �ִϸ��̼��� ���� bool�� �ʱ�ȭ
	player->set_Info()->bool_V.walk_Cheack = false;

	if (player->get_InputKey() == PRESS_LEFT)
	{
		// false��� idle �ִϸ��̼����� �ٲ��ش�.
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			cout << "���� �ִ� ��ü" << endl;
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
			cout << "������ �ִ� ��ü" << endl;
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
		// �÷��̾ �������� �̵�
		player->set_Info()->pos.center.x -= PLAYER_SPEED;

		// �÷��̾ ���� Ű�� �Է� �Ѵٸ� ���� ���·� �ٲ��ش�.

		// �÷��̾ ���� Ű�� �Է� �Ѵٸ� ���¸� �ٲ��ش�.

	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// �÷��̾ ���������� �̵�
		player->set_Info()->pos.center.x += PLAYER_SPEED;

		// �÷��̾ ���� Ű�� �Է� �Ѵٸ� ���� ���·� �ٲ��ش�.

		// �÷��̾ ���� Ű�� �Է� �Ѵٸ� ���¸� �ٲ��ش�.

	}

	// ī�޶� ��ġ ����
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// ��Ʈ ����
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void MoveState::Jump(Player * player)
{
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
}

void JumpState::Jump(Player * player)
{
	// ���� ��ġ�� �ް� ���� ��ġ�� 0���� ���Ҷ� �߶� ���·� ���� ��Ų��.
	if (player->get_InputKey() == PRESS_LEFT)
	{

	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{

	}

}

void JumpState::Fall(Player * player)
{
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
}

void FallState::Jump(Player * player)
{
}

void FallState::Fall(Player * player)
{
}

void FallState::update(Player * player)
{
}
