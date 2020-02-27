#pragma once

// 에너미의 기본 이동속도
#define ENEMYSPEED	3

// 에너미의 공격 쿨타임
#define ENEMYATTACKCOOLTIME 50

// 에너미의 피격 시 틱당 밀려나는 거리
#define ENEMYKNOCKBACK_RANGE	1

// 에너미의 피격 시간
#define ENEMYKNOCKBACK_TIME	50

// 에너미가 피격 시 밀려나는 시간
#define ENEMYKNOCKBACKING_TIME	0.1f

// 에너미가 피격 시 밀려나는 거리 
#define ENEMYKNOCKBACK_RANGE	50

// 에너미의 중력
#define ENEMY_GRAVITY	0.5f

// 체력이 떨어지는 스피드
#define HP_MINUS_SPEED_E	2

// 체력이 올라가는 스피드
#define HP_PLUS_SPEED_E		2


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


// 체력 피해 상태 Enum
enum class HP_UPDATE_STATE_E
{
	EMPTY,		// NULL
	HEAL,		// 회복중
	HIT			// 피격중
};

// 에너미 체력 이미지
struct Enemy_Hp_Img
{
	RECT					rc_HP_BG;			// 체력바 배경
	RECT					rc_HP_Back;			// 체력바 뒤
	RECT					rc_HP_Front;		// 체력바 앞

	image*					img_HP_BG;			// 체력바 배경
	image*					img_HP_Back;		// 체력바 뒤 이미지를 저장할 변수
	string					img_HP_Back_Name;	// 체력바 뒤 이미지 키값을 저장할 변수
	image*					img_HP_Front;		// 체력바 앞 이미지를 저장할 변수

	HP_UPDATE_STATE_E		state;				// 체력 업데이트 상태

	short					maxHP;				// 맥스 HP 정보를 담는다.
	short					curHP;				// 현재 HP 정보를 담는다.
	short					backHP;				// 백 HP 정보를 담는다.

};

// 에너미 스텟 구조체
struct EnemyStatus
{
	EnemyType			type;			// 에너미의 타입을 담는다.
	EnemyDirection		dir;			// 에너미의 방향을 담는다.

	short				hp;				// 에너미의 체력을 담는다.
	short				attack;			// 에너미의 공격력을 담는다.
	short				def;			// 에너미의 방어력을 담는다.
	short				speed;			// 에너미의 이동력을 담는다.

	short				gold;			// 에너미가 드랍할 골드량을 담는다.
	
};

// 에너미의 좌표 구조체
struct EnemyPos
{
	POINTFLOAT			center;				// 에너미의 중점을 담는다.
	RECT				ani_Rc;				// 에너미의 애니메이션 렉트를 담는다.
	RECT				hit_Range_Rc;		// 에너미의 피격 범위 렉트
	RECT				find_Range_Rc;		// 에너미 인식 범위
	RECT				attack_Range_Rc;	// 에너미 공격 범위

	RECT				Attack_Rc;			// 에너미 공격 렉트

	float				fall_Power;			// 에너미의 추락 연산 변수

	float				lerp_Start;			// 러프 시작 시간
};

// 에너미의 이미지 구조체
struct EnemyImage
{
	string				imgName;		// 에너미의 이미지 키값을 담는다.
	string				aniName;		// 에너미의 애니메이션 키값을 담는다.	
	animation*			ani;			// 에너미의 애니메이션을 담는다.

	short				curX, curY;		// 에너미의 이미지 x, y를 담는다.

};

// 에너미의 bool 구조체
struct EnemyBoolValue
{
	bool				idleCheck;			// 대기 애니메이션 교체 체크
	bool				walkCheck;			// 이동 애니메이션 교체 체크
	bool				attackCheck;		// 공격 애니메이션 교체 체크
	bool				hitCheck;			// 피격 애미네이션 교체 체크

	bool				Attack_Hit;			// 공격이 맞았는지

	bool				player_Attack_Hit;	// 플레이어의 공격을 맞았는지

	bool				lerping;			// 러프중인지

	bool				im_Hit;				// 난 맞았다
	bool				im_Death;			// 난 죽었다.

};

// 에너미 쿨타임
struct EnemyCoolTime
{
	short				attack_CoolTime;		// 공격 쿨타임
	short				attack_CoolTime_Cnt;	// 공격 쿨타임 카운터

	short				knockBack_Time;			// 넉백 시간

};

