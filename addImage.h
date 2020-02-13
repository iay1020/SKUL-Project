#pragma once
#include "stdafx.h"

struct tagAddImage
{
	
	// 이미지를 키값으로 추가하는 함수
	void addImage_Func()
	{
		// back Ground <임시>
		IMAGEMANAGER->addImage("base_MapTool_BG", "./image/mapTool/backGround/base_MapTool_BG.bmp", 1600, 960, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("tutorial_BG_0", "./image/mapTool/backGround/tutorial/tutorial_BG_0.bmp", 2304, 1920, false, RGB(0, 0, 0));
		IMAGEMANAGER->addImage("tutorial_BG_1", "./image/mapTool/backGround/tutorial/tutorial_BG_1.bmp", 2304, 1920, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("tutorial_BG_2", "./image/mapTool/backGround/tutorial/tutorial_BG_2.bmp", 2304, 1920, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("stage1_BG_0", "./image/mapTool/backGround/stage_1/stage1_BG_0.bmp", 2304, 1920, false, RGB(0, 0, 0));
		IMAGEMANAGER->addImage("stage1_BG_1", "./image/mapTool/backGround/stage_1/stage1_BG_1.bmp", 2304, 1920, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("stage1_BG_2", "./image/mapTool/backGround/stage_1/stage1_BG_2.bmp", 2304, 1920, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("intro_BG_0", "./image/mapTool/backGround/intro/intro_BG_0.bmp", 3392, 960, false, RGB(0, 0, 0));
		IMAGEMANAGER->addImage("intro_BG_1", "./image/mapTool/backGround/intro/intro_BG_1.bmp", 3392, 960, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("intro_BG_2", "./image/mapTool/backGround/intro/intro_BG_2.bmp", 3392, 960, true, RGB(255, 0, 255));
	

		// tile Rect Image
		IMAGEMANAGER->addImage("tile_Rect", "./image/Tile_Rect.bmp", 64, 64, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("tile_Rect_200", "./image/Tile_Rect_200.bmp", 200, 200, true, RGB(255, 0, 255));


		// mapTool Icon
		IMAGEMANAGER->addImage("save_Icon", "./image/mapTool/icon/BT_Save.bmp", 52, 52, true, RGB(255, 0, 255));									// 세이브 아이콘
		IMAGEMANAGER->addImage("load_Icon", "./image/mapTool/icon/BT_Load.bmp", 52, 52, true, RGB(255, 0, 255));									// 로드 아이콘
		IMAGEMANAGER->addImage("eraser_Icon", "./image/mapTool/icon/BT_Eraser.bmp", 52, 52, true, RGB(255, 0, 255));								// 지우개 아이콘
		IMAGEMANAGER->addImage("ground_Icon", "./image/mapTool/icon/BT_Tile.bmp", 52, 52, true, RGB(255, 0, 255));									// 지형 아이콘
		IMAGEMANAGER->addImage("ground_E_Icon", "./image/mapTool/icon/BT_Tile_E.bmp", 52, 52, true, RGB(255, 0, 255));								// 지형 지우개 아이콘
		IMAGEMANAGER->addImage("decoration_Icon", "./image/mapTool/icon/BT_Decoration.bmp", 52, 52, true, RGB(255, 0, 255));						// 데코레이션 아이콘
		IMAGEMANAGER->addImage("decoration_E_Icon", "./image/mapTool/icon/BT_Decoration_E.bmp", 52, 52, true, RGB(255, 0, 255));					// 데코레이션 지우개 아이콘
		IMAGEMANAGER->addImage("hit_Object_Icon", "./image/mapTool/icon/BT_Hit_Object.bmp", 52, 52, true, RGB(255, 0, 255));						// 파괴 오브젝트 아이콘
		IMAGEMANAGER->addImage("hit_Object_E_Icon", "./image/mapTool/icon/BT_Hit_Object_E.bmp", 52, 52, true, RGB(255, 0, 255));					// 파괴 오브젝트 지우개 아이콘
		IMAGEMANAGER->addImage("door_Icon", "./image/mapTool/icon/BT_Door.bmp", 52, 52, true, RGB(255, 0, 255));									// 문 아이콘
		IMAGEMANAGER->addImage("door_E_Icon", "./image/mapTool/icon/BT_Door_E.bmp", 52, 52, true, RGB(255, 0, 255));								// 문 지우개 아이콘
		IMAGEMANAGER->addImage("character_Icon", "./image/mapTool/icon/BT_Character.bmp", 52, 52, true, RGB(255, 0, 255));							// 캐릭터 아이콘
		IMAGEMANAGER->addImage("character_E_Icon", "./image/mapTool/icon/BT_Character_E.bmp", 52, 52, true, RGB(255, 0, 255));						// 캐릭터 지우개 아이콘
		IMAGEMANAGER->addImage("item_Icon", "./image/mapTool/icon/BT_Item.bmp", 52, 52, true, RGB(255, 0, 255));									// 아이템 아이콘
		IMAGEMANAGER->addImage("item_E_Icon", "./image/mapTool/icon/BT_Item_E.bmp", 52, 52, true, RGB(255, 0, 255));								// 아이템 지우개 아이콘
		IMAGEMANAGER->addImage("trap_Icon", "./image/mapTool/icon/BT_Trap.bmp", 52, 52, true, RGB(255, 0, 255));									// 함정 아이콘
		IMAGEMANAGER->addImage("trap_E_Icon", "./image/mapTool/icon/BT_Trap_E.bmp", 52, 52, true, RGB(255, 0, 255));								// 함정 지우개 아이콘
		IMAGEMANAGER->addImage("back_Ground_Icon", "./image/mapTool/icon/BT_BackGround.bmp", 52, 52, true, RGB(255, 0, 255));						// 백 그라운드 아이콘
		IMAGEMANAGER->addImage("back_Ground_E_Icon", "./image/mapTool/icon/BT_BackGround_E.bmp", 52, 52, true, RGB(255, 0, 255));					// 백 그라운드 아이콘
		IMAGEMANAGER->addImage("prev_Icon", "./image/mapTool/icon/leftArrow.bmp", 32, 30, true, RGB(255, 0, 255));									// 이전 아이콘
		IMAGEMANAGER->addImage("next_Icon", "./image/mapTool/icon/rightArrow.bmp", 32, 30, true, RGB(255, 0, 255));									// 다음 아이콘
		IMAGEMANAGER->addImage("up_Icon", "./image/mapTool/icon/UpArrow.bmp", 32, 30, true, RGB(255, 0, 255));										// 업 아이콘
		IMAGEMANAGER->addImage("down_Icon", "./image/mapTool/icon/DownArrow.bmp", 32, 30, true, RGB(255, 0, 255));									// 다운 아이콘
		IMAGEMANAGER->addImage("back_Ground_Select", "./image/mapTool/icon/backGround_Select.bmp", 32, 32, true, RGB(255, 0, 255));					// 백 그라운드 선택 위치
		IMAGEMANAGER->addImage("back_Ground_Select_Pointer", "./image/mapTool/icon/backGround_Select_Pointer.bmp", 32, 32, true, RGB(255, 0, 255));	// 백 그라운드 선택 포인터
		IMAGEMANAGER->addImage("minus_Icon", "./image/mapTool/icon/Minus.bmp", 32, 30, true, RGB(255, 0, 255));										// 레이어 삭제 버튼
		IMAGEMANAGER->addImage("rect_Plus_Icon", "./image/mapTool/icon/BT_Rect_Plus.bmp", 52, 52, true, RGB(255, 0, 255));


		// mapTool <tile Pallet>
		IMAGEMANAGER->addFrameImage("tutorial_Tile", "./image/mapTool/tile/terrain_Tile/Tutorial_Tile.bmp", 576, 256, 9, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("stage1_Tile", "./image/mapTool/tile/terrain_Tile/Stage1_Tile.bmp", 576, 256, 9, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("stage2_Tile", "./image/mapTool/tile/terrain_Tile/Stage2_Tile.bmp", 576, 256, 9, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("stage3_Tile", "./image/mapTool/tile/terrain_Tile/Stage3_Tile.bmp", 512, 320, 8, 5, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("startPoint_Tile", "./image/mapTool/tile/terrain_Tile/StartPoint_Tile.bmp", 512, 128, 8, 2, true, RGB(255, 0, 255));


		// mapTool <backGround Pallet>
		IMAGEMANAGER->addFrameImage("backGround_Pallet_0", "./image/mapTool/backGround/backGround_Img_0.bmp", 600, 600, 3, 3, true, RGB(255, 0, 255));


		//■■■■■■■■ Skul Image ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// <Idle>
		IMAGEMANAGER->addFrameImage("skul_Idle_NoWeapon", "./image/skul/Idle/skul_Idle_NoWeapon.bmp", 224, 132, 4, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("skul_Idle_HaveWeapon_NoHead", "./image/skul/Idle/skul_Idle_HaveWeapon_NoHead.bmp", 304, 100, 4, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("skul_Idle_HaveWeapon", "./image/skul/Idle/skul_Idle_HaveWeapon.bmp", 304, 132, 4, 4, true, RGB(255, 0, 255));

		// <Walk>

		// <Dash>
		IMAGEMANAGER->addImage("skul_Dash", "./image/skul/Dash/skul_Dash.bmp", 84, 56, true, RGB(255, 0, 255));
		IMAGEMANAGER->addImage("skul_Dash_NoHead", "./image/skul/Dash/skul_Dash_NoHead.bmp", 70, 48, true, RGB(255, 0, 255));

		// <Jump>
		IMAGEMANAGER->addFrameImage("skul_Jump", "./image/skul/Jump/skul_Jump.bmp", 72, 128, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("skul_Jump_NoHead", "./image/skul/Jump/skul_Jump_NoHead.bmp", 72, 96, 2, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("skul_Jump_Attack", "./image/skul/Jump/skul_Jump_Attack.bmp", 456, 216, 4, 4, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("skul_Jump_NoHead_Attack", "./image/skul/Jump/skul_Jump_NoHead_Attack.bmp", 456, 214, 4, 4, true, RGB(255, 0, 255));

		// <Fall>
		IMAGEMANAGER->addFrameImage("skul_Fall", "./image/skul/Fall/skul_Fall.bmp", 360, 148, 5, 2, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("skul_Fall_NoHead", "./image/skul/Fall/skul_Fall_NoHead.bmp", 360, 152, 5, 2, true, RGB(255, 0, 255));

		// <Loading Skul>

		// <Skul Parts>

		//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■


		// 메롱
	}
};
