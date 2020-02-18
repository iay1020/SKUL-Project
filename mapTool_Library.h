#pragma once
#include "stdafx.h"

// 배경 이미지 카운트용
enum BACKGROUND_CNT
{
	NONE,				// 비어있음
	ONE,				// 한개
	TWO,				// 두개
	THREE				// 세개
};


// 이미지 카운트용
enum IMAGE_COUNT
{
	Zero_Img,			// 0번째	 
	One_Img,			// 1번째	 
	Two_Img,			// 2번째	 
	Three_Img,			// 3번째	 
	Four_Img,			// 4번째	 
	Five_Img,			// 5번째	 
	Six_Img,			// 6번째	 
	Seven_Img,			// 7번째 
	Eight_Img,			// 8번째	 
	Nine_Img,			// 9번째	 
	Ten_Img				// 10번째
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
	TRAP,							// 트랩 버튼을 눌렀다면
	BACKGROUND,						// 백 그라운드 버튼을 눌렀다면
	RECT_ADD_OR_MINUS,				// 렉트 추가 삭제 버튼
	FOOTHOLDTYPE_CHECK,				// 발판 타입이라는 속성을 넣는 버튼
	WALLTYPE_CHECK,					// 벽 타입이라는 속성을 넣는 버튼
	TRAPTYPE_CHECK					// 함정 타입이라는 속성을 넣는 버튼
				
};

// 배경을 저장할 구조체
struct tagSaveBackGround
{
	string	imageName;	// 배경 이미지의 키값을 저장한다.
	RECT	rc;			// 뿌려질 좌표를 저장한다.
};

// 팔렛트 이동에 쓰일 렉트
struct tagPalletBar
{
	RECT Ground_Pallet_Bar;												// 바닥 팔렛트 바
	RECT Decoration_Pallet_Bar;											// 데코 팔렛트 바
	RECT Hit_Object_Bar;												// 파괴 오브젝트 바
	RECT Door_Pallet_Bar;												// 도어 팔렛트 바
	RECT Character_Pallet_Bar;											// 캐릭터 팔렛트 바
	RECT Item_Bar;														// 아이템 오브젝트 바
	RECT Trap_Bar;														// 트랙 팔렛트 바
	RECT Back_Ground_Bar;												// 백그라운드 바

	// 팔렛트 바를 이동 시킬 함수 (잠시 중단)
	void move_Bar()
	{

	}
};

// 타일의 이미지 이름을 담을 변수 구조체
struct tagTileName
{
	string groundName;
	string decorationName;
	string hitObjectName;
	string doorName;
	string characterName;
	string itemName;
	string trapName;
	string backGroundName;
	string backGroundImgName;

	void reset()
	{
		groundName = {};
		decorationName = {};
		hitObjectName = {};
		doorName = {};
		characterName = {};
		itemName = {};
		trapName = {};
		backGroundName = {};
	}
};

// 팔렛트의 정보를 담는다.
struct tagPallet_INFO
{
	RECT		rc;														// 렉트의 정보를 담는다.
	tag_U_Short	frame;													// 프레임 x, y를 담는다.
	tagTileName	imageName;												// 해당 타입의 이미지 이름을 담는다. 

	// 매번 타입을 넣을때 이전 타입을 초기화 할때 사용
	void reset_Type()
	{
		frame.x = frame.y = 0;
		imageName.reset();
	}
};

// 팔렛트의 종류를 담는다.
struct tagPalletKinds
{
	tagPallet_INFO	Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY];					// 지형 팔렛트
	tagPallet_INFO	Decoration_Pallet[2];										// 장식 팔렛트
	tagPallet_INFO	Hit_Object_Pallet[2];										// 파괴 오브젝트 팔렛트
	tagPallet_INFO	Door_Pallet[2];												// 도어 팔렛트
	tagPallet_INFO	Character_Pallet[2];										// 캐릭터 팔렛트
	tagPallet_INFO	Item_Pallet[2];												// 아이템 팔렛트
	tagPallet_INFO  Trap_Pallet[2];												// 트랩 팔렛트
	tagPallet_INFO	back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY];	// 백 그라운드 팔렛트
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
	string						mapName;											// 맵의 이름을 저장한다.
	tag_U_Short					tile_Size;											// 타일 사이즈를 저장한다.
	tag_U_Short					tile_Count;											// 타일의 갯수를 저장한다.

	tagLoop_Variable*			loop;												// 루프에서 사용할 변수

	tagSaveBackGround			_saveVInfo[BACKGROUND_LAYER_COUNT][10];				// 백그라운드 벡터를 세이브
	short						_layer_Cnt;											// 레이어 카운터
	short						_vSize[BACKGROUND_LAYER_COUNT];						// 백터 사이즈를 담는다.
		
	// 맵 정보 초기화
	void reset_MapInfo()
	{
		mapName = {};
		tile_Size.x = TILE_SIZE_X;		// 베이스 타일의 사이즈를 저장한다.
		tile_Size.y = TILE_SIZE_Y;		// 베이스 타일의 사이즈를 저장한다.
		tile_Count.x = TILE_COUNT_X;	// 베이스 타일의 갯수를 저장한다.
		tile_Count.y = TILE_COUNT_Y;	// 베이스 타일의 갯수를 저장한다.

		loop = new tagLoop_Variable;
		loop->reset_Func();

		for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)	_vSize[i] = 0;

		_layer_Cnt = 0;

		// 새로 맵을 불러오면 타일 갯수, 월드 사이즈를 갱신해준다.
		CAMERAMANAGER->Use_Func()->set_Tile_CountX(tile_Count.x);														// 가로 사이즈 설정 (맵마다 가로세로가 다르니까)
		CAMERAMANAGER->Use_Func()->set_Tile_CountY(tile_Count.y);														// 세로 사이즈 설정
		CAMERAMANAGER->Use_Func()->set_World_Size(tile_Count.x * TILE_SIZE_X, tile_Count.y * TILE_SIZE_Y);				// 가로세로에 맞게 월드 사이즈 설정
	}

};


// 타일의 이미지 프레임을 담을 변수 구조체
struct tagTileFrame
{
	tag_U_Short		ground;					// 지형 이미지 프레임을 담는곳
	tag_U_Short		backGround;				// 백 그라운드 이미지 프레임을 담는곳
};


