#pragma once

// 스컬의 머리가 사라지는 시간
#define SKUL_HEAD_DELETE_TIME 300

// 파티클이 사라지는 시간
#define PARTICLE_DELETE_TIME 50

// 화살이 사라지는 시간
#define ARROW_DELETE_TIME 150

// 투사체의 중력
#define FLYINGOBJECT_GRAVITY 0.5f

// 투사체 타입 Enum
enum class FLYINFOBJECT_TYPE
{
	NONE,							// NULL
	SKUL_HEAD,						// 스컬 머리
	PARTICLE,						// 파티클
	ARROW							// 화살

};

// 투사체의 방향 Enum
enum class FLYINGOBJECT_DIRECTION
{
	NONE,							// NULL
	LEFT,							// 왼쪽
	RIGHT							// 오른쪽
};

// 투사체의 기본 정보 구조체
struct FlyingObjectInfo
{
	FLYINFOBJECT_TYPE		type;			// 투사체 타입 

	image*					img;			// 투사체 이미지 저장
	animation*				ani;			// 투사체 애니메이션 저장
	string					aniName;		// 투사체 애니메이션 키값 저장
	POINTFLOAT				center;			// 투사체의 중점
	RECT					rc;				// 투사체의 렉트
	FLOAT					angle;			// 투사체의 각도
	FLOAT					speed;			// 투사체의 스피드
	FLOAT					gravity;		// 투사체의 중력
	FLYINGOBJECT_DIRECTION	dir;			// 투사체의 방향
	int						attack;			// 투사체의 공격력

	bool					isFrame;		// 이미지가 프레임인지 아닌지

	short					Delete_Timer;	// 투사체의 삭제 타이머

	bool					isFalling;		// 투사체가 추락중인지 여부
	bool					isHit;			// 투사체가 이미 충돌을 끝냈는지


	// 변수를 비워주는 함수
	void reset()
	{
		type = FLYINFOBJECT_TYPE::NONE;		// 타입 초기화
	
		img = new image;					// 이미지 할당
		ani = new animation;				// 애니 할당
		aniName = "";						// 애니 키값 초기화

		center.x = center.y = 0;			// 중점 초기화
		rc = { 0, 0, 0, 0 };				// 렉트 초기화

		angle = 0;							// 각도 초기화
		speed = 0;							// 스피드 초기화
		gravity = 0;						// 중력 초기화
		attack = 0;							// 공격력 초기화

		dir = FLYINGOBJECT_DIRECTION::NONE; // 방향 초기화

		Delete_Timer = 0;					// 타이머 초기화

		isFrame = false;					// bool 초기화

		isFalling = false;					// bool 초기화
		isHit = false;
	}

	// 값을 넣어주는 함수 (매개변수 : 이미지 이름, 애니메이션 이름, 중점x, 중점y, 각도, 스피드, 이미지가 프레임인지 아닌지)
	void setting_Info(string imgName, string aniName_V, FLYINFOBJECT_TYPE type_V, FLYINGOBJECT_DIRECTION dir_V,
		float x, float y, float angle_V, float speed_V, int atk_V, bool Frame = false)
	{
		// 타입을 저장한다.
		type = type_V;

		// 방향을 저장한다.
		dir = dir_V;

		// 중점을 저장한다.
		center.x = x;
		center.y = y;

		// 이미지의 프레임 여부를 저장
		isFrame = Frame;

		attack = atk_V;

		// 이미지가 프레임이 아니라면
		if (!isFrame)
		{
			// 키값을 이용하여 이미지를 저장한다.
			img = IMAGEMANAGER->findImage(imgName);

			// 이미지의 가로 세로를 이용하여 렉트를 만든다.
			rc = RectMakeCenter(center.x, center.y, img->getWidth(), img->getHeight());

		}

		// 이미지가 프레임이라면
		if (isFrame);
		{
			// 키값을 이용하여 애니메이션을 저장한다.
			ani = KEYANIMANAGER->findAnimation(aniName_V);

			// 애니메이션 스타트
			ani->start();

			// 이미지 키값을 저장한다.
			aniName = imgName;

			// 애니메이션의 가로 세로를 이용하여 렉트를 만든다.
			rc = RectMakeCenter(center.x, center.y, ani->getFrameWidth(), ani->getFrameHeight());

		}

		// 각도를 저장한다.
		angle = angle_V;

		// 스피드를 저장한다.
		speed = speed_V;
		
	}

	// 타입 셋팅
	void setting_Type(FLYINFOBJECT_TYPE typeName)
	{
		// 타입을 저장한다.
		type = typeName;

	}

	// 타입에 따라 타이머값을 반환한다.
	short get_Timer_Count()
	{
		// 타입에 따라 타이머를 저장한다.
		switch (type)
		{
			case FLYINFOBJECT_TYPE::SKUL_HEAD:
				return SKUL_HEAD_DELETE_TIME;

				break;

			case FLYINFOBJECT_TYPE::PARTICLE:
				return PARTICLE_DELETE_TIME;

				break;

			case FLYINFOBJECT_TYPE::ARROW:
				return ARROW_DELETE_TIME;

				break;
		}
	}

	// 렉트 갱신
	void update_Rect()
	{
		if (!isFrame)
		{
			// 이미지의 가로 세로를 이용하여 렉트를 만든다.
			rc = RectMakeCenter(center.x, center.y, img->getWidth(), img->getHeight());

		}

		if (isFrame)
		{
			// 애니메이션의 가로 세로를 이용하여 렉트를 만든다.
			rc = RectMake(center.x, center.y, ani->getFrameWidth(), ani->getFrameHeight());

		}
	}

};