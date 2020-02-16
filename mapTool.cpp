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

	_mapTool_Func.make_Base_TileList(&_vTileList);	// 타일의 기본 렉트를 만들어 준다.
	_mapTool_Func.reset();

	_button.reset();								// 버튼 위치 초기화

	_pallet.reset();								// 팔렛트 변수 초기화
	
	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	testMove();																																// 테스트용 카메라 이동 함수

	_button.click_Button(&_mapInfo, _mapTool_Func.get_VBackGround_Info_Address(), &_vTileList);																										// 클릭 했다면 클릭 한 버튼으로 속성을 바꿔주는 함수

	_pallet.setting_Pallet(_button.BT_Type, _button.BT_ImgNumber, 
		&_button.BT_Prev, &_button.BT_Next, &_button.BT_Up, &_button.BT_Down, &_button.BT_RectPlus, &_button.BT_Minus);															// 팔렛트 위치 갱신

	Find_Worker();																															// 클릭 한 버튼에 따라 함수 호출

	_button.reset_Next_Prev_Pos(_pallet.pallet);																							// 다음, 이전 버튼 위치 갱신 함수
	
	_pallet.click_PalletInfo_Save((BUTTON_TYPE)_button.BT_Type, _button.BT_ImgNumber, &_button.BT_start_Draw, &_button.BT_FindNoTile);		// 이미지 선택

	if(!_button.BT_FindNoTile)
		_mapTool_Func.setting_TileImg(&_vTileList, _pallet.current, _button, &_mapInfo, &_button.BT_start_Draw);							// 타일에 이미지를 셋팅한다. (다른 렉트에 충돌 되지 않는다면 그린다)
}

void mapTool::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);				// 전체 화면 갱신용

	//_mapTool_Func.show_BackImg(&_mapInfo, getMemDC());					// 백그라운드 배경을 출력한다.
	IMAGEMANAGER->findImage("base_MapTool_BG")->render(getMemDC(), 0, 0);	// 맵툴 기본 배경

	_mapTool_Func.show_TileImg(getMemDC(), &_vTileList, _mapInfo);

	// 타일 렉트 출력 (테스트용)
	if (KEYMANAGER->isToggleKey(VK_NUMPAD1))
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);
		_mapTool_Func.show_Camera_In_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Size().x, CAMERAMANAGER->Use_Func()->get_Camera_Size().y, getMemDC(), &_vTileList);
	}

	_button.show_Button(getMemDC());

	_mapTool_Func.show_Pallet(getMemDC(), (BUTTON_TYPE)_button.BT_Type, &_pallet, _mapInfo._layer_Cnt);
}

void mapTool::testMove()
{
	// 테스트용 카메라 키

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->Use_Func()->set_CameraX(CAMERAMANAGER->Use_Func()->get_CameraXY().x - 20);

	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->Use_Func()->set_CameraY(CAMERAMANAGER->Use_Func()->get_CameraXY().y - 20);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->Use_Func()->set_CameraX(CAMERAMANAGER->Use_Func()->get_CameraXY().x + 20);
	
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->Use_Func()->set_CameraY(CAMERAMANAGER->Use_Func()->get_CameraXY().y + 20);
	}

	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);
}

void mapTool::Find_Worker()
{
	// 클릭한 버튼에 따라서 필요한 함수를 호출한다.
	switch ((BUTTON_TYPE)_button.BT_Type)
	{
		case BUTTON_TYPE::SAVE:
			DATAMANAGER->map_Save(_vTileList, &_mapInfo, _mapTool_Func.get_VBackGround_Info_Address());
			_button.BT_Type = BUTTON_TYPE::NONE;
			break;

		case BUTTON_TYPE::LOAD:
			DATAMANAGER->map_Load(&_vTileList, &_mapInfo, _mapTool_Func.get_VBackGround_Info_Address());
			_button.BT_Type = BUTTON_TYPE::NONE;
			break;

		case BUTTON_TYPE::ERASER:

				// 마우스 위치 보정
				POINT ptMouse;
				ptMouse.x = _ptMouse.x + CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				ptMouse.y = _ptMouse.y + CAMERAMANAGER->Use_Func()->get_CameraXY().y;

				// 이 상태일때는 클릭하는 모든 타일의 속성을 초기화 시켜줘야한다.
				if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
				{
					for (int i = 0; i < _vTileList.size(); ++i)
					{
						if (PtInRect(&_vTileList[i].rc, ptMouse))
						{
							_vTileList[i].reset_Tile();
						}
					}
				}

			break;

		case BUTTON_TYPE::GROUND:

			break;

		case BUTTON_TYPE::DECORATION:

			break;

		case BUTTON_TYPE::HIT_OBJECT:

			break;

		case BUTTON_TYPE::DOOR:

			break;

		case BUTTON_TYPE::CHARACTER:

			break;

		case BUTTON_TYPE::ITEM:

			break;

		case BUTTON_TYPE::TRAP:

			break;
			
	}
}
