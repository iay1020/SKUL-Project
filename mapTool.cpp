#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	_mapInfo.reset_MapInfo();						// 맵정보 초기화

	_mapInfo.add_BackGround("tutorial_BG_0");		// 맵 추가 (테스트용)
	_mapInfo.add_BackGround("tutorial_BG_1");
	_mapInfo.add_BackGround("tutorial_BG_2");

	_mapTool_Func.make_Base_TileList(&_vTileList);	// 타일의 기본 렉트를 만들어 준다.

	_loop = new tagLoop_Variable;
	_loop->reset_Func();							// 루프용 변수를 초기화 해준다.

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	testMove();
	
}

void mapTool::render()
{

	//POINTFLOAT start = CAMERAMANAGER->Use_Func()->get_CameraXY();	// 카메라 x, y 좌표를 start에 넣는다.
	//POINTFLOAT end = { WINSIZEX, WINSIZEY };						// end에는 rightm bottom 좌표를 넣는다.
	//end.x += start.x;												// start x, y 를 추가로 더해준다.
	//end.y += start.y;
	//
	//POINT startIndex, endIndex;
	//start.x /= TILE_SIZE_X;
	//end.x /= TILE_SIZE_X;
	//start.y /= TILE_SIZE_Y;
	//end.y /= TILE_SIZE_Y;
	//startIndex = { (LONG)start.x, (LONG)start.y };
	//endIndex = { (LONG)end.x, (LONG)end.y };
	//
	//// 예외처리
	//startIndex.x < 0 ? startIndex.x = 0 : startIndex.x;
	//startIndex.y < 0 ? startIndex.y = 0 : startIndex.y;
	//
	////endIndex.x < 0 ? endIndex.x = 0 : endIndex.x;
	////endIndex.y < 0 ? endIndex.y = 0 : endIndex.y;
	//
	////startIndex.x >= TILE_COUNT_X ? startIndex.x = TILE_COUNT_X - 1 : startIndex.x;
	////startIndex.y >= TILE_COUNT_Y ? startIndex.y = TILE_COUNT_Y - 1 : startIndex.y;
	//
	//endIndex.x + 1 > TILE_COUNT_X ? endIndex.x = TILE_COUNT_X - 1 : endIndex.x;
	//endIndex.y + 1 > TILE_COUNT_Y ? endIndex.y = TILE_COUNT_Y - 1 : endIndex.y;


	/*POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

	RECT CAMERA_RC = RectMake(0, 0, IMAGEMANAGER->findImage("tutorial_BG_0")->getWidth(), IMAGEMANAGER->findImage("tutorial_BG_0")->getHeight());
	CAMERA_RC.left -= camera.x;
	CAMERA_RC.right -= camera.x;
	CAMERA_RC.top -= camera.y;
	CAMERA_RC.bottom -= camera.y;

	IMAGEMANAGER->findImage("tutorial_BG_0")->loopRender(getMemDC(), &CAMERA_RC, _loopX.LoopX_BG_0, 0);
	IMAGEMANAGER->findImage("tutorial_BG_1")->loopRender(getMemDC(), &CAMERA_RC, _loopX.LoopX_BG_1, 0);
	IMAGEMANAGER->findImage("tutorial_BG_2")->loopRender(getMemDC(), &CAMERA_RC, _loopX.LoopX_BG_2, 0);*/

	// 카메라 사이즈 만큼의 타일만 찾아서 출력을 한다.
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);		// 전체 화면 갱신용

	//_mapTool_Func.camera_In_FindTile();								// 카메라 안에 있는 타일을 찾는다. (시작 인덱스, 마지막 인덱스, 인덱스 범위)

	_mapTool_Func.show_BackImg(_mapInfo, getMemDC());

	if (KEYMANAGER->isToggleKey(VK_NUMPAD1))
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);
		_mapTool_Func.show_Camera_In_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Size().x, CAMERAMANAGER->Use_Func()->get_Camera_Size().y, getMemDC(), _vTileList);
	}

	//if (KEYMANAGER->isToggleKey(VK_NUMPAD1))
	//{
	//	for (int y = startIndex.y; y <= endIndex.y; y++)
	//	{
	//		for (int x = startIndex.x; x <= endIndex.x; x++)
	//		{
	//			RECT rc = _vTileList[y * TILE_COUNT_X + x]->rc;
	//	
	//			rc.left -= camera.x;
	//			rc.right -= camera.x;
	//			rc.top -= camera.y;
	//			rc.bottom -= camera.y;
	//	
	//			Rectangle(getMemDC(), rc);
	//	
	//		}
	//	}
	//
	//	//for (int y = 0; y < TILE_COUNT_Y; ++y)
	//	//{
	//	//	for (int x = 0; x < TILE_COUNT_X; ++x)
	//	//	{
	//	//		Rectangle(getMemDC(), _vTileList[y * TILE_COUNT_X + x]->rc);
	//	//	}
	//	//}
	//}
}

void mapTool::testMove()
{
	// 테스트용 카메라 키

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->Use_Func()->set_CameraX(CAMERAMANAGER->Use_Func()->get_CameraXY().x - 20);
		_mapInfo.loop.LoopX_BG_0 -= 6; 
		_mapInfo.loop.LoopX_BG_1 -= 4;
		_mapInfo.loop.LoopX_BG_2 -= 2;

		if (_mapInfo.loop.LoopX_BG_0 < 0) _mapInfo.loop.LoopX_BG_0 = 255;
		if (_mapInfo.loop.LoopX_BG_1 < 0) _mapInfo.loop.LoopX_BG_1 = 255;
		if (_mapInfo.loop.LoopX_BG_2 < 0) _mapInfo.loop.LoopX_BG_2 = 255;

	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->Use_Func()->set_CameraY(CAMERAMANAGER->Use_Func()->get_CameraXY().y - 20);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->Use_Func()->set_CameraX(CAMERAMANAGER->Use_Func()->get_CameraXY().x + 20);
		_mapInfo.loop.LoopX_BG_0 += 6;
		_mapInfo.loop.LoopX_BG_1 += 4;
		_mapInfo.loop.LoopX_BG_2 += 2;

		if (_mapInfo.loop.LoopX_BG_0 > 255) _mapInfo.loop.LoopX_BG_0 = 0;
		if (_mapInfo.loop.LoopX_BG_1 > 255) _mapInfo.loop.LoopX_BG_1 = 0;
		if (_mapInfo.loop.LoopX_BG_2 > 255) _mapInfo.loop.LoopX_BG_2 = 0;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->Use_Func()->set_CameraY(CAMERAMANAGER->Use_Func()->get_CameraXY().y + 20);
	}

	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);
}