// 타일 정보를 저장 할 구조체
struct tagTileInfo
{
	POINTFLOAT			center;					// 타일의 중점을 담는다.
	RECT				rc;						// 타일의 렉트를 담는다.
	tag_U_Short			index;					// 타일의 인덱스를 담는다. (범위 : 0 ~ 65535)

	TILE_TYPE			tile_Type;				// 타일의 타입을 담는다.
	COLLISION_TILE_TYPE	tile_Collision_Type;	// 타일의 충돌 타입을 담는다.
	tagTileName			tileName;				// 타일 이미지 이름을 담는다.

	tagTileFrame 	    frame;					// 이미지 프레임을 담는다.

	bool				useTile;				// 이미지가 있는 타일인지 아닌지

	// 타일을 기본 셋팅 해준다. (비워준다)
	void reset_Tile()
	{
		center.x = center.y = 0;
		index.x  = index.y = 0;
		frame.ground.x = frame.ground.y = 0;
		tile_Type = TILE_TYPE::EMPTY;
		tile_Collision_Type = COLLISION_TILE_TYPE::NONE_TYPE;
		tileName.reset();
		useTile = false;
	}
};

// 팔렛트의 종류를 담는다.
struct tagPallets
{
	tagPalletBar			palletBar;						// 팔렛트 바
	tagPalletKinds			pallet;							// 팔렛트
	tagPallet_INFO			current;						// 클릭 한 이미지 정보
	string					ImgName;						// 이미지 이름
	RECT					Layer[5];						// 백 그라운드 레이어 이미지 렉트
	

	// 사용할 변수 초기화
	void reset()
	{
		current.reset_Type();

		ImgName = "tutorial_Tile";
	}

	// 번호에 맞는 이미지 이름을 찾는다.
	void findImg(BUTTON_TYPE type, IMAGE_COUNT imgNum)
	{
		// 현재 이미지 번호에 맞는 이미지 네임을 넣어준다.
		switch (imgNum)
		{
			case IMAGE_COUNT::Zero_Img:
				if (type == BUTTON_TYPE::GROUND) ImgName = "tutorial_Tile";
				if (type == BUTTON_TYPE::BACKGROUND) ImgName = "backGround_Pallet_0";
				break;

			case IMAGE_COUNT::One_Img:
				if (type == BUTTON_TYPE::GROUND) ImgName = "stage1_Tile";
				break;

			case IMAGE_COUNT::Two_Img:
				if (type == BUTTON_TYPE::GROUND) ImgName = "stage2_Tile";
				break;

			case IMAGE_COUNT::Three_Img:
				if (type == BUTTON_TYPE::GROUND) ImgName = "stage3_Tile";
				break;

			case IMAGE_COUNT::Four_Img:
				if (type == BUTTON_TYPE::GROUND) ImgName = "startPoint_Tile";
				break;

			case IMAGE_COUNT::Five_Img:
				break;

			case IMAGE_COUNT::Six_Img:
				break;

			case IMAGE_COUNT::Seven_Img:
				break;

			case IMAGE_COUNT::Eight_Img:
				break;

			case IMAGE_COUNT::Nine_Img:
				break;

			case IMAGE_COUNT::Ten_Img:
				break;
		}
	}

	// 번호에 맞는 이미지 이름을 찾는다.
	void findImg_BG(BUTTON_TYPE type, IMAGE_COUNT imgNum, short x, short y)
	{
		// 현재 이미지 번호에 맞는 이미지 네임을 넣어준다.
		switch (imgNum)
		{
		case IMAGE_COUNT::Zero_Img:
			if (type == BUTTON_TYPE::BACKGROUND)
			{
				if (x == 0 && y == 0) ImgName = "stage1_BG_0";
				if (x == 1 && y == 0) ImgName = "tutorial_BG_0";
				if (x == 2 && y == 0) ImgName = "intro_BG_0";
				if (x == 0 && y == 1) ImgName = "stage1_BG_1";
				if (x == 1 && y == 1) ImgName = "tutorial_BG_1";
				if (x == 2 && y == 1) ImgName = "intro_BG_1";
				if (x == 0 && y == 2) ImgName = "stage1_BG_2";
				if (x == 1 && y == 2) ImgName = "tutorial_BG_2";
				if (x == 2 && y == 2) ImgName = "intro_BG_2";
			}

			break;

		case IMAGE_COUNT::One_Img:
			if (type == BUTTON_TYPE::GROUND) ImgName = "stage1_Tile";
			break;

		case IMAGE_COUNT::Two_Img:
			if (type == BUTTON_TYPE::GROUND) ImgName = "stage2_Tile";
			break;

		case IMAGE_COUNT::Three_Img:
			if (type == BUTTON_TYPE::GROUND) ImgName = "stage3_Tile";
			break;

		case IMAGE_COUNT::Four_Img:
			if (type == BUTTON_TYPE::GROUND) ImgName = "startPoint_Tile";
			break;

		case IMAGE_COUNT::Five_Img:
			break;

		case IMAGE_COUNT::Six_Img:
			break;

		case IMAGE_COUNT::Seven_Img:
			break;

		case IMAGE_COUNT::Eight_Img:
			break;

		case IMAGE_COUNT::Nine_Img:
			break;

		case IMAGE_COUNT::Ten_Img:
			break;
		}
	}

	// 팔렛트 기본 셋팅
	void setting_Pallet(BUTTON_TYPE type, IMAGE_COUNT imgNum, RECT* BT_Prev, RECT* BT_Next, RECT* BT_Up, RECT* BT_Down, RECT* BT_RectPlus, RECT* BT_Minus)
	{
		findImg(type, imgNum);	// 번호에 맞는 이미지 이름을 찾는다.
	
		switch (type)
		{
			case BUTTON_TYPE::GROUND:

				// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 지형 설정 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
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

						// 뿌려야 할 샘플이미지 이름
						pallet.Ground_Pallet[x + y * GROUND_SIZEX].imageName.groundName = ImgName;
					}
				}
				// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
			break;

			case BUTTON_TYPE::BACKGROUND:

				// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 백 그라운드 설정 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
				// 팔렛트 바의 위치를 정해준다.
				// 백 그라운드 바 셋팅

				short width, height;
				width = IMAGEMANAGER->findImage("backGround_Pallet_0")->getWidth();
				height = IMAGEMANAGER->findImage("backGround_Pallet_0")->getHeight();

				palletBar.Back_Ground_Bar = RectMake(WINSIZEX - width, 10, width, 20);

