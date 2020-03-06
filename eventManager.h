#pragma once
#include "gameNode.h"

enum class eventType
{
	EMPTY,						// �� ����
	GIVE_WEAPON_NPC,			// ���� �ִ� �̺�Ʈ 
	DOWN_HELP_NPC,				// �Ʒ� ������ �˷��ִ� �̺�Ʈ
	GET_GC_TYPE,				// ��� ���� Ÿ���� ��� �̺�Ʈ
	FIND_WITCH_NPC,				// ���� ���� �̺�Ʈ
	NEXT_GATE,					// ���� �������� ��
	START_GATE					// ���� �Ա�

};

struct eventInfo
{
	eventType		type;		// �̺�Ʈ Ÿ��
	POINTFLOAT		center;		// ����
	RECT			rc;			// ��Ʈ
	RECT			findRC;		// �ν� ��Ʈ
	image*			img;		// �̹���
	string			imgName;	// �̹��� Ű��
	animation*		ani;		// �ִ�
	string			aniName;	// �ִ� Ű��

	bool			loop;		// �����Ұ����� ������ �ִ°�����	
	bool			doubleImg;	// �̹����� ������

	bool			showButton;	// ��ư ���
	bool			eventStart;	// �̺�Ʈ ����
	bool			scene_1;	// �� �ϳ�
	bool			scene_2;	// �� ��

	short			stageNumber;	// �������� �ѹ�

	void reset()
	{
		type = eventType::EMPTY;
		center.x = center.y = 0;
		rc = { 0,0,0,0 };
		findRC = { 0,0,0,0 };
		img = new image;
		imgName = "";
		ani = new animation;
		aniName = "";
		loop = false;
		doubleImg = false;

		showButton = false;
		eventStart = false;
		scene_1 = false;
		scene_2 = false;

		stageNumber = 0;

	}

	void find_Img()
	{
		switch (type)
		{
		case eventType::GIVE_WEAPON_NPC:
			imgName = "give_Weapon_NPC";
			img = IMAGEMANAGER->findImage(imgName);
			aniName = "give_Weapon_Start";
			ani = KEYANIMANAGER->findAnimation(aniName);

			findRC = RectMake(center.x - 105, center.y , 55, 40);

			rc = RectMakeCenter(center.x, center.y + 20,
				img->getFrameWidth(), img->getFrameHeight());

			break;

		case eventType::GET_GC_TYPE:
			imgName = "GC_Deadbody";
			img = IMAGEMANAGER->findImage(imgName);
			aniName = "GC_Deadbody";
			ani = KEYANIMANAGER->findAnimation(aniName);

			findRC = RectMake(center.x - 105, center.y - 40, 50, 90);

			rc = RectMakeCenter(center.x, center.y + 20,
				img->getFrameWidth(), img->getFrameHeight());

			break;

		case eventType::NEXT_GATE:
			imgName = "Door_1";
			img = IMAGEMANAGER->findImage(imgName);
			aniName = "Door_Fire_1";
			ani = KEYANIMANAGER->findAnimation(aniName);
			ani->start();

			findRC = RectMake(center.x - 37, center.y - 100, 105, 150);
			
			rc = RectMakeCenter(center.x - 170, center.y - 200,
				img->getFrameWidth(), img->getFrameHeight());

			break;

		case eventType::START_GATE:
			imgName = "Door_1";
			img = IMAGEMANAGER->findImage(imgName);
			aniName = "Door_Fire_1";
			ani = KEYANIMANAGER->findAnimation(aniName);
			ani->stop();

			findRC = RectMake(center.x - 37, center.y - 100, 105, 150);

			rc = RectMakeCenter(center.x - 170, center.y - 200,
				img->getFrameWidth(), img->getFrameHeight());

			break;

		case eventType::DOWN_HELP_NPC:
			imgName = "down_Jump_NPC";
			img = IMAGEMANAGER->findImage(imgName);
			aniName = "down_Jump_NPC_Ani";
			ani = KEYANIMANAGER->findAnimation(aniName);
			ani->start();

			rc = RectMakeCenter(center.x + 10 , center.y ,
				img->getFrameWidth(), img->getFrameHeight());

			break;

		}
	}
};

class eventManager : public gameNode
{
private:
	vector<eventInfo>		vEvent;

public:
	eventManager();
	~eventManager();

	HRESULT init();
	void update();
	void render();

	void create_Event(eventType eventType_, int idX, int idY, short multiplication, bool Loop, bool doubleImg_, short stage_Num);
	void collision_Event(eventInfo* event_);

};

