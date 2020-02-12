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
	_mapInfo.reset_MapInfo();						// ������ �ʱ�ȭ

	_mapTool_Func.make_Base_TileList(&_vTileList);	// Ÿ���� �⺻ ��Ʈ�� ����� �ش�.
	_mapTool_Func.reset();

	_button.reset();								// ��ư ��ġ �ʱ�ȭ

	_pallet.reset();								// �ȷ�Ʈ ���� �ʱ�ȭ
	
	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	testMove();																																// �׽�Ʈ�� ī�޶� �̵� �Լ�

	_button.click_Button(&_mapInfo, _mapTool_Func.get_VBackGround_Info_Address(), &_vTileList);																										// Ŭ�� �ߴٸ� Ŭ�� �� ��ư���� �Ӽ��� �ٲ��ִ� �Լ�

	_pallet.setting_Pallet(_button.BT_Type, _button.BT_ImgNumber, 
		&_button.BT_Prev, &_button.BT_Next, &_button.BT_Up, &_button.BT_Down, &_button.BT_RectPlus, &_button.BT_Minus);															// �ȷ�Ʈ ��ġ ����

	Find_Worker();																															// Ŭ�� �� ��ư�� ���� �Լ� ȣ��

	_button.reset_Next_Prev_Pos(_pallet.pallet);																							// ����, ���� ��ư ��ġ ���� �Լ�
	
	_pallet.click_PalletInfo_Save((BUTTON_TYPE)_button.BT_Type, _button.BT_ImgNumber, &_button.BT_start_Draw, &_button.BT_FindNoTile);		// �̹��� ����

	if(!_button.BT_FindNoTile)
		_mapTool_Func.setting_TileImg(&_vTileList, _pallet.current, _button, &_mapInfo, &_button.BT_start_Draw);							// Ÿ�Ͽ� �̹����� �����Ѵ�. (�ٸ� ��Ʈ�� �浹 ���� �ʴ´ٸ� �׸���)

	//cout << "======================================================" << endl;
	//cout << _mapTool_Func.get_VBackGround_Info_Address()[0].size() << endl;
	//cout << _mapTool_Func.get_VBackGround_Info_Address()[1].size() << endl;
	//cout << _mapTool_Func.get_VBackGround_Info_Address()[2].size() << endl;
	//cout << _mapTool_Func.get_VBackGround_Info_Address()[3].size() << endl;
	//cout << _mapTool_Func.get_VBackGround_Info_Address()[4].size() << endl;
	//cout << "======================================================" << endl;
}

void mapTool::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);				// ��ü ȭ�� ���ſ�

	//_mapTool_Func.show_BackImg(&_mapInfo, getMemDC());					// ��׶��� ����� ����Ѵ�.
	IMAGEMANAGER->findImage("base_MapTool_BG")->render(getMemDC(), 0, 0);	// ���� �⺻ ���

	_mapTool_Func.show_TileImg(getMemDC(), &_vTileList, _mapInfo);

	// Ÿ�� ��Ʈ ��� (�׽�Ʈ��)
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
	// �׽�Ʈ�� ī�޶� Ű

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
	// Ŭ���� ��ư�� ���� �ʿ��� �Լ��� ȣ���Ѵ�.
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

				// ���콺 ��ġ ����
				POINT ptMouse;
				ptMouse.x = _ptMouse.x + CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				ptMouse.y = _ptMouse.y + CAMERAMANAGER->Use_Func()->get_CameraXY().y;

				// �� �����϶��� Ŭ���ϴ� ��� Ÿ���� �Ӽ��� �ʱ�ȭ ��������Ѵ�.
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
