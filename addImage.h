#pragma once
#include "stdafx.h"

struct tagAddImage
{
	
	// 이미지를 키값으로 추가하는 함수
	void addImage_Func()
	{
		
		// back Ground <임시>
		{
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
		}

		// tile Rect Image
		{
			IMAGEMANAGER->addImage("tile_Rect", "./image/Tile_Rect.bmp", 64, 64, true, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("tile_Rect_200", "./image/Tile_Rect_200.bmp", 200, 200, true, RGB(255, 0, 255));
		}

		// mapTool Icon
		{
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
			IMAGEMANAGER->addImage("footHoldType_Check", "./image/mapTool/icon/FootHoldType_Check.bmp", 64, 64, true, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("wallType_Check", "./image/mapTool/icon/WallType_Check.bmp", 64, 64, true, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("trapType_Check", "./image/mapTool/icon/TrapType_Check.bmp", 64, 64, true, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("footHoldType_Check_Button", "./image/mapTool/icon/FootHoldType_Check_Button.bmp", 32, 30, true, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("wallType_Check_Button", "./image/mapTool/icon/WallType_Check_Button.bmp", 32, 30, true, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("trapType_Check_Button", "./image/mapTool/icon/TrapType_Check_Button.bmp", 32, 30, true, RGB(255, 0, 255));
		}

		// 치킨은 사회 악이다
		// 치킨을 먹으면 건강이 나빠진당
		// 치킨 말고 모든 영양소를 가진 햄버거를 먹쟝
		// -혜완-


		// mapTool <tile Pallet>
		{
			IMAGEMANAGER->addFrameImage("tutorial_Tile", "./image/mapTool/tile/terrain_Tile/Tutorial_Tile.bmp", 576, 256, 9, 4, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("stage1_Tile", "./image/mapTool/tile/terrain_Tile/Stage1_Tile.bmp", 576, 256, 9, 4, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("stage2_Tile", "./image/mapTool/tile/terrain_Tile/Stage2_Tile.bmp", 576, 256, 9, 4, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("stage3_Tile", "./image/mapTool/tile/terrain_Tile/Stage3_Tile.bmp", 512, 320, 8, 5, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("startPoint_Tile", "./image/mapTool/tile/terrain_Tile/StartPoint_Tile.bmp", 512, 128, 8, 2, true, RGB(255, 0, 255));
		}

		// mapTool <backGround Pallet>
		{
			IMAGEMANAGER->addFrameImage("backGround_Pallet_0", "./image/mapTool/backGround/backGround_Img_0.bmp", 600, 600, 3, 3, true, RGB(255, 0, 255));
		}



		//■■■■■■■■ Ui Image ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// status 
		{
			IMAGEMANAGER->addImage("status_UI", "./image/UI/Status_Ui/status_Ui_img.bmp", 360, 112, true, RGB(255, 0, 255));
		}

		// character 
		{
			IMAGEMANAGER->addImage("skul_Icon", "./image/UI/Character_Icon/skul_Icon.bmp", 90, 90, true, RGB(255, 0, 255));
		}

		// skill 
		{
			IMAGEMANAGER->addImage("skill_Null", "./image/UI/Skill_Img/skill_Null.bmp", 48, 48, false, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("skul_ThrowHead_Skill", "./image/UI/Skill_Img/skul_ThrowHead_Skill_Img.bmp", 48, 48, true, RGB(255, 0, 255));
		}

		// hp 
		{
			IMAGEMANAGER->addImage("skul_HP", "./image/UI/HP_Bar/Hp_Bar.bmp", 280, 20, false, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("skul_HP_Heal", "./image/UI/HP_Bar/Hp_Bar_Heal.bmp", 280, 20, false, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("skul_HP_Hit", "./image/UI/HP_Bar/Hp_Bar_Hit.bmp", 280, 20, false, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("skul_HP_Null", "./image/UI/HP_Bar/Hp_Bar_Null.bmp", 280, 20, false, RGB(255, 0, 255));

		}

		// enemy 
		{
			IMAGEMANAGER->addImage("enemy_HP_Bar", "./image/UI/Enemy_HP_Bar/enemy_HP_Bar_Frame.bmp", 125, 12, true, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("enemy_HP", "./image/UI/Enemy_HP_Bar/enemy_HP.bmp", 117, 10, true, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("enemy_HP_Hit", "./image/UI/Enemy_HP_Bar/enemy_HP_Hit.bmp", 117, 10, true, RGB(255, 0, 255));

		}

		// miniMap
		{
			IMAGEMANAGER->addImage("miniMap_Player", "./image/UI/miniMap/player_MiniMap.bmp", 8, 16, false, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("miniMap_Enemy", "./image/UI/miniMap/enemy_MiniMap.bmp", 8, 16, false, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("miniMap_Door", "./image/UI/miniMap/door_miniMap.bmp", 16, 32, false, RGB(255, 0, 255));

			IMAGEMANAGER->addFrameImage("stage1_Tile_S", "./image/UI/miniMap/Stage1_Tile_S.bmp", 144, 64, 9, 4, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("stage2_Tile_S", "./image/UI/miniMap/Stage2_Tile_S.bmp", 144, 64, 9, 4, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("tutorial_Tile_S", "./image/UI/miniMap/Tutorial_Tile_S.bmp", 144, 64, 9, 4, true, RGB(255, 0, 255));

			IMAGEMANAGER->addImage("miniMap_Frame", "./image/UI/miniMap/Minimap_Frame.bmp", 400, 240, true, RGB(255, 0, 255));
			IMAGEMANAGER->addImage("miniMap_BG", "./image/UI/miniMap/miniMap_BG.bmp", 400, 240, false, RGB(255, 0, 255));
		}



		//■■■■■■■■ Event Image ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		{
			// 무기를 주는 이벤트 해골
			IMAGEMANAGER->addFrameImage("give_Weapon_NPC", "./image/event/give_Weapon_NPC.bmp", 2124, 54, 18, 1, true, RGB(255, 0, 255));
			KEYANIMANAGER->addCoordinateFrameAnimation("give_Weapon_Start", "give_Weapon_NPC", 0, 6, 3, false, false);
			KEYANIMANAGER->addCoordinateFrameAnimation("give_Weapon_End", "give_Weapon_NPC", 7, 17, 3, false, false);

			// 무기를 받는 이벤트 스컬
			IMAGEMANAGER->addFrameImage("get_Weapon_Skul", "./image/event/skul_Get_Weapon_Event.bmp", 1600, 119, 10, 1, true, RGB(255, 0, 255));
			KEYANIMANAGER->addCoordinateFrameAnimation("get_Weapon_Skul_Ani", "get_Weapon_Skul", 0, 9, 10, false, false);

			// 이벤트 키 출력
			IMAGEMANAGER->addImage("F_Key", "./image/event/F_Key.bmp", 26, 24, true, RGB(255, 0, 255));

			// 도어
			IMAGEMANAGER->addImage("Door_1", "./image/mapTool/door/next_Gate.bmp", 352, 258, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("Door_Fire_1", "./image/mapTool/door/gate_Fire_1.bmp", 1872, 80, 8, 1, true, RGB(255, 0, 255));
			KEYANIMANAGER->addCoordinateFrameAnimation("Door_Fire_1", "Door_Fire_1", 0, 7, 10, false, true);
		}


		//■■■■■■■■ Skul Image ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// <Idle>
		{
			IMAGEMANAGER->addFrameImage("skul_Idle_NoWeapon", "./image/skul/Idle/skul_Idle_NoWeapon.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Idle_HaveWeapon", "./image/skul/Idle/skul_Idle_HaveWeapon.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Idle_HaveWeapon_NoHead", "./image/skul/Idle/skul_Idle_HaveWeapon_NoHead.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
		}

		// <Walk>
		{
			IMAGEMANAGER->addFrameImage("skul_Walk_NoWeapon", "./image/skul/Walk/skul_Walk_NoWeapon.bmp", 1280, 238, 8, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Walk_Weapon", "./image/skul/Walk/skul_Walk_Weapon.bmp", 1280, 238, 8, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Walk_NoHead_Weapon", "./image/skul/Walk/skul_Walk_NoHead_Weapon.bmp", 1280, 238, 8, 2, true, RGB(255, 0, 255));
		}

		// <Dash>
		{
			IMAGEMANAGER->addFrameImage("skul_Dash", "./image/skul/Dash/skul_Dash.bmp", 320, 238, 2, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Dash_NoHead", "./image/skul/Dash/skul_Dash_NoHead.bmp", 320, 238, 2, 2, true, RGB(255, 0, 255));

			IMAGEMANAGER->addFrameImage("skul_Dash_Effect", "./image/effect/Dash/skul_Dash_Effect.bmp", 4654, 398, 13, 2, true, RGB(255, 0, 255));
	
		}
		// 게임을 시작하지 

		// <Jump>
		{
			//IMAGEMANAGER->addFrameImage("skul_Jump", "./image/skul/Jump/skul_Jump.bmp", 620, 442, 2, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Jump", "./image/skul/Jump/skul_Jump.bmp", 320, 238, 2, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Jump_NoHead", "./image/skul/Jump/skul_Jump_NoHead.bmp", 320, 238, 2, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Jump_Attack", "./image/skul/Jump/skul_Jump_Attack.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Jump_NoHead_Attack", "./image/skul/Jump/skul_Jump_NoHead_Attack.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));

			// 점프 이펙트
			IMAGEMANAGER->addFrameImage("skul_Jump_Effect", "./image/effect/Jump/skul_Jump_Effect.bmp", 4654, 199, 13, 1, true, RGB(255, 0, 255));
			// 더블 점프 이펙트
			IMAGEMANAGER->addFrameImage("skul_Double_Jump_Effect", "./image/effect/Jump/skul_Double_Jump_Effect.bmp", 3580, 199, 10, 1, true, RGB(255, 0, 255));
			
		}

		// <Fall>
		{
			IMAGEMANAGER->addFrameImage("skul_Fall", "./image/skul/Fall/skul_Fall.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Fall_NoHead", "./image/skul/Fall/skul_Fall_NoHead.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Falling", "./image/skul/Fall/skul_Falling.bmp", 480, 238, 3, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Falling_NoHead", "./image/skul/Fall/skul_Falling_NoHead.bmp", 480, 238, 3, 2, true, RGB(255, 0, 255));
		}

		// <Attack>
		{
			IMAGEMANAGER->addFrameImage("skul_Attack_A", "./image/skul/Attack/skul_Attack_A.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Attack_B", "./image/skul/Attack/skul_Attack_B.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Attack_A_NoHead", "./image/skul/Attack/skul_Attack_A_NoHead.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Attack_B_NoHead", "./image/skul/Attack/skul_Attack_B_NoHead.bmp", 800, 238, 5, 2, true, RGB(255, 0, 255));

			// < base Attack Effect>
			IMAGEMANAGER->addFrameImage("skul_Base_Attack_Right", "./image/effect/Skul_Base_Attack_Effect/base_Attack_Right.bmp", 900, 112, 9, 1, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Base_Attack_Left", "./image/effect/Skul_Base_Attack_Effect/base_Attack_Left.bmp", 900, 112, 9, 1, true, RGB(255, 0, 255));
			EFFECTMANAGER->addEffect("skul_Base_Attack_Right", "skul_Base_Attack_Right", 900, 112, 100, 112, 1, 1, 1);
			EFFECTMANAGER->addEffect("skul_Base_Attack_Left", "skul_Base_Attack_Left", 900, 112, 100, 112, 1, 1, 1);

			IMAGEMANAGER->addFrameImage("skul_Base_Attack_Cri_1", "./image/effect/Skul_Base_Attack_Effect/base_Attack_Cri_1.bmp", 1168, 129, 8, 1, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Base_Attack_Cri_2", "./image/effect/Skul_Base_Attack_Effect/base_Attack_Cri_2.bmp", 1168, 129, 8, 1, true, RGB(255, 0, 255));
			EFFECTMANAGER->addEffect("skul_Base_Attack_Cri_1", "skul_Base_Attack_Cri_1", 1168, 129, 146, 129, 1, 1, 1);
			EFFECTMANAGER->addEffect("skul_Base_Attack_Cri_2", "skul_Base_Attack_Cri_2", 1168, 129, 146, 129, 1, 1, 1);
		}

		// <Skill>
		{
			IMAGEMANAGER->addFrameImage("skul_Skill", "./image/skul/Skill/skul_Skill.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Skill_Head", "./image/skul/Skill/skul_Skill_Head.bmp", 120, 60, 4, 2, true, RGB(255, 0, 255));

			// throw Skul Skill
			IMAGEMANAGER->addFrameImage("throw_Head_Effect", "./image/effect/Hit_Skul/Hit_Skul.bmp", 1000, 224, 10, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("throw_Head_Effect_L", "./image/effect/Hit_Skul/hit_Skul_Left.bmp", 900, 112, 9, 1, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("throw_Head_Effect_R", "./image/effect/Hit_Skul/hit_Skul_Right.bmp", 900, 112, 9, 1, true, RGB(255, 0, 255));
			EFFECTMANAGER->addEffect("throw_Head_Effect_L", "throw_Head_Effect_L", 900, 112, 100, 112, 1, 1, 1);
			EFFECTMANAGER->addEffect("throw_Head_Effect_R", "throw_Head_Effect_R", 900, 112, 100, 112, 1, 1, 1);

			// <throw Skul Skill Reset Effect
			IMAGEMANAGER->addFrameImage("throw_Head_Reset_Effect", "./image/effect/skul_Head_Skill_Reset/skul_Head_Skill_Reset.bmp", 3200, 119, 20, 1, true, RGB(255, 0, 255));
			EFFECTMANAGER->addEffect("throw_Head_Reset_Effct", "throw_Head_Reset_Effect", 3200, 119, 160, 119, 1, 1, 1);

		}

		// <Hit>
		{
			IMAGEMANAGER->addFrameImage("skul_Hit_Damage", "./image/effect/skul_Hit_Damage/skul_Hit_Damage.bmp", 1296, 141, 8, 1, true, RGB(255, 0, 255));
			EFFECTMANAGER->addEffect("skul_Hit_Damage", "skul_Hit_Damage", 1296, 141, 162, 141, 1, 0.2f, 1);

		}

		// <Loading Skul>

		// <Skul Parts>

		//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

		//■■■■■■■■ Skul Ani Image ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

		// <Idle>
		{
			// Idle Right NoWeapon Ani
			int idle_R_NoWeapon[] = { 0, 1, 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Idle_Right_NoWeapon", "skul_Idle_NoWeapon", idle_R_NoWeapon, 4, 10, true);
			// Idle Right HaveWeapon Ani
			int idle_R_HaveWeapon[] = { 0, 1, 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Idle_Right_HaveWeapon", "skul_Idle_HaveWeapon", idle_R_HaveWeapon, 4, 10, true);
			// Idle Right HaveWeapon NoHead Ani
			int idle_R_HaveWeapon_NoHead[] = { 0, 1, 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Idle_Right_HaveWeapon_NoHead", "skul_Idle_HaveWeapon_NoHead", idle_R_HaveWeapon_NoHead, 4, 10, true);

			// Idle Left NoWeapon Ani
			int idle_L_NoWeapon[] = { 7, 6, 5, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Idle_Left_NoWeapon", "skul_Idle_NoWeapon", idle_L_NoWeapon, 4, 10, true);
			// Idle Left HaveWeapon Ani
			int idle_L_HaveWeapon[] = { 7, 6, 5, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Idle_Left_HaveWeapon", "skul_Idle_HaveWeapon", idle_L_HaveWeapon, 4, 10, true);
			// Idle Left HaveWeapon NoHead Ani
			int idle_L_HaveWeapon_NoHead[] = { 7, 6, 5, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Idle_Left_HaveWeapon_NoHead", "skul_Idle_HaveWeapon_NoHead", idle_L_HaveWeapon_NoHead, 4, 10, true);
		}

		// <Walk>
		{
			// Walk_Right NoWeapon Ani
			int walk_R_NoWeapon[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Walk_Right_NoWeapon", "skul_Walk_NoWeapon", walk_R_NoWeapon, 8, 10, true);
			// Walk Right HaveWeapon Ani
			int walk_R_HaveWeapon[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Walk_Right_HaveWeapon", "skul_Walk_Weapon", walk_R_HaveWeapon, 8, 10, true);
			// Walk Right HaveWeapon NoHead Ani
			int walk_R_HaveWeapon_NoHead[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Walk_Right_HaveWeapon_NoHead", "skul_Walk_NoHead_Weapon", walk_R_HaveWeapon_NoHead, 8, 10, true);

			// Walk Left NoWeapon Ani
			int walk_L_NoWeapon[] = { 8, 9, 10, 11, 12, 13, 14, 15 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Walk_Left_NoWeapon", "skul_Walk_NoWeapon", walk_L_NoWeapon, 8, 10, true);
			// Walk Left HaveWeapon Ani
			int walk_L_HaveWeapon[] = { 8, 9, 10, 11, 12, 13, 14, 15 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Walk_Left_HaveWeapon", "skul_Walk_Weapon", walk_L_HaveWeapon, 8, 10, true);
			// Walk Left HaveWeapon NoHead Ani
			int walk_L_HaveWeapon_NoHead[] = { 8, 9, 10, 11, 12, 13, 14, 15 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Walk_Left_HaveWeapon_NoHead", "skul_Walk_NoHead_Weapon", walk_L_HaveWeapon_NoHead, 8, 10, true);
		}

		// <Jump>
		{
			// jump Right NoWeapon Ani
			int jump_R_NoWeapon[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Jump_Right_NoWeapon", "skul_Jump", jump_R_NoWeapon, 2, 10, false);
			// jump Right NoHead Ani
			int jump_R_NoHead[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Jump_Right_NoHead", "skul_Jump_NoHead", jump_R_NoHead, 2, 10, false);



			// jump Left NoWeapon Ani
			int jump_L_NoWeapon[] = { 3, 2 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Jump_Left_NoWeapon", "skul_Jump", jump_L_NoWeapon, 2, 10, false);
			// jump Left NoHead Ani
			int jump_L_NoHead[] = { 3, 2 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Jump_Left_NoHead", "skul_Jump_NoHead", jump_L_NoHead, 2, 10, false);


			// jump Effect ani
			int jump_Effect[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Jump_Ani_Effect", "skul_Jump_Effect", jump_Effect, 8, 10, false);
			// Double Jump Effect ani
			int double_Jump_Effect[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Double_Jump_Ani_Effect", "skul_Double_Jump_Effect", double_Jump_Effect, 10, 10, false);

		}

		// <Jump Attack>
		{
			// jump Right Attack Ani
			int jump_R_Attack[] = { 0, 1, 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Jump_Right_Attack", "skul_Jump_Attack", jump_R_Attack, 4, 10, false);
			// jump Right Attack NoHead Ani
			int jump_R_Attack_NoHead[] = { 0, 1, 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Jump_Right_Attack_NoHead", "skul_Jump_NoHead_Attack", jump_R_Attack_NoHead, 4, 10, false);

			// jump Left Attack Ani
			int jump_L_Attack[] = { 7, 6, 5, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Jump_Left_Attack", "skul_Jump_Attack", jump_L_Attack, 4, 10, false);
			// jump Left Attack NoHead Ani
			int jump_L_Attack_NoHead[] = { 7, 6, 5, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Jump_Left_Attack_NoHead", "skul_Jump_NoHead_Attack", jump_L_Attack_NoHead, 4, 10, false);
		}

		// <Fall>
		{
			int fall_R_NoWeapon[] = { 0, 1, 2, 3, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Fall_Right_NoWeapon", "skul_Fall", fall_R_NoWeapon, 5, 10, false);
			int falling_R_NoWeapon[] = { 0, 1, 2 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Falling_Right_NoWeapon", "skul_Falling", falling_R_NoWeapon, 3, 10, true);
			int fall_R_NoHead[] = { 0, 1, 2, 3, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Fall_Right_NoHead", "skul_Fall_NoHead", fall_R_NoHead, 5, 10, false);
			int falling_R_NoHead[] = { 0, 1, 2 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Falling_Right_NoHead", "skul_Falling_NoHead", falling_R_NoHead, 3, 10, true);

			int fall_L_NoWeapon[] = { 5, 6, 7, 8, 9 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Fall_Left_NoWeapon", "skul_Fall", fall_L_NoWeapon, 5, 10, false);
			int falling_L_NoWeapon[] = { 3, 4, 5 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Falling_Left_NoWeapon", "skul_Falling", falling_L_NoWeapon, 3, 10, true);
			int fall_L_NoHead[] = { 5, 6, 7, 8, 9 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Fall_Left_NoHead", "skul_Fall_NoHead", fall_L_NoHead, 5, 10, false);
			int falling_L_NoHead[] = { 3, 4, 5 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Falling_Left_NoHead", "skul_Falling_NoHead", falling_L_NoHead, 3, 10, true);
		}

		// <Dash>
		{
			int dash_R[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Dash_Right", "skul_Dash", dash_R, 2, 10, true);
			int dash_R_NoHead[] = { 0, 1 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Dash_Right_NoHead", "skul_Dash_NoHead", dash_R_NoHead, 2, 10, true);
			int dash_R_Effect[] = { 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Dash_Right_Effect", "skul_Dash_Effect", dash_R_Effect, 13, 10, false);

			int dash_L[] = { 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Dash_Left", "skul_Dash", dash_L, 2, 10, true);
			int dash_L_NoHead[] = { 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Dash_Left_NoHead", "skul_Dash_NoHead", dash_L_NoHead, 2, 10, true);
			int dash_L_Effect[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Dash_Left_Effect", "skul_Dash_Effect", dash_L_Effect, 13, 10, false);
		
		}

		// <Attack A, B>
		{
			int attack_A_R[] = { 0, 1, 2, 3, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Attack_A_Right", "skul_Attack_A", attack_A_R, 5, 10, false);
			int attack_B_R[] = { 0, 1, 2, 3, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Attack_B_Right", "skul_Attack_B", attack_B_R, 5, 10, false);

			int attack_A_L[] = { 5, 6, 7, 8, 9 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Attack_A_Left", "skul_Attack_A", attack_A_L, 5, 10, false);
			int attack_B_L[] = { 5, 6, 7, 8, 9 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Attack_B_Left", "skul_Attack_B", attack_B_L, 5, 10, false);



			// <Attack A NoHead>
			int attack_A_R_N[] = { 0, 1, 2, 3, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Attack_A_Right_N", "skul_Attack_A_NoHead", attack_A_R_N, 5, 10, false);
			int attack_B_R_N[] = { 0, 1, 2, 3, 4 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Attack_B_Right_N", "skul_Attack_B_NoHead", attack_B_R_N, 5, 10, false);

			int attack_A_L_N[] = { 5, 6, 7, 8, 9 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Attack_A_Left_N", "skul_Attack_A_NoHead", attack_A_L_N, 5, 10, false);
			int attack_B_L_N[] = { 5, 6, 7, 8, 9 };
			KEYANIMANAGER->addArrayFrameAnimation("skul_Attack_B_Left_N", "skul_Attack_B_NoHead", attack_B_L_N, 5, 10, false);


		}


		// Throw Head Skill
		{
			int throw_Head_R[] = { 0, 1, 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("throw_Head_R", "skul_Skill", throw_Head_R, 4, 10, false);

			int skill_Head_R[] = { 0, 1, 2, 3 };
			KEYANIMANAGER->addArrayFrameAnimation("skill_Head_R", "skul_Skill_Head", skill_Head_R, 4, 10, true);


			int throw_Head_L[] = { 4, 5, 6, 7 };
			KEYANIMANAGER->addArrayFrameAnimation("throw_Head_L", "skul_Skill", throw_Head_L, 4, 10, false);

			int skill_Head_L[] = { 4, 5, 6, 7 };
			KEYANIMANAGER->addArrayFrameAnimation("skill_Head_L", "skul_Skill_Head", skill_Head_L, 4, 10, true);


			// Throw Head Skill Effect
			int throw_Head_R_Effect[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			KEYANIMANAGER->addArrayFrameAnimation("throw_Head_R_Effect", "throw_Head_Effect", throw_Head_R_Effect, 10, 10, false);

			int throw_Head_L_Effect[] = { 19, 18, 17, 16, 15, 14, 13, 12, 11, 10 };
			KEYANIMANAGER->addArrayFrameAnimation("throw_Head_L_Effect", "throw_Head_Effect", throw_Head_L_Effect, 10, 10, false);


		}


		//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■


		// 메롱

		
		//■■■■■■■■ Enemy ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// <soldier Idle>
		IMAGEMANAGER->addFrameImage("soldier_Idle", "./image/enemy/soldier/Idle/soldier_Idle.bmp", 860, 240, 5, 2, true, RGB(255, 0, 255));
		
		// <soldier Walk>
		IMAGEMANAGER->addFrameImage("soldier_Walk", "./image/enemy/soldier/Walk/soldier_Walk.bmp", 1376, 240, 8, 2, true, RGB(255, 0, 255));
		
		// <soldier Hit>
		IMAGEMANAGER->addFrameImage("soldier_Hit", "./image/enemy/soldier/Hit/soldier_Hit.bmp", 344, 240, 2, 2, true, RGB(255, 0, 255));
		
		// <soldier Attack>
		IMAGEMANAGER->addFrameImage("soldier_Attack", "./image/enemy/soldier/Attack/soldier_Attack.bmp", 860, 240, 5, 2, true, RGB(255, 0, 255));
		



		// <archer Idle>
		IMAGEMANAGER->addFrameImage("archer_Idle", "./image/enemy/archer/Idle/archer_Idle.bmp", 620, 250, 4, 2, true, RGB(255, 0, 255));

		// <archer Walk>
		IMAGEMANAGER->addFrameImage("archer_Walk", "./image/enemy/archer/Walk/archer_Walk.bmp", 775, 250, 5, 2, true, RGB(255, 0, 255));

		// <archer Hit>
		IMAGEMANAGER->addFrameImage("archer_Hit", "./image/enemy/archer/Hit/archer_Hit.bmp", 310, 250, 2, 2, true, RGB(255, 0, 255));

		// <archer Attack>
		IMAGEMANAGER->addFrameImage("archer_Attack", "./image/enemy/archer/Attack/archer_Attack.bmp", 620, 250, 4, 2, true, RGB(255, 0, 255));

		// <archer Arrow>
		IMAGEMANAGER->addFrameImage("archer_Arrow_Right", "./image/effect/archer_Arrow/enemy_Arrow_Right.bmp", 100, 22, 2, 1, true, RGB(255, 0, 255));
		IMAGEMANAGER->addFrameImage("archer_Arrow_Left", "./image/effect/archer_Arrow/enemy_Arrow_Left.bmp", 100, 22, 2, 1, true, RGB(255, 0, 255));


		// <enemy Die Effect>
		IMAGEMANAGER->addFrameImage("enemy_Die_Effect", "./image/effect/enemy_Die/enemy_Die.bmp", 600, 103, 6, 1, true, RGB(255, 0, 255));
		EFFECTMANAGER->addEffect("enemy_Die_Effect", "enemy_Die_Effect", 600, 103, 100, 103, 1, 0.2f, 1);

		
		//■■■■■■■■ Enemy Ani ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// <soldier Idle Ani>
		int soldier_Idle_Right[] = { 0, 1, 2, 3, 4 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Idle_Right_Ani", "soldier_Idle", soldier_Idle_Right, 5, 10, true);
		
		int soldier_Idle_Left[] = { 5, 6, 7, 8, 9 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Idle_Left_Ani", "soldier_Idle", soldier_Idle_Left, 5, 10, true);
		
		
		// <soldier Walk Ani>
		int soldier_Walk_Right[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Walk_Right_Ani", "soldier_Walk", soldier_Walk_Right, 8, 10, true);
		
		int soldier_Walk_Left[] = { 15, 14, 13, 12, 11, 10, 9, 8 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Walk_Left_Ani", "soldier_Walk", soldier_Walk_Left, 8, 10, true);
		
		
		// <soldier Hit Ani>
		int soldier_Hit_Right[] = { 0, 1 };   
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Hit_Right_Ani", "soldier_Hit", soldier_Hit_Right, 2, 10, false);
		
		int soldier_Hit_Left[] = { 2, 3 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Hit_Left_Ani", "soldier_Hit", soldier_Hit_Left, 2, 10, false);
		
		
		// <soldier Attack Ani>
		int soldier_Attack_Right[] = { 0, 1, 2, 3, 4 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Attack_Right_Ani", "soldier_Attack", soldier_Attack_Right, 5, 10, false);
		
		int soldier_Attack_Left[] = { 5, 6, 7, 8, 9 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Attack_Left_Ani", "soldier_Attack", soldier_Attack_Left, 5, 10, false);





		// <archer Idle Ani>
		int archer_Idle_Right[] = { 0, 1, 2, 3 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Idle_Right_Ani", "archer_Idle", archer_Idle_Right, 4, 10, true);

		int archer_Idle_Left[] = { 7, 6, 5, 4 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Idle_Left_Ani", "archer_Idle", archer_Idle_Left, 4, 10, true);


		// <archer Walk Ani>
		int archer_Walk_Right[] = { 0, 1, 2, 3, 4 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Walk_Right_Ani", "archer_Walk", archer_Walk_Right, 5, 10, true);

		int archer_Walk_Left[] = { 9, 8, 7, 6, 5 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Walk_Left_Ani", "archer_Walk", archer_Walk_Left, 5, 10, true);


		// <archer Hit Ani>
		int archer_Hit_Right[] = { 0, 1 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Hit_Right_Ani", "archer_Hit", archer_Hit_Right, 2, 10, false);

		int archer_Hit_Left[] = { 3, 2 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Hit_Left_Ani", "archer_Hit", archer_Hit_Left, 2, 10, false);


		// <archer Attack Ani>
		int archer_Attack_Right[] = { 0, 1, 2, 3 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Attack_Right_Ani", "archer_Attack", archer_Attack_Right, 4, 10, false);

		int archer_Attack_Left[] = { 7, 6, 5, 4 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Attack_Left_Ani", "archer_Attack", archer_Attack_Left, 4, 10, false);

		
		// <archer Arrow Ani>
		int archer_Arrow_Right[] = { 0 , 1 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Arrow_Right_Ani", "archer_Arrow_Right", archer_Arrow_Right, 2, 10, true);

		int archer_Arrow_Left[] = { 0 , 1 };
		KEYANIMANAGER->addArrayFrameAnimation("archer_Arrow_Left_Ani", "archer_Arrow_Left", archer_Arrow_Left, 2, 10, true);

	}
};
