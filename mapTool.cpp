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

	////////////////////////////////////////////////////////////////////
	_mapInfo.add_BackGround("tutorial_BG_0");		// �� �߰� (�׽�Ʈ��)
	_mapInfo.add_BackGround("tutorial_BG_1");
	_mapInfo.add_BackGround("tutorial_BG_2");
	////////////////////////////////////////////////////////////////////

	_mapTool_Func.make_Base_TileList(&_vTileList);	// Ÿ���� �⺻ ��Ʈ�� ����� �ش�.

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

	_button.click_Button();																													// Ŭ�� �ߴٸ� Ŭ�� �� ��ư���� �Ӽ��� �ٲ��ִ� �Լ�

	_pallet.setting_Pallet(_button.BT_Type, _button.BT_ImgNumber);																			// �ȷ�Ʈ ��ġ ����

	Find_Worker();																															// Ŭ�� �� ��ư�� ���� �Լ� ȣ��

	_button.reset_Next_Prev_Pos(_pallet.pallet);																							// ����, ���� ��ư ��ġ ���� �Լ�
	
	_pallet.click_PalletInfo_Save((BUTTON_TYPE)_button.BT_Type, _button.BT_ImgNumber, &_button.BT_start_Draw, &_button.BT_FindNoTile);		// �̹��� ����

	if(!_button.BT_FindNoTile)
		_mapTool_Func.setting_TileImg(&_vTileList, _pallet.current, _button, _mapInfo, &_button.BT_start_Draw);								// Ÿ�Ͽ� �̹����� �����Ѵ�. (�ٸ� ��Ʈ�� �浹 ���� �ʴ´ٸ� �׸���)


}

void mapTool::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);		// ��ü ȭ�� ���ſ�

	_mapTool_Func.show_BackImg(&_mapInfo, getMemDC());				// ��׶��� ����� ����Ѵ�.

	// Ÿ�� ��Ʈ ��� (�׽�Ʈ��)
	if (KEYMANAGER->isToggleKey(VK_NUMPAD1))
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);
		_mapTool_Func.show_Camera_In_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Size().x, CAMERAMANAGER->Use_Func()->get_Camera_Size().y, getMemDC(), &_vTileList);
	}

	_mapTool_Func.show_TileImg(getMemDC(), &_vTileList, _mapInfo);

	_button.show_Button(getMemDC());

	_mapTool_Func.show_Pallet(getMemDC(), (BUTTON_TYPE)_button.BT_Type, &_pallet);

}

void mapTool::testMove()
{
	// �׽�Ʈ�� ī�޶� Ű

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->Use_Func()->set_CameraX(CAMERAMANAGER->Use_Func()->get_CameraXY().x - 10);
		_mapInfo.loop->LoopX_BG_0 -= 6; 
		_mapInfo.loop->LoopX_BG_1 -= 4;
		_mapInfo.loop->LoopX_BG_2 -= 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->Use_Func()->set_CameraY(CAMERAMANAGER->Use_Func()->get_CameraXY().y - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->Use_Func()->set_CameraX(CAMERAMANAGER->Use_Func()->get_CameraXY().x + 10);
		_mapInfo.loop->LoopX_BG_0 += 6;
		_mapInfo.loop->LoopX_BG_1 += 4;
		_mapInfo.loop->LoopX_BG_2 += 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->Use_Func()->set_CameraY(CAMERAMANAGER->Use_Func()->get_CameraXY().y + 10);
	}

	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);
}

void mapTool::Find_Worker()
{
	// Ŭ���� ��ư�� ���� �ʿ��� �Լ��� ȣ���Ѵ�.
	switch ((BUTTON_TYPE)_button.BT_Type)
	{
		case BUTTON_TYPE::SAVE:
			DATAMANAGER->map_Save(_vTileList, &_mapInfo);

			break;

		case BUTTON_TYPE::LOAD:
			DATAMANAGER->map_Load(&_vTileList, &_mapInfo);

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
