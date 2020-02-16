#include "stdafx.h"
#include "CharacterState.h"

IdleState* IdleState::instance;
MoveState* MoveState::instance;
JumpState* JumpState::instance;
FallState* FallState::instance;

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 대기 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 멈춰있는 상태에서 왼쪽을 눌렀다면 왼쪽 이동 상태로 바꿔준다.
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		// inputKey에 입력한 키를 저장한다.
		player->set_InputKey(PRESS_LEFT);

		// 캐릭터의 방향을 저장한다.
		player->set_Info()->status.direction = DIRECTION_LEFT;

		// 이동키를 계속 누르고 있을때 이 값은 true로 바뀐다.
		player->set_Info()->bool_V.walking_Cheack = true;

		// 무브 상태로 바꾼다. (Idle 상태에서 Move로 교체했으니, Move 함수를 호출한다.)
		IdleState::Move(player);

	}

	// 멈춰있는 상태에서 오른쪽을 눌렀다면 오른쪽 이동 상태로 바꿔준다.
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		// inputKey에 입력한 키를 저장한다.
		player->set_InputKey(PRESS_RIGHT);

		// 캐릭터의 방향을 저장한다.
		player->set_Info()->status.direction = DIRECTION_RIGHT;

		// 이동키를 계속 누르고 있을때 이 값은 true로 바뀐다.
		player->set_Info()->bool_V.walking_Cheack = true;
			
		// 무브 상태로 바꾼다. (Idle 상태에서 Move로 교체했으니, Move 함수를 호출한다.) 
		IdleState::Move(player);

	}


	// 멈춰있는 상태에서 점프를 눌렀다면 점프 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		// 점프를 사용 했다면 점프 카운트 감소
		player->set_Info()->jump.Jump_Count--;

		// 점프 수치를 넣어준다.
		player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

		// 점프중이라면 ture
		player->set_Info()->bool_V.jumping_Cheack = true;

		// Jump함수 호출
		IdleState::Jump(player);
	}


	// 멈춰있는 상태에서 스킬을 눌렀다면 스킬 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('A'))
	{

	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{

	}



	// 멈춰있는 상태에서 대쉬를 눌렀다면 대쉬 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{

	}

	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void IdleState::Move(Player * player)
{
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// false라면 walk 애니메이션으로 바꿔준다.
		if (!player->get_Info().bool_V.walk_Cheack)
		{
			// 애니메이션 교체
			player->set_Info()->set_Ani("skul_Walk_NoWeapon", "skul_Walk_Left_NoWeapon");
			player->set_Info()->img.ani->start();

			// 애니메이션 교체 후 true (1번만 바꾸기 위해)
			player->set_Info()->bool_V.walk_Cheack = true;
		}

		// 상태를 무브로 바꿔준다.
		player->set_State(MoveState::getInstance());
		player->get_State()->update(player);
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// false라면 walk 애니메이션으로 바꿔준다.
		if (!player->get_Info().bool_V.walk_Cheack)
		{
			// 애니메이션 교체
			player->set_Info()->set_Ani("skul_Walk_NoWeapon", "skul_Walk_Right_NoWeapon");
			player->set_Info()->img.ani->start();

			// 애니메이션 교체 후 true (1번만 바꾸기 위해)
			player->set_Info()->bool_V.walk_Cheack = true;
		}

		// 상태를 무브로 바꿔준다.
		player->set_State(MoveState::getInstance());
		player->get_State()->update(player);
	}
}

void IdleState::Jump(Player * player)
{
	// 방향이 바뀌었다면 이미지를 교체해준다.
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

	// 상태를 다시 점프 상태로 교체
	player->set_State(JumpState::getInstance());
	player->get_State()->update(player);
}

void IdleState::Fall(Player * player)
{
}

void IdleState::update(Player * player)
{
	Idle(player);

	KEYANIMANAGER->update();
}





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 이동 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
		// false라면 idle 애니메이션으로 바꿔준다.
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			// 애니메이션 교체
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
			player->set_Info()->img.ani->start();

			// 애니메이션 교체 후 true (1번만 바꾸기 위해)
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// false라면 idle 애니메이션으로 바꿔준다.
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			// 애니메이션 교체
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
			player->set_Info()->img.ani->start();

			// 애니메이션 교체 후 true (1번만 바꾸기 위해)
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	// 상태를 대기로 바꿔준다.
	player->set_State(IdleState::getInstance());
}

