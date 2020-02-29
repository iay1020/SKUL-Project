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


// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 대기 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 만약 true의 값이라면 애니메이션 교체 스타트
	if (player->get_Info().bool_V.now_Ani_Change)
	{
		player->set_Info()->ani_Changer("Idle", player->get_InputKey());
		player->set_Info()->img.ani->start();

		player->set_Info()->bool_V.now_Ani_Change = false;
	}

	// 플레이어의 아래에 땅 타일이 없다면 추락 상태로 바꿔준다.
	if (!DATAMANAGER->Collision_PlayerFall_Ground())
	{
		IdleState::Fall(player);  // 추락함수 호출
	}

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

	// 멈춰있는 상태에서 아래 방향키와 점프를 눌렀다면 아래 점프를 시작한다.
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{

		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			// 아래 타일이 발판일때만
			if (DATAMANAGER->Collision_Player_FootHold_Down())
			{
				// 살짝 점프를 하기 때문에 점프 수치를 조금 넣어준다.
				player->set_Info()->jump.jump_Value = PLAYER_DOWNJUMPPOWER;

				// 점프, 추락 애니메이션으로 교체를 위해 false로 바꿔준다.
				player->set_Info()->bool_V.jump_Cheack = false;
				player->set_Info()->bool_V.fall_Cheack = false;

				// 아래점프 상태로 이동 한다.
				IdleState::DownJump(player);

			}
		}
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

		// 점프 이펙트를 만들어준다.
		DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Jump_Effect", "skul_Jump_Ani_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

		// Jump함수 호출
		IdleState::Jump(player);
	}


	// 멈춰있는 상태에서 스킬을 눌렀다면 스킬 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
	{
		// 스킬 A의 애니메이션으로 교체 해준다.
		IdleState::Skill_A(player);
	}

	if (KEYMANAGER->isOnceKeyDown('S'))
	{

	}


	// 멈춰있는 상태에서 공격키를 누른다면 공격 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// 공격 A의 애니메이션으로 교체 해준다.
		IdleState::Attack_A(player);
	}


	// 멈춰있는 상태에서 대쉬를 눌렀다면 대쉬 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		// 대쉬 횟수가 있다면 실행한다. ( 횟수가 하나라도 있다면)
		if (player->get_Info().dash.Dash_Count > 0)
		{
			// 대쉬 횟수 감소
			player->set_Info()->dash.Dash_Count--;
	
			// 대쉬 시작 시간 저장
			player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
	
			// 대쉬중이라면 true로 바꾼다.
			player->set_Info()->bool_V.dashing_Cheack = true;
	
			// 대쉬 애니메이션 교체를 해야 하니까 false로
			player->set_Info()->bool_V.dash_Cheack = false;

			// 대쉬 이펙트를 만들어 준다.
			if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect","skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
			if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
	
			// 애니메이션 교체와 상태 변환을 위해 Dash 함수 호출
			IdleState::Dash(player);
		}
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
			player->set_Info()->ani_Changer("Move", player->get_InputKey());

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
			player->set_Info()->ani_Changer("Move", player->get_InputKey());

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
		// 애니메이션 교체
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());

		player->set_Info()->img.ani->start();
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// 애니메이션 교체
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());

		player->set_Info()->img.ani->start();
	}

	// 상태를 다시 점프 상태로 교체
	player->set_State(JumpState::getInstance());
	player->get_State()->update(player);
}

