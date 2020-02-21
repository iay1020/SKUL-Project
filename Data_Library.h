#pragma once

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 상태 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// 상태패턴에 사용하는 enum
enum InputKey
{
	PRESS_EMPTY,
	PRESS_LEFT,
	PRESS_RIGHT
};

// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 캐릭터 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
// 캐릭터는 플레이어, 몬스터 같이 사용 가능한 구조체

// 캐릭터의 방향 enum
enum CharacterDirection
{
	DIRECTION_EMPTY,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

// 캐릭터 렉트 사이즈
#define	PLAYER_RECT_SIZE_X				40
#define PLAYER_RECT_SIZE_Y				40		// (살짝 20정도 bottom이 더 길어야 함)

// 캐릭터 이동속도
#define PLAYER_SPEED					5

// 캐릭터 중력
#define PLAYER_GRAVITY					0.5f

// 캐릭터 점프 파워
#define PLAYER_JUMPPOWER				15
#define PLAYER_DOWNJUMPPOWER			5

// 캐릭터 점프 공격 쿨타임
#define PLAYER_JUMPATTACK_COOLTIME		30

// 캐릭터 최대 추락 속도
#define PLAYER_MAX_FALL_SPEED			-30.0f

// 캐릭터 기본 점프 횟수
#define PLAYER_JUMP_COUNT				1

// 캐릭터 대쉬 기본 횟수
#define PLAYER_DASH_COUNT				1

// 캐릭터 대쉬 거리
#define PLAYER_DASH_RANGE				150

// 캐릭터 대쉬 시간
#define PLAYER_DASH_TIME				0.1f

// 캐릭터 대쉬 쿨타임
#define PLAYER_DASH_COOLTIME			100



// 캐릭터 좌표 구조체
struct CharacterPos
{
	POINTFLOAT			center;		// 캐릭터의 중점을 저장한다.
	RECT				rc;			// 캐릭터의 렉트를 저장한다.

};

// 캐릭터의 이미지 구조체
struct CharacterImage
{
	string				imgName;	// 캐릭터의 이미지 키값을 저장한다.
	animation*			ani;		// 캐릭터의 애니메이션을 저장한다.
	string				aniName;	// 캐릭터의 애니메이션 키값을 저장한다.
	RECT				img_Rc;		// 캐릭터의 이미지가 그려질 렉트.
			
};

// 캐릭터의 스테이터스
struct CharacterStatus
{
	string				Name;		// 캐릭터의 이름을 저장한다.
	short				HP;			// 캐릭터의 체력을 저장한다.
	short				Atk;		// 캐릭터의 공격력을 저장한다.
	short				Def;		// 캐릭터의 방어력을 저장한다.
	CharacterDirection	direction;	// 캐릭터의 방향을 저장한다.

};

// 캐릭터의 bool
struct CharacterBool
{
	bool				idle_Cheack;		// 캐릭터의 idle 이미지 교체가 있었는지
	bool				walk_Cheack;		// 캐릭터의 walk 이미지 교체가 있었는지
	bool				jump_Cheack;		// 캐릭터의 jump 이미지 교체가 있었는지
	bool				fall_Cheack;		// 캐릭터의 fall 이미지 교체가 있었는지
	bool				dash_Cheack;		// 캐릭터가 dash 이미지 교체가 있었는지

	bool				walking_Cheack;		// 캐릭터가 이동중인지 체크하는 변수
	bool				jumping_Cheack;		// 캐릭터가 점프중인지 체크하는 변수
	bool				falling_Cheack;		// 캐릭터가 추락중인지 체크하는 변수
	bool				dashing_Cheack;		// 캐릭터가 대쉬중인지 체크하는 변수

};

// 캐릭터의 점프 구조체
struct CharacterJump
{
	short				Jump_Count;			// 점프 횟수
	short				Jump_Count_Save;	// 점프 횟수 저장 (충전 할때 이용)
	float				jump_Value;			// 점프 수치

	short				jump_Attack_Count;	// 점프 어택을 했을때 애니메이션 유지 시간 (다음 점프 어택까지의 시간)
};

// 캐릭터의 대쉬 구조체
struct CharacterDash
{
	short				Dash_Count;			// 대쉬 횟수
	short				Dash_Count_Save;	// 대쉬 횟수 저장 (충전 할때 이용)

