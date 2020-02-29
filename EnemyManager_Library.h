#pragma once

// ���ʹ��� �⺻ �̵��ӵ�
#define ENEMYSPEED	3

// ���ʹ��� ���� ��Ÿ��
#define ENEMYATTACKCOOLTIME 50

// ���ʹ��� �ǰ� �� ƽ�� �з����� �Ÿ�
#define ENEMYKNOCKBACK_RANGE	1

// ���ʹ��� �ǰ� �ð�
#define ENEMYKNOCKBACK_TIME	25

// ���ʹ̰� �ǰ� �� �з����� �ð�
#define ENEMYKNOCKBACKING_TIME	0.1f

// ���ʹ̰� �ǰ� �� �з����� �Ÿ� 
#define ENEMYKNOCKBACK_RANGE	50

// ���ʹ��� �߷�
#define ENEMY_GRAVITY	0.5f

// ü���� �������� ���ǵ�
#define HP_MINUS_SPEED_E	2

// ü���� �ö󰡴� ���ǵ�
#define HP_PLUS_SPEED_E		2

// ���ʹ��� ���� �� ������
#define NEXT_ATTACK_DELAY 50


// ���ʹ� Ÿ�� enum
enum class EnemyType
{
	NONE,			// NULL                                                                            
	SOLDIER,		// ����
	ARCHER			// �ü�
};

// ���ʹ��� ���� enum
enum class EnemyDirection
{
	NONE,			// NULL
	LEFT,			// ����
	RIGHT			// ������
};

// ���ʹ��� ���� enum
enum class EnemyStateEnum
{
	NONE,
	IDLE,
	WALK,
	FALL,
	HIT,
	ATK_A,
	ATK_B,
	SKILL_A,
	SKILL_B
};


// ü�� ���� ���� Enum
enum class HP_UPDATE_STATE_E
{
	EMPTY,		// NULL
	HEAL,		// ȸ����
	HIT			// �ǰ���
};

// ���ʹ� ü�� �̹���
struct Enemy_Hp_Img
{
	RECT					rc_HP_BG;			// ü�¹� ���
	RECT					rc_HP_Back;			// ü�¹� ��
	RECT					rc_HP_Front;		// ü�¹� ��

	image*					img_HP_BG;			// ü�¹� ���
	image*					img_HP_Back;		// ü�¹� �� �̹����� ������ ����
	string					img_HP_Back_Name;	// ü�¹� �� �̹��� Ű���� ������ ����
	image*					img_HP_Front;		// ü�¹� �� �̹����� ������ ����

	HP_UPDATE_STATE_E		state;				// ü�� ������Ʈ ����

	short					maxHP;				// �ƽ� HP ������ ��´�.
	short					curHP;				// ���� HP ������ ��´�.
	short					backHP;				// �� HP ������ ��´�.

};

// ���ʹ� ���� ����ü
struct EnemyStatus
{
	EnemyType			type;			// ���ʹ��� Ÿ���� ��´�.
	EnemyDirection		dir;			// ���ʹ��� ������ ��´�.

	short				hp;				// ���ʹ��� ü���� ��´�.
	short				attack;			// ���ʹ��� ���ݷ��� ��´�.
	short				def;			// ���ʹ��� ������ ��´�.
	short				speed;			// ���ʹ��� �̵����� ��´�.

	short				gold;			// ���ʹ̰� ����� ��差�� ��´�.

	short				show_Attack;	// ��µǴ� ������ ��

	EnemyStateEnum		state;			// ���ʹ��� ����
	
};

// ���ʹ��� ��ǥ ����ü
struct EnemyPos
{
	POINTFLOAT			center;					// ���ʹ��� ������ ��´�.
	RECT				ani_Rc;					// ���ʹ��� �ִϸ��̼� ��Ʈ�� ��´�.
	RECT				hit_Range_Rc;			// ���ʹ��� �ǰ� ���� ��Ʈ
	RECT				find_Range_Rc;			// ���ʹ� �ν� ����
	RECT				attack_Range_Rc;		// ���ʹ� ���� ����
	RECT				long_Attack_Ranger_RC;	// ���ʹ� ���Ÿ� ���� ����

	RECT				Attack_Rc;				// ���ʹ� ���� ��Ʈ

	float				fall_Power;				// ���ʹ��� �߶� ���� ����

	float				lerp_Start;				// ���� ���� �ð�
	float				lerp_Time;				// ���� �ð�
	float				lerp_Range;				// ���� �Ÿ�
	
	POINTFLOAT			damege_Center;			// ������ ��� ����
};

// ���ʹ��� �̹��� ����ü
struct EnemyImage
{
	string				imgName;		// ���ʹ��� �̹��� Ű���� ��´�.
	string				aniName;		// ���ʹ��� �ִϸ��̼� Ű���� ��´�.	
	animation*			ani;			// ���ʹ��� �ִϸ��̼��� ��´�.

	short				curX, curY;		// ���ʹ��� �̹��� x, y�� ��´�.

};

// ���ʹ��� ���� ���� ����ü
struct EnemyOperater
{
	int				after_Delay;		// ���� �� ������
	int				after_Delay_Cnt;	// ���� �� ������ ī��Ʈ

	short			curX, curY;			// �������̹��� ���� ����
	short			imgFPS;				// ������ �ӵ�
	short			buffer;				// ������ Ƚ����ŭ ����ؾ� �ϴ���
	float			curTime;			// ���� �ð�

	bool			loop;				// �ѹ��� ����ؾ� �ϴ��� ������ ����ؾ� �ϴ���
	bool			revers;				// ������ �̹����� ���ٷ� ����� �Ǿ�� �ϴ���
	bool			start;				// ������ ������ �����ϴ��� ����
	bool			saveTime;			// ���� �ð��� �޾�����

};

// ���ʹ��� bool ����ü
struct EnemyBoolValue
{
	bool				idleCheck;			// ��� �ִϸ��̼� ��ü üũ
	bool				walkCheck;			// �̵� �ִϸ��̼� ��ü üũ
	bool				attackCheck;		// ���� �ִϸ��̼� ��ü üũ
	bool				hitCheck;			// �ǰ� �ֹ̳��̼� ��ü üũ

	bool				Attack_Hit;			// ������ �¾Ҵ���

	bool				player_Attack_Hit;	// �÷��̾��� ������ �¾Ҵ���

	bool				lerping;			// ����������
	bool				atk_End;			// ���� ��
	bool				next_Atk_Delay;		// ���� ���� �غ���

	bool				im_Hit;				// �� �¾Ҵ�
	bool				im_Death;			// �� �׾���.

	bool				Critical_Hit;		// ġ��Ÿ ������ �޾Ҵ���

	bool				find_Player;		// �÷��̾ �߰��ߴ�.

};

// ���ʹ� ��Ÿ��
struct EnemyCoolTime
{
	short				attack_CoolTime;		// ���� ��Ÿ��
	short				attack_CoolTime_Cnt;	// ���� ��Ÿ�� ī����

	short				knockBack_Time;			// �˹� �ð�

};

// ���ʹ��� ���� ����ü
struct EnemyInfo
{
	EnemyStatus			status;			// ���ʹ��� ���� ����
	EnemyImage			img;			// ���ʹ��� �̹��� ����
	EnemyPos			pos;			// ���ʹ��� ��ǥ ����
	EnemyBoolValue		bool_V;			// ���ʹ��� bool ����
	EnemyCoolTime		cool_Time;		// ���ʹ��� ��Ÿ�� ����
	Enemy_Hp_Img		hp;				// ���ʹ��� HP ����
	EnemyOperater		oper;			// ���ʹ��� ���� ���� ����
 