void IdleState::Fall(Player * player)
{
	// 캐릭터의 방향에 따라 추락 애니메이션을 넣어주고 추락 상태로 교체해준다.
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

	// 추락상태 교체
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void IdleState::DownJump(Player * player)
{
	// 점프 애니메이션으로 교체 한다.
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
	
	// 아래 점프 상태로 이동한다.
	player->set_State(DownJumpState::getInstance());
	player->get_State()->update(player);
}

void IdleState::Dash(Player * player)
{
	// 방향에 맞는 대쉬 애니메이션으로 교체해준다.
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

	// 애니메이션 교체가 끝났다면 Dash 상태로 바꿔준다.
	player->set_State(DashState::getInstance());
	player->get_State()->update(player);
}

void IdleState::JumpAttack(Player * player)
{
}

void IdleState::Attack_A(Player * player)
{
	// 공격 A 애니메이션으로 교체
	player->set_Info()->ani_Changer("Attack_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 공격 A 상태로 교체해준다.
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

	// 스킬 A의 애니메이션으로 교체
	player->set_Info()->ani_Changer("Skill_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 스킬 A 상태로 교체 
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





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 이동 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
			player->set_Info()->ani_Changer("Idle", player->get_InputKey());
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
			player->set_Info()->ani_Changer("Idle", player->get_InputKey());
			player->set_Info()->img.ani->start();

			// 애니메이션 교체 후 true (1번만 바꾸기 위해)
			player->set_Info()->bool_V.idle_Cheack = true;
		}
	}

	// 상태를 대기로 바꿔준다.
	player->set_State(IdleState::getInstance());
	player->get_State()->update(player);
}

void MoveState::Move(Player * player)
{
	// 만약 true의 값이라면 애니메이션 교체 스타트
	if (player->get_Info().bool_V.now_Ani_Change)
	{
		player->set_Info()->ani_Changer("Move", player->get_InputKey());
		player->set_Info()->img.ani->start();

		player->set_Info()->bool_V.now_Ani_Change = false;
	}

	// 플레이어의 아래에 땅 타일이 없다면 추락 상태로 바꿔준다.
	if (!DATAMANAGER->Collision_PlayerFall_Ground())
	{
		MoveState::Fall(player);  // 추락함수 호출
	}

	if (player->get_InputKey() == PRESS_LEFT)
	{
		// 캐릭터 옆에 벽이 없어야 실행
		if (!DATAMANAGER->Collision_Player_Wall())
		{
			// 플레이어가 왼쪽으로 이동 (이동중이라면)
			if (player->get_Info().bool_V.walking_Cheack)  player->set_Info()->pos.center.x -= PLAYER_SPEED;
		}

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

				// 점프 이펙트를 만들어준다.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Jump_Effect", "skul_Jump_Ani_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);


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

		// 이동 상태에서 대쉬를 눌렀다면 대쉬 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			// 대쉬 횟수가 있다면 실행한다. ( 횟수가 하나라도 있다면)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// 대쉬 횟수 감소
				player->set_Info()->dash.Dash_Count--;
		
				// 대쉬 시작 시간 저장
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// 대쉬중이라면 true로 바꾼다.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// 대쉬 애니메이션 교체를 해야 하니까 false로
				player->set_Info()->bool_V.dash_Cheack = false;

				// 대쉬 이펙트를 만들어 준다.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// 애니메이션 교체와 상태 변환을 위해 Dash 함수 호출
				MoveState::Dash(player);
			}
		}

		// 이동 상태에서 공격을 눌렀다면 공격 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			MoveState::Attack_A(player);
		}

		// 이동 상태에서 스킬 A키를 눌렀다면, 스킬 애니메이션으로 교체한다.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			MoveState::Skill_A(player);
		}
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// 캐릭터 옆에 벽이 없어야 실행
		if (!DATAMANAGER->Collision_Player_Wall())
		{
			// 플레이어가 오른쪽으로 이동 (이동중이라면)
			if (player->get_Info().bool_V.walking_Cheack) player->set_Info()->pos.center.x += PLAYER_SPEED;
		}

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

				// 점프 이펙트를 만들어준다.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Jump_Effect", "skul_Jump_Ani_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

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

		// 이동 상태에서 대쉬를 눌렀다면 대쉬 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			
			// 대쉬 횟수가 있다면 실행한다. ( 횟수가 하나라도 있다면)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// 대쉬 횟수 감소
				player->set_Info()->dash.Dash_Count--;
		
				// 대쉬 시작 시간 저장
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// 대쉬중이라면 true로 바꾼다.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// 대쉬 애니메이션 교체를 해야 하니까 false로
				player->set_Info()->bool_V.dash_Cheack = false;

				// 대쉬 이펙트를 만들어 준다.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// 애니메이션 교체와 상태 변환을 위해 Dash 함수 호출
				MoveState::Dash(player);
			}
		}

		// 이동 상태에서 공격을 눌렀다면 공격 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			MoveState::Attack_A(player);
		}

		// 이동 상태에서 스킬 A키를 눌렀다면, 스킬 애니메이션으로 교체한다.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			MoveState::Skill_A(player);
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
			//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
			player->set_Info()->ani_Changer("Jump", player->get_InputKey());
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
			//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
			player->set_Info()->ani_Changer("Jump", player->get_InputKey());
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
	// 캐릭터의 방향에 따라 추락 애니메이션을 넣어주고 추락 상태로 교체해준다.
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

	// 추락상태 교체
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void MoveState::DownJump(Player * player)
{
}

void MoveState::Dash(Player * player)
{
	// 방향에 맞는 대쉬 애니메이션으로 교체해준다.
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

	// 애니메이션 교체가 끝났다면 Dash 상태로 바꿔준다.
	player->set_State(DashState::getInstance());
	player->get_State()->update(player);

}

void MoveState::JumpAttack(Player * player)
{
}

