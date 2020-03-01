#include "stdafx.h"
#include "Stage_0.h"

Stage_0::Stage_0()
{
}

Stage_0::~Stage_0()
{
}

HRESULT Stage_0::init()
{
	// 맵을 불러와 데이터매니저에 있는 변수에 저장한다.
	DATAMANAGER->map_Load_Datamanager("Stage_0.map", "Stage_0_Info.map");

	DATAMANAGER->create_Skul();				// 스컬 생성
	_skul = DATAMANAGER->skul_Address();	// 스컬 데이터 연결
	_skul->update_Pos(4, 25);

	// ui 셋팅
	DATAMANAGER->setting_ui(_skul);
	// 미니맵 정보 셋팅
	DATAMANAGER->ui_Address()->setting_MiniMap();
	DATAMANAGER->setting_MiniMap();

	// 이벤트 매니저 생성
	eventM = new eventManager;
	eventM->create_Event(eventType::GIVE_WEAPON_NPC, 28, 19, 4, false, false, 0);
	eventM->create_Event(eventType::NEXT_GATE, 36, 25, 1, false, true, 1);
	eventM->create_Event(eventType::DOWN_HELP_NPC, 40, 18, 1, true, false, 0);

	// 테스트 에너미 생성
	//DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 30, 17);

	// 맵을 새로 불러오면 카메라 셋팅을 해야한다. (카메라 위치, 타일 갯수, 맵 크기 갱신)
	// 기본 카메라 위치 설정 (플레이어 중점으로)
	CAMERAMANAGER->Use_Func()->set_CameraXY(_skul->get_Info().pos.center.x, _skul->get_Info().pos.center.y, true);

	return S_OK;
}

void Stage_0::release()
{
}

void Stage_0::update()
{
	testControl(); // 테스트용 이동키

	// 플레이어 연산
	DATAMANAGER->update();

	eventM->update();

	// 캐릭터 타일 위치
	//cout << "x : " << (int)(_skul->get_Info().pos.center.x / TILE_SIZE_X) << ", y : " << (int)(_skul->get_Info().pos.center.y / TILE_SIZE_Y) << endl;


}

void Stage_0::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	// 맵 출력
	DATAMANAGER->map_Render_Datamanager_Loop(getMemDC());

	showRect(getMemDC());	// 테스트용 렉트

	eventM->render();

	// 에너미 출력
	DATAMANAGER->show_Enemy();


	// 플레이어 출력
	IMAGEMANAGER->findImage(_skul->get_Info().img.imgName)->aniRender(getMemDC(),
		_skul->get_Info().img.img_Rc.left, _skul->get_Info().img.img_Rc.top, _skul->get_Info().img.ani);


	// 플레이어 공격 렉트 출력
	//_skul->set_Info()->show_Attack_Rect(getMemDC());

	// 투사체 출력
	DATAMANAGER->show_FlyingObject();

	// 이펙트 출력
	DATAMANAGER->show_Effect();

	// ui 출력
	DATAMANAGER->show_Ui();

	EFFECTMANAGER->render();

}

void Stage_0::testControl()
{

	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		if (_skul->get_InputKey() == PRESS_RIGHT)
			DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) + 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);

		if (_skul->get_InputKey() == PRESS_LEFT)
			DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) - 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		if (_skul->get_InputKey() == PRESS_RIGHT)
			DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::LEFT, "archer_Idle", "archer_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) + 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);

		if (_skul->get_InputKey() == PRESS_LEFT)
			DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::LEFT, "archer_Idle", "archer_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) - 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		if (_skul->get_InputKey() == PRESS_RIGHT)
			DATAMANAGER->Create_Enemy(EnemyType::PALADIN, EnemyDirection::LEFT, "paladin_Idle", "paladin_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) + 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);

		if (_skul->get_InputKey() == PRESS_LEFT)
			DATAMANAGER->Create_Enemy(EnemyType::PALADIN, EnemyDirection::RIGHT, "paladin_Idle", "paladin_Idle_Right_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) - 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);
	}
}

void Stage_0::showRect(HDC getMemDC)
{
	if (KEYMANAGER->isToggleKey(VK_NUMPAD9))
	{
		DATAMANAGER->Rect_Render_Datamanager(getMemDC);
	}

	if (KEYMANAGER->isToggleKey(VK_NUMPAD7))
	{
		// 플레이어 이미지 렉트
		Rectangle(getMemDC, _skul->get_Info().img.img_Rc.left, _skul->get_Info().img.img_Rc.top, _skul->get_Info().img.img_Rc.right, _skul->get_Info().img.img_Rc.bottom);
	}

	if (KEYMANAGER->isToggleKey(VK_NUMPAD8))
	{
		// 플레이어 피격 렉트
		Rectangle(getMemDC, _skul->get_Info().pos.rc.left, _skul->get_Info().pos.rc.top, _skul->get_Info().pos.rc.right, _skul->get_Info().pos.rc.bottom);
	}
}


