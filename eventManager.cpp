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
		if (!vEvent[i].doubleImg)
		{
			vEvent[i].img->aniRender(getMemDC(), tempRC.left, tempRC.top, vEvent[i].ani);
		}

		if (vEvent[i].doubleImg)
		{
			vEvent[i].img->render(getMemDC(), tempRC.left, tempRC.top);
			IMAGEMANAGER->findImage(vEvent[i].aniName)->aniRender(getMemDC(), tempRC.left+ 70, tempRC.top + 120, vEvent[i].ani);
		}

		if (vEvent[i].showButton)
		{
			if (vEvent[i].type == eventType::GIVE_WEAPON_NPC)
			{
				IMAGEMANAGER->findImage("F_Key")->render(getMemDC(),
					vEvent[i].center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x - 20,
					vEvent[i].center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y - 60);
			}

			if (vEvent[i].type == eventType::NEXT_GATE)
			{
				IMAGEMANAGER->findImage("F_Key")->render(getMemDC(),
					vEvent[i].center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x + 5,
					vEvent[i].center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y - 60);
			}
		}

		//tempRC = vEvent[i].findRC;
		//tempRC = DATAMANAGER->minus_CameraPos(tempRC);
		//Rectangle(getMemDC(), tempRC);
	}
}

void eventManager::create_Event(eventType eventType_, int idX, int idY, short multiplication, bool Loop, bool doubleImg_)
{
	eventInfo new_Event;
	new_Event.reset();
	new_Event.type = eventType_;
	new_Event.center.x = idX * TILE_SIZE_X + (TILE_SIZE_X / 2);
	new_Event.center.y = idY * TILE_SIZE_Y + (TILE_SIZE_Y / 2);
	new_Event.find_Img();

	new_Event.loop = Loop;
	new_Event.doubleImg = doubleImg_;

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

				cout << DATAMANAGER->skul_Address()->get_Info().img.ani->getFramePos().x << endl;

				// 스컬의 애니메이션에서 손이 멈추는 장면에서 다음 애니메이션 재생
				if (DATAMANAGER->skul_Address()->get_Info().img.ani->getFramePos().x == 800 && !event_->scene_2)
				{
					event_->scene_2 = true;

					event_->ani = KEYANIMANAGER->findAnimation("give_Weapon_End");
					event_->ani->start();
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

					
				}
			}
			else event_->showButton = false;
		}
	}
}
