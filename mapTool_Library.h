#pragma once
#include "stdafx.h"

// 타일의 타입
enum class TILE_TYPE
{
	EMPTY,									// NULL
	PLAYER,									// 플레이어
	ENEMY,									// 에너미
	DOOR,									// 도어	
	GROUND,									// 땅
	DECORATION,								// 데코레이션 오브젝트
	HIT_OBJECT,								// 타격 가능한 오브젝트
	TRAP,									// 함정 타일
	ITEM									// 아이템 오브젝트

};

// 에너미 타입

// 땅(지형) 타입
enum class GROUND_TYPE
{
	EMPTY_GROUND,							// NULL
	TUTORIAL_GROUND,						// 튜토리얼 땅
	STAGE1_GROUND,							// 스테이지 1 땅
	STAGE2_GROUND							// 스테이지 2 땅
};



// 배경 이미지 카운트용
enum BACKGROUND_CNT
{
	NONE,				// 비어있음
	ONE,				// 한개
	TWO,				// 두개
	THREE				// 세개
};


// 버튼 타입
enum class BUTTON_TYPE
{
	NONE,							// 아무것도 누르지 않았다면
	SAVE,							// 세이브 버튼을 눌렀다면
	LOAD,							// 로드 버튼을 눌렀다면
	ERASER,							// 지우개 버튼을 눌렀다면
	GROUND,							// 지형 버튼을 눌렀다면
	DECORATION,						// 데코 버튼을 눌렀다면
	HIT_OBJECT,						// 파괴 가능 오브젝트 버튼을 눌렀다면
	DOOR,							// 문 버튼을 눌렀다면
	CHARACTER,						// 캐릭터 버튼을 눌렀다면
	ITEM,							// 아이템 버튼을 눌렀다면
	TRAP							// 트랩 버튼을 눌렀다면
};

// 팔렛트 이동에 쓰일 렉트
struct tagPalletBar
{
	RECT Ground_Pallet_Bar;												// 바닥 팔렛트 바
	RECT Dcoration_Pallet_Bar;											// 데코 팔렛트 바
	RECT Hit_Object_Bar;												// 파괴 오브젝트 바
	RECT Door_Pallet_Bar;												// 도어 팔렛트 바
	RECT Character_Pallet_Bar;											// 캐릭터 팔렛트 바
	RECT Item_Bar;														// 아이템 오브젝트 바
	RECT Trap_Bar;														// 트랙 팔렛트 바

	// 팔렛트 바를 이동 시킬 함수 (잠시 중단)
	void move_Bar()
	{

	}
};

// 팔렛트의 정보를 담는다.
struct tagPallet_INFO
{
	RECT		rc;														// 렉트의 정보를 담는다.
	tag_U_Short	frame;													// 프레임 x, y를 담는다.
	GROUND_TYPE	ground_Type;											// 그라운드 타입을 담는다.

	// 매번 타입을 넣을때 이전 타입을 초기화 할때 사용
	void reset_Type()
	{
		ground_Type = GROUND_TYPE::EMPTY_GROUND;
	}
};

// 팔렛트의 종류를 담는다.
struct tagPalletKinds
{
	tagPallet_INFO	Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY];			// 지형 팔렛트
	tagPallet_INFO	Dcoration_Pallet[2];								// 장식 팔렛트
	tagPallet_INFO	Hit_Object_Pallet[2];								// 파괴 오브젝트 팔렛트
	tagPallet_INFO	Door_Pallet[2];										// 도어 팔렛트
	tagPallet_INFO	Character_Pallet[2];								// 캐릭터 팔렛트
	tagPallet_INFO	Item_Pallet[2];										// 아이템 팔렛트
	tagPallet_INFO  Trap_Pallet[2];										// 트랩 팔렛트
};


// 배경 루프랜더용 변수
struct tagLoop_Variable
{
	short LoopX_BG_0;		// 맨 뒤에 있는 백 그라운드 루프용 변수
	short LoopX_BG_1;		// 그 앞에 백 그라운드 루프용 변수
	short LoopX_BG_2;		// 맨 앞에 있는 백 그라운드 루프용 변수