	// ��� �ʱ�ȭ
	void All_ReSet()
	{
		// �������ͽ� �ʱ�ȭ
		status.type = EnemyType::NONE;
		status.dir = EnemyDirection::NONE;
		status.hp = 0;
		status.attack = 0;
		status.def = 0;
		status.speed = 0;
		status.gold = 0;
		status.show_Attack = 0;
		status.state = EnemyStateEnum::NONE;

		// �̹��� �ʱ�ȭ
		img.ani = new animation;
		img.imgName = "";
		img.aniName = "";
		img.curX = img.curY = 0;

		// ��ǥ �ʱ�ȭ
		pos.center.x = pos.center.y = 0;
		pos.ani_Rc = { 0, 0, 0, 0 };
		pos.hit_Range_Rc = { 0, 0, 0, 0 };
		pos.find_Range_Rc = { 0, 0, 0, 0 };
		pos.attack_Range_Rc = { 0, 0, 0, 0 };
		pos.Attack_Rc = { 0, 0, 0, 0 };
		pos.long_Attack_Ranger_RC = { 0,0,0,0 };
		pos.fall_Power = 0;
		pos.lerp_Start = 0;
		pos.lerp_Time = 0;
		pos.lerp_Range = 0;
		pos.damege_Center.x = pos.damege_Center.y = 0;

		// bool �ʱ�ȭ
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;

		bool_V.Attack_Hit = false;

		bool_V.player_Attack_Hit = false;
		
		bool_V.lerping = false;
		bool_V.atk_End = false;
		bool_V.next_Atk_Delay = false;

		bool_V.im_Hit = false;
		bool_V.im_Death = false;

		bool_V.Critical_Hit = false;

		bool_V.find_Player = false;
		

		// CoolTime �ʱ�ȭ
		cool_Time.attack_CoolTime = 0;
		cool_Time.attack_CoolTime_Cnt = 0;

		cool_Time.knockBack_Time = 0;

		hp.maxHP = 0;
		hp.curHP = 0;
		hp.backHP = 0;

		hp.state = HP_UPDATE_STATE_E::EMPTY;

		// ���� ���� �ʱ�ȭ
		oper.after_Delay = NEXT_ATTACK_DELAY;
		oper.after_Delay_Cnt = 0;

		oper.curX = oper.curY = 0;
		oper.imgFPS = oper.buffer = 0;
		oper.curTime = 0;
		oper.loop = false;
		oper.revers = false;
		oper.start = false;
		oper.saveTime = false;

	}