				// 팔렛트 바의 아래에 팔렛트의 렉트를 그려준다.
				// 백 그라운드 팔렛트 셋팅
				for (int y = 0; y < BACKGROUND_COUNTY; ++y)
				{
					for (int x = 0; x < BACKGROUND_COUNTX; ++x)
					{
						// 프레임 값을 넣어준다.
						pallet.back_Ground_Pallet[x + y * BACKGROUND_COUNTX].frame.x = x;
						pallet.back_Ground_Pallet[x + y * BACKGROUND_COUNTX].frame.y = y;

						// 렉트 위치를 만든다. (팔렛트 바의 left, bottom 기준으로)
						pallet.back_Ground_Pallet[x + y * BACKGROUND_COUNTX].rc =
							RectMake(palletBar.Back_Ground_Bar.left + (x * (width / BACKGROUND_COUNTX)), palletBar.Back_Ground_Bar.bottom + (y * (height / BACKGROUND_COUNTY)),
								width / BACKGROUND_COUNTX, height / BACKGROUND_COUNTY);

						// 뿌려야 할 샘플 이미지 이름
						pallet.back_Ground_Pallet[x + y * BACKGROUND_COUNTX].imageName.backGroundName = ImgName;
					}
				}

				// 백그라운드 팔렛트 왼쪽에 레이어의 위치를 표시하는 이미지 위치를 잡아준다.
				Layer[0] = RectMake(pallet.back_Ground_Pallet[0].rc.left - 32, pallet.back_Ground_Pallet[0].rc.top + 32 * 2, 32, 32);
				Layer[1] = RectMake(Layer[0].left, Layer[0].top + 32 * 1, 32, 32);
				Layer[2] = RectMake(Layer[0].left, Layer[0].top + 32 * 2, 32, 32);
				Layer[3] = RectMake(Layer[0].left, Layer[0].top + 32 * 3, 32, 32);
				Layer[4] = RectMake(Layer[0].left, Layer[0].top + 32 * 4, 32, 32);

				// 레이어 삭제 버튼 위치를 만든다.
				*BT_Minus = RectMake(Layer[0].left, Layer[0].top + 32 * 5 + 3, 32, 30);
				
				break;

			case BUTTON_TYPE::RECT_ADD_OR_MINUS:

				// 왼,오,아,위 버튼의 위치를 다시 만들어준다. (렉트 추가 버튼 아래에?)
				*BT_Prev = RectMake(BT_RectPlus->left - 32, BT_RectPlus->bottom, 32, 30);
				*BT_Next = RectMake(BT_Prev->right, BT_RectPlus->bottom, 32, 30);
				*BT_Up = RectMake(BT_Next->right, BT_RectPlus->bottom, 32, 30);
				*BT_Down = RectMake(BT_Up->right, BT_RectPlus->bottom, 32, 30);

