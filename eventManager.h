#pragma once
#include "gameNode.h"

enum class eventType
{
	EMPTY,						// 빈 공간
	GIVE_WEAPON_NPC,			// 무기 주는 이벤트 
	DOWN_HELP_NPC,				// 아래 점프를 알려주는 이벤트
	GET_GC_TYPE,				// 기사 단장 타입을 얻는 이벤트
	FIND_WITCH_NPC,				// 마녀 구출 이벤트
	NEXT_GATE,					// 다음 스테이지 문
	START_GATE					// 시작 입구

};

struct eventInfo
{
	eventType		type;		// 이벤트 타입
	POINTFLOAT		center;		// 중점
	RECT			rc;			// 렉트
	RECT			findRC;		// 인식 렉트
	image*			img;		// 이미지
	string			imgName;	// 이미지 키값
	animation*		ani;		// 애니
	string			aniName;	// 애니 키값

	bool			loop;		// 루프할것인지 패턴이 있는것인지	
	bool			doubleImg;	// 이미지가 여러개

	bool			showButton;	// 버튼 출력
	bool			eventStart;	// 이벤트 시작
	bool			scene_1;	// 씬 하나
	bool			scene_2;	// 씬 둘

	short			stageNumber;	// 스테이지 넘버

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