void MoveState::Move(Player * player)
{
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// 플레이어가 왼쪽으로 이동 (이동중이라면)
		if(player->get_Info().bool_V.walking_Cheack) player->set_Info()->pos.center.x -= PLAYER_SPEED;

		// 플레이어가 점프 키를 입력 한다면 점프 함수를 호출한다.
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			// 점프 횟수가 남아있다면
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// 점프 횟수를 감소 한다.
				player->set_Info()->jump.Jump_Count--;

				// 점프키를 눌렀다면 true로 바꿔준다.
				player->set_Info()->bool_V.jumping_Cheack = true;

				// 점프 애니메이션 교체를 위해 Jump함수 호출
				MoveState::Jump(player);
			}
		}

		// 왼쪽키를 땐다면 대기 상태로 돌아가야한다.
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			// 이동이 종료 됐기 때문에 false로 바꿔준다.
			player->set_Info()->bool_V.walking_Cheack = false;
			player->set_Info()->bool_V.walk_Cheack = false;
			player->set_Info()->bool_V.idle_Cheack = false;

			// 대기 이미지로 바꾸기 위해 Idle함수 호출
			MoveState::Idle(player);
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// 플레이어가 오른쪽으로 이동 (이동중이라면)
		if (player->get_Info().bool_V.walking_Cheack) player->set_Info()->pos.center.x += PLAYER_SPEED;

		// 플레이어가 점프 키를 입력 한다면 점프 함수를 호출한다.
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			// 점프 횟수가 남아있다면
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// 점프 횟수를 감소 한다.
				player->set_Info()->jump.Jump_Count--;

				// 점프키를 눌렀다면 true로 바꿔준다.
				player->set_Info()->bool_V.jumping_Cheack = true;

				// 점프 애니메이션 교체를 위해 Jump함수 호출
				MoveState::Jump(player);
			}
		}

		// 오른쪽키를 땐다면 대기 상태로 돌아가야한다.
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			// 이동이 종료 됐기 때문에 false로 바꿔준다.
			player->set_Info()->bool_V.walking_Cheack = false;
			player->set_Info()->bool_V.walk_Cheack = false;
			player->set_Info()->bool_V.idle_Cheack = false;

			// 대기 이미지로 바꾸기 위해 Idle함수 호출
			MoveState::Idle(player);
		}
	}

	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void MoveState::Jump(Player * player)
{
	if (player->get_InputKey() == PRESS_LEFT)
	{
		if (!player->get_Info().bool_V.jump_Cheack)
		{
			// 점프 애니메이션을 넣어준다.
			player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
			player->set_Info()->img.ani->start();

			// 점프 변수에 값을 넣어준다.
			player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

			// 점프중으로 바꾼다.
			player->set_Info()->bool_V.jumping_Cheack = true;

			// 점프 애니메이션 교체 했으면 true
			player->set_Info()->bool_V.jump_Cheack = true;
		}

		// 만약 방향키에서 손을 땠다면
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			// 더 이상 이동을 하지 않는다는 뜻
			player->set_Info()->bool_V.walking_Cheack = false;
		}

		// 다른 방향키를 눌렀다면
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			// 입력치를 갱신해준다.
			player->set_InputKey(PRESS_RIGHT);

			// 다시 이미지를 받기 위해 false로 바꿔준다.
			player->set_Info()->bool_V.jump_Cheack = false;

			// 함수를 재실행 한다.
			MoveState::Jump(player);
		}

		// 점프 상태로 바꿔준다.
		player->set_State(JumpState::getInstance());
		player->get_State()->update(player);
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		if (!player->get_Info().bool_V.jump_Cheack)
		{
			// 점프 애니메이션을 넣어준다.
			player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
			player->set_Info()->img.ani->start();

			// 점프 변수에 값을 넣어준다.
			player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

			// 점프중으로 바꾼다.
			player->set_Info()->bool_V.jump_Cheack = true;
		}

		// 만약 방향키에서 손을 땠다면
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			// 더 이상 이동을 하지 않는다는 뜻
			player->set_Info()->bool_V.walking_Cheack = false;
		}

		// 다른 방향키를 눌렀다면
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			// 입력치를 갱신해준다.
			player->set_InputKey(PRESS_LEFT);

			// 다시 이미지를 받기 위해 false로 바꿔준다.
			player->set_Info()->bool_V.jump_Cheack = false;

			// 함수를 재실행 한다.
			MoveState::Jump(player);
		}

		// 점프 상태로 바꿔준다.
		player->set_State(JumpState::getInstance());
		player->get_State()->update(player);
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




// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 점프 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 이동중일 경우 연산
	if (player->get_Info().bool_V.walking_Cheack)
	{

		// 해당 방향으로 이동한다.
		if (player->get_InputKey() == PRESS_LEFT)
		{
			player->set_Info()->pos.center.x -= PLAYER_SPEED;
		}

		if (player->get_InputKey() == PRESS_RIGHT)
		{
			player->set_Info()->pos.center.x += PLAYER_SPEED;
		}

		// 점프 연산을 해준다.
		// 점프 연산을 시작한다. 점프 수치가 0 이상일때만
		if (player->get_Info().jump.jump_Value > 0)
		{
			// 점프 수치만큼 캐릭터의 y좌표를 뺀다.
			player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

			// 점프 수치를 중력만큼 뺀다. (최대 추락 속도보다 클때만)
			if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED)
			{
				player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;
			}
		}

		// 점프 수치가 0 이하라면 추락 상태로 바꿔야한다.
		else
		{
			// 점프는 이제 끝이다.
			player->set_Info()->bool_V.jumping_Cheack = false;
		
			// 추락 시작
			player->set_Info()->bool_V.falling_Cheack = true;
		
			// Fall함수 호출
			JumpState::Fall(player);
		}

		// 만약 키를 땠다면
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			// 더 이상 이동을 못하도록 false 값을 넣어준다.
			player->set_Info()->bool_V.walking_Cheack = false;

			// 다음 입력때 애니메이션 교체를 위해 flase로 바꿔준다.
			player->set_Info()->bool_V.jump_Cheack = false;

			// 이동이 끝났다면 다른 연산을 하기 위해 Jump로 돌아간다.
			Jump(player);
		}

		// 점프키를 다시 눌렀다면 (점프 횟수가 남아있다면)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// 점프 카운트를 감소 시켜주고, 점프 수치 회복
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;
			}
		}
	}
}

