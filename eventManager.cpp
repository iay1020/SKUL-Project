#include "stdafx.h"
#include "eventManager.h"

eventManager::eventManager()
{
}

eventManager::~eventManager()
{
}

HRESULT eventManager::init()
{
	vEvent.clear();

	return S_OK;
}

void eventManager::update()
{
	for (int i = 0; i < vEvent.size(); ++i)
	{
		// 루프하지 않는 녀석은 따로 이벤트
		if (!vEvent[i].loop)
		{
			collision_Event(&vEvent[i]);

		}
	}
}

void eventManager::render()
{
	for (int i = 0; i < vEvent.size(); ++i)
	{
		RECT tempRC = vEvent[i].rc;
		tempRC = DATAMANAGER->minus_CameraPos(tempRC);
		RECT tempFindRC = vEvent[i].findRC;
		tempFindRC = DATAMANAGER->minus_CameraPos(tempFindRC);

		if (!vEvent[i].doubleImg)
		{
			vEvent[i].img->aniRender(getMemDC(), tempRC.left, tempRC.top, vEvent[i].ani);
		}

		if (vEvent[i].doubleImg)
		{
			vEvent[i].img->render(getMemDC(), tempRC.left, tempRC.top);
			if(vEvent[i].type != eventType::START_GATE)
				IMAGEMANAGER->findImage(vEvent[i].aniName)->aniRender(getMemDC(), tempRC.left+ 70, tempRC.top + 120, vEvent[i].ani);
		}

		if (vEvent[i].showButton)
		{
			if (vEvent[i].type == eventType::GIVE_WEAPON_NPC)
			{
				IMAGEMANAGER->findImage("F_Key")->render(getMemDC(),
					vEvent[i].center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x - 60,
					vEvent[i].center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y - 60);

				char text_99[50];
				sprintf_s(text_99, 50, "를 눌러서 내 다리뼈를 받아..");

				SetBkMode(getMemDC(), 0);
				SetTextColor(getMemDC(), RGB(255, 255, 255));
				TextOut(getMemDC(), tempRC.left + 30,
					tempRC.top - 50,
					text_99, strlen(text_99));
			}

			if (vEvent[i].type == eventType::NEXT_GATE)
			{
				IMAGEMANAGER->findImage("F_Key")->render(getMemDC(),
					vEvent[i].center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x + 5,
					vEvent[i].center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y - 60);
			}

			if (vEvent[i].type == eventType::GET_GC_TYPE)
			{
				IMAGEMANAGER->findImage("F_Key")->render(getMemDC(),
					vEvent[i].center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x - 15,
					vEvent[i].center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y - 30);

				char text_99[50];
				sprintf_s(text_99, 50, "어째서 기사단장의 시체가?");

				SetBkMode(getMemDC(), 0);
				SetTextColor(getMemDC(), RGB(255, 255, 255));
				TextOut(getMemDC(), tempRC.left - 120,
					tempRC.top - 60,
					text_99, strlen(text_99));

			}
		}

		if (vEvent[i].type == eventType::GIVE_WEAPON_NPC &&
			!vEvent[i].showButton && !vEvent[i].eventStart)
		{
			char text_0[50];
			sprintf_s(text_0, 50, "리틀본.. 내 앞으로 가까이 와..");

			SetBkMode(getMemDC(), 0);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), tempRC.left - 30,
				tempRC.top - 40,
				text_0, strlen(text_0));
		}

		if (vEvent[i].type == eventType::DOWN_HELP_NPC)
		{
			char text_1[50];
			sprintf_s(text_1, 50, "아래 방향키와 C를 누르면,");

			char text_2[50];
			sprintf_s(text_2, 50, "아래 점프를 할 수 있어.");

			SetBkMode(getMemDC(), 0);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), tempRC.left - 180,
				tempRC.top - 10,
				text_1, strlen(text_1));
			TextOut(getMemDC(), tempRC.left - 180,
				tempRC.top + 20,
				text_2, strlen(text_2));
		}

		//tempRC = vEvent[i].findRC;
		//tempRC = DATAMANAGER->minus_CameraPos(tempRC);
		//Rectangle(getMemDC(), tempRC);
	}
}

void eventManager::create_Event(eventType eventType_, int idX, int idY, short multiplication, bool Loop, bool doubleImg_, short stage_Num)
{
	eventInfo new_Event;
	new_Event.reset();
	new_Event.type = eventType_;
	new_Event.center.x = idX * TILE_SIZE_X + (TILE_SIZE_X / 2);
	new_Event.center.y = idY * TILE_SIZE_Y + (TILE_SIZE_Y / 2);
	new_Event.find_Img();

	new_Event.loop = Loop;
	new_Event.doubleImg = doubleImg_;
	new_Event.stageNumber = stage_Num;

	vEvent.push_back(new_Event);
}

