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
	_mapInfo = new tagMapInfo;
	_mapInfo->reset_MapInfo();						// ������ �ʱ�ȭ

	////////////////////////////////////////////////////////////////////
	_mapInfo->add_BackGround("tutorial_BG_0");		// �� �߰� (�׽�Ʈ��)
	_mapInfo->add_BackGround("tutorial_BG_1");
	_mapInfo->add_BackGround("tutorial_BG_2");
	////////////////////////////////////////////////////////////////////

	_mapTool_Func.make_Base_TileList(&_vTileList);	// Ÿ���� �⺻ ��Ʈ�� ����� �ش�.

	_button.reset();								// ��ư �ʱ�ȭ

	_pallet = new tagPallets;
	_pallet->setting();

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	testMove();

	_button.click_Button();
	_button.reset_Next_Prev_Pos(_pallet->pallet);
	
	_pallet->click_PalletInfo_Save((BUTTON_TYPE)_button.BT_Type);

	_mapTool_Func.setting_TileImg(_vTileList, _pallet->current, _button);
}

void mapTool::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);		// ��ü ȭ�� ���ſ�

	_mapTool_Func.show_BackImg(_mapInfo, getMemDC());				// ��׶��� ����� ����Ѵ�.

	// Ÿ�� ��Ʈ ���
	if (KEYMANAGER->isToggleKey(VK_NUMPAD1))
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);
		_mapTool_Func.show_Camera_In_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Size().x, CAMERAMANAGER->Use_Func()->get_Camera_Size().y, getMemDC(), _vTileList);
	}
	_mapTool_Func.show_TileImg(getMemDC(), _vTileList);

	_button.show_Button(getMemDC());

	_mapTool_Func.show_Pallet(getMemDC(), (BUTTON_TYPE)_button.BT_Type, _pallet);

}

void mapTool::testMove()
{
	// �׽�Ʈ�� ī�޶� Ű

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->Use_Func()->set_CameraX(CAMERAMANAGER->Use_Func()->get_CameraXY().x - 10);
		_mapInfo->loop->LoopX_BG_0 -= 6; 
		_mapInfo->loop->LoopX_BG_1 -= 4;
		_mapInfo->loop->LoopX_BG_2 -= 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->Use_Func()->set_CameraY(CAMERAMANAGER->Use_Func()->get_CameraXY().y - 10);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->Use_Func()->set_CameraX(CAMERAMANAGER->Use_Func()->get_CameraXY().x + 10);
		_mapInfo->loop->LoopX_BG_0 += 6;
		_mapInfo->loop->LoopX_BG_1 += 4;
		_mapInfo->loop->LoopX_BG_2 += 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->Use_Func()->set_CameraY(CAMERAMANAGER->Use_Func()->get_CameraXY().y + 10);
	}

	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);
}
