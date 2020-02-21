#pragma once

// ���������������������������������� ���� ��������������������������������������
// �������Ͽ� ����ϴ� enum
enum InputKey
{
	PRESS_EMPTY,
	PRESS_LEFT,
	PRESS_RIGHT
};

// ���������������������������������� ĳ���� ��������������������������������������
// ĳ���ʹ� �÷��̾�, ���� ���� ��� ������ ����ü

// ĳ������ ���� enum
enum CharacterDirection
{
	DIRECTION_EMPTY,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

// ĳ���� ��Ʈ ������
#define	PLAYER_RECT_SIZE_X				40
#define PLAYER_RECT_SIZE_Y				40		// (��¦ 20���� bottom�� �� ���� ��)

// ĳ���� �̵��ӵ�
#define PLAYER_SPEED					5

// ĳ���� �߷�
#define PLAYER_GRAVITY					0.5f

// ĳ���� ���� �Ŀ�
#define PLAYER_JUMPPOWER				15
#define PLAYER_DOWNJUMPPOWER			5

// ĳ���� ���� ���� ��Ÿ��
#define PLAYER_JUMPATTACK_COOLTIME		30

// ĳ���� �ִ� �߶� �ӵ�
#define PLAYER_MAX_FALL_SPEED			-30.0f

// ĳ���� �⺻ ���� Ƚ��
#define PLAYER_JUMP_COUNT				1

// ĳ���� �뽬 �⺻ Ƚ��
#define PLAYER_DASH_COUNT				1

// ĳ���� �뽬 �Ÿ�
#define PLAYER_DASH_RANGE				150

// ĳ���� �뽬 �ð�
#define PLAYER_DASH_TIME				0.1f

// ĳ���� �뽬 ��Ÿ��
#define PLAYER_DASH_COOLTIME			100



// ĳ���� ��ǥ ����ü
struct CharacterPos
{
	POINTFLOAT			center;		// ĳ������ ������ �����Ѵ�.
	RECT				rc;			// ĳ������ ��Ʈ�� �����Ѵ�.

};

// ĳ������ �̹��� ����ü
struct CharacterImage
{
	string				imgName;	// ĳ������ �̹��� Ű���� �����Ѵ�.
	animation*			ani;		// ĳ������ �ִϸ��̼��� �����Ѵ�.
	string				aniName;	// ĳ������ �ִϸ��̼� Ű���� �����Ѵ�.
	RECT				img_Rc;		// ĳ������ �̹����� �׷��� ��Ʈ.
			
};

// ĳ������ �������ͽ�
struct CharacterStatus
{
	string				Name;		// ĳ������ �̸��� �����Ѵ�.
	short				HP;			// ĳ������ ü���� �����Ѵ�.
	short				Atk;		// ĳ������ ���ݷ��� �����Ѵ�.
	short				Def;		// ĳ������ ������ �����Ѵ�.
	CharacterDirection	direction;	// ĳ������ ������ �����Ѵ�.

};

// ĳ������ bool
struct CharacterBool
{
	bool				idle_Cheack;		// ĳ������ idle �̹��� ��ü�� �־�����
	bool				walk_Cheack;		// ĳ������ walk �̹��� ��ü�� �־�����
	bool				jump_Cheack;		// ĳ������ jump �̹��� ��ü�� �־�����
	bool				fall_Cheack;		// ĳ������ fall �̹��� ��ü�� �־�����
	bool				dash_Cheack;		// ĳ���Ͱ� dash �̹��� ��ü�� �־�����

	bool				walking_Cheack;		// ĳ���Ͱ� �̵������� üũ�ϴ� ����
	bool				jumping_Cheack;		// ĳ���Ͱ� ���������� üũ�ϴ� ����
	bool				falling_Cheack;		// ĳ���Ͱ� �߶������� üũ�ϴ� ����
	bool				dashing_Cheack;		// ĳ���Ͱ� �뽬������ üũ�ϴ� ����

};

// ĳ������ ���� ����ü
struct CharacterJump
{
	short				Jump_Count;			// ���� Ƚ��
	short				Jump_Count_Save;	// ���� Ƚ�� ���� (���� �Ҷ� �̿�)
	float				jump_Value;			// ���� ��ġ

	short				jump_Attack_Count;	// ���� ������ ������ �ִϸ��̼� ���� �ð� (���� ���� ���ñ����� �ð�)
};

// ĳ������ �뽬 ����ü
struct CharacterDash
{
	short				Dash_Count;			// �뽬 Ƚ��
	short				Dash_Count_Save;	// �뽬 Ƚ�� ���� (���� �Ҷ� �̿�)