	float				Dash_StartTime;		// 대쉬 시작 시간

	short				Dash_CoolTime;		// 대쉬 횟수가 생성되는 쿨타임
};

// 캐릭터 타입 Enum
enum class SKUL_TYPE
{
	SKUL_NOWEAPON,			// 무기없는 스컬
	SKUL_WEAPON,			// 무기 있는 스컬
	SKUL_WEAPON_NOHEAD,		// 무기 있는 머리 없는 스컬
	SKUL_NIGHT				// 기사 스컬
};

// 캐릭터 타입 구조체
struct CharacterType
{
	SKUL_TYPE	skul_Type;
	string		skul_Type_Name;
};

// 캐릭터의 정보 구조체
struct CharacterInfo
{
	CharacterPos		pos;		// 캐릭터의 좌표 정보를담는다.
	CharacterImage		img;		// 캐릭터의 이미지 정보를 담는다.
	CharacterStatus		status;		// 캐릭터의 스테이터스 정보를 담는다.
	CharacterBool		bool_V;		// 캐릭터의 bool 정보를 담는다.
	CharacterJump		jump;		// 캐릭터의 점프 정보를 담는다.
	CharacterDash		dash;		// 캐릭터의 대쉬 정보를 담는다.
	CharacterType		type;		// 캐릭터의 클래스 타입 정보를 담는다.

	// 캐릭터의 정보를 담을 변수 초기화
	void reset()
	{
		// 좌표 초기화
		pos.center.x = pos.center.y = 0;
		pos.rc = RectMake(0, 0, 0, 0);

		// 이미지 초기화
		img.imgName = "";
		img.ani = new animation;
		img.aniName = "";
		img.img_Rc = RectMake(0, 0, 0, 0);

		// 스테이터스 초기화
		status.Name = "";
		status.HP = 0;
		status.Atk = 0;
		status.Def = 0;
		status.direction = DIRECTION_EMPTY;

		// bool 초기화
		bool_V.idle_Cheack = false;
		bool_V.walk_Cheack = false;
		bool_V.jump_Cheack = false;
		bool_V.fall_Cheack = false;
		bool_V.dash_Cheack = false;

		bool_V.walking_Cheack = false;
		bool_V.jumping_Cheack = false;
		bool_V.falling_Cheack = false;
		bool_V.dashing_Cheack = false;

		// 점프 초기화
		jump.jump_Value = 0;
		jump.Jump_Count = PLAYER_JUMP_COUNT;
		jump.Jump_Count_Save = 0;
		jump.jump_Attack_Count = 0;

		// 대쉬 초기화
		dash.Dash_StartTime = 0;
		dash.Dash_Count = PLAYER_DASH_COUNT;
		dash.Dash_Count_Save = 0;
		dash.Dash_CoolTime = 0;

		// 스컬 클래스 초기화
		type.skul_Type = SKUL_TYPE::SKUL_NOWEAPON;
		//type.skul_Type_Name = ;
	}

	// 캐릭터 bool 초기화
	void bool_Value_Reset()
	{
		// bool 초기화
		bool_V.idle_Cheack = false;
		bool_V.walk_Cheack = false;
		bool_V.jump_Cheack = false;
		bool_V.fall_Cheack = false;
		bool_V.dash_Cheack = false;

		bool_V.walking_Cheack = false;
		bool_V.jumping_Cheack = false;
		bool_V.falling_Cheack = false;
		bool_V.dashing_Cheack = false;
	}

	// 캐릭터 좌표 셋팅 (매개변수 : 중점x, 중점y, 렉트사이즈x, 렉트사이즈y)
	void set_Pos(float x, float y, short sizeX, short sizeY)
	{
		// 캐릭터의 중점을 저장한다. 
		pos.center.x = x; 
		pos.center.y = y;

		// 캐릭터의 중점을 기준으로 매개변수 사이즈 만큼의 렉트를 만든다.
		pos.rc = RectMakeCenter(pos.center.x, pos.center.y, sizeX, sizeY);
	}

	// 캐릭터의 렉트 셋팅
	void set_Rect(float left, float top, float right, float bottom)
	{
		pos.rc.left = left;
		pos.rc.right = right;
		pos.rc.top = top;
		pos.rc.bottom = bottom;
	}