void JumpState::Jump(Player * player)
{
	// 만약 계속 이동중이라면 true값
	if (player->get_Info().bool_V.walking_Cheack) Move(player);

	// 플레이어가 이동중이지 않을때
	if (!player->get_Info().bool_V.walking_Cheack)
	{
		// 만약 방향키를 누르면 애니메이션 교체 후 Jump함수 호출 후 Move로 보내준다.
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			// 입력키 저장
			player->set_InputKey(PRESS_LEFT);

			// 방향에 맞는 애니메이션으로 교체
			player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");

			// 이동중이라면 true
			player->set_Info()->bool_V.walking_Cheack = true;

			// 이동 + 점프 연산을 위해 Move 호출
			Move(player);
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// 입력키 저장
			player->set_InputKey(PRESS_RIGHT);

			// 방향에 맞는 애니메이션으로 교체
			player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");

			// 이동중이라면 true
			player->set_Info()->bool_V.walking_Cheack = true;

			// 이동 + 점프 연산을 위해 Move 호출
			Move(player);
		}

		// 점프키를 다시 눌렀다면 (점프 횟수가 남아있다면)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// 점프 카운트를 감소 시켜주고, 점프 수치 회복
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;
			}
		}
	
		// 점프 연산을 시작한다. 점프 수치가 0 이상일때만
		if (player->get_Info().jump.jump_Value > 0)
		{
			// 점프 수치만큼 캐릭터의 y좌표를 뺀다.
			player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

			// 점프 수치를 중력만큼 뺀다. (최대 추락 속도보다 클때만)
			if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED)
			{
				player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;
			}
		}

		// 점프 수치가 0 이하라면 추락 상태로 바꿔야한다.
		else
		{
			// 점프는 이제 끝이다.
			player->set_Info()->bool_V.jumping_Cheack = false;
		
			// 추락 시작
			player->set_Info()->bool_V.falling_Cheack = true;
		
			// Fall함수 호출
			JumpState::Fall(player);
		}
	}

	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void JumpState::Fall(Player * player)
{
	// 방향에 맞는 추락 이미지를 넣어준다.
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

	// 추락 상태로 이동한다.
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void JumpState::update(Player * player)
{
	Jump(player);

	KEYANIMANAGER->update();
}





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 추락 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 방향에 따라 다른 대기 애니메이션을 넣어준다.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			// 대기 애니메이션으로 교체
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
			player->set_Info()->img.ani->start();

			// 교체를 했다면 true
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		if (!player->get_Info().bool_V.idle_Cheack)
		{
			// 대기 애니메이션으로 교체
			player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
			player->set_Info()->img.ani->start();

			// 교체를 했다면 true
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	// 대기 상태로 바꿔준다.
	player->set_State(IdleState::getInstance());
	player->get_State()->update(player);
}

void FallState::Move(Player * player)
{
	// 이동중이라면 인동 연산을 한다.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		player->set_Info()->pos.center.x -= PLAYER_SPEED;
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		player->set_Info()->pos.center.x += PLAYER_SPEED;
	}

	// 만약 땅에 닿았으면 추락 상태에서 빠져나간다.
	if (player->get_Info().pos.center.y - player->get_Info().jump.jump_Value > CAMERAMANAGER->Use_Func()->get_World_Size().y - 200)
	{
		player->set_Info()->pos.center.y -= (player->get_Info().pos.center.y - player->get_Info().jump.jump_Value) - (CAMERAMANAGER->Use_Func()->get_World_Size().y - 200);

		// 카메라 위치 갱신
		CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

		// 렉트 갱신
		player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		player->update_Ani_Rect();

		// 나가기 전에 새 연산을 위해 모두 초기화
		player->set_Info()->bool_V.idle_Cheack = false;
		player->set_Info()->bool_V.walk_Cheack = false;
		player->set_Info()->bool_V.walking_Cheack = false;
		player->set_Info()->bool_V.jump_Cheack = false;
		player->set_Info()->bool_V.jumping_Cheack = false;
		player->set_Info()->bool_V.fall_Cheack = false;
		player->set_Info()->bool_V.falling_Cheack = false;
		player->set_Info()->jump.jump_Value = 0;

		// 점프 수치 초기화
		player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;

		// Idle 애니메이션 교체를 위해 호출
		Idle(player);
	}

	// 추락연산
	player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

	// 점프 수치를 중력만큼 뺀다. (최대 추락 속도보다 클때만)
	if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED)
	{
		player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;
	}

	// 만약 방향키를 땠다면 더 이상 이동하지 않는다.
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		// 이동중이 아니라면 false
		player->set_Info()->bool_V.walking_Cheack = false;

		// 다른 방향을 입력 시 추락 애니메이션 교체를 위해 false로
		player->set_Info()->bool_V.fall_Cheack = false;

		// 이동이 끝났으니 다른 연산을 위해 Fall 함수 호출
		Fall(player);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		// 이동중이 아니라면 false
		player->set_Info()->bool_V.walking_Cheack = false;

		// 다른 방향을 입력 시 추락 애니메이션 교체를 위해 false로
		player->set_Info()->bool_V.fall_Cheack = false;

		// 이동이 끝났으니 다른 연산을 위해 Fall 함수 호출
		Fall(player);
	}

	// 점프키를 다시 눌렀다면 (점프 횟수가 남아있다면)
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (player->get_Info().jump.Jump_Count > 0)
		{
			// 점프 카운트를 감소 시켜주고, 점프 수치 회복
			player->set_Info()->jump.Jump_Count--;
			player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

			// 점프 애니메이션 교체를 위해 호출
			Jump(player);
		}
	}


	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void FallState::Jump(Player * player)
{
	// 방향에 따라서 맞는 점프 애니메이션으로 바꿔준다.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// 애니메이션 교체 + 시작
		player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
		player->set_Info()->img.ani->start();

		// 점프 애니메이션을 바꿨다면 true (중복 교체 방지)
		player->set_Info()->bool_V.jump_Cheack = true;

		// 점프중으로 바꿔준다.
		player->set_Info()->bool_V.jumping_Cheack = true;

		// 추락중이 아니므로 flase
		player->set_Info()->bool_V.falling_Cheack = false;

		// 점프 상태로 바꿔준다.
		player->set_State(JumpState::getInstance());
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// 애니메이션 교체 + 시작
		player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
		player->set_Info()->img.ani->start();

		// 점프 애니메이션을 바꿨다면 true (중복 교체 방지)
		player->set_Info()->bool_V.jump_Cheack = true;

		// 점프중으로 바꿔준다.
		player->set_Info()->bool_V.jumping_Cheack = true;

		// 추락중이 아니므로 flase
		player->set_Info()->bool_V.falling_Cheack = false;

		// 점프 상태로 바꿔준다.
		player->set_State(JumpState::getInstance());
	}
}

