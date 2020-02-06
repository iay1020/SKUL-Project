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
	ITEM							// 아이템 버튼을 눌렀다면
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

	POINTFLOAT			center;						// 중점 좌표를 저장
	RECT				rc;							// 렉트 좌표를 저장
		
	// 맵 정보 초기화
	void reset_MapInfo()
	{
		mapName = {};
		tile_Size.x = tile_Size.y = 0;
		tile_Count.x = tile_Count.y = 0;

		backGround_Count = 0;
		backImgName = {};
		centerImgName = {};
		frontImgName = {};

		center.x = center.y = 0;
		rc.left = rc.top = rc.right = rc.bottom = 0;

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

	void reset_Tile()
	{
		center.x = center.y = 0;
		index.x  = index.y = 0;
		frame.ground.x = frame.ground.y = 0;
		tile_Type = TILE_TYPE::EMPTY;
		ground = GROUND_TYPE::EMPTY_GROUND;
	}
};

// 팔렛트 이동에 쓰일 렉트
struct tagPalletBar
{
	RECT Character_Pallet_Bar;											// 캐릭터 팔렛트 바
	RECT Door_Pallet_Bar;												// 도어 팔렛트 바
	RECT Ground_Pallet_Bar;												// 바닥 팔렛트 바
	RECT Dcoration_Pallet_Bar;											// 데코 팔렛트 바
	RECT Hit_Object_Bar;												// 파괴 오브젝트 바
	RECT Item_Bar;														// 아이템 오브젝트 바

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
};

// 팔렛트의 종류를 담는다.
struct tagPalletKinds
{
	tagPallet_INFO	Character_Pallet;									// 캐릭터 팔렛트
	tagPallet_INFO	Door_Pallet;										// 도어 팔렛트
	tagPallet_INFO	Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY];			// 지형 팔렛트
	tagPallet_INFO	Dcoration_Pallet;									// 장식 팔렛트
	tagPallet_INFO	Hit_Object_Pallet;									// 파괴 오브젝트 팔렛트
	tagPallet_INFO	Item_Bar;											// 아이템 팔렛트
};

// 팔렛트의 종류를 담는다.
struct tagPallets
{
	tagPalletBar	palletBar;											// 팔렛트 바
	tagPalletKinds	pallet;												// 팔렛트

	// 팔렛트 기본 셋팅
	void setting()
	{
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
			}
		}

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
	void show_Pallet(HDC getMem)
	{
		// 팔렛트 바 렉트 출력
		Rectangle(getMem, palletBar.Ground_Pallet_Bar);

		// 팔렛트 렉트 출력
		for (int i = 0; i < GROUND_SIZEX * GROUND_SIZEY; ++i)
			Rectangle(getMem, pallet.Ground_Pallet[i].rc);
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
		ITEM							// 아이템 버튼을 눌렀다면
	};

	// 기억 변수
	BUTTON_TYPE		BT_Type;			// 클릭한 버튼을 저장한다.

	// 초기화 함수
	void reset()
	{
		// 아무것도 클릭하지 않은 상태는 NONE
		BT_Type = BUTTON_TYPE::NONE;

		// 버튼 렉트의 위치를 잡는다.
		BT_Save = RectMake(10, 10, 52, 52);
		BT_Load = RectMake(72, 10, 52, 52);
		BT_Ground = RectMake(10 * 3 + 52 * 2, 10, 52, 52);
	}

	// 버튼 이미지를 그려준다. (+ 렉트)
	void show_Button(HDC getDC)
	{
		// 테스트용 렉트 출력
		if (KEYMANAGER->isToggleKey(VK_NUMPAD2))
		{
			Rectangle(getDC, BT_Save);
			Rectangle(getDC, BT_Load);
			Rectangle(getDC, BT_Ground);
		}

		// 버튼 이미지 출력
		IMAGEMANAGER->findImage("save_Icon")->render(getDC, BT_Save.left, BT_Save.top);
		IMAGEMANAGER->findImage("load_Icon")->render(getDC, BT_Load.left, BT_Load.top);
		IMAGEMANAGER->findImage("ground_Icon")->render(getDC, BT_Ground.left, BT_Ground.top);
	}

	// 버튼 클릭 함수
	void click_Button()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// 버튼을 클릭하면 해당 타입으로 저장한다.
			if (PtInRect(&BT_Save, _ptMouse)) BT_Type = BUTTON_TYPE::SAVE;
			if (PtInRect(&BT_Load, _ptMouse)) BT_Type = BUTTON_TYPE::LOAD;
			if (PtInRect(&BT_Ground, _ptMouse)) BT_Type = BUTTON_TYPE::GROUND;
		}	
	}
};


// 맵툴 함수
class mapTool_Func
{

public:
	// 기본 타일을 만들어 준다.
	void make_Base_TileList(vector<tagTileInfo*>* tileList)
	{
		// 타일의 기본 렉트를 만들어 준다.
		for (int y = 0; y < TILE_COUNT_Y; ++y)
		{
			for (int x = 0; x < TILE_COUNT_X; ++x)
			{
				tagTileInfo* new_Tile = new tagTileInfo;
				new_Tile->reset_Tile();
				new_Tile->index.x = x;
				new_Tile->index.y = y;
				new_Tile->rc = RectMake(new_Tile->index.x * TILE_SIZE_X, new_Tile->index.y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y);
				new_Tile->center.x = (new_Tile->rc.left + new_Tile->rc.right) / 2.f;
				new_Tile->center.y = (new_Tile->rc.top + new_Tile->rc.bottom) / 2.f;

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
	void show_Camera_In_Tile(unsigned short sizeX, unsigned short sizeY, HDC getMemDC, vector<tagTileInfo*> _vTileList)
	{
		// 카메라의 정보를 복사한다. (연산할때 간단하게 사용하기 위해서)
		POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

		// 원하는 위치에 그려지게 할 렉트를 만들어 준다.
		RECT camera_Rc = RectMake(0, 0, sizeX, sizeY);
		camera_Rc.left -= camera.x;
		camera_Rc.right -= camera.x;
		camera_Rc.top -= camera.y;
		camera_Rc.bottom -= camera.y;

		// 렉트를 출력한다.
		for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
		{
			for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
			{
				RECT rc = _vTileList[y * TILE_COUNT_X + x]->rc;

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
};