	void reset_Func()
	{
		LoopX_BG_0 = LoopX_BG_1 = LoopX_BG_2 = 0;
	}
};


// 맵의 정보를 저장 할 구조체
struct tagMapInfo
{
	string				mapName;					// 맵의 이름을 저장한다.
	tag_U_Short			tile_Size;					// 타일 사이즈를 저장한다.
	tag_U_Short			tile_Count;					// 타일의 갯수를 저장한다.
	
	char				backGround_Count;			// 배경의 갯수 (최대 갯수가 3개니까 char으로)
	string				backImgName;				// 맨 뒤의 배경 이미지 키값
	string				centerImgName;				// 중간 배경 이미지 키값
	string				frontImgName;				// 앞의 배경 이미지 키값

	tagLoop_Variable*	loop;						// 루프에서 사용할 변수
		
	// 맵 정보 초기화
	void reset_MapInfo()
	{
		mapName = {};
		tile_Size.x = TILE_SIZE_X;		// 베이스 타일의 사이즈를 저장한다.
		tile_Size.y = TILE_SIZE_Y;		// 베이스 타일의 사이즈를 저장한다.
		tile_Count.x = TILE_COUNT_X;	// 베이스 타일의 갯수를 저장한다.
		tile_Count.y = TILE_COUNT_Y;	// 베이스 타일의 갯수를 저장한다.

		backGround_Count = 0;
		backImgName = {};
		centerImgName = {};
		frontImgName = {};

		loop = new tagLoop_Variable;
		loop->reset_Func();
	}

	// 맵 배경 추가
	void add_BackGround(string mapName)
	{
		// 카운트 값이 비정상적일 경우에는 함수를 빠져나간다.
		if (backGround_Count == 4) return;

		backGround_Count++;	// 한장을 추가 했때마다 증가한다.

		if (backGround_Count == ONE)
		{
			backImgName = mapName;		// 맵의 이름을 넣어준다.
		}

		if (backGround_Count == TWO)
		{
			centerImgName = mapName;	// 맵의 이름을 넣어준다.
		}

		if (backGround_Count == THREE)
		{
			frontImgName = mapName;		// 맵의 이름을 넣어준다.
		}

	}

	// 맵 배경 교체
	void change_BackGround(string mapName, signed short num)
	{
		// 교체하기 원하는 맵 이름과, 교체 하려는 위치를 받아온다.
		if (num > 0 && num <= 3)
		{
			switch (num)
			{
				case ONE:
					backImgName = mapName;
		
					break;

				case TWO:
					centerImgName = mapName;
		
					break;

				case THREE:
					frontImgName = mapName;

					break;
			}
		}
	}


};


// 타일의 이미지 프레임을 담을 변수 구조체
struct tagTileFrame
{
	tag_U_Short		ground;					// 지형 이미지 프레임을 담는곳
};


// 타일 정보를 저장 할 구조체
struct tagTileInfo
{
	POINTFLOAT			center;				// 타일의 중점을 담는다.
	RECT				rc;					// 타일의 렉트를 담는다.
	tag_U_Short			index;				// 타일의 인덱스를 담는다. (범위 : 0 ~ 65535)

	TILE_TYPE			tile_Type;			// 타일의 타입을 담는다.
	GROUND_TYPE			ground;				// 땅(지형) 타입을 담는다.

	tagTileFrame 	    frame;				// 이미지 프레임을 담는다.

	// 타일을 기본 셋팅 해준다. (비워준다)
	void reset_Tile()
	{
		center.x = center.y = 0;
		index.x  = index.y = 0;
		frame.ground.x = frame.ground.y = 0;
		tile_Type = TILE_TYPE::EMPTY;
		ground = GROUND_TYPE::EMPTY_GROUND;
	}
};

// 팔렛트의 종류를 담는다.
struct tagPallets
{
	tagPalletBar	palletBar;											// 팔렛트 바
	tagPalletKinds	pallet;												// 팔렛트
	tagPallet_INFO	current;											// 클릭 한 이미지 정보

