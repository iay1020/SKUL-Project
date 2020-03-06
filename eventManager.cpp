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
		// �������� �ʴ� �༮�� ���� �̺�Ʈ
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
				sprintf_s(text_99, 50, "�� ������ �� �ٸ����� �޾�..");

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
				sprintf_s(text_99, 50, "��°�� �������� ��ü��?");

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
			sprintf_s(text_0, 50, "��Ʋ��.. �� ������ ������ ��..");

			SetBkMode(getMemDC(), 0);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			TextOut(getMemDC(), tempRC.left - 30,
				tempRC.top - 40,
				text_0, strlen(text_0));
		}

		if (vEvent[i].type == eventType::DOWN_HELP_NPC)
		{
			char text_1[50];
			sprintf_s(text_1, 50, "�Ʒ� ����Ű�� C�� ������,");

			char text_2[50];
			sprintf_s(text_2, 50, "�Ʒ� ������ �� �� �־�.");

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
			// ������ �ش� �̺�Ʈ���� ���Դٸ�
			if (skulRC.left > event_->findRC.left && skulRC.right < event_->findRC.right &&
				!event_->eventStart)
			{
				if (!event_->showButton)
				{
					// 'F' ��ư ���
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

			// �̺�Ʈ�� ���� �ߴٸ�
			if (event_->eventStart)
			{
				// ���� �ִϸ��̼� ����
				if (event_->ani->getFramePos().x == 590 && !event_->scene_1)
				{
					event_->scene_1 = true;

					DATAMANAGER->skul_Address()->get_State()->Event(DATAMANAGER->skul_Address());
				}

				// ������ �ִϸ��̼ǿ��� ���� ���ߴ� ��鿡�� ���� �ִϸ��̼� ���
				if (DATAMANAGER->skul_Address()->get_Info().img.ani->getFramePos().x == 800 && !event_->scene_2)
				{
					event_->scene_2 = true;

					event_->ani = KEYANIMANAGER->findAnimation("give_Weapon_End");
					event_->ani->start();
				}
			}

			break;

		case eventType::GET_GC_TYPE:
			// ������ �̺�Ʈ���� ���ͼ� F�� �����ٸ�
			// ������ x���� �������ְ� �ִϸ��̼��� ����Ѵ�.
			// ������ �ڽ��� �Ӹ��� ���� ������ �������϶�
			// ������ �Ӹ��� �������� ���ư��� ������°� �߰�
			// ������ ������ �������϶� �̺�Ʈ ȣ��
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

			// �̺�Ʈ�� ���� �ߴٸ�
			if (event_->eventStart)
			{
				// ���� �ִϸ��̼� ����
				if (event_->ani->getFramePos().x == 110 && !event_->scene_1)
				{
					event_->scene_1 = true;

					DATAMANAGER->skul_Address()->get_State()->Event(DATAMANAGER->skul_Address());
				}

				// ������ �Ӹ��� ������ ��ǿ��� ���� �Ӹ� ����ü�� ���� �� �����ش�.
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