	// 캐릭터의 애니메이션 셋팅 (매개변수 : 이미지 키값, 애니 키값)
	void set_Ani(string imgName, string aniName)
	{
		// 이미지 키값
		img.imgName = imgName;

		// 애니 키값
		img.aniName = aniName;
		img.ani = KEYANIMANAGER->findAnimation(img.aniName);

		// 이미지를 그릴 렉트 갱신
		img.img_Rc = RectMakeCenter(pos.center.x, pos.center.y, img.ani->getFrameWidth(), img.ani->getFrameHeight());
	}


	// 캐릭터의 스테이터스 셋팅 (매개변수 : 이름, HP, ATK, DEF, 방향, 점프 횟수 추가)
	void set_Status(string name, short hp, short atk, short def, CharacterDirection direction, short jumpCnt = 0, short dashCnt = 0)
	{
		status.Name = name;
		status.HP = hp;
		status.Atk = atk;
		status.Def = def;
		status.direction = direction;

		jump.Jump_Count += jumpCnt;					// 특정 클래스는 점프가 2번
		jump.Jump_Count_Save = jump.Jump_Count;		// 점프 카운트를 저장한다. 충전할때 이 값을 이용하여 충전

		dash.Dash_Count += dashCnt;					// 특정 클래스는 대쉬가 2번 
		dash.Dash_Count_Save = dash.Dash_Count;		// 대쉬 카운트를 저장한다. 충전할때 이 값을 이용하여 충전
	}

	// 캐릭터의 렉트를 갱신한다. (매개변수 : 렉트 사이즈x, 렉트 사이즈y)
	void update_Rect(short sizeX, short sizeY)
	{
		pos.rc = RectMakeCenter(pos.center.x, pos.center.y, sizeX, sizeY);
		pos.rc.bottom += 20;

		pos.rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		pos.rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		pos.rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		pos.rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	}

	// 애니메이션 렉트를 갱신한다. 
	void update_Ani_Rect()
	{
		img.img_Rc = RectMakeCenter(pos.center.x, pos.center.y, IMAGEMANAGER->findImage(img.imgName)->getFrameWidth(), IMAGEMANAGER->findImage(img.imgName)->getFrameHeight());

		img.img_Rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		img.img_Rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		img.img_Rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		img.img_Rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	}

	// 대쉬 쿨타임을 돌려준다.
	void dash_CoolTime()
	{
		// 대쉬 횟수가 맥스 대쉬 횟수보다 낮아지면
		if (dash.Dash_Count < dash.Dash_Count_Save)
		{
			// 쿨타임을 돌려준다.
			dash.Dash_CoolTime++;

			// 쿨타임과 같거나 크다면
			if (dash.Dash_CoolTime >= PLAYER_DASH_COOLTIME)
			{
				// 맥스 대쉬보다 횟수가 낮으면 하나 채워준다.
				dash.Dash_Count = dash.Dash_Count_Save;

				// 쿨타임 변수 초기화
				dash.Dash_CoolTime = 0;

			}
		}
	}