	// 팔렛트 기본 셋팅
	void setting()
	{
		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■지형 설정■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
		// 팔렛트 바의 위치를 정해준다.
		// 지형 팔렛트 바 셋팅
		palletBar.Ground_Pallet_Bar = RectMake(WINSIZEX - IMAGEMANAGER->findImage("tutorial_Tile")->getWidth(), 10,
			IMAGEMANAGER->findImage("tutorial_Tile")->getWidth(), 20);

		// 팔렛트 바의 아래에 팔렛트의 렉트를 그려준다.
		// 지형 팔렛트 셋팅
		for (int y = 0; y < GROUND_SIZEY; ++y)
		{
			for (int x = 0; x < GROUND_SIZEX; ++x)
			{
				// 프레임 값을 넣어준다.
				pallet.Ground_Pallet[x + y * GROUND_SIZEX].frame.x = x;
				pallet.Ground_Pallet[x + y * GROUND_SIZEX].frame.y = y;

				// 렉트 위치를 만든다. (팔렛트 바의 left, bottom 기준으로)
				pallet.Ground_Pallet[x + y * GROUND_SIZEX].rc =
					RectMake(palletBar.Ground_Pallet_Bar.left + x * TILE_SIZE_X, palletBar.Ground_Pallet_Bar.bottom + y * TILE_SIZE_Y,
						TILE_SIZE_X, TILE_SIZE_Y);

				// 팔렛트 기본 넘버
				pallet.Ground_Pallet->ground_Type = GROUND_TYPE::TUTORIAL_GROUND;
			}
		}
		// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

		// 클릭 한 정보를 담는 변수를 비워준다.
		current.frame.x = current.frame.y = 0;
	}

	// 팔렛트 갱신 함수 (팔렛트 이동 시 했을때 좌표 갱신)
	void pallet_Update()
	{
		// 팔렛트 바의 아래에 팔렛트의 렉트를 그려준다.
		// 지형 팔렛트 셋팅
		for (int y = 0; y < GROUND_SIZEY; ++y)
		{
			for (int x = 0; x < GROUND_SIZEX; ++x)
			{
				// 렉트 위치를 만든다. (팔렛트 바의 left, bottom 기준으로)
				pallet.Ground_Pallet[x + y * GROUND_SIZEX].rc =
					RectMake(palletBar.Ground_Pallet_Bar.left + x * TILE_SIZE_X, palletBar.Ground_Pallet_Bar.bottom + y * TILE_SIZE_Y,
						TILE_SIZE_X, TILE_SIZE_Y);
			}
		}


	}

	// 팔렛트 출력 함수
	void show_Pallet(HDC getMem, BUTTON_TYPE button)
	{
		// 버튼 타입에 따라 다른 팔렛트 바 출력
		switch (button)
		{
			case BUTTON_TYPE::GROUND:
				// 팔렛트 바 렉트 출력
				Rectangle(getMem, palletBar.Ground_Pallet_Bar);

				// 팔렛트 테두리 렉트 출력
				Rectangle(getMem, palletBar.Ground_Pallet_Bar.left, palletBar.Ground_Pallet_Bar.bottom,
					palletBar.Ground_Pallet_Bar.right, palletBar.Ground_Pallet_Bar.bottom + IMAGEMANAGER->findImage("tutorial_Tile")->getHeight());
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
		}
	}

	// 클릭 한 팔레트의 정보를 저장한다.
	void click_PalletInfo_Save(BUTTON_TYPE button)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			switch (button)
			{
				case BUTTON_TYPE::GROUND:
					// Ground 팔렛트의 렉트를 마우스로 클릭 했다면, 그 클릭 한 팔렛트의 정보를 담는다.
					for (int i = 0; i < GROUND_SIZEX * GROUND_SIZEY; ++i)
					{
						if (PtInRect(&pallet.Ground_Pallet[i].rc, _ptMouse))
						{
							current.frame.x = pallet.Ground_Pallet[i].frame.x;
							current.frame.y = pallet.Ground_Pallet[i].frame.y;
							current.reset_Type();	// 타입을 저장 하기 전에 이전 정보를 삭제

							current.ground_Type = GROUND_TYPE::TUTORIAL_GROUND;
						}
					}

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
			}

			KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// 키 씹히는걸 방지하기 위해
		}
	}
};