void FallState::Fall(Player * player)
{
	// 추락 루프 애니메이션으로 교체하는 시점 (스컬 추락 애니메이션 중에만)
	if (player->get_Info().img.imgName == "skul_Fall")
	{

		// 프레임이 2로 변하는 시점 (프레임가로의 크기가 160이므로, 0 = 0, 160 = 1, 320 = 2로 프레임 위치를 가리킨다.)
		if (player->get_Info().img.ani->getFramePos().x == 320)
		{
			// 망토가 계속 펄럭거려야 하기 때문에 루프 애니메이션으로 교체한다.
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

	// 이동중이라면 이동 연산을 한다.
	if (player->get_Info().bool_V.walking_Cheack) Move(player);

	// 이동중이 아니라면
	if (!player->get_Info().bool_V.walking_Cheack)
	{
		// 방향키를 누른다면
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			// 해당 방향키 저장
			player->set_InputKey(PRESS_LEFT);

			// 해당 방향으로 애니메이션 교체
			player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
			player->set_Info()->img.ani->start();

			// 이동중이라면 true
			player->set_Info()->bool_V.walking_Cheack = true;

			// 이동 + 추락 연산을 위해 Jall함수 다시 호출
			Fall(player);
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// 해당 방향키 저장
			player->set_InputKey(PRESS_RIGHT);

			// 해당 방향으로 애니메이션 교체
			player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
			player->set_Info()->img.ani->start();

			// 이동중이라면 true
			player->set_Info()->bool_V.walking_Cheack = true;

			// 이동 + 추락 연산을 위해 Jall함수 다시 호출
			Fall(player);
		}

		// 점프키를 다시 눌렀다면 (점프 횟수가 남아있다면)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// 점프 카운트를 감소 시켜주고, 점프 수치 회복
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

				// 점프 애니메이션 교체를 위해 호출
				Jump(player);
			}
		}
		
		// 만약 땅에 닿았으면 추락 상태에서 빠져나간다.
		if (player->get_Info().pos.center.y - player->get_Info().jump.jump_Value > (CAMERAMANAGER->Use_Func()->get_World_Size().y - 200))
		{
			player->set_Info()->pos.center.y -= (player->get_Info().pos.center.y - player->get_Info().jump.jump_Value) - (CAMERAMANAGER->Use_Func()->get_World_Size().y - 200);

			// 카메라 위치 갱신
			CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

			// 렉트 갱신
			player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
			player->update_Ani_Rect();

			// 나가기 전에 새 연산을 위해 모두 초기화
			player->set_Info()->bool_V.idle_Cheack = false;
			player->set_Info()->bool_V.walk_Cheack = false;
			player->set_Info()->bool_V.walking_Cheack = false;
			player->set_Info()->bool_V.jump_Cheack = false;
			player->set_Info()->bool_V.jumping_Cheack = false;
			player->set_Info()->bool_V.fall_Cheack = false;
			player->set_Info()->bool_V.falling_Cheack = false;
			player->set_Info()->jump.jump_Value = 0;

			// 점프 수치 초기화
			player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;

			// Idle 애니메이션 교체를 위해 호출
			Idle(player);
		}

		// 추락연산
		player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;

		// 점프 수치를 중력만큼 뺀다. (최대 추락 속도보다 클때만)
		if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED)
		{
			player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;
		}

	}

	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void FallState::update(Player * player)
{
	Fall(player);

	KEYANIMANAGER->update();
}