void eventManager::collision_Event(eventInfo* event_)
{
	RECT temp;
	RECT skulRC = DATAMANAGER->skul_Address()->get_Info().pos.rc;
	skulRC = DATAMANAGER->plus_CameraPos(skulRC);

	switch (event_->type)
	{
		case eventType::GIVE_WEAPON_NPC:
			// 스컬이 해당 이벤트존에 들어왔다면
			if (skulRC.left > event_->findRC.left && skulRC.right < event_->findRC.right &&
				!event_->eventStart)
			{
				if (!event_->showButton)
				{
					// 'F' 버튼 출력
					event_->showButton = true;
				}

				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					event_->eventStart = true;
					event_->showButton = false;

					event_->ani->start();

					DATAMANAGER->skul_Address()->set_InputKey(PRESS_RIGHT);
					DATAMANAGER->skul_Address()->set_Info()->ani_Changer("Idle", PRESS_RIGHT);
					DATAMANAGER->skul_Address()->get_Info().img.ani->start();
				}
			}
			else event_->showButton = false;

			// 이벤트가 시작 했다면
			if (event_->eventStart)
			{
				// 스컬 애니메이션 시작
				if (event_->ani->getFramePos().x == 590 && !event_->scene_1)
				{
					event_->scene_1 = true;

					DATAMANAGER->skul_Address()->get_State()->Event(DATAMANAGER->skul_Address());
				}

				// 스컬의 애니메이션에서 손이 멈추는 장면에서 다음 애니메이션 재생
				if (DATAMANAGER->skul_Address()->get_Info().img.ani->getFramePos().x == 800 && !event_->scene_2)
				{
					event_->scene_2 = true;

					event_->ani = KEYANIMANAGER->findAnimation("give_Weapon_End");
					event_->ani->start();
				}
			}

			break;

		case eventType::GET_GC_TYPE:
			// 스컬이 이벤트존에 들어와서 F를 눌렀다면
			// 스컬의 x축을 보정해주고 애니메이션을 재생한다.
			// 스컬이 자신의 머리를 위로 던지는 프레임일때
			// 스컬의 머리가 위쪽으로 날아가며 사라지는것 추가
			// 마지막 스컬의 프레임일때 이벤트 호출
			if (skulRC.left > event_->findRC.left &&
				skulRC.right < event_->findRC.right &&
				skulRC.bottom < event_->findRC.bottom &&
				skulRC.top > event_->findRC.top &&
				!event_->eventStart)
			{
				event_->showButton = true;

				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					event_->eventStart = true;
					event_->showButton = false;

					event_->ani->start();

					DATAMANAGER->skul_Address()->set_InputKey(PRESS_RIGHT);
					DATAMANAGER->skul_Address()->set_Info()->ani_Changer("Idle", PRESS_RIGHT);
					DATAMANAGER->skul_Address()->get_Info().img.ani->start();

				}
			}
			else event_->showButton = false;

			// 이벤트가 시작 했다면
			if (event_->eventStart)
			{
				// 스컬 애니메이션 시작
				if (event_->ani->getFramePos().x == 110 && !event_->scene_1)
				{
					event_->scene_1 = true;

					DATAMANAGER->skul_Address()->get_State()->Event(DATAMANAGER->skul_Address());
				}

				// 스컬이 머리를 던지는 모션에서 스컬 머리 투사체를 생성 후 날려준다.
				if (DATAMANAGER->skul_Address()->get_Info().img.ani->getFramePos().x == 10 * 128 && !event_->scene_2)
				{
					event_->scene_2 = true;

					DATAMANAGER->flyObj_Manager_Address()->Create_FlyingObj("skul_Skill_Head", "skill_Head_L", FLYINFOBJECT_TYPE::EVENT_SKUL_HEAD,
						FLYINGOBJECT_DIRECTION::LEFT, DATAMANAGER->skul_Address()->get_Info().pos.center.x - 20, DATAMANAGER->skul_Address()->get_Info().pos.center.y - 5,
						(3.14 / 180.f) * 120, 5, 0, true);
				}
			}



			break;

		case eventType::NEXT_GATE:
		{
			if (skulRC.left > event_->findRC.left && skulRC.right < event_->findRC.right &&
				skulRC.top > event_->findRC.top &&	!event_->eventStart)
			{
				event_->showButton = true;

				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					event_->eventStart = true;
					event_->showButton = false;

					if (event_->stageNumber == 1)
					{
						DATAMANAGER->Delete_Enemy();
						DATAMANAGER->Delete_ImageMaker();
						SCENEMANAGER->changeScene("Stage_1");
					}
					if (event_->stageNumber == 2)
					{
						DATAMANAGER->Delete_Enemy();
						DATAMANAGER->Delete_ImageMaker();
						SCENEMANAGER->changeScene("Stage_2");
					}
					if (event_->stageNumber == 3)
					{
						DATAMANAGER->Delete_Enemy();
						DATAMANAGER->Delete_ImageMaker();
						SCENEMANAGER->changeScene("ClearGame");
					}
				}
			}
			else event_->showButton = false;
		}
	}
}
