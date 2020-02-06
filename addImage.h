#pragma once
#include "stdafx.h"

struct tagAddImage
{
	
	// 이미지를 키값으로 추가하는 함수
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
	
		// tile Rect Image
		IMAGEMANAGER->addImage("tile_Rect", "./image/Tile_Rect.bmp", 64, 64, true, RGB(255, 0, 255));

		// mapTool Icon
		IMAGEMANAGER->addImage("save_Icon", "./image/mapTool/icon/BT_Save.bmp", 52, 52, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("load_Icon", "./image/mapTool/icon/BT_Load.bmp", 52, 52, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("eraser_Icon", "./image/mapTool/icon/BT_Erase.bmp", 52, 52, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("ground_Icon", "./image/mapTool/icon/BT_Ground.bmp", 52, 52, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("ground_E_Icon", "./image/mapTool/icon/BT_Gound_E.bmp", 52, 52, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("trap_Icon", "./image/mapTool/icon/BT_Trap.bmp", 52, 52, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("Trap_E_Icon", "./image/mapTool/icon/BT_Trap_E.bmp", 52, 52, true, RGB(255, 0, 255));
	}
};