// 에너미의 정보 구조체
struct EnemyInfo
{
	EnemyStatus			status;			// 에너미의 스텟 정보
	EnemyImage			img;			// 에너미의 이미지 정보
	EnemyPos			pos;			// 에너미의 좌표 정보
	EnemyBoolValue		bool_V;			// 에너미의 bool 정보
	EnemyCoolTime		cool_Time;		// 에너미의 쿨타임 정보
	Enemy_Hp_Img		hp;				// 에너미의 HP 정보
 
	// 모두 초기화
	void All_ReSet()
	{
		// 스테이터스 초기화
		status.type = EnemyType::NONE;
		status.dir = EnemyDirection::NONE;
		status.hp = 0;
		status.attack = 0;
		status.def = 0;
		status.speed = 0;
		status.gold = 0;

		// 이미지 초기화
		img.ani = new animation;
		img.imgName = "";
		img.aniName = "";
		img.curX = img.curY = 0;

		// 좌표 초기화
		pos.center.x = pos.center.y = 0;
		pos.ani_Rc = { 0, 0, 0, 0 };
		pos.hit_Range_Rc = { 0, 0, 0, 0 };
		pos.find_Range_Rc = { 0, 0, 0, 0 };
		pos.attack_Range_Rc = { 0, 0, 0, 0 };
		pos.Attack_Rc = { 0, 0, 0, 0 };
		pos.fall_Power = 0;
		pos.lerp_Start = 0;

		// bool 초기화
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;

		bool_V.Attack_Hit = false;

		bool_V.player_Attack_Hit = false;
		
		bool_V.lerping = false;

		bool_V.im_Hit = false;
		bool_V.im_Death = false;

		// CoolTime 초기화
		cool_Time.attack_CoolTime = 0;
		cool_Time.attack_CoolTime_Cnt = 0;

		cool_Time.knockBack_Time = 0;

		hp.maxHP = 0;
		hp.curHP = 0;
		hp.backHP = 0;

		hp.state = HP_UPDATE_STATE_E::EMPTY;
	}

	// HP 변수 셋팅
	void setting_HP()
	{
		// 체력 초기화
		hp.img_HP_BG = new image;
		hp.img_HP_BG = IMAGEMANAGER->findImage("enemy_HP_Bar");
		hp.rc_HP_BG = RectMake(pos.center.x - hp.img_HP_BG->getWidth() / 2, 
			pos.center.y + IMAGEMANAGER->findImage(img.imgName)->getFrameHeight() / 2, 
			hp.img_HP_BG->getWidth(), hp.img_HP_BG->getHeight());

		hp.img_HP_Front = new image;
		hp.img_HP_Front = IMAGEMANAGER->findImage("enemy_HP");
		hp.rc_HP_Front = RectMake(pos.center.x - hp.img_HP_Front->getWidth() / 2,
			pos.center.y + IMAGEMANAGER->findImage(img.imgName)->getFrameHeight() / 2,
			hp.img_HP_Front->getWidth(), hp.img_HP_Front->getHeight());

		hp.img_HP_Back_Name = "enemy_HP_Hit";
		hp.img_HP_Back = new image;
		hp.img_HP_Back = IMAGEMANAGER->findImage(hp.img_HP_Back_Name);
		hp.rc_HP_Back = RectMake(pos.center.x - hp.img_HP_Back->getWidth() / 2,
			pos.center.y + IMAGEMANAGER->findImage(img.imgName)->getFrameHeight() / 2,
			hp.img_HP_Back->getWidth(), hp.img_HP_Back->getHeight());

		hp.state = HP_UPDATE_STATE_E::EMPTY;
	}

	// HP 게이지 위치 갱신
	void update_HP_Pos()
	{
		hp.rc_HP_BG = RectMake(pos.center.x - hp.img_HP_BG->getWidth() / 2,
			pos.center.y + IMAGEMANAGER->findImage(img.imgName)->getFrameHeight() / 2,
			hp.img_HP_BG->getWidth(), hp.img_HP_BG->getHeight());

		hp.rc_HP_Front = RectMake(pos.center.x - hp.img_HP_Front->getWidth() / 2,
			pos.center.y + IMAGEMANAGER->findImage(img.imgName)->getFrameHeight() / 2,
			hp.rc_HP_Front.right - hp.rc_HP_Front.left, hp.img_HP_Front->getHeight());

		hp.img_HP_Back = IMAGEMANAGER->findImage(hp.img_HP_Back_Name);
		hp.rc_HP_Back = RectMake(pos.center.x - hp.img_HP_Back->getWidth() / 2,
			pos.center.y + IMAGEMANAGER->findImage(img.imgName)->getFrameHeight() / 2,
			hp.rc_HP_Back.right - hp.rc_HP_Back.left, hp.img_HP_Back->getHeight());
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

		bool_V.Attack_Hit = false;

		bool_V.player_Attack_Hit = false;
	}

