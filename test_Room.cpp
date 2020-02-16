#include "stdafx.h"
#include "test_Room.h"

test_Room::test_Room()
{
}

test_Room::~test_Room()
{
}

HRESULT test_Room::init()
{
	DATAMANAGER->map_Load_Datamanager("tutorial.map", "tutorial_Info.map");

	for (int i = 0; i < 5; ++i)	// 루프랜더용 변수
	{
		loopSpeed[i] = 0;
	}

	DATAMANAGER->create_Skul();				// 스컬 생성
	_skul = DATAMANAGER->skul_Address();	// 스컬 데이터 연결

	// 맵을 새로 불러오면 카메라 셋팅을 해야한다. (카메라 위치, 타일 갯수, 맵 크기 갱신)
	// 기본 카메라 위치 설정 (플레이어 중점으로)
	CAMERAMANAGER->Use_Func()->set_CameraXY(_skul->get_Info().pos.center.x, _skul->get_Info().pos.center.y, true);

	return S_OK;
}

void test_Room::release()
{
}

void test_Room::update()
{
	testControl(); // 테스트용 이동키

	// 플레이어 연산
	DATAMANAGER->update();
	
	// 캐릭터 타일 위치
	//cout << "x : " << (int)(_player->get_Info().pos.center.x / TILE_SIZE_X) << ", y : " << (int)(_player->get_Info().pos.center.y / TILE_SIZE_Y) << endl;
}

void test_Room::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	// 맵 출력
	DATAMANAGER->map_Render_Datamanager(getMemDC(), loopSpeed);

	showRect(getMemDC());	// 테스트용 렉트

	// 플레이어 출력
	IMAGEMANAGER->findImage(_skul->get_Info().img.imgName)->aniRender(getMemDC(),
		_skul->get_Info().img.img_Rc.left, _skul->get_Info().img.img_Rc.top, _skul->get_Info().img.ani);
}

void test_Room::testControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		for (int i = 0; i < 5; ++i)
		{
			loopSpeed[i] -= 6 - i * 2;		// 0번째 레이어는 6의 값이 빼지고, 다음으로 넘어갈수록 -2씩 감소
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_skul->set_Info()->pos.center.y -= 10;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		for (int i = 0; i < 5; ++i)
		{
			loopSpeed[i] += 6 - i * 2;		// 0번째 레이어는 6의 값이 빼지고, 다음으로 넘어갈수록 +2씩 감소
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_skul->set_Info()->pos.center.y += 10;
	}
}

void test_Room::showRect(HDC getMemDC)
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


