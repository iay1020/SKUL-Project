#pragma once

// ���ʹ��� �⺻ �̵��ӵ�
#define ENEMYSPEED	3

// ���ʹ��� ���� ��Ÿ��
#define ENEMYATTACKCOOLTIME 50

// ���ʹ��� �ǰ� �� ƽ�� �з����� �Ÿ�
#define ENEMYKNOCKBACK_RANGE	1

// ���ʹ��� �ǰ� �ð�
#define ENEMYKNOCKBACK_TIME	50

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


// ���ʹ� Ÿ�� enum
enum class EnemyType
{
	NONE,			// NULL                                                                            
	SOLDIER			// ����

};

// ���ʹ��� ���� enum
enum class EnemyDirection
{
	NONE,			// NULL
	LEFT,			// ����
	RIGHT			// ������
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
	
};

// ���ʹ��� ��ǥ ����ü
struct EnemyPos
{
	POINTFLOAT			center;				// ���ʹ��� ������ ��´�.
	RECT				ani_Rc;				// ���ʹ��� �ִϸ��̼� ��Ʈ�� ��´�.
	RECT				hit_Range_Rc;		// ���ʹ��� �ǰ� ���� ��Ʈ
	RECT				find_Range_Rc;		// ���ʹ� �ν� ����
	RECT				attack_Range_Rc;	// ���ʹ� ���� ����

	RECT				Attack_Rc;			// ���ʹ� ���� ��Ʈ

	float				fall_Power;			// ���ʹ��� �߶� ���� ����

	float				lerp_Start;			// ���� ���� �ð�
};

// ���ʹ��� �̹��� ����ü
struct EnemyImage
{
	string				imgName;		// ���ʹ��� �̹��� Ű���� ��´�.
	string				aniName;		// ���ʹ��� �ִϸ��̼� Ű���� ��´�.	
	animation*			ani;			// ���ʹ��� �ִϸ��̼��� ��´�.

	short				curX, curY;		// ���ʹ��� �̹��� x, y�� ��´�.

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

	bool				im_Hit;				// �� �¾Ҵ�
	bool				im_Death;			// �� �׾���.

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
		pos.fall_Power = 0;
		pos.lerp_Start = 0;

		// bool �ʱ�ȭ
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;

		bool_V.Attack_Hit = false;

		bool_V.player_Attack_Hit = false;
		
		bool_V.lerping = false;

		bool_V.im_Hit = false;
		bool_V.im_Death = false;

		// CoolTime �ʱ�ȭ
		cool_Time.attack_CoolTime = 0;
		cool_Time.attack_CoolTime_Cnt = 0;

		cool_Time.knockBack_Time = 0;

		hp.maxHP = 0;
		hp.curHP = 0;
		hp.backHP = 0;

		hp.state = HP_UPDATE_STATE_E::EMPTY;
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

		// ���ʹ� �ν� ���� ��Ʈ
		pos.find_Range_Rc = RectMakeCenter(pos.center.x, pos.center.y, temp_Img->getFrameWidth() * 3, temp_Img->getFrameHeight());
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

				break;
		}
	}

	// �̹��� ü����
	void img_Changer()
	{
		// �ǰ� �̹����� �������� ���ϱ� ����
		short num;
		num = RND->getInt(2);

		// �̹��� Ű���� �־��ش�.
		img.imgName = "soldier_Hit";

		switch (status.type)
		{
			case EnemyType::SOLDIER:
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

		}
	}

	// ���� ��Ʈ ����
	void make_Attack_Rect()
	{
		image* tempImg = IMAGEMANAGER->findImage(img.imgName);

		// ���⿡ ���� ���� �������� ��Ʈ�� ������ش�.
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
};


//�������� ���� ����� �������?
//ġŲġŲ�� ����̾����ϴ�.