				break;
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
					palletBar.Ground_Pallet_Bar.right, palletBar.Ground_Pallet_Bar.bottom + GROUND_SIZEY * TILE_SIZE_Y);
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

			case BUTTON_TYPE::BACKGROUND:
				// 팔렛트 바 렉트 출력
				Rectangle(getMem, palletBar.Back_Ground_Bar);

				// 팔렛트 테두리 렉트 출력
				Rectangle(getMem, palletBar.Back_Ground_Bar.left, palletBar.Back_Ground_Bar.bottom,
					palletBar.Back_Ground_Bar.right, palletBar.Back_Ground_Bar.bottom + BACKGROUND_COUNTY * BACKGROUND_SIZEY);
				break;
		}
	}

	// 클릭 한 팔레트의 정보를 저장한다.
	void click_PalletInfo_Save(BUTTON_TYPE button, IMAGE_COUNT imgNum, bool* click, bool* findNoTile)
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

							current.imageName.groundName = pallet.Ground_Pallet[i].imageName.groundName;	// 이미지 이름을 넣어준다.

							*click = true;
							*findNoTile = true;
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

				case BUTTON_TYPE::TRAP:
					break;

				case BUTTON_TYPE::BACKGROUND:
					// BackGround 팔렛트의 렉트를 마우스로 클릭 했다면, 그 클릭 한 팔렛트의 정보를 담는다.
					for (int i = 0; i < BACKGROUND_COUNTX * BACKGROUND_COUNTY; ++i)
					{
						if (PtInRect(&pallet.back_Ground_Pallet[i].rc, _ptMouse))
						{
							current.frame.x = pallet.back_Ground_Pallet[i].frame.x;
							current.frame.y = pallet.back_Ground_Pallet[i].frame.y;

							findImg_BG(button, imgNum, current.frame.x, current.frame.y);								// 현재 이미지 넘버에 맞는 이미지 이름을 찾는다.

							current.imageName.backGroundImgName = ImgName;												// 이미지 이름을 넣어준다.

							*click = true;
							*findNoTile = true;
						}
					}
					break;

				case BUTTON_TYPE::FOOTHOLDTYPE_CHECK: case BUTTON_TYPE::WALLTYPE_CHECK: case BUTTON_TYPE::TRAPTYPE_CHECK:
					*click = true;
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
	RECT			BT_Up;				// 위 버튼 (새로 생성 수정 했으면 이 주석 삭제)
	RECT			BT_Down;			// 다운 버튼 (새로 생성 수정 했으면 이 주석 삭제)
	RECT			BT_Minus;			// 레이어 삭제 버튼
	RECT			BT_RectPlus;		// 렉트 추가 버튼
	RECT			BT_FootHold_Check;	// 발판 속성 체크 버튼
	RECT			BT_Wall_Check;		// 벽 속성 체크 버튼
	RECT			BT_Trap_Check;		// 함정 속성 체크 버튼

	// 팔렛트 버튼
	RECT			BT_Ground;			// 지형 이미지 버튼
	RECT			BT_Decoration;		// 데코레이션 이미지 버튼
	RECT			BT_Hit_Object;		// 파괴 가능 이미지 버튼
	RECT			BT_Door;			// 문 이미지 버튼
	RECT			BT_Character;		// 캐릭터 이미지 버튼
	RECT			BT_Item;			// 아이템 이미지 버튼
	RECT			BT_Trap;			// 함정 이미지 버튼
	RECT			BT_BackGround;		// 백그라운드 이미지 버튼

	// 기억 변수
	BUTTON_TYPE		BT_Type;			// 클릭한 버튼을 저장한다.

	// 불의 마을
	bool			BT_start_Draw;		// 그리기 시작 했다면 true
	bool			BT_Click_Eraser;	// 지우개 버튼을 클릭 했다면
	bool			BT_FindNoTile;		// 그리면 안되는 타일을 찾는다.

	IMAGE_COUNT		BT_ImgNumber;		// 이미지 번호를 저장 한다.
	short			ImgNumber;			// 이미지 번호
	short			ImgCnt;				// 이미지 갯수
	bool			next_Prev_Push_Okay;	// 다음, 이전 버튼 인터벌
	short			next_Prev_Push_Timer;	// 인터벌 카운터

	// 초기화 함수
	void reset()
	{
		// 변수 초기화
		BT_start_Draw = false;
		BT_Click_Eraser = false;
		BT_FindNoTile = false;
		next_Prev_Push_Okay = false;
		BT_ImgNumber = IMAGE_COUNT::Zero_Img;
		ImgNumber = 0;
		ImgCnt = 0;
		next_Prev_Push_Timer = 0;

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
		BT_BackGround = RectMake(start_Pos * 11 + button_Size * 10, 10, 52, 52);
		BT_RectPlus = RectMake(start_Pos * 12 + button_Size * 11, 10, 52, 52);
		BT_FootHold_Check = RectMake(start_Pos * 13 + button_Size * 12, 10, 32, 30);
		BT_Wall_Check = RectMake(BT_FootHold_Check.right, 10, 32, 30);
		BT_Trap_Check = RectMake(BT_Wall_Check.right, 10, 32, 30);

	}

	// 다음, 이전 버튼의 위치를 갱신 해준다.
	void reset_Next_Prev_Pos(tagPalletKinds pallet)
	{
		switch (BT_Type)
		{
		case BUTTON_TYPE::GROUND:
			// prev 버튼 위치
			BT_Prev = RectMake(pallet.Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY - 1].rc.left, pallet.Ground_Pallet[GROUND_SIZEX *GROUND_SIZEY - 1].rc.bottom,
				32, 30);

			// next 버튼 위치
			BT_Next = RectMake(pallet.Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY - 1].rc.left + 33, pallet.Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY - 1].rc.bottom,
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

		case BUTTON_TYPE::TRAP:
			break;

		case BUTTON_TYPE::BACKGROUND:
			// prev 버튼 위치
			BT_Prev = RectMake(pallet.back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY - 1].rc.left, pallet.back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY - 1].rc.bottom,
				32, 30);

			// next 버튼 위치
			BT_Next = RectMake(pallet.back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY - 1].rc.left + 33, pallet.back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY - 1].rc.bottom,
				32, 30);

			// up 버튼 위치
			BT_Up = RectMake(pallet.back_Ground_Pallet[0].rc.left - 32, pallet.back_Ground_Pallet[0].rc.top, 32, 30);

			// down 버튼 위치
			BT_Down = RectMake(pallet.back_Ground_Pallet[0].rc.left - 32, pallet.back_Ground_Pallet[0].rc.top + 30, 32, 30);

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
			Rectangle(getDC, BT_BackGround);
			Rectangle(getDC, BT_Next);
			Rectangle(getDC, BT_Prev); 
			Rectangle(getDC, BT_Up);
			Rectangle(getDC, BT_Down);
			Rectangle(getDC, BT_RectPlus);
			Rectangle(getDC, BT_FootHold_Check);
			Rectangle(getDC, BT_Wall_Check);
			Rectangle(getDC, BT_Trap_Check);
		}

		// 버튼 이미지 출력
		IMAGEMANAGER->findImage("save_Icon")->render(getDC, BT_Save.left, BT_Save.top);
		IMAGEMANAGER->findImage("load_Icon")->render(getDC, BT_Load.left, BT_Load.top);
		IMAGEMANAGER->findImage("eraser_Icon")->render(getDC, BT_Eraser.left, BT_Eraser.top);
		IMAGEMANAGER->findImage("rect_Plus_Icon")->render(getDC, BT_RectPlus.left, BT_RectPlus.top);
		IMAGEMANAGER->findImage("footHoldType_Check_Button")->render(getDC, BT_FootHold_Check.left, BT_FootHold_Check.top);
		IMAGEMANAGER->findImage("wallType_Check_Button")->render(getDC, BT_Wall_Check.left, BT_Wall_Check.top);
		IMAGEMANAGER->findImage("trapType_Check_Button")->render(getDC, BT_Trap_Check.left, BT_Trap_Check.top);

		// 지우개 버튼을 클릭 하지 않았을때
		if (!BT_Click_Eraser)
		{
			IMAGEMANAGER->findImage("ground_Icon")->render(getDC, BT_Ground.left, BT_Ground.top);
			IMAGEMANAGER->findImage("decoration_Icon")->render(getDC, BT_Decoration.left, BT_Decoration.top);
			IMAGEMANAGER->findImage("hit_Object_Icon")->render(getDC, BT_Hit_Object.left, BT_Hit_Object.top);
			IMAGEMANAGER->findImage("trap_Icon")->render(getDC, BT_Trap.left, BT_Trap.top);
			IMAGEMANAGER->findImage("door_Icon")->render(getDC, BT_Door.left, BT_Door.top);
			IMAGEMANAGER->findImage("character_Icon")->render(getDC, BT_Character.left, BT_Character.top);
			IMAGEMANAGER->findImage("item_Icon")->render(getDC, BT_Item.left, BT_Item.top);
			IMAGEMANAGER->findImage("back_Ground_Icon")->render(getDC, BT_BackGround.left, BT_BackGround.top);
		}

		// 지우개 버튼을 클릭 했을때
		if (BT_Click_Eraser)
		{
			IMAGEMANAGER->findImage("ground_E_Icon")->render(getDC, BT_Ground.left, BT_Ground.top);
			IMAGEMANAGER->findImage("decoration_E_Icon")->render(getDC, BT_Decoration.left, BT_Decoration.top);
			IMAGEMANAGER->findImage("hit_Object_E_Icon")->render(getDC, BT_Hit_Object.left, BT_Hit_Object.top);
			IMAGEMANAGER->findImage("trap_E_Icon")->render(getDC, BT_Trap.left, BT_Trap.top);
			IMAGEMANAGER->findImage("door_E_Icon")->render(getDC, BT_Door.left, BT_Door.top);
			IMAGEMANAGER->findImage("character_E_Icon")->render(getDC, BT_Character.left, BT_Character.top);
			IMAGEMANAGER->findImage("item_E_Icon")->render(getDC, BT_Item.left, BT_Item.top);
			IMAGEMANAGER->findImage("back_Ground_E_Icon")->render(getDC, BT_BackGround.left, BT_BackGround.top);
		}

		if (BT_Type != BUTTON_TYPE::NONE && BT_Type != BUTTON_TYPE::SAVE && BT_Type != BUTTON_TYPE::LOAD && BT_Type != BUTTON_TYPE::ERASER)
		{
			IMAGEMANAGER->findImage("next_Icon")->render(getDC, BT_Next.left, BT_Next.top);
			IMAGEMANAGER->findImage("prev_Icon")->render(getDC, BT_Prev.left, BT_Prev.top);
		}

		if (BT_Type == BUTTON_TYPE::BACKGROUND)
		{
			IMAGEMANAGER->findImage("up_Icon")->render(getDC, BT_Up.left, BT_Up.top);
			IMAGEMANAGER->findImage("down_Icon")->render(getDC, BT_Down.left, BT_Down.top);
			IMAGEMANAGER->findImage("minus_Icon")->render(getDC, BT_Minus.left, BT_Minus.top);
		}

		if (BT_Type == BUTTON_TYPE::RECT_ADD_OR_MINUS)
		{
			IMAGEMANAGER->findImage("next_Icon")->render(getDC, BT_Next.left, BT_Next.top);
			IMAGEMANAGER->findImage("prev_Icon")->render(getDC, BT_Prev.left, BT_Prev.top);
			IMAGEMANAGER->findImage("up_Icon")->render(getDC, BT_Up.left, BT_Up.top);
			IMAGEMANAGER->findImage("down_Icon")->render(getDC, BT_Down.left, BT_Down.top);
		}
	}

	// 버튼 클릭 함수
	void click_Button(tagMapInfo* mapInfo, vector<tagSaveBackGround>* vBackGround, vector<tagTileInfo>* _vTileList)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			BT_FindNoTile = false;		// 버튼, 팔렛트 뒤쪽에 찍히지 않게 하기 위해서 쓰는 bool값

			// 버튼을 클릭하면 해당 타입으로 저장한다.
			if (PtInRect(&BT_Save, _ptMouse)) { BT_Type = BUTTON_TYPE::SAVE; BT_FindNoTile = true; }
			if (PtInRect(&BT_Load, _ptMouse)) { BT_Type = BUTTON_TYPE::LOAD; BT_FindNoTile = true; }
			if (PtInRect(&BT_Eraser, _ptMouse) && !next_Prev_Push_Okay)
			{ BT_Type = BUTTON_TYPE::ERASER; BT_Click_Eraser = !BT_Click_Eraser; BT_FindNoTile = true; next_Prev_Push_Okay = true; }					// 지우개를 눌렀다면 Bool값도 같이 변한다.




			if (PtInRect(&BT_Ground, _ptMouse)) { BT_Type = BUTTON_TYPE::GROUND; BT_ImgNumber = IMAGE_COUNT::Zero_Img; ImgNumber = 0; BT_FindNoTile = true; ImgCnt = GROUND_IMAGE_CONUT - 1; }	// 클릭 할때마다 첫 이미지를 가리켜야 하기 때문에 값을 초기화 해준다.
			if (PtInRect(&BT_Decoration, _ptMouse)) { BT_Type = BUTTON_TYPE::DECORATION; BT_ImgNumber = IMAGE_COUNT::Zero_Img; ImgNumber = 0; BT_FindNoTile = true; }
			if (PtInRect(&BT_Hit_Object, _ptMouse)) { BT_Type = BUTTON_TYPE::HIT_OBJECT; BT_ImgNumber = IMAGE_COUNT::Zero_Img; ImgNumber = 0; BT_FindNoTile = true; }
			if (PtInRect(&BT_Door, _ptMouse)) { BT_Type = BUTTON_TYPE::DOOR; BT_ImgNumber = IMAGE_COUNT::Zero_Img; ImgNumber = 0; BT_FindNoTile = true; }
			if (PtInRect(&BT_Character, _ptMouse)) { BT_Type = BUTTON_TYPE::CHARACTER;  BT_ImgNumber = IMAGE_COUNT::Zero_Img; ImgNumber = 0; BT_FindNoTile = true; }
			if (PtInRect(&BT_Item, _ptMouse)) { BT_Type = BUTTON_TYPE::ITEM; BT_ImgNumber = IMAGE_COUNT::Zero_Img; ImgNumber = 0; BT_FindNoTile = true; }
			if (PtInRect(&BT_Trap, _ptMouse)) { BT_Type = BUTTON_TYPE::TRAP; BT_ImgNumber = IMAGE_COUNT::Zero_Img; ImgNumber = 0; BT_FindNoTile = true; }
			if (PtInRect(&BT_BackGround, _ptMouse)) { BT_Type = BUTTON_TYPE::BACKGROUND; BT_ImgNumber = IMAGE_COUNT::Zero_Img; ImgNumber = 0; BT_FindNoTile = true; }
			if (PtInRect(&BT_RectPlus, _ptMouse)) { BT_Type = BUTTON_TYPE::RECT_ADD_OR_MINUS; BT_FindNoTile = true; }
			if (PtInRect(&BT_FootHold_Check, _ptMouse)) { BT_Type = BUTTON_TYPE::FOOTHOLDTYPE_CHECK; BT_FindNoTile = true; }
			if (PtInRect(&BT_Wall_Check, _ptMouse)) { BT_Type = BUTTON_TYPE::WALLTYPE_CHECK; BT_FindNoTile = true; }
			if (PtInRect(&BT_Trap_Check, _ptMouse)) { BT_Type = BUTTON_TYPE::TRAPTYPE_CHECK; BT_FindNoTile = true; }

			// 다음 버튼을 눌렀다면 새로 갱신
			if (PtInRect(&BT_Next, _ptMouse) && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true;

				// 렉트 추가 버튼을 누르지 않았을때
				if (BT_Type != BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{
					ImgNumber++;
					if (ImgNumber > ImgCnt) ImgNumber = (int)IMAGE_COUNT::Zero_Img;
					BT_ImgNumber = (IMAGE_COUNT)ImgNumber;
				}

				// 렉트 추가 버튼을 눌렀을때
				if (BT_Type == BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{
					// 타일 렉트의 x 갯수가 1개 늘어난다.

					// x의 마지막 벡터 뒤에 새 타일 정보를 추가해준다. 
					for (int y = 0; y < mapInfo->tile_Count.y; ++y)
					{
						tagTileInfo add_Tile;
						add_Tile.reset_Tile();
						add_Tile.index.x = mapInfo->tile_Count.x;
						add_Tile.index.y = y;
						add_Tile.rc = RectMake(add_Tile.index.x * TILE_SIZE_X, add_Tile.index.y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y);
						add_Tile.center.x = (add_Tile.rc.left + add_Tile.rc.right) / 2.f;
						add_Tile.center.y = (add_Tile.rc.top + add_Tile.rc.bottom) / 2.f;

						(*_vTileList).insert(_vTileList->begin() + (mapInfo->tile_Count.x + (y * (mapInfo->tile_Count.x + 1))), add_Tile);
					}
					
					mapInfo->tile_Count.x++;

					CAMERAMANAGER->Use_Func()->set_Tile_CountX(mapInfo->tile_Count.x);
					CAMERAMANAGER->Use_Func()->set_World_Size(mapInfo->tile_Count.x * TILE_SIZE_X, mapInfo->tile_Count.y * TILE_SIZE_Y);
				}



				BT_FindNoTile = true;
			}

			// 이전 버튼을 눌렀다면 새로 갱신
			if (PtInRect(&BT_Prev, _ptMouse) && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true;

				// 렉트 추가 버튼을 누르지 않았을때
				if (BT_Type != BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{
					ImgNumber--;
					if (ImgNumber < (int)IMAGE_COUNT::Zero_Img) ImgNumber = ImgCnt;
					BT_ImgNumber = (IMAGE_COUNT)ImgNumber;
				}

				// 렉트 추가 버튼을 눌렀을때
				if (BT_Type == BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{

					if (mapInfo->tile_Count.x > TILE_COUNT_X)
					{

						int delete_Tile_Index = mapInfo->tile_Count.x * mapInfo->tile_Count.y - 1;	// 타일의 최대 수량 - 1을 하면 제일 마지막 인덱스를 알 수 있다.

						// 타일 렉트의 x 갯수가 1개 줄어든다.
						// x의 마지막 벡터를 y 갯수만큼 삭제한다.
						for (int y = 0; y < mapInfo->tile_Count.y; ++y)
						{
							(*_vTileList).erase((*_vTileList).begin() + delete_Tile_Index);			// 마지막 인덱스 삭제
							delete_Tile_Index -= mapInfo->tile_Count.x;								// 마지막 인덱스에서 가로 갯수를 빼면 바로 위의 인덱스가 나온다.
						}

						mapInfo->tile_Count.x--;													// 한줄이 모두 사라졌으면 가로 타일 갯수를 하나 줄여준다.

						CAMERAMANAGER->Use_Func()->set_Tile_CountX(mapInfo->tile_Count.x);
						CAMERAMANAGER->Use_Func()->set_World_Size(mapInfo->tile_Count.x * TILE_SIZE_X, mapInfo->tile_Count.y * TILE_SIZE_Y);
					}
				}

				BT_FindNoTile = true;
			}

			// 업 버튼을 눌렀다면
			if (PtInRect(&BT_Up, _ptMouse) && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true; // 중복 클릭 방지 인터벌

				// 백그라운드 버튼을 눌렀을때 연산
				if (BT_Type == BUTTON_TYPE::BACKGROUND)
				{
					// 백그라운드 레이어 카운트가 바뀐다.
					mapInfo->_layer_Cnt--;
					if (mapInfo->_layer_Cnt < 0) mapInfo->_layer_Cnt = BACKGROUND_LAYER_COUNT - 1;	// 만약 카운트가 0 이하로 된다면 카운트 최대치로 바꿔준다.
				}

				// 렉트 삭제 버튼을 눌렀을때 연산
				if (BT_Type == BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{

					if (mapInfo->tile_Count.y > TILE_COUNT_Y)
					{
						// 타일 렉트의 y 갯수가 1개 줄어든다.

						// y열을 감소
						for (int x = 0; x < mapInfo->tile_Count.x; ++x)
						{
							_vTileList->erase(_vTileList->begin() + (_vTileList->size() - 1));
						}

						mapInfo->tile_Count.y--;

						CAMERAMANAGER->Use_Func()->set_Tile_CountY(mapInfo->tile_Count.y);
						CAMERAMANAGER->Use_Func()->set_World_Size(mapInfo->tile_Count.x * TILE_SIZE_X, mapInfo->tile_Count.y * TILE_SIZE_Y);
					}
				}

				BT_FindNoTile = true;
			}

			// 다운 버튼을 눌렀다면
			if (PtInRect(&BT_Down, _ptMouse) && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true; // 중복 클릭 방지 인터벌

				// 백그라운드 버튼을 눌렀을때 연산
				if (BT_Type == BUTTON_TYPE::BACKGROUND)
				{
					// 백그라운드 레이어 카운트가 바뀐다.
					mapInfo->_layer_Cnt++;
					if (mapInfo->_layer_Cnt == BACKGROUND_LAYER_COUNT)	mapInfo->_layer_Cnt = 0;	// 만약 카운트가 최대가 된다면 0으로 되돌아간다.
				}

				// 렉트 추가 버튼을 눌렀을때 연산
				if (BT_Type == BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{
					// 타일 렉트의 y 갯수가 1개 늘어난다.

					// y열을 추가시켜준다.
					for (int x = 0; x < mapInfo->tile_Count.x; ++x)
					{
						tagTileInfo add_Tile;
						add_Tile.reset_Tile();
						add_Tile.index.x = x;
						add_Tile.index.y = mapInfo->tile_Count.y;
						add_Tile.rc = RectMake(add_Tile.index.x * TILE_SIZE_X, add_Tile.index.y * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y);
						add_Tile.center.x = (add_Tile.rc.left + add_Tile.rc.right) / 2.f;
						add_Tile.center.y = (add_Tile.rc.top + add_Tile.rc.bottom) / 2.f;

						_vTileList->push_back(add_Tile);
					}

					mapInfo->tile_Count.y++;

					CAMERAMANAGER->Use_Func()->set_Tile_CountY(mapInfo->tile_Count.y);
					CAMERAMANAGER->Use_Func()->set_World_Size(mapInfo->tile_Count.x * TILE_SIZE_X, mapInfo->tile_Count.y * TILE_SIZE_Y);
				}

				BT_FindNoTile = true;
			}

			// 레이어 마이너스 버튼을 눌렀다면
			if (PtInRect(&BT_Minus, _ptMouse) && BT_Type == BUTTON_TYPE::BACKGROUND && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true; // 중복 클릭 방지 인터벌

				// 현재 레이어 카운트에 있는 벡터를 한개 지워준다. (벡터 사이즈가 0 이상일때만)
				if (vBackGround[mapInfo->_layer_Cnt].size() > 0) vBackGround[mapInfo->_layer_Cnt].erase(vBackGround[mapInfo->_layer_Cnt].end()-1);

				BT_FindNoTile = true;
			}

		
			KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// 키 씹히는걸 방지하기 위해
		}	

		if (next_Prev_Push_Okay)
		{
			next_Prev_Push_Timer++;
			if (next_Prev_Push_Timer > 20)
			{
				next_Prev_Push_Okay = false;
				next_Prev_Push_Timer = 0;
			}
		}
	}
};


// 맵툴 함수
class mapTool_Func
{
private:
	// 연산에 쓰일 함수
	bool	draw_Ready_BG;													// 백그라운드 그리기 준비
	short	draw_Cnt_BG;													// 백그라운드 그리기 인터벌
	vector<tagSaveBackGround>	_vBackGround_Info[BACKGROUND_LAYER_COUNT];	// 백그라운드 정보를 저장한다.

public:
	vector<tagSaveBackGround>* get_VBackGround_Info_Address() { return _vBackGround_Info; }
	

public:
	// 사용하기 전에 변수 초기화
	void reset()
	{
		draw_Ready_BG = false;
		draw_Cnt_BG = 0;

		for (int i = 0; i < BACKGROUND_BACKCOUNT; ++i)
		{
			_vBackGround_Info[i].clear();
		}
	}


	// 기본 타일을 만들어 준다.
	void make_Base_TileList(vector<tagTileInfo>* tileList)
	{
		tileList->clear();

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

		char testNum[100];

		// 렉트를 출력한다.
		for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
		{
			for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
			{
				RECT rc = (*_vTileList)[y * CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X + x].rc;

				rc.left -= camera.x;
				rc.right -= camera.x;
				rc.top -= camera.y;
				rc.bottom -= camera.y;

				//Rectangle(getMemDC, rc);
				IMAGEMANAGER->findImage("tile_Rect")->render(getMemDC, rc.left, rc.top);

				int a = (y * CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X + x);
				sprintf_s(testNum, 100, "%d", a);
				TextOut(getMemDC, rc.left, rc.top, testNum, strlen(testNum));
			}
		}

	}

	

	// 팔렛트를 출력 한다.
	void show_Pallet(HDC getMemDC, BUTTON_TYPE button, tagPallets* pallet, short layerCnt)
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
				IMAGEMANAGER->findImage(pallet->ImgName)->frameRender(getMemDC, pallet->pallet.Ground_Pallet[i].rc.left, pallet->pallet.Ground_Pallet[i].rc.top,
					pallet->pallet.Ground_Pallet[i].frame.x, pallet->pallet.Ground_Pallet[i].frame.y);
				

				// 렉트 출력
				IMAGEMANAGER->findImage("tile_Rect")->render(getMemDC, pallet->pallet.Ground_Pallet[i].rc.left, pallet->pallet.Ground_Pallet[i].rc.top);
			}
			break;

		case BUTTON_TYPE::BACKGROUND:

			// 팔렛트 테두리 출력
			pallet->show_Pallet(getMemDC, button);

			for (int i = 0; i < BACKGROUND_COUNTX * BACKGROUND_COUNTY; ++i)
			{
				// 지형 이미지 출력 
				IMAGEMANAGER->findImage(pallet->ImgName)->frameRender(getMemDC, pallet->pallet.back_Ground_Pallet[i].rc.left, pallet->pallet.back_Ground_Pallet[i].rc.top,
					pallet->pallet.back_Ground_Pallet[i].frame.x, pallet->pallet.back_Ground_Pallet[i].frame.y);


				// 렉트 출력
				IMAGEMANAGER->findImage("tile_Rect_200")->render(getMemDC, pallet->pallet.back_Ground_Pallet[i].rc.left, pallet->pallet.back_Ground_Pallet[i].rc.top);
			}

			// 레이어 위치 출력
			for (int i = 0; i < 5; ++i)
			{
				// 레이어 위치 렉트
				//Rectangle(getMemDC, pallet->Layer[i]);

				// 레이어 이미지 출력
				if (i == layerCnt)	IMAGEMANAGER->findImage("back_Ground_Select_Pointer")->render(getMemDC, pallet->Layer[i].left, pallet->Layer[i].top);
				else				IMAGEMANAGER->findImage("back_Ground_Select")->render(getMemDC, pallet->Layer[i].left, pallet->Layer[i].top);
			}



			break;
		}
	}
	
	// 선택한 이미지를 타일에 저장한다.
	void setting_TileImg(vector<tagTileInfo>* TileList, tagPallet_INFO pallet, tagButton_Info button, tagMapInfo* mapInfo, bool* click)
	{
		if (*click)
		{

			POINT _ptMouse_Ver2 = _ptMouse;
			_ptMouse_Ver2.x += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			_ptMouse_Ver2.y += CAMERAMANAGER->Use_Func()->get_CameraXY().y;

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				switch ((BUTTON_TYPE)button.BT_Type)
				{
					case BUTTON_TYPE::GROUND:
						for (int i = 0; i < mapInfo->tile_Count.x * mapInfo->tile_Count.y; ++i)
						{
							if (PtInRect(&(*TileList)[i].rc, _ptMouse_Ver2))
							{
								(*TileList)[i].frame.ground = pallet.frame;
								(*TileList)[i].tile_Type = TILE_TYPE::GROUND;
								(*TileList)[i].tileName.groundName = pallet.imageName.groundName;
								(*TileList)[i].useTile = true;	// 이 타일은 사용중이라는 뜻
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

					case BUTTON_TYPE::TRAP:
						break;

					case BUTTON_TYPE::BACKGROUND:
						for (int i = 0; i < mapInfo->tile_Count.x * mapInfo->tile_Count.y; ++i)
						{
							if (PtInRect(&button.BT_Up, _ptMouse) || PtInRect(&button.BT_Down, _ptMouse) || PtInRect(&button.BT_Minus, _ptMouse)) continue;
							if (PtInRect(&(*TileList)[i].rc, _ptMouse_Ver2) && !draw_Ready_BG)
							{

								// 그 타일의 좌표를 얻어서 그냥 그려버리는건 어떨까?
								// 그 좌표를 벡터에 저장하고 이미지 정보도 가지고 있는 벡터
								// 지울때는 뒤에서부터 하나씩 지우는것으로 
								// 클릭할때마다 늘어나기만 하고 
								// 한번씩만 클릭하게 바꿔야함
								draw_Ready_BG = true;

								tagSaveBackGround BG_Info;
								BG_Info.imageName = pallet.imageName.backGroundImgName;
								BG_Info.rc = (*TileList)[i].rc;	// 배경이 뿌려질 좌표
								_vBackGround_Info[mapInfo->_layer_Cnt].push_back(BG_Info);
								break;
							}
						}

						if (draw_Ready_BG)
						{
							draw_Cnt_BG++;
							if (draw_Cnt_BG > 10)
							{
								draw_Cnt_BG = 0;
								draw_Ready_BG = false;
							}
						}
						break;

					case BUTTON_TYPE::FOOTHOLDTYPE_CHECK:
						for (int i = 0; i < mapInfo->tile_Count.x * mapInfo->tile_Count.y; ++i)
						{
							if (PtInRect(&(*TileList)[i].rc, _ptMouse_Ver2))
							{
								// 발판 속성을 넣어준다.
								(*TileList)[i].tile_Collision_Type = COLLISION_TILE_TYPE::FOOTHOLD_TYPE;
								(*TileList)[i].tile_Type = TILE_TYPE::EMPTY;
							}
						}
						break;

					case BUTTON_TYPE::WALLTYPE_CHECK:
						for (int i = 0; i < mapInfo->tile_Count.x * mapInfo->tile_Count.y; ++i)
						{
							if (PtInRect(&(*TileList)[i].rc, _ptMouse_Ver2))
							{
								// 벽 속성을 넣어준다.
								(*TileList)[i].tile_Collision_Type = COLLISION_TILE_TYPE::WALL_TYPE;
								(*TileList)[i].tile_Type = TILE_TYPE::EMPTY;
							}
						}
						break;

					case BUTTON_TYPE::TRAPTYPE_CHECK:
						for (int i = 0; i < mapInfo->tile_Count.x * mapInfo->tile_Count.y; ++i)
						{
							if (PtInRect(&(*TileList)[i].rc, _ptMouse_Ver2))
							{
								// 함정 속성을 넣어준다.
								(*TileList)[i].tile_Collision_Type = COLLISION_TILE_TYPE::TRAP_TYPE;
								(*TileList)[i].tile_Type = TILE_TYPE::EMPTY;
							}
						}
						break;
				}

				KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// 키 씹히는걸 방지하기 위해
			}
		}
	}




	// 보이는 부분의 타일을 출력해준다.
	void show_TileImg(HDC getMemDC ,vector<tagTileInfo>* _vTileList, tagMapInfo mapInfo)
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// 카메라 안에 들어온 타일을 찾아서 저장한다.

		// 백그라운드를 그려준다.
		for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
		{
			if (_vBackGround_Info[i].size() > 0)	// 해당 벡터가 0이상이여야만 들어간다.
			{
				for (int j = 0; j < _vBackGround_Info[i].size(); ++j)
				{
					RECT rc = (_vBackGround_Info[i])[j].rc;
					rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
					rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
					rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
					rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
					IMAGEMANAGER->findImage((_vBackGround_Info[i])[j].imageName)->render(getMemDC, rc.left, rc.top);
				}
			}
		}

		//if (_vBackGround_Info->size() > 0)
		//{
		//	for (int i = 0; i < _vBackGround_Info->size();++i)
		//	{
		//		RECT rc = (_vBackGround_Info[0])[i].rc;
		//		rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		//		rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		//		rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		//		rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		//		IMAGEMANAGER->findImage((_vBackGround_Info[0])[i].imageName)->render(getMemDC, rc.left, rc.top);
		//	}
		//}

		// 마우스가 클릭한 타일을 찾아준다. (내 화면에 있는 타일만 찾아서)
		for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
		{
			for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
			{
				//cout << y * mapInfo.tile_Count.x + x << ":" << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.x << "," << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.y << endl;

				RECT rc = (*_vTileList)[y * mapInfo.tile_Count.x + x].rc;
				POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

				rc.left -= camera.x;
				rc.right -= camera.x;
				rc.top -= camera.y;
				rc.bottom -= camera.y;

				// 안 쓰는 타입은 제외한다.
				if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
				{
					// 백 그라운드를 그려준다.
					//if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::BACKGROUND)
					//{
					//	if ((*_vTileList)[y * mapInfo.tile_Count.x + x].useTile)
					//	{
					//		IMAGEMANAGER->findImage((*_vTileList)[y * mapInfo.tile_Count.x + x].tileName.backGroundImgName)->render(getMemDC, rc.left, rc.top);
					//		
					//	}
					//}

					// 지형을 그려준다.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
					{
						if ((*_vTileList)[y * mapInfo.tile_Count.x + x].useTile)
						{
						
							IMAGEMANAGER->findImage((*_vTileList)[y * mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
								(*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.x, (*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.y);
						}
					}

					// 데코를 그려준다.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
					{
					
					}
				}

				// 충돌 타입이 없다면 제외한다.
				if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Collision_Type != COLLISION_TILE_TYPE::NONE_TYPE)
				{
					// 발판 타입을 표시해준다.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
					{
						IMAGEMANAGER->findImage((*_vTileList)[y * mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							(*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.x, (*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.y);
						IMAGEMANAGER->findImage("footHoldType_Check")->render(getMemDC, rc.left, rc.top);
					}

					// 벽 타입을 표시해준다.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
					{
						IMAGEMANAGER->findImage((*_vTileList)[y * mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							(*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.x, (*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.y);
						IMAGEMANAGER->findImage("wallType_Check")->render(getMemDC, rc.left, rc.top);
					}

					// 함정 타입을 표시해준다.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::TRAP_TYPE)
					{
						IMAGEMANAGER->findImage((*_vTileList)[y * mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							(*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.x, (*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.y);
						IMAGEMANAGER->findImage("trapType_Check")->render(getMemDC, rc.left, rc.top);
					}
				}
			}
		}
	}
};