// 버튼 정보를 담는 구조체
struct tagButton_Info
{
	// 기능 버튼
	RECT			BT_Save;			// 세이브 버튼
	RECT			BT_Load;			// 로드 버튼
	RECT			BT_Eraser;			// 지우개 버튼
	RECT			BT_Next;			// 다음 버튼
	RECT			BT_Prev;			// 이전 버튼

	// 팔렛트 버튼
	RECT			BT_Ground;			// 지형 이미지 버튼
	RECT			BT_Decoration;		// 데코레이션 이미지 버튼
	RECT			BT_Hit_Object;		// 파괴 가능 이미지 버튼
	RECT			BT_Door;			// 문 이미지 버튼
	RECT			BT_Character;		// 캐릭터 이미지 버튼
	RECT			BT_Item;			// 아이템 이미지 버튼
	RECT			BT_Trap;			// 함정 이미지 버튼

	// 기억 변수
	BUTTON_TYPE		BT_Type;			// 클릭한 버튼을 저장한다.

	// 불의 마을
	bool			BT_Type_B;			// 어떤 버튼을 클릭 했는지 체크 할때 사용


	// 초기화 함수
	void reset()
	{
		// 변수 초기화
		BT_Type_B = false;

		// 아무것도 클릭하지 않은 상태는 NONE
		BT_Type = BUTTON_TYPE::NONE;

		short start_Pos, button_Size;
		start_Pos = 10; button_Size = 52;	// 간격, 버튼 사이즈를 저장한다.

		// 버튼 렉트의 위치를 잡는다.
		BT_Save = RectMake(start_Pos, 10, 52, 52);
		BT_Load = RectMake(start_Pos * 2 + button_Size * 1, 10, 52, 52);
		BT_Eraser = RectMake(start_Pos * 3 + button_Size * 2, 10, 52, 52);
		BT_Ground = RectMake(start_Pos * 4 + button_Size * 3, 10, 52, 52);
		BT_Decoration = RectMake(start_Pos * 5 + button_Size * 4, 10, 52, 52);
		BT_Hit_Object = RectMake(start_Pos * 6 + button_Size * 5, 10, 52, 52);
		BT_Trap = RectMake(start_Pos * 7 + button_Size * 6, 10, 52, 52);
		BT_Door = RectMake(start_Pos * 8 + button_Size * 7, 10, 52, 52);
		BT_Character = RectMake(start_Pos * 9 + button_Size * 8, 10, 52, 52);
		BT_Item = RectMake(start_Pos * 10 + button_Size * 9, 10, 52, 52);

	}

	// 다음, 이전 버튼의 위치를 갱신 해준다.
	void reset_Next_Prev_Pos(tagPalletKinds pallet)
	{
		switch (BT_Type)
		{
		case BUTTON_TYPE::GROUND:
			// prev 버튼 위치
			BT_Prev = RectMake(pallet.Ground_Pallet[GROUND_SIZEX * (GROUND_SIZEY - 1)].rc.left, pallet.Ground_Pallet[GROUND_SIZEX * (GROUND_SIZEY - 1)].rc.bottom,
				32, 30);

			// next 버튼 위치
			BT_Next = RectMake(pallet.Ground_Pallet[GROUND_SIZEX * (GROUND_SIZEY - 1)].rc.left + 37, pallet.Ground_Pallet[GROUND_SIZEX * (GROUND_SIZEY - 1)].rc.bottom,
				32, 30);


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
		}
	}