void MoveState::Attack_A(Player * player)
{
	// 공격 A 애니메이션으로 교체 
	player->set_Info()->ani_Changer("Attack_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 공격 A 상태로 바꿔준다.
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

	// 스킬 A의 애니메이션으로 교체
	player->set_Info()->ani_Changer("Skill_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 스킬 A 상태로 교체 
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




// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 점프 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
		// 캐릭터 옆에 벽이 없어야 실행
		if (!DATAMANAGER->Collision_Player_Wall())
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
		}

		// 점프 연산을 해준다.
		// 점프 연산을 시작한다. 점프 수치가 0 이상일때만
		if (player->get_Info().jump.jump_Value > 0)
		{
			// 점프 수치만큼 캐릭터의 y좌표를 뺀다.
			if (!DATAMANAGER->Collision_PlayerJump_Ground())
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
			JumpState::Jump(player);
		}

		// 점프키를 다시 눌렀다면 (점프 횟수가 남아있다면)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// 점프 이펙트를 만들어준다.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Double_Jump_Effect", "skul_Double_Jump_Ani_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

				// 점프 카운트를 감소 시켜주고, 점프 수치 회복
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;
			}
		}

		// 점프 상태에서 대쉬를 눌렀다면 대쉬 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			
			// 대쉬 횟수가 있다면 실행한다. ( 횟수가 하나라도 있다면)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// 대쉬 횟수 감소
				player->set_Info()->dash.Dash_Count--;
		
				// 대쉬 시작 시간 저장
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// 대쉬중이라면 true로 바꾼다.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// 대쉬 애니메이션 교체를 해야 하니까 false로
				player->set_Info()->bool_V.dash_Cheack = false;

				// 대쉬 이펙트를 만들어 준다.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// 애니메이션 교체와 상태 변환을 위해 Dash 함수 호출
				JumpState::Dash(player);
			}
		}

		// 점프 상태에서 공격을 눌렀다면 점프 공격 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			// 애니메이션 교체를 위해 JumpAttack 함수 호출
			JumpState::JumpAttack(player);
		}

		// 이동 상태에서 스킬 A키를 눌렀다면, 스킬 애니메이션으로 교체한다.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			JumpState::Skill_A(player);
		}
	}
}