	// HP ���� ����
	void setting_HP()
	{
		// ü�� �ʱ�ȭ
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

	// HP ������ ��ġ ����
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

	// ���� �ʱ�ȭ
	void state_ReSet()
	{
		// bool �ʱ�ȭ
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;
	}

	// bool �ʱ�ȭ 
	void bool_ReSet()
	{
		// bool �ʱ�ȭ
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;

		bool_V.Attack_Hit = false;

		bool_V.player_Attack_Hit = false;
	}

	// ���ʹ��� Ÿ�Կ� ���� ������ �־��ش�.
	void find_EnemyStatus()
	{
		switch (status.type)
		{
		case EnemyType::SOLDIER:
			status.hp = 545;
			status.attack = 15;
			status.def = 0;
			status.speed = ENEMYSPEED;
			status.gold = 100;

			cool_Time.attack_CoolTime = ENEMYATTACKCOOLTIME;
			cool_Time.attack_CoolTime_Cnt = 0;

			hp.maxHP = status.hp;
			hp.curHP = status.hp;
			hp.backHP = status.hp;

			break;

		case EnemyType::ARCHER:
			status.hp = 300;
			status.attack = 10;
			status.def = 0;
			status.speed = ENEMYSPEED;
			status.gold = 150;

			cool_Time.attack_CoolTime = ENEMYATTACKCOOLTIME;
			cool_Time.attack_CoolTime_Cnt = 0;

			hp.maxHP = status.hp;
			hp.curHP = status.hp;
			hp.backHP = status.hp;

			break;
		}
	}

	// ���� ������ �����Ѵ�.
	void make_Attack_Range()
	{
		image* img_T = new image;
		img_T = IMAGEMANAGER->findImage(img.imgName);

		switch (status.type)
		{
			case EnemyType::SOLDIER:
				if (status.dir == EnemyDirection::RIGHT)
				{
					pos.attack_Range_Rc = RectMake(pos.center.x, pos.center.y - img_T->getFrameHeight() / 2,
						img_T->getFrameWidth(), img_T->getFrameHeight());
				}
				if (status.dir == EnemyDirection::LEFT)
				{
					pos.attack_Range_Rc = RectMake(pos.center.x - img_T->getFrameWidth(), pos.center.y - img_T->getFrameHeight() / 2,
						img_T->getFrameWidth(), img_T->getFrameHeight());
				}

				pos.lerp_Range = img_T->getFrameWidth();

				break;

			case EnemyType::ARCHER:
				if (status.dir == EnemyDirection::RIGHT)
				{
					pos.long_Attack_Ranger_RC = RectMake(pos.center.x, pos.center.y - img_T->getFrameHeight() / 2,
						img_T->getFrameWidth() * 4, img_T->getFrameHeight());
				}
				if (status.dir == EnemyDirection::LEFT)
				{
					pos.long_Attack_Ranger_RC = RectMake(pos.center.x - img_T->getFrameWidth() * 4, pos.center.y - img_T->getFrameHeight() / 2,
						img_T->getFrameWidth() * 4, img_T->getFrameHeight());
				}
			
				break;
		}
		
	}

	// ���ʹ� ���� ���� (�Ű����� : Ÿ��, ����, �̹��� Ű��, �ִϸ��̼� Ű��, ���� x, ���� y)
	void Create_Enemy(EnemyType type_V, EnemyDirection dir_V,
		string imgName, string aniName,	float x_V, float y_V)
	{
		// �������ͽ� ����
		status.type = type_V;
		status.dir = dir_V;

		// Ÿ���� �̿��Ͽ� ���ʹ��� ������ �־��ش�.
		find_EnemyStatus();

		// �̹��� ����
		img.imgName = imgName;
		img.aniName = aniName;
		img.ani = KEYANIMANAGER->findAnimation(aniName);
		img.ani->start();

		// ���� ����
		pos.center.x = x_V * TILE_SIZE_X + TILE_SIZE_X / 2;
		pos.center.y = y_V * TILE_SIZE_Y + TILE_SIZE_Y / 2;

		// HP ����
		setting_HP();

		// �̹��� ���� (����� ���ϰ� �ϱ� ����)
		image* temp_Img = new image;
		temp_Img = IMAGEMANAGER->findImage(img.imgName);

		// �ִϸ��̼��� �׸��� ����ϴ� ��Ʈ
		pos.ani_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth(), temp_Img->getFrameHeight());
		pos.ani_Rc.bottom -= 10;
		pos.ani_Rc.top -= 10;

		// ���ʹ��� �ǰ� ���� ��Ʈ
		pos.hit_Range_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth() / 2, temp_Img->getFrameHeight() / 2);

