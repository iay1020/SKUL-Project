#pragma once

#define ENEMYSPEED	3

#define ENEMYATTACKCOOLTIME 100

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


};

// ���ʹ��� �̹��� ����ü
struct EnemyImage
{
	string				imgName;		// ���ʹ��� �̹��� Ű���� ��´�.
	string				aniName;		// ���ʹ��� �ִϸ��̼� Ű���� ��´�.
	animation*			ani;			// ���ʹ��� �ִϸ��̼��� ��´�.

};

// ���ʹ��� bool ����ü
struct EnemyBoolValue
{
	bool				idleCheck;		// ��� �ִϸ��̼� ��ü üũ
	bool				walkCheck;		// �̵� �ִϸ��̼� ��ü üũ
	bool				attackCheck;	// ���� �ִϸ��̼� ��ü üũ
	bool				hitCheck;		// �ǰ� �ֹ̳��̼� ��ü üũ
};

// ���ʹ� ��Ÿ��
struct EnemyCoolTime
{
	short				attack_CoolTime;		// ���� ��Ÿ��
	short				attack_CoolTime_Cnt;	// ���� ��Ÿ�� ī����
};

// ���ʹ��� ���� ����ü
struct EnemyInfo
{
	EnemyStatus			status;			// ���ʹ��� ���� ����
	EnemyImage			img;			// ���ʹ��� �̹��� ����
	EnemyPos			pos;			// ���ʹ��� ��ǥ ����
	EnemyBoolValue		bool_V;			// ���ʹ��� bool ����
	EnemyCoolTime		cool_Time;		// ���ʹ��� ��Ÿ�� ����
 
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

		// ��ǥ �ʱ�ȭ
		pos.center.x = pos.center.y = 0;
		pos.ani_Rc = { 0, 0, 0, 0 };
		pos.hit_Range_Rc = { 0, 0, 0, 0 };
		pos.find_Range_Rc = { 0,0,0,0 };
		pos.attack_Range_Rc = { 0,0,0,0 };

		// bool �ʱ�ȭ
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;

		// CoolTime �ʱ�ȭ
		cool_Time.attack_CoolTime = 0;
		cool_Time.attack_CoolTime_Cnt = 0;

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
					if (StateName == "Hit") set_Ani("soldier_Hit", "soldier_Hit_Left_Ani");
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
					if (StateName == "Hit") set_Ani("soldier_Hit", "soldier_Hit_Right_Ani");
					// ����
					if (StateName == "Attack_A") set_Ani("soldier_Attack", "soldier_Attack_Right_Ani");

				}

				break;
		}
	}
};


//�������� ���� ����� �������?
//ġŲġŲ�� ����̾����ϴ�.
