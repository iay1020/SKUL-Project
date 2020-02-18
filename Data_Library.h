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
#define	PLAYER_RECT_SIZE_X	40
#define PLAYER_RECT_SIZE_Y	40		// (살짝 20정도 bottom이 더 길어야 함)

// 캐릭터 이동속도
#define PLAYER_SPEED		5

// 캐릭터 중력
#define PLAYER_GRAVITY		0.5f

// 캐릭터 점프 파워
#define PLAYER_JUMPPOWER    15
#define PLAYER_DOWNJUMPPOWER 5

// 캐릭터 최대 추락 속도
#define PLAYER_MAX_FALL_SPEED -30.0f

// 캐릭터 기본 점프 횟수
#define PLAYER_JUMP_COUNT	1


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
};

// 캐릭터의 정보 구조체
struct CharacterInfo
{
	CharacterPos		pos;		// 캐릭터의 좌표 정보를담는다.
	CharacterImage		img;		// 캐릭터의 이미지 정보를 담는다.
	CharacterStatus		status;		// 캐릭터의 스테이터스 정보를 담는다.
	CharacterBool		bool_V;		// 캐릭터의 bool 정보를 담는다.
	CharacterJump		jump;		// 캐릭터의 점프 정보를 담는다.

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
	void set_Status(string name, short hp, short atk, short def, CharacterDirection direction, short jumpCnt = 0)
	{
		status.Name = name;
		status.HP = hp;
		status.Atk = atk;
		status.Def = def;
		status.direction = direction;

		jump.Jump_Count += jumpCnt;					// 특정 클래스는 점프가 2번
		jump.Jump_Count_Save = jump.Jump_Count;		// 점프 카운트를 저장한다. 충전할때 이 값을 이용하여 충전
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

};

