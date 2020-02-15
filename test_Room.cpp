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

	for (int i = 0; i < 5; ++i)	// 루프랜더용 변수
	{
		loopSpeed[i] = 0;
	}

	_player = new Player();

	// 맵을 새로 불러오면 카메라 셋팅을 해야한다. (카메라 위치, 타일 갯수, 맵 크기 갱신)
	CAMERAMANAGER->Use_Func()->set_CameraXY(_player->get_Info().pos.center.x, _player->get_Info().pos.center.y, true);	// 기본 카메라 위치 설정 (플레이어 중점으로)

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

	IMAGEMANAGER->findImage(_player->get_Info().img.imgName)->aniRender(getMemDC(), 
		_player->get_Info().img.img_Rc.left, _player->get_Info().img.img_Rc.top, _player->get_Info().img.ani);
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
		_player->set_Info()->pos.center.y -= 10;
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
		_player->set_Info()->pos.center.y += 10;
	}
}