	float				Dash_StartTime;		// �뽬 ���� �ð�

	short				Dash_CoolTime;		// �뽬 Ƚ���� �����Ǵ� ��Ÿ��
};

// ĳ���� Ÿ�� Enum
enum class SKUL_TYPE
{
	SKUL_NOWEAPON,			// ������� ����
	SKUL_WEAPON,			// ���� �ִ� ����
	SKUL_WEAPON_NOHEAD,		// ���� �ִ� �Ӹ� ���� ����
	SKUL_NIGHT				// ��� ����
};

// ĳ���� Ÿ�� ����ü
struct CharacterType
{
	SKUL_TYPE	skul_Type;
	string		skul_Type_Name;
};

// ĳ������ ���� ����ü
struct CharacterInfo
{
	CharacterPos		pos;		// ĳ������ ��ǥ ��������´�.
	CharacterImage		img;		// ĳ������ �̹��� ������ ��´�.
	CharacterStatus		status;		// ĳ������ �������ͽ� ������ ��´�.
	CharacterBool		bool_V;		// ĳ������ bool ������ ��´�.
	CharacterJump		jump;		// ĳ������ ���� ������ ��´�.
	CharacterDash		dash;		// ĳ������ �뽬 ������ ��´�.
	CharacterType		type;		// ĳ������ Ŭ���� Ÿ�� ������ ��´�.

	// ĳ������ ������ ���� ���� �ʱ�ȭ
	void reset()
	{
		// ��ǥ �ʱ�ȭ
		pos.center.x = pos.center.y = 0;
		pos.rc = RectMake(0, 0, 0, 0);

		// �̹��� �ʱ�ȭ
		img.imgName = "";
		img.ani = new animation;
		img.aniName = "";
		img.img_Rc = RectMake(0, 0, 0, 0);

		// �������ͽ� �ʱ�ȭ
		status.Name = "";
		status.HP = 0;
		status.Atk = 0;
		status.Def = 0;
		status.direction = DIRECTION_EMPTY;

		// bool �ʱ�ȭ
		bool_V.idle_Cheack = false;
		bool_V.walk_Cheack = false;
		bool_V.jump_Cheack = false;
		bool_V.fall_Cheack = false;
		bool_V.dash_Cheack = false;

		bool_V.walking_Cheack = false;
		bool_V.jumping_Cheack = false;
		bool_V.falling_Cheack = false;
		bool_V.dashing_Cheack = false;

		// ���� �ʱ�ȭ
		jump.jump_Value = 0;
		jump.Jump_Count = PLAYER_JUMP_COUNT;
		jump.Jump_Count_Save = 0;
		jump.jump_Attack_Count = 0;

		// �뽬 �ʱ�ȭ
		dash.Dash_StartTime = 0;
		dash.Dash_Count = PLAYER_DASH_COUNT;
		dash.Dash_Count_Save = 0;
		dash.Dash_CoolTime = 0;

		// ���� Ŭ���� �ʱ�ȭ
		type.skul_Type = SKUL_TYPE::SKUL_NOWEAPON;
		//type.skul_Type_Name = ;
	}

