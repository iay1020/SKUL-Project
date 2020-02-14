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
	mapInfo.reset_MapInfo();	// 기본 맵 정보 초기화

	// 로드에 필요한것 변수
	// vector<tagTileInfo>			자료형 변수								타일 정보를 담는다.
	// tagMapInfo					자료형 변수								맵의 정보를 담는다.
	// vector<tagSaveBackGround>	자료형 변수[BACKGROUND_LAYER_COUNT]개		배경의 정보를 담는다.

	DATAMANAGER->map_Load(&tileList, &mapInfo, vMapInfo);	// 맵을 불러온다. (불러오면서 맵의 정보를 카메라매니저에 갱신)

	testSetting_Player();

	for (int i = 0; i < 5; ++i)	// 루프랜더용 변수
	{
		loopSpeed[i] = 0;
	}

	// 맵을 새로 불러오면 카메라 셋팅을 해야한다. (카메라 위치, 타일 갯수, 맵 크기 갱신)
	CAMERAMANAGER->Use_Func()->set_CameraXY(testP.center.x, testP.center.y, true);	// 기본 카메라 위치 설정 (플레이어 중점으로)

	_player = new Player();

	return S_OK;
}

void test_Room::release()
{
}

void test_Room::update()
{
	testControl(); // 테스트용 이동키


	_player->update();

}

void test_Room::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	DATAMANAGER->map_Render(getMemDC(), &tileList, mapInfo, vMapInfo, loopSpeed); // 루프스피드는 5개를 넣어줘야 한다.

	testP.rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	testP.rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	testP.rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	testP.rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	Rectangle(getMemDC(), testP.rc);
}

void test_Room::testControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		testP.center.x -= testP.speed;
		for (int i = 0; i < 5; ++i)
		{
			loopSpeed[i] -= 6 - i * 2;		// 0번째 레이어는 6의 값이 빼지고, 다음으로 넘어갈수록 -2씩 감소
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		testP.center.y -= testP.speed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		testP.center.x += testP.speed;
		for (int i = 0; i < 5; ++i)
		{
			loopSpeed[i] += 6 - i * 2;		// 0번째 레이어는 6의 값이 빼지고, 다음으로 넘어갈수록 +2씩 감소
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		testP.center.y += testP.speed;
	}

	CAMERAMANAGER->Use_Func()->set_CameraXY(testP.center.x, testP.center.y, true);	// 카메라 갱신
	testP.rc = RectMakeCenter(testP.center.x, testP.center.y, 30, 50);

}

void test_Room::testSetting_Player()
{
	//POINTFLOAT	center;
	//RECT		rc;
	//float		speed;
	//image*		img;
	//animation*	ani;

	// 테스트 플레이어의 위치를 잡는다.
	testP.center.x = 100;
	testP.center.y = WINSIZEY - 100;

	testP.rc = RectMakeCenter(testP.center.x, testP.center.y, 30, 50);

	testP.speed = 10;
}
