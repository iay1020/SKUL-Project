#pragma once

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

	short				attack;			// ���ʹ��� ���ݷ��� ��´�.
	short				def;			// ���ʹ��� ������ ��´�.
	short				speed;			// ���ʹ��� �̵����� ��´�.

	short				gold;			// ���ʹ̰� ����� ��差�� ��´�.
	
};

// ���ʹ��� ��ǥ ����ü
struct EnemyPos
{
	POINTFLOAT			center;			// ���ʹ��� ������ ��´�.
	RECT				ani_Rc;			// ���ʹ��� �ִϸ��̼� ��Ʈ�� ��´�.
	RECT				hit_Range_Rc;	// ���ʹ��� �ǰ� ���� ��Ʈ


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

// ���ʹ��� ���� ����ü
struct EnemyInfo
{
	EnemyStatus			status;			// ���ʹ��� ���� ����
	EnemyImage			img;			// ���ʹ��� �̹��� ����
	EnemyPos			pos;			// ���ʹ��� ��ǥ ����
	EnemyBoolValue		bool_V;			// ���ʹ��� bool ����

	// ��� �ʱ�ȭ
	void All_ReSet()
	{
		// �������ͽ� �ʱ�ȭ
		status.type = EnemyType::NONE;
		status.dir = EnemyDirection::NONE;
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

		// bool �ʱ�ȭ
		bool_V.idleCheck = false;
		bool_V.walkCheck = false;
		bool_V.attackCheck = false;
		bool_V.hitCheck = false;

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
			status.attack = 10;
			status.def = 0;
			status.speed = 10;
			status.gold = 100;

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

		// ��ǥ ����
		// ���� ����
		pos.center.x = x_V;
		pos.center.y = y_V;

		// �̹��� ���� (����� ���ϰ� �ϱ� ����)
		image* temp_Img = new image;
		temp_Img = IMAGEMANAGER->findImage(img.imgName);

		// �ִϸ��̼��� �׸��� ����ϴ� ��Ʈ
		pos.ani_Rc = RectMakeCenter(x_V, y_V, temp_Img->getFrameWidth(), temp_Img->getFrameHeight());

		// ���ʹ��� �ǰ� ���� ��Ʈ
		pos.hit_Range_Rc = RectMakeCenter(x_V, y_V, temp_Img->getFrameWidth() / 2, temp_Img->getFrameHeight() / 2);
	}

};


//�������� ���� ����� �������?
//ġŲġŲ�� ����̾����ϴ�.
