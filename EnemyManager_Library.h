#pragma once

// 에너미 타입 enum
enum class EnemyType
{
	NONE,			// NULL
	SOLDIER			// 병사

};

// 에너미의 방향 enum
enum class EnemyDirection
{
	NONE,			// NULL
	LEFT,			// 왼쪽
	RIGHT			// 오른쪽
};

// 에너미 스텟 구조체
struct EnemyStatus
{
	EnemyType			type;			// 에너미의 타입을 담는다.
	EnemyDirection		dir;			// 에너미의 방향을 담는다.

	short				attack;			// 에너미의 공격력을 담는다.
	short				def;			// 에너미의 방어력을 담는다.
	short				speed;			// 에너미의 이동력을 담는다.

	short				gold;			// 에너미가 드랍할 골드량을 담는다.
	
};

// 에너미의 좌표 구조체
struct EnemyPos
{
	POINTFLOAT			center;			// 에너미의 중점을 담는다.
	RECT				ani_Rc;			// 에너미의 애니메이션 렉트를 담는다.
	RECT				hit_Range_Rc;	// 에너미의 피격 범위 렉트


};

// 에너미의 이미지 구조체
struct EnemyImage
{
	string				imgName;		// 에너미의 이미지 키값을 담는다.
	string				aniName;		// 에너미의 애니메이션 키값을 담는다.
	animation*			ani;			// 에너미의 애니메이션을 담는다.

};

// 에너미의 bool 구조체
struct EnemyBoolValue
{
	bool				idleCheck;		// 대기 애니메이션 교체 체크
	bool				walkCheck;		// 이동 애니메이션 교체 체크
	bool				attackCheck;	// 공격 애니메이션 교체 체크
	bool				hitCheck;		// 피격 애미네이션 교체 체크
};

// 에너미의 정보 구조체
struct EnemyInfo
{
	EnemyStatus			status;			// 에너미의 스텟 정보
	EnemyImage			img;			// 에너미의 이미지 정보
	EnemyPos			pos;			// 에너미의 좌표 정보
	EnemyBoolValue		bool_V;			// 에너미의 bool 정보

	// 모두 초기화
	void All_ReSet()
	{
		// 스테이터스 초기화
		status.type = EnemyType::NONE;
		status.dir = EnemyDirection::NONE;
		status.attack = 0;
		status.def = 0;
		status.speed = 0;
		status.gold = 0;

		// 이미지 초기화
		img.ani = new animation;
		img.imgName = "";
		img.aniName = "";

		// 좌표 초기화
		pos.center.x = pos.center.y = 0;
		pos.ani_Rc = { 0, 0, 0, 0 };
		pos.hit_Range_Rc = { 0, 0, 0, 0 };

		// bool 초기화
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;

	}

	// 상태 초기화
	void state_ReSet()
	{
		// bool 초기화
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;
	}

	// bool 초기화 
	void bool_ReSet()
	{
		// bool 초기화
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;

	}

	// 에너미의 타입에 따라 스텟을 넣어준다.
	void find_EnemyStatus()
	{
		switch (status.type)
		{
		case EnemyType::SOLDIER:
			status.attack = 10;
			status.def = 0;
			status.speed = 10;
			status.gold = 100;

			break;
		}
	}

	// 에너미 스텟 생성 (매개변수 : 타입, 방향, 이미지 키값, 애니메이션 키값, 중점 x, 중점 y)
	void Create_Enemy(EnemyType type_V, EnemyDirection dir_V,
		string imgName, string aniName,	float x_V, float y_V)
	{
		// 스테이터스 생성
		status.type = type_V;
		status.dir = dir_V;

		// 타입을 이용하여 에너미의 스텟을 넣어준다.
		find_EnemyStatus();

		// 이미지 생성
		img.imgName = imgName;
		img.aniName = aniName;
		img.ani = KEYANIMANAGER->findAnimation(aniName);
		img.ani->start();

		// 좌표 생성
		// 중점 저장
		pos.center.x = x_V;
		pos.center.y = y_V;

		// 이미지 저장 (계산을 편하게 하기 위해)
		image* temp_Img = new image;
		temp_Img = IMAGEMANAGER->findImage(img.imgName);

		// 애니메이션을 그릴때 사용하는 렉트
		pos.ani_Rc = RectMakeCenter(x_V, y_V, temp_Img->getFrameWidth(), temp_Img->getFrameHeight());

		// 에너미의 피격 범위 렉트
		pos.hit_Range_Rc = RectMakeCenter(x_V, y_V, temp_Img->getFrameWidth() / 2, temp_Img->getFrameHeight() / 2);
	}

};


//형길이형 지금 기분이 어떠신지요?
//치킨치킨한 기분이었읍니다.