		// ���ʹ� �ν� ���� ��Ʈ
		pos.find_Range_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth() * 3, temp_Img->getFrameHeight());

		// ���ʹ� ���� ���� ��Ʈ
		make_Attack_Range();

	}

	// ���ʹ��� ��Ʈ�� ����
	void update_Rect()
	{
		// �̹��� ���� (����� ���ϰ� �ϱ� ����)
		image* temp_Img = new image;
		temp_Img = IMAGEMANAGER->findImage(img.imgName);

		// �ִϸ��̼��� �׸��� ����ϴ� ��Ʈ
		pos.ani_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth(), temp_Img->getFrameHeight());
		pos.ani_Rc.bottom -= 10;
		pos.ani_Rc.top -= 10;

		// ���ʹ��� �ǰ� ���� ��Ʈ
		pos.hit_Range_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth() / 2, temp_Img->getFrameHeight() / 2);

		// ���ʹ� �ν� ���� ��Ʈ (�÷��̾ �߰��ϱ� ������ �ڽ��� �ٶ󺸴� ����ۿ� ã�� ���Ѵ�.
		if (!bool_V.find_Player)
		{
			if (status.dir == EnemyDirection::LEFT)
				pos.find_Range_Rc = RectMakeCenter(pos.center.x - temp_Img->getFrameWidth(), pos.center.y, temp_Img->getFrameWidth() * 2, temp_Img->getFrameHeight());
			if (status.dir == EnemyDirection::RIGHT)
				pos.find_Range_Rc = RectMakeCenter(pos.center.x + temp_Img->getFrameWidth(), pos.center.y, temp_Img->getFrameWidth() * 2, temp_Img->getFrameHeight());
		}

		// �÷��̾ �߰��Ѵٸ� �ν� ������ �þ��. ( �� ���̵��)
		if (bool_V.find_Player)
		{
			pos.find_Range_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth() * 4, temp_Img->getFrameHeight());
		}
	}

	// ���ʹ��� �ִϸ��̼� ���� (�Ű����� : �̹��� Ű��, �ִ� Ű��)
	void set_Ani(string imgName, string aniName)
	{
		// �̹��� Ű��
		img.imgName = imgName;

		// �ִ� Ű��
		img.aniName = aniName;
		img.ani = KEYANIMANAGER->findAnimation(img.aniName);

		// �̹��� ���� (����� ���ϰ� �ϱ� ����)
		image* temp_Img = new image;
		temp_Img = IMAGEMANAGER->findImage(img.imgName);

		// �̹����� �׸� ��Ʈ ����
		pos.ani_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth(), temp_Img->getFrameHeight());
		pos.ani_Rc.bottom -= 10;
		pos.ani_Rc.top -= 10;
	}

	// �ִϸ��̼� ü����
	void ani_Changer(string StateName)
	{
		switch (status.type)
		{
			case EnemyType::SOLDIER:
				if (status.dir == EnemyDirection::LEFT)
				{
					// ���
					if (StateName == "Idle") set_Ani("soldier_Idle", "soldier_Idle_Left_Ani");
					// �̵�
					if (StateName == "Walk") set_Ani("soldier_Walk", "soldier_Walk_Left_Ani");
					// �ǰ�
					if (StateName == "Hit") set_Ani("soldier_Hit", "soldier_Hit_Right_Ani");
					// ����
					if (StateName == "Attack_A") set_Ani("soldier_Attack", "soldier_Attack_Left_Ani");

				}

				if (status.dir == EnemyDirection::RIGHT)
				{
					// ���
					if (StateName == "Idle") set_Ani("soldier_Idle", "soldier_Idle_Right_Ani");
					// �̵�
					if (StateName == "Walk") set_Ani("soldier_Walk", "soldier_Walk_Right_Ani");
					// �ǰ�
					if (StateName == "Hit") set_Ani("soldier_Hit", "soldier_Hit_Left_Ani");
					// ����
					if (StateName == "Attack_A") set_Ani("soldier_Attack", "soldier_Attack_Right_Ani");

				}

				// ����� ���� �غ� �� ������ �����ϱ� ������ �ִϸ��̼��� ������ �ʴ´�.

				break;

			case EnemyType::ARCHER:
				if (status.dir == EnemyDirection::LEFT)
				{
					// ���
					if (StateName == "Idle") set_Ani("archer_Idle", "archer_Idle_Left_Ani");
					// �̵�
					if (StateName == "Walk") set_Ani("archer_Walk", "archer_Walk_Left_Ani");
					// �ǰ�
					if (StateName == "Hit") set_Ani("archer_Hit", "archer_Hit_Right_Ani");
					// ����
					if (StateName == "Attack_A") set_Ani("archer_Attack", "archer_Attack_Left_Ani");

				}

				if (status.dir == EnemyDirection::RIGHT)
				{
					// ���
					if (StateName == "Idle") set_Ani("archer_Idle", "archer_Idle_Right_Ani");
					// �̵�
					if (StateName == "Walk") set_Ani("archer_Walk", "archer_Walk_Right_Ani");
					// �ǰ�x
					if (StateName == "Hit") set_Ani("archer_Hit", "archer_Hit_Left_Ani");
					// ����
					if (StateName == "Attack_A") set_Ani("archer_Attack", "archer_Attack_Right_Ani");

				}

				img.ani->start();

				break;
		}
	}

	// �̹��� ü����
	void img_Changer()
	{
		// �ǰ� �̹����� �������� ���ϱ� ����
		short num;
		num = RND->getInt(2);

		switch (status.type)
		{
			case EnemyType::SOLDIER:
				// �̹��� Ű���� �־��ش�.
				img.imgName = "soldier_Hit";

				// ���⿡ �°� �ǰ� �̹����� �־��ش�.
				if (status.dir == EnemyDirection::LEFT)
				{
					// �̹����� �־��ش�.
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

					// �̹����� �־��ٴ� üũ�� ���ش�. (�ߺ� ����)
					bool_V.hitCheck = true;

				}

				if (status.dir == EnemyDirection::RIGHT)
				{
					// �̹����� �־��ش�.
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

					// �̹����� �־��ٴ� üũ�� ���ش�. (�ߺ� ����)
					bool_V.hitCheck = true;

				}

				break;

			case EnemyType::ARCHER:
				// �̹��� Ű���� �־��ش�.
				img.imgName = "archer_Hit";

				// ���⿡ �°� �ǰ� �̹����� �־��ش�.
				if (status.dir == EnemyDirection::LEFT)
				{
					// �̹����� �־��ش�.
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

					// �̹����� �־��ٴ� üũ�� ���ش�. (�ߺ� ����)
					bool_V.hitCheck = true;

				}

				if (status.dir == EnemyDirection::RIGHT)
				{
					// �̹����� �־��ش�.
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

					// �̹����� �־��ٴ� üũ�� ���ش�. (�ߺ� ����)
					bool_V.hitCheck = true;

				}

				break;

		}
	}

	// ���� ��Ʈ ����
	void make_Attack_Rect()
	{
		image* tempImg = IMAGEMANAGER->findImage(img.imgName);

		// ���⿡ ���� ���� �������� ��Ʈ�� ������ش�.
		if (status.dir == EnemyDirection::LEFT)
		{
			pos.Attack_Rc = RectMake(pos.center.x - tempImg->getFrameWidth() / 2 - 50 , pos.center.y - tempImg->getFrameHeight() / 2,
				tempImg->getFrameWidth() / 2 + 50 , tempImg->getFrameHeight());
		}

		if (status.dir == EnemyDirection::RIGHT)
		{
			pos.Attack_Rc = RectMake(pos.center.x, pos.center.y - tempImg->getFrameHeight() / 2,
				tempImg->getFrameWidth() / 2 + 50, tempImg->getFrameHeight());
		}
	}

	// ü�� ������ ������Ʈ
	void update_HP()
	{
		// ü���� ȸ���ϰ� �ִ���
		if (hp.state == HP_UPDATE_STATE_E::HEAL)
		{
			// ȸ�����϶��� back right�� �ٷ� ���� �ȴ�.
			hp.rc_HP_Back.right = hp.rc_HP_Back.left + (hp.curHP * hp.img_HP_Back->getWidth() / hp.maxHP);

			// ȸ�����϶��� front right�� õõ�� �����Ѵ�.
			hp.rc_HP_Front.right += HP_PLUS_SPEED_E;

			// front right�� back right�� ���ų� �� �̻��̶�� �ִ��� ��
			if (hp.rc_HP_Front.right >= hp.rc_HP_Back.right)
			{
				// �Ѿ�� ��� �� ����
				hp.rc_HP_Front.right = hp.rc_HP_Back.right;

				// ü�� ���¸� ��ü�Ѵ�.
				hp.state = HP_UPDATE_STATE_E::EMPTY;
			}
		}

		// ü���� �����ϴ� ���̴�.
		if (hp.state == HP_UPDATE_STATE_E::HIT)
		{
			// �������϶��� front right�� �ٷ� ���� �ȴ�.
			hp.rc_HP_Front.right = hp.rc_HP_Front.left + (hp.curHP * hp.img_HP_Front->getWidth() / hp.maxHP);

			// �������϶��� back right�� õõ�� �����Ѵ�.
			hp.rc_HP_Back.right -= HP_MINUS_SPEED_E;

			// back right�� front right�� ���ų� �� ���϶�� 
			if (hp.rc_HP_Back.right <= hp.rc_HP_Front.right)
			{
				// �Ѿ�� ��� �� ����
				hp.rc_HP_Back.right = hp.rc_HP_Front.right;

				// ü�� ���¸� ��ü�Ѵ�.
				hp.state = HP_UPDATE_STATE_E::EMPTY;
			}
		}

		// HP�� ��ġ����
		update_HP_Pos();
	}

	// ���ʹ� ���� ����
	void enemy_Attack_Pattern()
	{
		switch (status.type)
		{
		case EnemyType::SOLDIER:
			// ��Ÿ���� ���� �� �ִϸ��̼� ���� 
			if(!bool_V.attackCheck) cool_Time.attack_CoolTime_Cnt++;
			
			if (cool_Time.attack_CoolTime <= cool_Time.attack_CoolTime_Cnt && !bool_V.attackCheck)
			{
				// �ߺ� ���� 
				bool_V.attackCheck = true;

				// �ִ� ��ŸƮ
				img.ani->start();

				// ���� ��ŸƮ
				bool_V.lerping = true;

				// ���� �ð� ����
				pos.lerp_Start = TIMEMANAGER->getWorldTime();

				// ���� �ð�
				pos.lerp_Time = 0.5f;
				

			}		

			// ���� �����Ӹ� ���ݷ�Ʈ ����
			if (img.ani->getFramePos().x == 172) make_Attack_Rect();
			else pos.Attack_Rc = { 0,0,0,0 };

			break;

		case EnemyType::ARCHER:
			// �ִϸ��̼��� ������ ���� �ް� ���´�.
			
			// ��Ÿ���� ��� ���� �� ����ü �߻�

			// ����ü�� ���� �� �� ���� �ð� �ڿ� ��� ���·� ����

			break;

		//case EnemyType::NONE:
		//	break;

		}
	}

	// ������ ���� ���� �ʱ�ȭ
	void reset_FrameImage_oper()
	{
		oper.imgFPS = 0;
		oper.buffer = 0;
		oper.loop = false;
		oper.revers = false;
		oper.curX = 0;
		oper.curY = 0;
	}


	// ������ ���� ���� (�Ű����� : �����Ӽӵ�, Ƚ��, ����, ����, ������y ��ȣ
	void setting_FrameImage(short fps_, short buff_, bool loop_, bool revers_, short frameY)
	{
		oper.imgFPS = fps_;
		oper.buffer = buff_;
		oper.loop = loop_;
		oper.revers = revers_;

		// �ڿ��� ����ϴ���
		if (!oper.revers)
		{
			oper.curX = -1;
			oper.curY = frameY;
		}

		// �տ��� ����ϴ���
		if (oper.revers)
		{
			oper.curX = IMAGEMANAGER->findImage(img.imgName)->getMaxFrameX() + 1;
			oper.curY = frameY;
		}

	}

	// ������ ���� ����
	void start_Frame()
	{
		oper.start = true;

	}

	// ������ ���� ��ž
	void stop_Frame()
	{
		oper.start = false;

	}

	// ������ �̹��� ���� �Լ�
	void play_FrameImage()
	{
		if (!oper.saveTime)
		{
			oper.curTime = TIMEMANAGER->getWorldTime();

			oper.saveTime = true;
		}


		// ��ŸƮ�� ����������
		if (oper.start)
		{
			if (oper.curTime + oper.imgFPS <= TIMEMANAGER->getWorldTime())
			{
				oper.saveTime = false;

				// ������ �����Ѵ�.
				if (oper.loop)
				{
					if (!oper.revers)
					{
						oper.curX++;

						if (oper.curX > IMAGEMANAGER->findImage(img.imgName)->getMaxFrameX())
						{
							oper.curX = -1;
						}

					}

					if (oper.revers)
					{
						oper.curX--;

						if (oper.curX < 0)
						{
							oper.curX = IMAGEMANAGER->findImage(img.imgName)->getFrameWidth();
						}

					}
				}

				// �������� �������� �ʴ´�.
				if (!oper.loop)
				{
					if (!oper.revers)
					{
						oper.curX++;

						if (oper.curX > IMAGEMANAGER->findImage(img.imgName)->getMaxFrameX())
						{
							oper.start = false;
						}
					}

					if (oper.revers)
					{
						oper.curX--;

						if (oper.curX < 0)
						{
							oper.start = false;
						}
					}

				}
			}
		}

	}
	
};


//�������� ���� ����� �������?
//ġŲġŲ�� ����̾����ϴ�.