	// 버튼 이미지를 그려준다. (+ 렉트)
	void show_Button(HDC getDC)
	{
		// 테스트용 렉트 출력
		if (KEYMANAGER->isToggleKey(VK_NUMPAD2))
		{
			Rectangle(getDC, BT_Save);
			Rectangle(getDC, BT_Load);
			Rectangle(getDC, BT_Eraser);
			Rectangle(getDC, BT_Ground);
			Rectangle(getDC, BT_Decoration);
			Rectangle(getDC, BT_Hit_Object);
			Rectangle(getDC, BT_Trap);
			Rectangle(getDC, BT_Door);
			Rectangle(getDC, BT_Character);
			Rectangle(getDC, BT_Item);
			Rectangle(getDC, BT_Next);
			Rectangle(getDC, BT_Prev); 
		}

		// 버튼 이미지 출력
		IMAGEMANAGER->findImage("save_Icon")->render(getDC, BT_Save.left, BT_Save.top);
		IMAGEMANAGER->findImage("load_Icon")->render(getDC, BT_Load.left, BT_Load.top);
		IMAGEMANAGER->findImage("eraser_Icon")->render(getDC, BT_Eraser.left, BT_Eraser.top);
		IMAGEMANAGER->findImage("ground_Icon")->render(getDC, BT_Ground.left, BT_Ground.top);
		IMAGEMANAGER->findImage("decoration_Icon")->render(getDC, BT_Decoration.left, BT_Decoration.top);
		IMAGEMANAGER->findImage("hit_Object_Icon")->render(getDC, BT_Hit_Object.left, BT_Hit_Object.top);
		IMAGEMANAGER->findImage("trap_Icon")->render(getDC, BT_Trap.left, BT_Trap.top);
		IMAGEMANAGER->findImage("door_Icon")->render(getDC, BT_Door.left, BT_Door.top);
		IMAGEMANAGER->findImage("character_Icon")->render(getDC, BT_Character.left, BT_Character.top);
		IMAGEMANAGER->findImage("item_Icon")->render(getDC, BT_Item.left, BT_Item.top);

		if (BT_Type != BUTTON_TYPE::NONE && BT_Type != BUTTON_TYPE::SAVE && BT_Type != BUTTON_TYPE::LOAD && BT_Type != BUTTON_TYPE::ERASER)
		{
			IMAGEMANAGER->findImage("next_Icon")->render(getDC, BT_Next.left, BT_Next.top);
			IMAGEMANAGER->findImage("prev_Icon")->render(getDC, BT_Prev.left, BT_Prev.top);
		}
	}

	// 버튼 클릭 함수
	void click_Button()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// 버튼을 클릭하면 해당 타입으로 저장한다.
			if (PtInRect(&BT_Save, _ptMouse)) BT_Type = BUTTON_TYPE::SAVE;
			if (PtInRect(&BT_Load, _ptMouse)) BT_Type = BUTTON_TYPE::LOAD;
			if (PtInRect(&BT_Eraser, _ptMouse)) BT_Type = BUTTON_TYPE::ERASER;
			if (PtInRect(&BT_Ground, _ptMouse)) BT_Type = BUTTON_TYPE::GROUND;
			if (PtInRect(&BT_Decoration, _ptMouse)) BT_Type = BUTTON_TYPE::DECORATION;
			if (PtInRect(&BT_Hit_Object, _ptMouse)) BT_Type = BUTTON_TYPE::HIT_OBJECT;
			if (PtInRect(&BT_Door, _ptMouse)) BT_Type = BUTTON_TYPE::DOOR;
			if (PtInRect(&BT_Character, _ptMouse)) BT_Type = BUTTON_TYPE::CHARACTER;
			if (PtInRect(&BT_Item, _ptMouse)) BT_Type = BUTTON_TYPE::ITEM;
			if (PtInRect(&BT_Trap, _ptMouse)) BT_Type = BUTTON_TYPE::TRAP;

			KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// 키 씹히는걸 방지하기 위해
		}	
	}
};


// 맵툴 함수
class mapTool_Func
{

public:
	// 기본 타일을 만들어 준다.
	void make_Base_TileList(vector<tagTileInfo>* tileList)
	{
		// 타일의 기본 렉트를 만들어 준다.
		for (int y = 0; y < TILE_COUNT_Y; ++y)
		{
			for (int x = 0; x < TILE_COUNT_X; ++x)
			{
				tagTileInfo new_Tile;
				new_Tile.reset_Tile();
				new_Tile.index.x = x;
				new_Tile.index.y = y;
				new_Tile.rc = RectMake(new_Tile.index.x * TILE_SIZE_X, new_Tile.index.y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y);
				new_Tile.center.x = (new_Tile.rc.left + new_Tile.rc.right) / 2.f;
				new_Tile.center.y = (new_Tile.rc.top + new_Tile.rc.bottom) / 2.f;

				(*tileList).push_back(new_Tile);
			}
		}
	}