	// 애니메이션 체인저
	void ani_Changer(string StateName, InputKey Key)
	{
		
		switch (type.skul_Type)
		{
			case SKUL_TYPE::SKUL_NOWEAPON:
				if (Key == PRESS_LEFT)
				{
					// 대기
					if (StateName == "Idle") set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
					// 이동
					if (StateName == "Move") set_Ani("skul_Walk_NoWeapon", "skul_Walk_Left_NoWeapon");
					// 점프
					if (StateName == "Jump") set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
					// 점프 공격
					if (StateName == "JumpAttack") set_Ani("skul_Jump_Attack", "skul_Jump_Left_Attack");
					// 추락
					if (StateName == "Fall") set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
					// 추락중
					if (StateName == "Falling") set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
					// 대쉬
					if (StateName == "Dash") set_Ani("skul_Dash", "skul_Dash_Left");
					// 공격 A
					//if (StateName == "AttackA") set_Ani("skul_Attack_A", "skul_Attack_A_Left");
					// 공격 B
					//if (StateName == "AttackB") set_Ani("skul_Attack_B", "skul_Attack_B_Left");
					// 공격 C
					//if (StateName == "AttackC");
					// 스킬 A
					//if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_L"); 
					// 스킬 B
					//if (StateName == "SkillB");
				}
				if (Key == PRESS_RIGHT)
				{
					// 대기
					if (StateName == "Idle") set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
					// 이동
					if (StateName == "Move") set_Ani("skul_Walk_NoWeapon", "skul_Walk_Right_NoWeapon");
					// 점프
					if (StateName == "Jump") set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
					// 점프 공격
					if (StateName == "JumpAttack") set_Ani("skul_Jump_Attack", "skul_Jump_Right_Attack");
					// 추락
					if (StateName == "Fall") set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
					// 추락중
					if (StateName == "Falling") set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
					// 대쉬
					if (StateName == "Dash") set_Ani("skul_Dash", "skul_Dash_Right");
					// 공격 A
					//if (StateName == "AttackA") set_Ani("skul_Attack_A", "skul_Attack_A_Right");
					// 공격 B
					//if (StateName == "AttackB") set_Ani("skul_Attack_B", "skul_Attack_B_Right");
					// 공격 C
					//if (StateName == "AttackC");
					// 스킬 A
					//if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_R");
					// 스킬 B
					//if (StateName == "SkillB");
				}
				break;

			case SKUL_TYPE::SKUL_WEAPON:
				if (Key == PRESS_LEFT)
				{
					// 대기
					if (StateName == "Idle") set_Ani("skul_Idle_HaveWeapon", "skul_Idle_Left_HaveWeapon");
					// 이동
					if (StateName == "Move") set_Ani("skul_Walk_Weapon", "skul_Walk_Left_HaveWeapon");
					// 점프
					if (StateName == "Jump") set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
					// 점프 공격
					if (StateName == "JumpAttack") set_Ani("skul_Jump_Attack", "skul_Jump_Left_Attack");
					// 추락
					if (StateName == "Fall") set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
					// 추락중
					if (StateName == "Falling") set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
					// 대쉬
					if (StateName == "Dash") set_Ani("skul_Dash", "skul_Dash_Left");
					// 공격 A
					if (StateName == "AttackA") set_Ani("skul_Attack_A", "skul_Attack_A_Left");
					// 공격 B
					if (StateName == "AttackB") set_Ani("skul_Attack_B", "skul_Attack_B_Left");
					// 공격 C
					//if (StateName == "AttackC");
					// 스킬 A
					if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_L");
					// 스킬 B
					//if (StateName == "SkillB");
				}
				if (Key == PRESS_RIGHT)
				{
					// 대기
					if (StateName == "Idle") set_Ani("skul_Idle_HaveWeapon", "skul_Idle_Right_HaveWeapon");
					// 이동
					if (StateName == "Move") set_Ani("skul_Walk_Weapon", "skul_Walk_Right_HaveWeapon");
					// 점프
					if (StateName == "Jump") set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
					// 점프 공격
					if (StateName == "JumpAttack") set_Ani("skul_Jump_Attack", "skul_Jump_Right_Attack");
					// 추락
					if (StateName == "Fall") set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
					// 추락중
					if (StateName == "Falling") set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
					// 대쉬
					if (StateName == "Dash") set_Ani("skul_Dash", "skul_Dash_Right");
					// 공격 A
					if (StateName == "AttackA") set_Ani("skul_Attack_A", "skul_Attack_A_Right");
					// 공격 B
					if (StateName == "AttackB") set_Ani("skul_Attack_B", "skul_Attack_B_Right");
					// 공격 C
					//if (StateName == "AttackC");
					// 스킬 A
					if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_R");
					// 스킬 B
					//if (StateName == "SkillB");
				}
				break;

			case SKUL_TYPE::SKUL_WEAPON_NOHEAD:
				if (Key == PRESS_LEFT)
				{
					// 대기
					if (StateName == "Idle") set_Ani("skul_Idle_HaveWeapon_NoHead", "skul_Idle_Left_HaveWeapon_NoHead");
					// 이동
					if (StateName == "Move") set_Ani("skul_Walk_NoHead_Weapon", "skul_Walk_Left_HaveWeapon_NoHead");
					// 점프
					if (StateName == "Jump") set_Ani("skul_Jump_NoHead", "skul_Jump_Left_NoHead");
					// 점프 공격
					if (StateName == "JumpAttack") set_Ani("skul_Jump_NoHead_Attack", "skul_Jump_Left_Attack_NoHead");
					// 추락
					if (StateName == "Fall") set_Ani("skul_Fall_NoHead", "skul_Fall_Left_NoHead");
					// 추락중
					if (StateName == "Falling") set_Ani("skul_Falling_NoHead", "skul_Falling_Left_NoHead");
					// 대쉬
					if (StateName == "Dash") set_Ani("skul_Dash_NoHead", "skul_Dash_Left_NoHead");
					// 공격 A
					if (StateName == "AttackA") set_Ani("skul_Attack_A_NoHead", "skul_Attack_A_Left_N");
					// 공격 B
					if (StateName == "AttackB") set_Ani("skul_Attack_B_NoHead", "skul_Attack_B_Left_N");
					// 공격 C
					//if (StateName == "AttackC");
					// 스킬 A
					if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_L");
					// 스킬 B
					//if (StateName == "SkillB");
				}
				if (Key == PRESS_RIGHT)
				{
					// 대기
					if (StateName == "Idle") set_Ani("skul_Idle_HaveWeapon_NoHead", "skul_Idle_Right_HaveWeapon_NoHead");
					// 이동
					if (StateName == "Move") set_Ani("skul_Walk_NoHead_Weapon", "skul_Walk_Right_HaveWeapon_NoHead");
					// 점프
					if (StateName == "Jump") set_Ani("skul_Jump_NoHead", "skul_Jump_Right_NoHead");
					// 점프 공격
					if (StateName == "JumpAttack") set_Ani("skul_Jump_NoHead_Attack", "skul_Jump_Right_Attack_NoHead");
					// 추락
					if (StateName == "Fall") set_Ani("skul_Fall_NoHead", "skul_Fall_Right_NoHead");
					// 추락중
					if (StateName == "Falling") set_Ani("skul_Falling_NoHead", "skul_Falling_Right_NoHead");
					// 대쉬
					if (StateName == "Dash") set_Ani("skul_Dash_NoHead", "skul_Dash_Right_NoHead");
					// 공격 A
					if (StateName == "AttackA") set_Ani("skul_Attack_A_NoHead", "skul_Attack_A_Right_N");
					// 공격 B
					if (StateName == "AttackB") set_Ani("skul_Attack_B_NoHead", "skul_Attack_B_Right_N");
					// 공격 C
					//if (StateName == "AttackC");
					// 스킬 A
					if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_R");
					// 스킬 B
					//if (StateName == "SkillB");
				}
				break;

			//case SKUL_TYPE::SKUL_NIGHT:
			//	if (Key == PRESS_LEFT)
			//	{
			//		// 대기
			//		if (StateName == "Idle");
			//		// 이동
			//		if (StateName == "Move");
			//		// 점프
			//		if (StateName == "Jump");
			//		// 점프 공격
			//		if (StateName == "JumpAttack");
			//		// 추락
			//		if (StateName == "Fall");
			//		// 추락중
			//		if (StateName == "Falling");
			//		// 대쉬
			//		if (StateName == "Dash");
			//		// 공격 A
			//		if (StateName == "AttackA");
			//		// 공격 B
			//		if (StateName == "AttackB");
			//		// 공격 C
			//		if (StateName == "AttackC");
			//		// 스킬 A
			//		if (StateName == "SkillA");
			//		// 스킬 B
			//		if (StateName == "SkillB");
			//	}
			//	if (Key == PRESS_RIGHT)
			//	{
			//		// 대기
			//		if (StateName == "Idle");
			//		// 이동
			//		if (StateName == "Move");
			//		// 점프
			//		if (StateName == "Jump");
			//		// 점프 공격
			//		if (StateName == "JumpAttack");
			//		// 추락
			//		if (StateName == "Fall");
			//		// 추락중
			//		if (StateName == "Falling");
			//		// 대쉬
			//		if (StateName == "Dash");
			//		// 공격 A
			//		if (StateName == "AttackA");
			//		// 공격 B
			//		if (StateName == "AttackB");
			//		// 공격 C
			//		if (StateName == "AttackC");
			//		// 스킬 A
			//		if (StateName == "SkillA");
			//		// 스킬 B
			//		if (StateName == "SkillB");
			//	}
			//	break;
		}
		

		

		

	}
};

