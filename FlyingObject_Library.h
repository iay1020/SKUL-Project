#pragma once

// ������ �Ӹ��� ������� �ð�
#define SKUL_HEAD_DELETE_TIME 300

// ��ƼŬ�� ������� �ð�
#define PARTICLE_DELETE_TIME 50

// ȭ���� ������� �ð�
#define ARROW_DELETE_TIME 150

// ����ü�� �߷�
#define FLYINGOBJECT_GRAVITY 0.5f

// ����ü Ÿ�� Enum
enum class FLYINFOBJECT_TYPE
{
	NONE,							// NULL
	SKUL_HEAD,						// ���� �Ӹ�
	PARTICLE,						// ��ƼŬ
	ARROW							// ȭ��

};

// ����ü�� ���� Enum
enum class FLYINGOBJECT_DIRECTION
{
	NONE,							// NULL
	LEFT,							// ����
	RIGHT							// ������
};

// ����ü�� �⺻ ���� ����ü
struct FlyingObjectInfo
{
	FLYINFOBJECT_TYPE		type;			// ����ü Ÿ�� 

	image*					img;			// ����ü �̹��� ����
	animation*				ani;			// ����ü �ִϸ��̼� ����
	string					aniName;		// ����ü �ִϸ��̼� Ű�� ����
	POINTFLOAT				center;			// ����ü�� ����
	RECT					rc;				// ����ü�� ��Ʈ
	FLOAT					angle;			// ����ü�� ����
	FLOAT					speed;			// ����ü�� ���ǵ�
	FLOAT					gravity;		// ����ü�� �߷�
	FLYINGOBJECT_DIRECTION	dir;			// ����ü�� ����
	int						attack;			// ����ü�� ���ݷ�

	bool					isFrame;		// �̹����� ���������� �ƴ���

	short					Delete_Timer;	// ����ü�� ���� Ÿ�̸�

	bool					isFalling;		// ����ü�� �߶������� ����
	bool					isHit;			// ����ü�� �̹� �浹�� ���´���


	// ������ ����ִ� �Լ�
	void reset()
	{
		type = FLYINFOBJECT_TYPE::NONE;		// Ÿ�� �ʱ�ȭ
	
		img = new image;					// �̹��� �Ҵ�
		ani = new animation;				// �ִ� �Ҵ�
		aniName = "";						// �ִ� Ű�� �ʱ�ȭ

		center.x = center.y = 0;			// ���� �ʱ�ȭ
		rc = { 0, 0, 0, 0 };				// ��Ʈ �ʱ�ȭ

		angle = 0;							// ���� �ʱ�ȭ
		speed = 0;							// ���ǵ� �ʱ�ȭ
		gravity = 0;						// �߷� �ʱ�ȭ
		attack = 0;							// ���ݷ� �ʱ�ȭ

		dir = FLYINGOBJECT_DIRECTION::NONE; // ���� �ʱ�ȭ

		Delete_Timer = 0;					// Ÿ�̸� �ʱ�ȭ

		isFrame = false;					// bool �ʱ�ȭ

		isFalling = false;					// bool �ʱ�ȭ
		isHit = false;
	}

	// ���� �־��ִ� �Լ� (�Ű����� : �̹��� �̸�, �ִϸ��̼� �̸�, ����x, ����y, ����, ���ǵ�, �̹����� ���������� �ƴ���)
	void setting_Info(string imgName, string aniName_V, FLYINFOBJECT_TYPE type_V, FLYINGOBJECT_DIRECTION dir_V,
		float x, float y, float angle_V, float speed_V, int atk_V, bool Frame = false)
	{
		// Ÿ���� �����Ѵ�.
		type = type_V;

		// ������ �����Ѵ�.
		dir = dir_V;

		// ������ �����Ѵ�.
		center.x = x;
		center.y = y;

		// �̹����� ������ ���θ� ����
		isFrame = Frame;

		attack = atk_V;

		// �̹����� �������� �ƴ϶��
		if (!isFrame)
		{
			// Ű���� �̿��Ͽ� �̹����� �����Ѵ�.
			img = IMAGEMANAGER->findImage(imgName);

			// �̹����� ���� ���θ� �̿��Ͽ� ��Ʈ�� �����.
			rc = RectMakeCenter(center.x, center.y, img->getWidth(), img->getHeight());

		}

		// �̹����� �������̶��
		if (isFrame);
		{
			// Ű���� �̿��Ͽ� �ִϸ��̼��� �����Ѵ�.
			ani = KEYANIMANAGER->findAnimation(aniName_V);

			// �ִϸ��̼� ��ŸƮ
			ani->start();

			// �̹��� Ű���� �����Ѵ�.
			aniName = imgName;

			// �ִϸ��̼��� ���� ���θ� �̿��Ͽ� ��Ʈ�� �����.
			rc = RectMakeCenter(center.x, center.y, ani->getFrameWidth(), ani->getFrameHeight());

		}

		// ������ �����Ѵ�.
		angle = angle_V;

		// ���ǵ带 �����Ѵ�.
		speed = speed_V;
		
	}

	// Ÿ�� ����
	void setting_Type(FLYINFOBJECT_TYPE typeName)
	{
		// Ÿ���� �����Ѵ�.
		type = typeName;

	}

	// Ÿ�Կ� ���� Ÿ�̸Ӱ��� ��ȯ�Ѵ�.
	short get_Timer_Count()
	{
		// Ÿ�Կ� ���� Ÿ�̸Ӹ� �����Ѵ�.
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

	// ��Ʈ ����
	void update_Rect()
	{
		if (!isFrame)
		{
			// �̹����� ���� ���θ� �̿��Ͽ� ��Ʈ�� �����.
			rc = RectMakeCenter(center.x, center.y, img->getWidth(), img->getHeight());

		}

		if (isFrame)
		{
			// �ִϸ��̼��� ���� ���θ� �̿��Ͽ� ��Ʈ�� �����.
			rc = RectMake(center.x, center.y, ani->getFrameWidth(), ani->getFrameHeight());

		}
	}

};