	// 카메라 안에 들어온 타일을 찾아서 저장한다.
	void camera_In_FindTile()
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// 카메라 안에 들어온 타일을 찾아서 저장한다.
	}

	// 카메라 안에 들어온 렉트를 출력 한다.
	void show_Camera_In_Tile(unsigned short sizeX, unsigned short sizeY, HDC getMemDC, vector<tagTileInfo>* _vTileList)
	{
		// 카메라의 정보를 복사한다. (연산할때 간단하게 사용하기 위해서)
		POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

		// 렉트를 출력한다.
		for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
		{
			for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
			{
				RECT rc = (*_vTileList)[y * TILE_COUNT_X + x].rc;

				rc.left -= camera.x;
				rc.right -= camera.x;
				rc.top -= camera.y;
				rc.bottom -= camera.y;

				//Rectangle(getMemDC, rc);
				IMAGEMANAGER->findImage("tile_Rect")->render(getMemDC, rc.left, rc.top);
			}
		}

	}

	// 배경을 출력 한다.
	void show_BackImg(tagMapInfo* mapInfo, HDC getMemDC)
	{
		// 카메라의 정보를 복사한다. (연산할때 간단하게 사용하기 위해서)
		POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

		// 배경을 담을 렉트 크기를 정한다.
		RECT camera_Rc = RectMake(0, 0, IMAGEMANAGER->findImage(mapInfo->backImgName)->getWidth(), IMAGEMANAGER->findImage(mapInfo->backImgName)->getHeight());	

		camera.x > 560 ? camera.x = 560 : camera.x;
		camera.y > 890 ? camera.y = 890 : camera.y;

		camera_Rc.left -= camera.x;
		camera_Rc.right -= camera.x;
		camera_Rc.top -= camera.y;
		camera_Rc.bottom -= camera.y;

		// 배경 갯수에 따라 출력이 다르다.
		if (mapInfo->backGround_Count >= 1)			// 배경 갯수가 3개 이하
		{
			IMAGEMANAGER->findImage(mapInfo->backImgName)->loopRender(getMemDC,
				&camera_Rc, mapInfo->loop->LoopX_BG_0, 0);
		}

		if (mapInfo->backGround_Count >= 2)			// 배경 갯수가 2개 이하
		{
			IMAGEMANAGER->findImage(mapInfo->centerImgName)->loopRender(getMemDC,
				&camera_Rc, mapInfo->loop->LoopX_BG_1, 0);
		}

		if (mapInfo->backGround_Count >= 3)			// 배경 갯수가 1개 이하
		{

		}IMAGEMANAGER->findImage(mapInfo->frontImgName)->loopRender(getMemDC,
			&camera_Rc, mapInfo->loop->LoopX_BG_2, 0);

	}

	// 팔렛트를 출력 한다.
	void show_Pallet(HDC getMemDC, BUTTON_TYPE button, tagPallets* pallet)
	{
		switch (button)
		{
		case BUTTON_TYPE::SAVE:

			break;

		case BUTTON_TYPE::LOAD:

			break;

		case BUTTON_TYPE::GROUND:

			// 팔렛트 테두리 출력
			pallet->show_Pallet(getMemDC, button);

			for (int i = 0; i < GROUND_SIZEX * GROUND_SIZEY; ++i)
			{
				// 지형 이미지 출력
				IMAGEMANAGER->findImage("tutorial_Tile")->frameRender(getMemDC, pallet->pallet.Ground_Pallet[i].rc.left, pallet->pallet.Ground_Pallet[i].rc.top,
					pallet->pallet.Ground_Pallet[i].frame.x, pallet->pallet.Ground_Pallet[i].frame.y);

				// 렉트 출력
				IMAGEMANAGER->findImage("tile_Rect")->render(getMemDC, pallet->pallet.Ground_Pallet[i].rc.left, pallet->pallet.Ground_Pallet[i].rc.top);
			}
			break;
		}
	}

	// 타일을 제외한 모든 렉트를 와의 충돌을 막는 함수
	bool find_NoTile(tagPallets pallet, tagButton_Info button)
	{
		POINT mouse_Pos;
		mouse_Pos.x = _ptMouse.x + CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		mouse_Pos.y = _ptMouse.y + CAMERAMANAGER->Use_Func()->get_CameraXY().y;

		if (PtInRect(&pallet.palletBar.Ground_Pallet_Bar, mouse_Pos) ||
			PtInRect(&pallet.palletBar.Dcoration_Pallet_Bar, mouse_Pos) ||
			PtInRect(&pallet.palletBar.Hit_Object_Bar, mouse_Pos) ||
			PtInRect(&pallet.palletBar.Door_Pallet_Bar, mouse_Pos) ||
			PtInRect(&pallet.palletBar.Character_Pallet_Bar, mouse_Pos) ||
			PtInRect(&pallet.palletBar.Item_Bar, mouse_Pos) || 
			PtInRect(&pallet.palletBar.Trap_Bar, mouse_Pos) ||
			PtInRect(&pallet.pallet.Ground_Pallet->rc, mouse_Pos) ||
			PtInRect(&pallet.pallet.Dcoration_Pallet->rc, mouse_Pos) || 
			PtInRect(&pallet.pallet.Hit_Object_Pallet->rc, mouse_Pos) ||
			PtInRect(&pallet.pallet.Door_Pallet->rc, mouse_Pos) ||
			PtInRect(&pallet.pallet.Character_Pallet->rc, mouse_Pos) ||
			PtInRect(&pallet.pallet.Item_Pallet->rc, mouse_Pos) ||
			PtInRect(&pallet.pallet.Trap_Pallet->rc, mouse_Pos))
		{
			// 충돌이 하나라도 있다면 false
			return false;
		}

		// 충돌하는게 없다면 true
		return true;
	}
	
	// 선택한 이미지를 타일에 저장한다.
	void setting_TileImg(vector<tagTileInfo>* TileList, tagPallet_INFO pallet, tagButton_Info button)
	{
		POINT _ptMouse_Ver2 = _ptMouse;
		_ptMouse_Ver2.x += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		_ptMouse_Ver2.y += CAMERAMANAGER->Use_Func()->get_CameraXY().y;

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			switch ((BUTTON_TYPE)button.BT_Type)
			{
				case BUTTON_TYPE::GROUND:
					for (int i = 0; i < TILE_COUNT_X * TILE_COUNT_Y; ++i)
					{
						if (PtInRect(&(*TileList)[i].rc, _ptMouse_Ver2))
						{
							(*TileList)[i].frame.ground = pallet.frame;
							(*TileList)[i].tile_Type = TILE_TYPE::GROUND;
						}
					}

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
			}

			KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// 키 씹히는걸 방지하기 위해
		}
	}




	// 보이는 부분의 타일을 출력해준다.
	void show_TileImg(HDC getMemDC ,vector<tagTileInfo>* _vTileList)
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// 카메라 안에 들어온 타일을 찾아서 저장한다.

		// 마우스가 클릭한 타일을 찾아준다. (내 화면에 있는 타일만 찾아서)
		for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
		{
			for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
			{
				RECT rc = (*_vTileList)[y * TILE_COUNT_X + x].rc;
				POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

				rc.left -= camera.x;
				rc.right -= camera.x;
				rc.top -= camera.y;
				rc.bottom -= camera.y;

				// 안 쓰는 타입은 제외한다.
				if ((*_vTileList)[y * TILE_COUNT_X + x].tile_Type != TILE_TYPE::EMPTY)
				{

					// 지형을 그려준다.
					if ((*_vTileList)[y * TILE_COUNT_X + x].tile_Type == TILE_TYPE::GROUND)
					{
						IMAGEMANAGER->findImage("tutorial_Tile")->frameRender(getMemDC, rc.left, rc.top,
							(*_vTileList)[y * TILE_COUNT_X + x].frame.ground.x, (*_vTileList)[y * TILE_COUNT_X + x].frame.ground.y);
					}

					// 데코를 그려준다.
					if ((*_vTileList)[y * TILE_COUNT_X + x].tile_Type == TILE_TYPE::DECORATION)
					{

					}
				}
			}
		}
	}
};