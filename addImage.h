#pragma once
#include "stdafx.h"

struct tagAddImage
{
	
	// �̹����� Ű������ �߰��ϴ� �Լ�
	void addImage_Func()
	{
		// back Ground
		IMAGEMANAGER->addImage("tutorial_BG_0", "./image/mapTool/backGround/tutorial/tutorial_BG_0.bmp", 2160, 1800, false, RGB(0, 0, 0));
		IMAGEMANAGER->addImage("tutorial_BG_1", "./image/mapTool/backGround/tutorial/tutorial_BG_1.bmp", 2160, 1800, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("tutorial_BG_2", "./image/mapTool/backGround/tutorial/tutorial_BG_2.bmp", 2160, 1800, true, RGB(255, 0, 255));
	
		// tile
		IMAGEMANAGER->addFrameImage("tutorial_Tile", "./image/mapTool/tile/terrain_Tile/Tutorial_Tile.bmp", 576, 256, 9, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("stage1_Tile", "./image/mapTool/tile/terrain_Tile/Stage1_Tile.bmp", 576, 256, 9, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("stage2_Tile", "./image/mapTool/tile/terrain_Tile/Stage2_Tile.bmp", 576, 256, 9, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("stage3_Tile", "./image/mapTool/tile/terrain_Tile/Stage3_Tile.bmp", 512, 320, 8, 6, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("startPoint_Tile", "./image/mapTool/tile/terrain_Tile/StartPoint_Tile.bmp", 512, 128, 8, 2, true, RGB(255, 0, 255));
	
		// tile Rect Image
		IMAGEMANAGER->addImage("tile_Rect", "./image/Tile_Rect.bmp", 64, 64, true, RGB(255, 0, 255));

		// mapTool Icon
		IMAGEMANAGER->addImage("save_Icon", "./image/mapTool/icon/BT_Save.bmp", 52, 52, true, RGB(255, 0, 255));					// ���̺� ������
		IMAGEMANAGER->addImage("load_Icon", "./image/mapTool/icon/BT_Load.bmp", 52, 52, true, RGB(255, 0, 255));					// �ε� ������
		IMAGEMANAGER->addImage("eraser_Icon", "./image/mapTool/icon/BT_Eraser.bmp", 52, 52, true, RGB(255, 0, 255));					// ���찳 ������
		IMAGEMANAGER->addImage("ground_Icon", "./image/mapTool/icon/BT_Tile.bmp", 52, 52, true, RGB(255, 0, 255));					// ���� ������
		IMAGEMANAGER->addImage("ground_E_Icon", "./image/mapTool/icon/BT_Tile_E.bmp", 52, 52, true, RGB(255, 0, 255));				// ���� ���찳 ������
		IMAGEMANAGER->addImage("decoration_Icon", "./image/mapTool/icon/BT_Decoration.bmp", 52, 52, true, RGB(255, 0, 255));		// ���ڷ��̼� ������
		IMAGEMANAGER->addImage("decoration_E_Icon", "./image/mapTool/icon/BT_Decoration_E.bmp", 52, 52, true, RGB(255, 0, 255));	// ���ڷ��̼� ���찳 ������
		IMAGEMANAGER->addImage("hit_Object_Icon", "./image/mapTool/icon/BT_Hit_Object.bmp", 52, 52, true, RGB(255, 0, 255));		// �ı� ������Ʈ ������
		IMAGEMANAGER->addImage("hit_Object_E_Icon", "./image/mapTool/icon/BT_Hit_Object_E.bmp", 52, 52, true, RGB(255, 0, 255));	// �ı� ������Ʈ ���찳 ������
		IMAGEMANAGER->addImage("door_Icon", "./image/mapTool/icon/BT_Door.bmp", 52, 52, true, RGB(255, 0, 255));					// �� ������
		IMAGEMANAGER->addImage("door_E_Icon", "./image/mapTool/icon/BT_Door_E.bmp", 52, 52, true, RGB(255, 0, 255));				// �� ���찳 ������
		IMAGEMANAGER->addImage("character_Icon", "./image/mapTool/icon/BT_Character.bmp", 52, 52, true, RGB(255, 0, 255));			// ĳ���� ������
		IMAGEMANAGER->addImage("character_E_Icon", "./image/mapTool/icon/BT_Character_E.bmp", 52, 52, true, RGB(255, 0, 255));		// ĳ���� ���찳 ������
		IMAGEMANAGER->addImage("item_Icon", "./image/mapTool/icon/BT_Item.bmp", 52, 52, true, RGB(255, 0, 255));					// ������ ������
		IMAGEMANAGER->addImage("item_E_Icon", "./image/mapTool/icon/BT_Item_E.bmp", 52, 52, true, RGB(255, 0, 255));				// ������ ���찳 ������
		IMAGEMANAGER->addImage("trap_Icon", "./image/mapTool/icon/BT_Trap.bmp", 52, 52, true, RGB(255, 0, 255));					// ���� ������
		IMAGEMANAGER->addImage("trap_E_Icon", "./image/mapTool/icon/BT_Trap_E.bmp", 52, 52, true, RGB(255, 0, 255));				// ���� ���찳 ������
		IMAGEMANAGER->addImage("prev_Icon", "./image/mapTool/icon/leftArrow.bmp", 32, 30, true, RGB(255, 0, 255));					// ���� ������
		IMAGEMANAGER->addImage("next_Icon", "./image/mapTool/icon/rightArrow.bmp", 32, 30, true, RGB(255, 0, 255));					// ���� ������
	}
};