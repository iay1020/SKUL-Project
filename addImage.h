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
		}

		// <Skill>
		{
			IMAGEMANAGER->addFrameImage("skul_Skill", "./image/skul/Skill/skul_Skill.bmp", 640, 238, 4, 2, true, RGB(255, 0, 255));
			IMAGEMANAGER->addFrameImage("skul_Skill_Head", "./image/skul/Skill/skul_Skill_Head.bmp", 120, 60, 4, 2, true, RGB(255, 0, 255));

			// throw Skul Skill
			IMAGEMANAGER->addFrameImage("throw_Head_Effect", "./image/effect/Hit_Skul/Hit_Skul.bmp", 1000, 224, 10, 2, true, RGB(255, 0, 255));

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
		IMAGEMANAGER->addFrameImage("soldier_Walk", "./image/enemy/soldier/Walk/soldier_Walk.bmp", 1376, 240, 7, 2, true, RGB(255, 0, 255));
		
		// <soldier Hit>
		IMAGEMANAGER->addFrameImage("soldier_Hit", "./image/enemy/soldier/Hit/soldier_Hit.bmp", 344, 240, 2, 2, true, RGB(255, 0, 255));
		
		// <soldier Attack>
		IMAGEMANAGER->addFrameImage("soldier_Attack", "./image/enemy/soldier/Attack/soldier_Attack.bmp", 860, 240, 5, 2, true, RGB(255, 0, 255));
		
		
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
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Hit_Right_Ani", "soldier_Hit", soldier_Hit_Right, 2, 10, true);
		
		int soldier_Hit_Left[] = { 2, 3 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Hit_Left_Ani", "soldier_Hit", soldier_Hit_Left, 2, 10, true);
		
		
		// <soldier Attack Ani>
		int soldier_Attack_Right[] = { 0, 1, 2, 3, 4 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Attack_Right_Ani", "soldier_Attack", soldier_Attack_Right, 5, 10, false);
		
		int soldier_Attack_Left[] = { 5, 6, 7, 8, 9 };
		KEYANIMANAGER->addArrayFrameAnimation("soldier_Attack_Left_Ani", "soldier_Attack", soldier_Attack_Left, 5, 10, false);


	}
};