	// 에너미의 타입에 따라 스텟을 넣어준다.
	void find_EnemyStatus()
	{
		switch (status.type)
		{
		case EnemyType::SOLDIER:
			status.hp = 45;
			status.attack = 10;
			status.def = 0;
			status.speed = ENEMYSPEED;
			status.gold = 100;

			cool_Time.attack_CoolTime = ENEMYATTACKCOOLTIME;
			cool_Time.attack_CoolTime_Cnt = 0;

			hp.maxHP = status.hp;
			hp.curHP = status.hp;;
			hp.backHP = status.hp;;

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

		// 중점 저장
		pos.center.x = x_V * TILE_SIZE_X + TILE_SIZE_X / 2;
		pos.center.y = y_V * TILE_SIZE_Y + TILE_SIZE_Y / 2;

		// HP 셋팅
		setting_HP();

		// 이미지 저장 (계산을 편하게 하기 위해)
		image* temp_Img = new image;
		temp_Img = IMAGEMANAGER->findImage(img.imgName);

		// 애니메이션을 그릴때 사용하는 렉트
		pos.ani_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth(), temp_Img->getFrameHeight());
		pos.ani_Rc.bottom -= 10;
		pos.ani_Rc.top -= 10;

		// 에너미의 피격 범위 렉트
		pos.hit_Range_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth() / 2, temp_Img->getFrameHeight() / 2);

