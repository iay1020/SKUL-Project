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
#define	PLAYER_RECT_SIZE_X	40
#define PLAYER_RECT_SIZE_Y	40		// (��¦ 20���� bottom�� �� ���� ��)

// ĳ���� �̵��ӵ�
#define PLAYER_SPEED		5

// ĳ���� �߷�
#define PLAYER_GRAVITY		0.5f

// ĳ���� ���� �Ŀ�
#define PLAYER_JUMPPOWER    15
#define PLAYER_DOWNJUMPPOWER 5

// ĳ���� �ִ� �߶� �ӵ�
#define PLAYER_MAX_FALL_SPEED -30.0f

// ĳ���� �⺻ ���� Ƚ��
#define PLAYER_JUMP_COUNT	1


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
};

// ĳ������ ���� ����ü
struct CharacterInfo
{
	CharacterPos		pos;		// ĳ������ ��ǥ ��������´�.
	CharacterImage		img;		// ĳ������ �̹��� ������ ��´�.
	CharacterStatus		status;		// ĳ������ �������ͽ� ������ ��´�.
	CharacterBool		bool_V;		// ĳ������ bool ������ ��´�.
	CharacterJump		jump;		// ĳ������ ���� ������ ��´�.

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
	void set_Status(string name, short hp, short atk, short def, CharacterDirection direction, short jumpCnt = 0)
	{
		status.Name = name;
		status.HP = hp;
		status.Atk = atk;
		status.Def = def;
		status.direction = direction;

		jump.Jump_Count += jumpCnt;					// Ư�� Ŭ������ ������ 2��
		jump.Jump_Count_Save = jump.Jump_Count;		// ���� ī��Ʈ�� �����Ѵ�. �����Ҷ� �� ���� �̿��Ͽ� ����
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

};

