#include "stdafx.h"
#include "Stage_1.h"

Stage_1::Stage_1()
{
}

Stage_1::~Stage_1()
{
}

HRESULT Stage_1::init()
{
	// 맵을 불러와 데이터매니저에 있는 변수에 저장한다.
	DATAMANAGER->map_Load_Datamanager("Stage_1.map", "Stage_1_Info.map");

	_skul = DATAMANAGER->skul_Address();	// 스컬 데이터 연결
	_skul->update_Pos(4, 25);

	// 이벤트 매니저 생성
	eventM = new eventManager;
	//eventM->create_Event(eventType::GIVE_WEAPON_NPC, 28, 19, 4, false, false);
	eventM->create_Event(eventType::START_GATE, 3, 25, 1, false, true, 0);
	eventM->create_Event(eventType::NEXT_GATE, 58, 25, 1, false, true, 2);

	// 에너미 생성
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 27, 25);
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 29, 25);
	DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::RIGHT, "archer_Idle", "archer_Idle_Left_Ani", 32, 25);
	DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::RIGHT, "archer_Idle", "archer_Idle_Left_Ani", 34, 25);
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 32, 19);
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 44, 14);
	DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::RIGHT, "archer_Idle", "archer_Idle_Left_Ani", 47, 14);

	// 맵을 새로 불러오면 카메라 셋팅을 해야한다. (카메라 위치, 타일 갯수, 맵 크기 갱신)
	// 기본 카메라 위치 설정 (플레이어 중점으로)
	CAMERAMANAGER->Use_Func()->set_CameraXY(_skul->get_Info().pos.center.x, _skul->get_Info().pos.center.y, true);

	return S_OK;
}

void Stage_1::release()
{
}

void Stage_1::update()
{
	// 플레이어 연산
	DATAMANAGER->update();

	eventM->update();

	// 캐릭터 타일 위치
	cout << "x : " << (int)(_skul->get_Info().pos.center.x / TILE_SIZE_X) << ", y : " << (int)(_skul->get_Info().pos.center.y / TILE_SIZE_Y) << endl;

}

void Stage_1::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	// 맵 출력
	DATAMANAGER->map_Render_Datamanager_Loop(getMemDC());

	//showRect(getMemDC());	// 테스트용 렉트

	eventM->render();

	// 에너미 출력
	DATAMANAGER->show_Enemy();

	// 이미지 출력
	DATAMANAGER->Render_ImageMaker();


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

void Stage_1::testControl()
{
}

void Stage_1::showRect(HDC getMemDC)
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