		// 에너미 인식 범위 렉트
		pos.find_Range_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth() * 3, temp_Img->getFrameHeight());

	}

	// 에너미의 렉트를 갱신
	void update_Rect()
	{
		// 이미지 저장 (계산을 편하게 하기 위해)
		image* temp_Img = new image;
		temp_Img = IMAGEMANAGER->findImage(img.imgName);

		// 애니메이션을 그릴때 사용하는 렉트
		pos.ani_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth(), temp_Img->getFrameHeight());
		pos.ani_Rc.bottom -= 10;
		pos.ani_Rc.top -= 10;

		// 에너미의 피격 범위 렉트
		pos.hit_Range_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth() / 2, temp_Img->getFrameHeight() / 2);

		// 에너미 인식 범위 렉트
		pos.find_Range_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth() * 3, temp_Img->getFrameHeight());
	}

	// 에너미의 애니메이션 셋팅 (매개변수 : 이미지 키값, 애니 키값)
	void set_Ani(string imgName, string aniName)
	{
		// 이미지 키값
		img.imgName = imgName;

		// 애니 키값
		img.aniName = aniName;
		img.ani = KEYANIMANAGER->findAnimation(img.aniName);

		// 이미지 저장 (계산을 편하게 하기 위해)
		image* temp_Img = new image;
		temp_Img = IMAGEMANAGER->findImage(img.imgName);

		// 이미지를 그릴 렉트 갱신
		pos.ani_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth(), temp_Img->getFrameHeight());
		pos.ani_Rc.bottom -= 10;
		pos.ani_Rc.top -= 10;
	}

	// 애니메이션 체인저
	void ani_Changer(string StateName)
	{
		switch (status.type)
		{
			case EnemyType::SOLDIER:
				if (status.dir == EnemyDirection::LEFT)
				{
					// 대기
					if (StateName == "Idle") set_Ani("soldier_Idle", "soldier_Idle_Left_Ani");
					// 이동
					if (StateName == "Walk") set_Ani("soldier_Walk", "soldier_Walk_Left_Ani");
					// 피격
					if (StateName == "Hit") set_Ani("soldier_Hit", "soldier_Hit_Right_Ani");
					// 공격
					if (StateName == "Attack_A") set_Ani("soldier_Attack", "soldier_Attack_Left_Ani");

				}

				if (status.dir == EnemyDirection::RIGHT)
				{
					// 대기
					if (StateName == "Idle") set_Ani("soldier_Idle", "soldier_Idle_Right_Ani");
					// 이동
					if (StateName == "Walk") set_Ani("soldier_Walk", "soldier_Walk_Right_Ani");
					// 피격
					if (StateName == "Hit") set_Ani("soldier_Hit", "soldier_Hit_Left_Ani");
					// 공격
					if (StateName == "Attack_A") set_Ani("soldier_Attack", "soldier_Attack_Right_Ani");

				}

				break;
		}
	}

	// 이미지 체인저
	void img_Changer()
	{
		// 피격 이미지를 랜덤으로 정하기 위해
		short num;
		num = RND->getInt(2);

		// 이미지 키값을 넣어준다.
		img.imgName = "soldier_Hit";

		switch (status.type)
		{
			case EnemyType::SOLDIER:
				// 방향에 맞게 피격 이미지를 넣어준다.
				if (status.dir == EnemyDirection::LEFT)
				{
					// 이미지를 넣어준다.
					if (num == 0)
					{
						img.curX = 0;
						img.curY = 0;
					}

					if (num == 1)
					{
						img.curX = 1;
						img.curY = 0;
					}

					// 이미지를 넣었다는 체크를 켜준다. (중복 방지)
					bool_V.hitCheck = true;

				}

				if (status.dir == EnemyDirection::RIGHT)
				{
					// 이미지를 넣어준다.
					if (num == 0)
					{
						img.curX = 0;
						img.curY = 1;
					}

					if (num == 1)
					{
						img.curX = 1;
						img.curY = 1;
					}

					// 이미지를 넣었다는 체크를 켜준다. (중복 방지)
					bool_V.hitCheck = true;

				}

				break;

		}
	}

	// 공격 렉트 생성
	void make_Attack_Rect()
	{
		image* tempImg = IMAGEMANAGER->findImage(img.imgName);

		// 방향에 따라 그쪽 방향으로 렉트를 만들어준다.
		if (status.dir == EnemyDirection::LEFT)
		{
			pos.Attack_Rc = RectMake(pos.center.x - tempImg->getFrameWidth() / 2, pos.center.y - tempImg->getFrameHeight() / 2,
				tempImg->getFrameWidth() / 2, tempImg->getFrameHeight());
		}

		if (status.dir == EnemyDirection::RIGHT)
		{
			pos.Attack_Rc = RectMake(pos.center.x, pos.center.y - tempImg->getFrameHeight() / 2,
				tempImg->getFrameWidth() / 2, tempImg->getFrameHeight());
		}
	}

	// 체력 게이지 업데이트
	void update_HP()
	{
		// 체력이 회복하고 있는중
		if (hp.state == HP_UPDATE_STATE_E::HEAL)
		{
			// 회복중일때는 back right가 바로 갱신 된다.
			hp.rc_HP_Back.right = hp.rc_HP_Back.left + (hp.curHP * hp.img_HP_Back->getWidth() / hp.maxHP);

			// 회복중일때는 front right가 천천히 증가한다.
			hp.rc_HP_Front.right += HP_PLUS_SPEED_E;

			// front right가 back right와 같거나 그 이상이라면 최대라는 뜻
			if (hp.rc_HP_Front.right >= hp.rc_HP_Back.right)
			{
				// 넘어갔을 경우 값 보정
				hp.rc_HP_Front.right = hp.rc_HP_Back.right;

				// 체력 상태를 교체한다.
				hp.state = HP_UPDATE_STATE_E::EMPTY;
			}
		}

		// 체력이 감소하는 중이다.
		if (hp.state == HP_UPDATE_STATE_E::HIT)
		{
			// 감소중일때는 front right가 바로 갱신 된다.
			hp.rc_HP_Front.right = hp.rc_HP_Front.left + (hp.curHP * hp.img_HP_Front->getWidth() / hp.maxHP);

			// 감소중일때는 back right가 천천히 감소한다.
			hp.rc_HP_Back.right -= HP_MINUS_SPEED_E;

			// back right가 front right와 같거나 그 이하라면 
			if (hp.rc_HP_Back.right <= hp.rc_HP_Front.right)
			{
				// 넘어갔을 경우 값 보정
				hp.rc_HP_Back.right = hp.rc_HP_Front.right;

				// 체력 상태를 교체한다.
				hp.state = HP_UPDATE_STATE_E::EMPTY;
			}
		}

		// HP바 위치갱신
		update_HP_Pos();
	}
};


//형길이형 지금 기분이 어떠신지요?
//치킨치킨한 기분이었읍니다.