void JumpState::Jump(Player * player)
{
	// 만약 true의 값이라면 애니메이션 교체 스타트
	if (player->get_Info().bool_V.now_Ani_Change)
	{
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());
		player->set_Info()->img.ani->start();

		player->set_Info()->bool_V.now_Ani_Change = false;
	}

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
			//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
			player->set_Info()->ani_Changer("Jump", player->get_InputKey());

			// 이동중이라면 true
			player->set_Info()->bool_V.walking_Cheack = true;

			// 이동 + 점프 연산을 위해 Move 호출
			JumpState::Move(player);
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// 입력키 저장
			player->set_InputKey(PRESS_RIGHT);

			// 방향에 맞는 애니메이션으로 교체
			//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
			player->set_Info()->ani_Changer("Jump", player->get_InputKey());

			// 이동중이라면 true
			player->set_Info()->bool_V.walking_Cheack = true;

			// 이동 + 점프 연산을 위해 Move 호출
			JumpState::Move(player);
		}

		// 점프키를 다시 눌렀다면 (점프 횟수가 남아있다면)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{
			if (player->get_Info().jump.Jump_Count > 0)
			{
				// 점프 이펙트를 만들어준다.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Double_Jump_Effect", "skul_Double_Jump_Ani_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

				// 점프 카운트를 감소 시켜주고, 점프 수치 회복
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;
			}
		}

		// 점프 상태에서 대쉬를 눌렀다면 대쉬 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
			
			// 대쉬 횟수가 있다면 실행한다. ( 횟수가 하나라도 있다면)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// 대쉬 횟수 감소
				player->set_Info()->dash.Dash_Count--;
		
				// 대쉬 시작 시간 저장
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// 대쉬중이라면 true로 바꾼다.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// 대쉬 애니메이션 교체를 해야 하니까 false로
				player->set_Info()->bool_V.dash_Cheack = false;

				// 대쉬 이펙트를 만들어 준다.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// 애니메이션 교체와 상태 변환을 위해 Dash 함수 호출
				JumpState::Dash(player);
			}
		}

		// 점프 상태에서 공격을 눌렀다면 점프 공격 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			// 애니메이션 교체를 위해 JumpAttack 함수 호출
			JumpState::JumpAttack(player);
		}

		// 이동 상태에서 스킬 A키를 눌렀다면, 스킬 애니메이션으로 교체한다.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			JumpState::Skill_A(player);
		}

		// 점프 연산을 시작한다. 점프 수치가 0 이상일때만
		if (player->get_Info().jump.jump_Value > 0)
		{
			// 점프 수치만큼 캐릭터의 y좌표를 뺀다.
			if (!DATAMANAGER->Collision_PlayerJump_Ground())
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

	// 추락 상태로 이동한다.
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void JumpState::DownJump(Player * player)
{
}

void JumpState::Dash(Player * player)
{
	// 방향에 맞는 대쉬 애니메이션으로 교체해준다.
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

	// 애니메이션 교체가 끝났다면 Dash 상태로 바꿔준다.
	player->set_State(DashState::getInstance());
	player->get_State()->update(player);
}

void JumpState::JumpAttack(Player * player)
{
	// 점프어택 애니메이션으로 교체해준다.
	player->set_Info()->ani_Changer("JumpAttack", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 점프어택 상태로 바꿔준다.
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

	// 스킬 A의 애니메이션으로 교체
	player->set_Info()->ani_Changer("Skill_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 스킬 A 상태로 교체 
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





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 추락 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
			//player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
			player->set_Info()->ani_Changer("Idle", player->get_InputKey());
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
			//player->set_Info()->set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
			player->set_Info()->ani_Changer("Idle", player->get_InputKey());
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
	// 캐릭터 옆에 벽이 없어야 실행
	if (!DATAMANAGER->Collision_Player_Wall())
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
	}

	// 만약 땅에 닿았으면 추락 상태에서 빠져나간다.

	if (DATAMANAGER->Collision_PlayerFall_Ground())
	{
		//// 카메라 위치 갱신
		CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);
		
		// 렉트 갱신
		player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		player->update_Ani_Rect();
		
		// 나가기 전에 새 연산을 위해 모두 초기화
		//player->set_Info()->bool_Value_Reset();
		player->set_Info()->bool_State_Reset();

		player->set_Info()->jump.jump_Value = 0;
		
		// 점프 수치 초기화
		player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;
		
		// Idle 애니메이션 교체를 위해 호출
		FallState::Idle(player);
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
		FallState::Fall(player);
	}

	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		// 이동중이 아니라면 false
		player->set_Info()->bool_V.walking_Cheack = false;

		// 다른 방향을 입력 시 추락 애니메이션 교체를 위해 false로
		player->set_Info()->bool_V.fall_Cheack = false;

		// 이동이 끝났으니 다른 연산을 위해 Fall 함수 호출
		FallState::Fall(player);
	}

	// 점프키를 다시 눌렀다면 (점프 횟수가 남아있다면)
	if (KEYMANAGER->isOnceKeyDown('C'))
	{

		if (player->get_Info().jump.Jump_Count > 0)
		{
			// 점프 이펙트를 만들어준다.
			DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Double_Jump_Effect", "skul_Double_Jump_Ani_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

			// 점프 카운트를 감소 시켜주고, 점프 수치 회복
			player->set_Info()->jump.Jump_Count--;
			player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

			// 점프 애니메이션 교체를 위해 호출
			FallState::Jump(player);
		}
	}

	// 추락 상태에서 대쉬를 눌렀다면 대쉬 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
	
		// 대쉬 횟수가 있다면 실행한다. ( 횟수가 하나라도 있다면)
		if (player->get_Info().dash.Dash_Count > 0)
		{
			// 추락 상태에서 대쉬를 사용하면 추락 수치가 감소한다.
			player->set_Info()->jump.jump_Value = 0;
	
			// 대쉬 횟수 감소
			player->set_Info()->dash.Dash_Count--;
	
			// 대쉬 시작 시간 저장
			player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
	
			// 대쉬중이라면 true로 바꾼다.
			player->set_Info()->bool_V.dashing_Cheack = true;
	
			// 대쉬 애니메이션 교체를 해야 하니까 false로
			player->set_Info()->bool_V.dash_Cheack = false;

			// 대쉬 이펙트를 만들어 준다.
			if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
			if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
	
			// 애니메이션 교체와 상태 변환을 위해 Dash 함수 호출
			FallState::Dash(player);
		}
	}

	// 추락 상태에서 공격키를 누르면 점프 공격 상태로 바꿔준다.
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		// 점프 공격 애니메이션으로 바꾸기 위해 함수 호출
		FallState::JumpAttack(player);
	}

	// 이동 상태에서 스킬 A키를 눌렀다면, 스킬 애니메이션으로 교체한다.
	if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
	{
		FallState::Skill_A(player);
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
		//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());

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
		//player->set_Info()->set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
		player->set_Info()->ani_Changer("Jump", player->get_InputKey());

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
	// 만약 true의 값이라면 애니메이션 교체 스타트
	if (player->get_Info().bool_V.now_Ani_Change)
	{
		player->set_Info()->ani_Changer("Fall", player->get_InputKey());
		player->set_Info()->img.ani->start();

		player->set_Info()->bool_V.now_Ani_Change = false;
	}

	// 추락 루프 애니메이션으로 교체하는 시점 (스컬 추락 애니메이션 중에만)
	if (player->get_Info().img.imgName == "skul_Fall" ||
		player->get_Info().img.imgName == "skul_Fall_NoHead")
	{

		// 프레임이 2로 변하는 시점 (프레임가로의 크기가 160이므로, 0 = 0, 160 = 1, 320 = 2로 프레임 위치를 가리킨다.)
		if (player->get_Info().img.ani->getFramePos().x >= 320)
		{
			// 망토가 계속 펄럭거려야 하기 때문에 루프 애니메이션으로 교체한다.
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
			//player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
			player->set_Info()->ani_Changer("Falling", player->get_InputKey());
			player->set_Info()->img.ani->start();
			
			// 캐릭터 옆에 벽이 없어야 실행
			if (!DATAMANAGER->Collision_Player_Wall())
			{
				// 이동중이라면 true
				player->set_Info()->bool_V.walking_Cheack = true;

				// 이동 + 추락 연산을 위해 Jall함수 다시 호출
				FallState::Fall(player);
			}
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			// 해당 방향키 저장
			player->set_InputKey(PRESS_RIGHT);

			// 해당 방향으로 애니메이션 교체
			//player->set_Info()->set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
			player->set_Info()->ani_Changer("Falling", player->get_InputKey());
			player->set_Info()->img.ani->start();

			// 캐릭터 옆에 벽이 없어야 실행
			if (!DATAMANAGER->Collision_Player_Wall())
			{
				// 이동중이라면 true
				player->set_Info()->bool_V.walking_Cheack = true;

				// 이동 + 추락 연산을 위해 Jall함수 다시 호출
				FallState::Fall(player);
			}
		}

		// 점프키를 다시 눌렀다면 (점프 횟수가 남아있다면)
		if (KEYMANAGER->isOnceKeyDown('C'))
		{

			if (player->get_Info().jump.Jump_Count > 0)
			{
				// 점프 이펙트를 만들어준다.
				DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Double_Jump_Effect", "skul_Double_Jump_Ani_Effect", EffectType::DOUBLE_JUMP, player->get_Info().pos.center.x, player->get_Info().pos.center.y);

				// 점프 카운트를 감소 시켜주고, 점프 수치 회복
				player->set_Info()->jump.Jump_Count--;
				player->set_Info()->jump.jump_Value = PLAYER_JUMPPOWER;

				// 점프 애니메이션 교체를 위해 호출
				FallState::Jump(player);
			}
		}

		// 추락 상태에서 대쉬를 눌렀다면 대쉬 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('Z'))
		{
		
			// 대쉬 횟수가 있다면 실행한다. ( 횟수가 하나라도 있다면)
			if (player->get_Info().dash.Dash_Count > 0)
			{
				// 추락 상태에서 대쉬를 사용하면 추락 수치가 감소한다.
				player->set_Info()->jump.jump_Value = 0;
		
				// 대쉬 횟수 감소
				player->set_Info()->dash.Dash_Count--;
		
				// 대쉬 시작 시간 저장
				player->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();
		
				// 대쉬중이라면 true로 바꾼다.
				player->set_Info()->bool_V.dashing_Cheack = true;
		
				// 대쉬 애니메이션 교체를 해야 하니까 false로
				player->set_Info()->bool_V.dash_Cheack = false;

				// 대쉬 이펙트를 만들어 준다.
				if (player->get_InputKey() == PRESS_LEFT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Left_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
				if (player->get_InputKey() == PRESS_RIGHT)	DATAMANAGER->effect_Maker_Address()->Create_Effect("skul_Dash_Effect", "skul_Dash_Right_Effect", EffectType::DASH, player->get_Info().pos.center.x, player->get_Info().pos.center.y - 10);
		
				// 애니메이션 교체와 상태 변환을 위해 Dash 함수 호출
				FallState::Dash(player);
			}
		}

		// 추락 상태에서 공격키를 누르면 점프 공격 상태로 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown('X'))
		{
			// 점프 공격 애니메이션으로 바꾸기 위해 함수 호출
			FallState::JumpAttack(player);
		}

		// 이동 상태에서 스킬 A키를 눌렀다면, 스킬 애니메이션으로 교체한다.
		if (KEYMANAGER->isOnceKeyDown('A') && !player->get_Info().bool_V.useing_Skill_A)
		{
			FallState::Skill_A(player);
		}
		
		// 만약 땅에 닿았으면 추락 상태에서 빠져나간다.
		if (DATAMANAGER->Collision_PlayerFall_Ground())
		{

			// 카메라 위치 갱신
			CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

			// 렉트 갱신
			player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
			player->update_Ani_Rect();

			// 나가기 전에 새 연산을 위해 모두 초기화
			//player->set_Info()->bool_Value_Reset();
			player->set_Info()->bool_State_Reset();

			player->set_Info()->jump.jump_Value = 0;

			// 점프 수치 초기화
			player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;

			// Idle 애니메이션 교체를 위해 호출
			FallState::Idle(player);
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

void FallState::DownJump(Player * player)
{
}

void FallState::Dash(Player * player)
{
	// 방향에 맞는 대쉬 애니메이션으로 교체해준다.
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

	// 애니메이션 교체가 끝났다면 Dash 상태로 바꿔준다.
	player->set_State(DashState::getInstance());
	player->get_State()->update(player);
}

void FallState::JumpAttack(Player * player)
{
	// 점프어택 애니메이션으로 교체해준다.
	player->set_Info()->ani_Changer("JumpAttack", player->get_InputKey());
	player->set_Info()->img.ani->start();


	// 점프어택 상태로 바꿔준다.
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

	// 스킬 A의 애니메이션으로 교체
	player->set_Info()->ani_Changer("Skill_A", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 스킬 A 상태로 교체 
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





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 아래 점프 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 점프 수치만큼 캐릭터를 위로 올려주고, 중력만큼 수치를 감소한다.
	player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;
	player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

}

void DownJumpState::Fall(Player * player)
{
	// 추락 애니메이션 교체
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

	// 점프 수치만큼 아래로 떨어진다.
	player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;
	player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

	// 만약 위에 위치한 발판 렉트를 지나면 추락 상태로 바꿔준다.
	if (DATAMANAGER->Collision_Player_FootHold())
	{
		// 추락 상태로 변경
		player->set_State(FallState::getInstance());
		player->get_State()->update(player);
	}
}

void DownJumpState::DownJump(Player * player)
{
	// 점프 수치가 남아있다면 점프 연산을 한다.
	if (player->get_Info().jump.jump_Value > 0)	Jump(player);

	// 아래로 떨어진다.
	if (player->get_Info().jump.jump_Value <= 0) Fall(player);

	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
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






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 대쉬 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 대기 애니메이션으로 교체 후 대기 상태로 이동
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
	// 방향에 맞는 추락 이미지를 넣어준다.
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

	// 추락 상태로 이동한다.
	player->set_State(FallState::getInstance());
	player->get_State()->update(player);
}

void DashState::DownJump(Player * player)
{
}

void DashState::Dash(Player * player)
{
	// 대쉬중일때만 실행
	if (player->get_Info().bool_V.dashing_Cheack) DATAMANAGER->Lerp_Player();

	// 대쉬중이 아닐때
	if (!player->get_Info().bool_V.dashing_Cheack)
	{
		// 아래 땅이 없다면 추락 함수 호출
		if (!DATAMANAGER->Collision_PlayerFall_Ground())
		{
			DashState::Fall(player);
		}
		
		// 아래 땅이 있다면 대기 함수 호출
		if (DATAMANAGER->Collision_PlayerFall_Ground())
		{
			player->set_Info()->bool_V.idle_Cheack = false;
		
			// 점프 수치 초기화
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




// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 점프 어택 상태! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 공격렉트 초기화
	player->set_Info()->pos.Attack_RC = { 0,0,0,0 };

	// 대기 애니메이션으로 교체한다.
	player->set_Info()->ani_Changer("Idle", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 사용 한 변수 초기화
	player->set_Info()->jump.jump_Value = 0;
	player->set_Info()->jump.Jump_Count = player->get_Info().jump.Jump_Count_Save;
	player->set_Info()->jump.jump_Attack_Count = 0;

	player->set_Info()->bool_Value_Reset();

	// 대기 상태로 교체
	player->set_State(IdleState::getInstance());
	player->get_State()->update(player);
}

void JumpAttackState::Move(Player * player)
{
	if (player->get_Info().jump.jump_Value < 0)
	{
		player->set_Info()->bool_V.jumping_Cheack = false;
		player->set_Info()->bool_V.falling_Cheack = true;

		// 아래에 타일이 있으면 추락을 멈추고 대기 애니메이션으로 바꿔준다.
		if (DATAMANAGER->Collision_PlayerFall_Ground() &&
			player->get_Info().bool_V.falling_Cheack &&
			!player->get_Info().bool_V.jumping_Cheack) Idle(player);
	}

	// 만약 방향키를 땠을 경우에는 이동 bool 값을 false로
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		player->set_Info()->bool_V.walking_Cheack = false;

		JumpAttackState::JumpAttack(player);
	}

	// 방향키에 맞게 플레이어를 이동시켜준다.
	if (player->get_InputKey() == PRESS_LEFT)
	{
		// 벽이 있으면 이동하지 않도록 한다.
		if (!DATAMANAGER->Collision_Player_Wall()) player->set_Info()->pos.center.x -= PLAYER_SPEED;
	}

	if (player->get_InputKey() == PRESS_RIGHT)
	{
		// 벽이 있으면 이동하지 않도록 한다.
		if (!DATAMANAGER->Collision_Player_Wall()) player->set_Info()->pos.center.x += PLAYER_SPEED;
	}

	player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;
	if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED) player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();
}

void JumpAttackState::Jump(Player * player)
{
}

void JumpAttackState::Fall(Player * player)
{
	// 공격 렉트 초기화
	player->set_Info()->pos.Attack_RC = { 0, 0, 0, 0 };

	// 점프어택 카운트 초기화
	player->set_Info()->jump.jump_Attack_Count = 0;

	// 추락중 애니메이션으로 바꿔준다.
	player->set_Info()->ani_Changer("Falling", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 추락 상태로 바꿔준다.
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

		// 아래에 타일이 있으면 추락을 멈추고 대기 애니메이션으로 바꿔준다.
		if (DATAMANAGER->Collision_PlayerFall_Ground() &&
			player->get_Info().bool_V.falling_Cheack &&
			!player->get_Info().bool_V.jumping_Cheack) Idle(player);
	}

	// 만약 이동중이라면
	if (player->get_Info().bool_V.walking_Cheack) Move(player);

	// 이동중이지 않다면 그냥 추락 연산만
	if (!player->get_Info().bool_V.walking_Cheack)
	{
		// 만약 이동키를 눌렀을 경우에는 bool값을 바꿔준다.
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			player->set_InputKey(PRESS_LEFT);

			player->set_Info()->bool_V.walking_Cheack = true;

			// 이동을 같이 해야 하기 때문에 재호출
			JumpAttackState::JumpAttack(player);
		}

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			player->set_InputKey(PRESS_RIGHT);

			player->set_Info()->bool_V.walking_Cheack = true;

			// 이동을 같이 해야 하기 때문에 재호출
			JumpAttackState::JumpAttack(player);
		}

		player->set_Info()->pos.center.y -= player->get_Info().jump.jump_Value;
		if (player->get_Info().jump.jump_Value > PLAYER_MAX_FALL_SPEED) player->set_Info()->jump.jump_Value -= PLAYER_GRAVITY;

		// 카메라 위치 갱신
		CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

		// 렉트 갱신
		player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		player->update_Ani_Rect();
	}

	// 점프 공격 인터벌용
	player->set_Info()->jump.jump_Attack_Count++;

	// 공격 렉트를 만들어준다.
	if (player->get_InputKey() == PRESS_LEFT && player->get_Info().img.ani->getFramePos().x == 320)		player->set_Info()->create_Attack_Rect(player->get_InputKey());
	else if (player->get_InputKey() == PRESS_RIGHT && player->get_Info().img.ani->getFramePos().x == 160)	player->set_Info()->create_Attack_Rect(player->get_InputKey());
	else player->set_Info()->pos.Attack_RC = { 0,0,0,0 };

	// 점프 공격을 시작하면 일정 시간이 지난 후 추락중 애니메이션으로 바뀐다.
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





// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 기본공격 A! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 공격 렉트 초기화
	player->set_Info()->pos.Attack_RC = { 0, 0, 0, 0 };

	// 다음 공격을 위해 공격 bool 초기화
	player->set_Info()->bool_V.Attack_Success = false;

	// 사용했던 변수 초기화
	player->set_Info()->bool_State_Reset();

	// 대기 애니메이션을 넣어준다.
	player->set_Info()->ani_Changer("Idle", player->get_InputKey());
	player->get_Info().img.ani->start();

	// 대기 상태로 바꿔준다.
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
	// 만약 이동중인 bool 값이 켜져있다면 조금 움직인다.
	if (player->get_Info().bool_V.walking_Cheack)
	{
		if (player->get_InputKey() == PRESS_LEFT)
		{
			player->set_Info()->pos.center.x -= PLAYER_SPEED * 3;

			// 한번만 움직여야하기 때문에 false로 바꿔준다.
			player->set_Info()->bool_V.walking_Cheack = false;
		}

		if (player->get_InputKey() == PRESS_RIGHT)
		{
			player->set_Info()->pos.center.x += PLAYER_SPEED * 3;

			// 한번만 움직여야하기 때문에 false로 바꿔준다.
			player->set_Info()->bool_V.walking_Cheack = false;
		}

		// 카메라 위치 갱신
		CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

		// 렉트 갱신
		player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		player->update_Ani_Rect();
	}

	// 만약 공격 A를 실행시키고 있는 도중에 X키를 눌렀다면 (+ 아직 Attack_B의 bool값이 true가 안됐을때)
	{
		if (KEYMANAGER->isOnceKeyDown('X') && !player->get_Info().bool_V.next_Attack_B)
		{
			player->set_Info()->bool_V.next_Attack_B = true;
		}
	}

	// 일정 공격 프레임일때 렉트 생성 그 외 프레임일땐 삭제
	if (player->get_Info().img.ani->getFramePos().x == 2 * 160)
	{
		// 공격 렉트를 만들어준다.
		player->set_Info()->create_Attack_Rect(player->get_InputKey());
	}
	else player->set_Info()->pos.Attack_RC = { 0,0,0,0 };


	// 공격 애니메이션의 마지막 프레임일때
	if (player->get_Info().img.ani->getFramePos().x == 640)
	{
		// 만약 공격 B의 bool값이 켜져 있다면 공격 B 애니메이션으로 교체 하러 간다.
		if(player->get_Info().bool_V.next_Attack_B) Attack_B(player);
	
		// 아니라면 대기 애니메이션을 넣어준다.
		else Idle(player);
	}
}

void Attack_A_State::Attack_B(Player * player)
{
	// 다음 공격이 가능하게 bool값 초기화
	player->set_Info()->bool_V.Attack_Success = false;

	// 공격 B 애니메이션으로 교체해준다.
	player->set_Info()->ani_Changer("Attack_B", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 공격 B 상태로 교체해준다.
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






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 기본공격 B! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 공격 렉트 초기화
	player->set_Info()->pos.Attack_RC = { 0, 0, 0, 0 };

	// 사용한 변수 초기화
	player->set_Info()->bool_State_Reset();

	player->set_Info()->bool_V.next_Attack_B = false;

	// 대기 애니메이션으로 교체 해준다.
	player->set_Info()->ani_Changer("Idle", player->get_InputKey());

	// 대기 상태로 바꿔준다.
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
	// 카메라 위치 갱신
	CAMERAMANAGER->Use_Func()->set_CameraXY(player->get_Info().pos.center.x, player->get_Info().pos.center.y, true);

	// 렉트 갱신
	player->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
	player->update_Ani_Rect();

	// 일정 공격 프레임일때 렉트 생성 그 외 프레임일땐 삭제
	if (player->get_Info().img.ani->getFramePos().x == 2 * 160)
	{
		// 공격 렉트를 만들어준다.
		player->set_Info()->create_Attack_Rect(player->get_InputKey());
	}
	else player->set_Info()->pos.Attack_RC = { 0,0,0,0 };

	// 공격 애니메이션의 마지막 프레임일때
	if (player->get_Info().img.ani->getFramePos().x == 640)
	{
		// 대기 상태로 돌아간다.
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






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 기본공격 C! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 스킬 A! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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
	// 불값 초기화
	player->set_Info()->bool_State_Reset();

	// 대기 애니메이션으로 교체
	player->set_Info()->ani_Changer("Idle", player->get_InputKey());
	player->set_Info()->img.ani->start();

	// 대기 상태로 교체
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
	// 스컬의 머리 위치에서 렉트를 생성하여 바라보는 방향으로 날려준다. (머리통 렉트 생성 함수 호출)
	// 스컬의 머리는 한번만 날아가야 한다. 한개를 생성과 동시에 bool값을 바꿔준다.
	// 스컬이 머리를 다시 줍거나, 일정 시간이 자나면 bool값이 false로 바뀐다.
	if (!player->get_Info().bool_V.useing_Skill_A)
	{
		// 스컬의 머리를 생성해준다. (방향에 따라 다른 이미지, 다른 각도)
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

		// 스킬을 사용했으면 true
		player->set_Info()->bool_V.useing_Skill_A = true;
	}

	// 스컬이 머리를 날리는 애니메이션이 끝나면 스컬 머리가 없는 애니메이션 타입으로 교체 후 대기 상태로
	if (player->get_Info().img.ani->getFramePos().x == 480)
	{
		// 점프 초기화 (스킬이 끝난 후 대기 -> 추락으로 넘어갈 경우)
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






// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 스킬 B! ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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