	// ĳ���� bool �ʱ�ȭ
	void bool_Value_Reset()
	{
		// bool �ʱ�ȭ
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

	// ĳ���� ��ǥ ���� (�Ű����� : ����x, ����y, ��Ʈ������x, ��Ʈ������y)
	void set_Pos(float x, float y, short sizeX, short sizeY)
	{
		// ĳ������ ������ �����Ѵ�. 
		pos.center.x = x; 
		pos.center.y = y;

		// ĳ������ ������ �������� �Ű����� ������ ��ŭ�� ��Ʈ�� �����.
		pos.rc = RectMakeCenter(pos.center.x, pos.center.y, sizeX, sizeY);
	}

	// ĳ������ ��Ʈ ����
	void set_Rect(float left, float top, float right, float bottom)
	{
		pos.rc.left = left;
		pos.rc.right = right;
		pos.rc.top = top;
		pos.rc.bottom = bottom;
	}

	// ĳ������ �ִϸ��̼� ���� (�Ű����� : �̹��� Ű��, �ִ� Ű��)
	void set_Ani(string imgName, string aniName)
	{
		// �̹��� Ű��
		img.imgName = imgName;

		// �ִ� Ű��
		img.aniName = aniName;
		img.ani = KEYANIMANAGER->findAnimation(img.aniName);

		// �̹����� �׸� ��Ʈ ����
		img.img_Rc = RectMakeCenter(pos.center.x, pos.center.y, img.ani->getFrameWidth(), img.ani->getFrameHeight());
	}


	// ĳ������ �������ͽ� ���� (�Ű����� : �̸�, HP, ATK, DEF, ����, ���� Ƚ�� �߰�)
	void set_Status(string name, short hp, short atk, short def, CharacterDirection direction, short jumpCnt = 0, short dashCnt = 0)
	{
		status.Name = name;
		status.HP = hp;
		status.Atk = atk;
		status.Def = def;
		status.direction = direction;

		jump.Jump_Count += jumpCnt;					// Ư�� Ŭ������ ������ 2��
		jump.Jump_Count_Save = jump.Jump_Count;		// ���� ī��Ʈ�� �����Ѵ�. �����Ҷ� �� ���� �̿��Ͽ� ����

		dash.Dash_Count += dashCnt;					// Ư�� Ŭ������ �뽬�� 2�� 
		dash.Dash_Count_Save = dash.Dash_Count;		// �뽬 ī��Ʈ�� �����Ѵ�. �����Ҷ� �� ���� �̿��Ͽ� ����
	}

	// ĳ������ ��Ʈ�� �����Ѵ�. (�Ű����� : ��Ʈ ������x, ��Ʈ ������y)
	void update_Rect(short sizeX, short sizeY)
	{
		pos.rc = RectMakeCenter(pos.center.x, pos.center.y, sizeX, sizeY);
		pos.rc.bottom += 20;

		pos.rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		pos.rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		pos.rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		pos.rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	}

	// �ִϸ��̼� ��Ʈ�� �����Ѵ�. 
	void update_Ani_Rect()
	{
		img.img_Rc = RectMakeCenter(pos.center.x, pos.center.y, IMAGEMANAGER->findImage(img.imgName)->getFrameWidth(), IMAGEMANAGER->findImage(img.imgName)->getFrameHeight());

		img.img_Rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		img.img_Rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		img.img_Rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		img.img_Rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	}

	// �뽬 ��Ÿ���� �����ش�.
	void dash_CoolTime()
	{
		// �뽬 Ƚ���� �ƽ� �뽬 Ƚ������ ��������
		if (dash.Dash_Count < dash.Dash_Count_Save)
		{
			// ��Ÿ���� �����ش�.
			dash.Dash_CoolTime++;

			// ��Ÿ�Ӱ� ���ų� ũ�ٸ�
			if (dash.Dash_CoolTime >= PLAYER_DASH_COOLTIME)
			{
				// �ƽ� �뽬���� Ƚ���� ������ �ϳ� ä���ش�.
				dash.Dash_Count = dash.Dash_Count_Save;

				// ��Ÿ�� ���� �ʱ�ȭ
				dash.Dash_CoolTime = 0;

			}
		}
	}

	// �ִϸ��̼� ü����
	void ani_Changer(string StateName, InputKey Key)
	{
		
		switch (type.skul_Type)
		{
			case SKUL_TYPE::SKUL_NOWEAPON:
				if (Key == PRESS_LEFT)
				{
					// ���
					if (StateName == "Idle") set_Ani("skul_Idle_NoWeapon", "skul_Idle_Left_NoWeapon");
					// �̵�
					if (StateName == "Move") set_Ani("skul_Walk_NoWeapon", "skul_Walk_Left_NoWeapon");
					// ����
					if (StateName == "Jump") set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
					// ���� ����
					if (StateName == "JumpAttack") set_Ani("skul_Jump_Attack", "skul_Jump_Left_Attack");
					// �߶�
					if (StateName == "Fall") set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
					// �߶���
					if (StateName == "Falling") set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
					// �뽬
					if (StateName == "Dash") set_Ani("skul_Dash", "skul_Dash_Left");
					// ���� A
					//if (StateName == "AttackA") set_Ani("skul_Attack_A", "skul_Attack_A_Left");
					// ���� B
					//if (StateName == "AttackB") set_Ani("skul_Attack_B", "skul_Attack_B_Left");
					// ���� C
					//if (StateName == "AttackC");
					// ��ų A
					//if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_L"); 
					// ��ų B
					//if (StateName == "SkillB");
				}
				if (Key == PRESS_RIGHT)
				{
					// ���
					if (StateName == "Idle") set_Ani("skul_Idle_NoWeapon", "skul_Idle_Right_NoWeapon");
					// �̵�
					if (StateName == "Move") set_Ani("skul_Walk_NoWeapon", "skul_Walk_Right_NoWeapon");
					// ����
					if (StateName == "Jump") set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
					// ���� ����
					if (StateName == "JumpAttack") set_Ani("skul_Jump_Attack", "skul_Jump_Right_Attack");
					// �߶�
					if (StateName == "Fall") set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
					// �߶���
					if (StateName == "Falling") set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
					// �뽬
					if (StateName == "Dash") set_Ani("skul_Dash", "skul_Dash_Right");
					// ���� A
					//if (StateName == "AttackA") set_Ani("skul_Attack_A", "skul_Attack_A_Right");
					// ���� B
					//if (StateName == "AttackB") set_Ani("skul_Attack_B", "skul_Attack_B_Right");
					// ���� C
					//if (StateName == "AttackC");
					// ��ų A
					//if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_R");
					// ��ų B
					//if (StateName == "SkillB");
				}
				break;

			case SKUL_TYPE::SKUL_WEAPON:
				if (Key == PRESS_LEFT)
				{
					// ���
					if (StateName == "Idle") set_Ani("skul_Idle_HaveWeapon", "skul_Idle_Left_HaveWeapon");
					// �̵�
					if (StateName == "Move") set_Ani("skul_Walk_Weapon", "skul_Walk_Left_HaveWeapon");
					// ����
					if (StateName == "Jump") set_Ani("skul_Jump", "skul_Jump_Left_NoWeapon");
					// ���� ����
					if (StateName == "JumpAttack") set_Ani("skul_Jump_Attack", "skul_Jump_Left_Attack");
					// �߶�
					if (StateName == "Fall") set_Ani("skul_Fall", "skul_Fall_Left_NoWeapon");
					// �߶���
					if (StateName == "Falling") set_Ani("skul_Falling", "skul_Falling_Left_NoWeapon");
					// �뽬
					if (StateName == "Dash") set_Ani("skul_Dash", "skul_Dash_Left");
					// ���� A
					if (StateName == "AttackA") set_Ani("skul_Attack_A", "skul_Attack_A_Left");
					// ���� B
					if (StateName == "AttackB") set_Ani("skul_Attack_B", "skul_Attack_B_Left");
					// ���� C
					//if (StateName == "AttackC");
					// ��ų A
					if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_L");
					// ��ų B
					//if (StateName == "SkillB");
				}
				if (Key == PRESS_RIGHT)
				{
					// ���
					if (StateName == "Idle") set_Ani("skul_Idle_HaveWeapon", "skul_Idle_Right_HaveWeapon");
					// �̵�
					if (StateName == "Move") set_Ani("skul_Walk_Weapon", "skul_Walk_Right_HaveWeapon");
					// ����
					if (StateName == "Jump") set_Ani("skul_Jump", "skul_Jump_Right_NoWeapon");
					// ���� ����
					if (StateName == "JumpAttack") set_Ani("skul_Jump_Attack", "skul_Jump_Right_Attack");
					// �߶�
					if (StateName == "Fall") set_Ani("skul_Fall", "skul_Fall_Right_NoWeapon");
					// �߶���
					if (StateName == "Falling") set_Ani("skul_Falling", "skul_Falling_Right_NoWeapon");
					// �뽬
					if (StateName == "Dash") set_Ani("skul_Dash", "skul_Dash_Right");
					// ���� A
					if (StateName == "AttackA") set_Ani("skul_Attack_A", "skul_Attack_A_Right");
					// ���� B
					if (StateName == "AttackB") set_Ani("skul_Attack_B", "skul_Attack_B_Right");
					// ���� C
					//if (StateName == "AttackC");
					// ��ų A
					if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_R");
					// ��ų B
					//if (StateName == "SkillB");
				}
				break;

			case SKUL_TYPE::SKUL_WEAPON_NOHEAD:
				if (Key == PRESS_LEFT)
				{
					// ���
					if (StateName == "Idle") set_Ani("skul_Idle_HaveWeapon_NoHead", "skul_Idle_Left_HaveWeapon_NoHead");
					// �̵�
					if (StateName == "Move") set_Ani("skul_Walk_NoHead_Weapon", "skul_Walk_Left_HaveWeapon_NoHead");
					// ����
					if (StateName == "Jump") set_Ani("skul_Jump_NoHead", "skul_Jump_Left_NoHead");
					// ���� ����
					if (StateName == "JumpAttack") set_Ani("skul_Jump_NoHead_Attack", "skul_Jump_Left_Attack_NoHead");
					// �߶�
					if (StateName == "Fall") set_Ani("skul_Fall_NoHead", "skul_Fall_Left_NoHead");
					// �߶���
					if (StateName == "Falling") set_Ani("skul_Falling_NoHead", "skul_Falling_Left_NoHead");
					// �뽬
					if (StateName == "Dash") set_Ani("skul_Dash_NoHead", "skul_Dash_Left_NoHead");
					// ���� A
					if (StateName == "AttackA") set_Ani("skul_Attack_A_NoHead", "skul_Attack_A_Left_N");
					// ���� B
					if (StateName == "AttackB") set_Ani("skul_Attack_B_NoHead", "skul_Attack_B_Left_N");
					// ���� C
					//if (StateName == "AttackC");
					// ��ų A
					if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_L");
					// ��ų B
					//if (StateName == "SkillB");
				}
				if (Key == PRESS_RIGHT)
				{
					// ���
					if (StateName == "Idle") set_Ani("skul_Idle_HaveWeapon_NoHead", "skul_Idle_Right_HaveWeapon_NoHead");
					// �̵�
					if (StateName == "Move") set_Ani("skul_Walk_NoHead_Weapon", "skul_Walk_Right_HaveWeapon_NoHead");
					// ����
					if (StateName == "Jump") set_Ani("skul_Jump_NoHead", "skul_Jump_Right_NoHead");
					// ���� ����
					if (StateName == "JumpAttack") set_Ani("skul_Jump_NoHead_Attack", "skul_Jump_Right_Attack_NoHead");
					// �߶�
					if (StateName == "Fall") set_Ani("skul_Fall_NoHead", "skul_Fall_Right_NoHead");
					// �߶���
					if (StateName == "Falling") set_Ani("skul_Falling_NoHead", "skul_Falling_Right_NoHead");
					// �뽬
					if (StateName == "Dash") set_Ani("skul_Dash_NoHead", "skul_Dash_Right_NoHead");
					// ���� A
					if (StateName == "AttackA") set_Ani("skul_Attack_A_NoHead", "skul_Attack_A_Right_N");
					// ���� B
					if (StateName == "AttackB") set_Ani("skul_Attack_B_NoHead", "skul_Attack_B_Right_N");
					// ���� C
					//if (StateName == "AttackC");
					// ��ų A
					if (StateName == "SkillA") set_Ani("skul_Skill", "throw_Head_R");
					// ��ų B
					//if (StateName == "SkillB");
				}
				break;

			//case SKUL_TYPE::SKUL_NIGHT:
			//	if (Key == PRESS_LEFT)
			//	{
			//		// ���
			//		if (StateName == "Idle");
			//		// �̵�
			//		if (StateName == "Move");
			//		// ����
			//		if (StateName == "Jump");
			//		// ���� ����
			//		if (StateName == "JumpAttack");
			//		// �߶�
			//		if (StateName == "Fall");
			//		// �߶���
			//		if (StateName == "Falling");
			//		// �뽬
			//		if (StateName == "Dash");
			//		// ���� A
			//		if (StateName == "AttackA");
			//		// ���� B
			//		if (StateName == "AttackB");
			//		// ���� C
			//		if (StateName == "AttackC");
			//		// ��ų A
			//		if (StateName == "SkillA");
			//		// ��ų B
			//		if (StateName == "SkillB");
			//	}
			//	if (Key == PRESS_RIGHT)
			//	{
			//		// ���
			//		if (StateName == "Idle");
			//		// �̵�
			//		if (StateName == "Move");
			//		// ����
			//		if (StateName == "Jump");
			//		// ���� ����
			//		if (StateName == "JumpAttack");
			//		// �߶�
			//		if (StateName == "Fall");
			//		// �߶���
			//		if (StateName == "Falling");
			//		// �뽬
			//		if (StateName == "Dash");
			//		// ���� A
			//		if (StateName == "AttackA");
			//		// ���� B
			//		if (StateName == "AttackB");
			//		// ���� C
			//		if (StateName == "AttackC");
			//		// ��ų A
			//		if (StateName == "SkillA");
			//		// ��ų B
			//		if (StateName == "SkillB");
			//	}
			//	break;
		}
		

		

		

	}
};

