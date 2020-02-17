#pragma once
#include "stdafx.h"

// ��� �̹��� ī��Ʈ��
enum BACKGROUND_CNT
{
	NONE,				// �������
	ONE,				// �Ѱ�
	TWO,				// �ΰ�
	THREE				// ����
};


// �̹��� ī��Ʈ��
enum IMAGE_COUNT
{
	Zero_Img,			// 0��°	 
	One_Img,			// 1��°	 
	Two_Img,			// 2��°	 
	Three_Img,			// 3��°	 
	Four_Img,			// 4��°	 
	Five_Img,			// 5��°	 
	Six_Img,			// 6��°	 
	Seven_Img,			// 7��° 
	Eight_Img,			// 8��°	 
	Nine_Img,			// 9��°	 
	Ten_Img				// 10��°
};


// ��ư Ÿ��
enum class BUTTON_TYPE
{
	NONE,							// �ƹ��͵� ������ �ʾҴٸ�
	SAVE,							// ���̺� ��ư�� �����ٸ�
	LOAD,							// �ε� ��ư�� �����ٸ�
	ERASER,							// ���찳 ��ư�� �����ٸ�
	GROUND,							// ���� ��ư�� �����ٸ�
	DECORATION,						// ���� ��ư�� �����ٸ�
	HIT_OBJECT,						// �ı� ���� ������Ʈ ��ư�� �����ٸ�
	DOOR,							// �� ��ư�� �����ٸ�
	CHARACTER,						// ĳ���� ��ư�� �����ٸ�
	ITEM,							// ������ ��ư�� �����ٸ�
	TRAP,							// Ʈ�� ��ư�� �����ٸ�
	BACKGROUND,						// �� �׶��� ��ư�� �����ٸ�
	RECT_ADD_OR_MINUS,				// ��Ʈ �߰� ���� ��ư
	FOOTHOLDTYPE_CHECK,				// ���� Ÿ���̶�� �Ӽ��� �ִ� ��ư
	WALLTYPE_CHECK,					// �� Ÿ���̶�� �Ӽ��� �ִ� ��ư
	TRAPTYPE_CHECK					// ���� Ÿ���̶�� �Ӽ��� �ִ� ��ư
				
};

// ����� ������ ����ü
struct tagSaveBackGround
{
	string	imageName;	// ��� �̹����� Ű���� �����Ѵ�.
	RECT	rc;			// �ѷ��� ��ǥ�� �����Ѵ�.
};

// �ȷ�Ʈ �̵��� ���� ��Ʈ
struct tagPalletBar
{
	RECT Ground_Pallet_Bar;												// �ٴ� �ȷ�Ʈ ��
	RECT Decoration_Pallet_Bar;											// ���� �ȷ�Ʈ ��
	RECT Hit_Object_Bar;												// �ı� ������Ʈ ��
	RECT Door_Pallet_Bar;												// ���� �ȷ�Ʈ ��
	RECT Character_Pallet_Bar;											// ĳ���� �ȷ�Ʈ ��
	RECT Item_Bar;														// ������ ������Ʈ ��
	RECT Trap_Bar;														// Ʈ�� �ȷ�Ʈ ��
	RECT Back_Ground_Bar;												// ��׶��� ��

	// �ȷ�Ʈ �ٸ� �̵� ��ų �Լ� (��� �ߴ�)
	void move_Bar()
	{

	}
};

// Ÿ���� �̹��� �̸��� ���� ���� ����ü
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

// �ȷ�Ʈ�� ������ ��´�.
struct tagPallet_INFO
{
	RECT		rc;														// ��Ʈ�� ������ ��´�.
	tag_U_Short	frame;													// ������ x, y�� ��´�.
	tagTileName	imageName;												// �ش� Ÿ���� �̹��� �̸��� ��´�. 

	// �Ź� Ÿ���� ������ ���� Ÿ���� �ʱ�ȭ �Ҷ� ���
	void reset_Type()
	{
		frame.x = frame.y = 0;
		imageName.reset();
	}
};

// �ȷ�Ʈ�� ������ ��´�.
struct tagPalletKinds
{
	tagPallet_INFO	Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY];					// ���� �ȷ�Ʈ
	tagPallet_INFO	Decoration_Pallet[2];										// ��� �ȷ�Ʈ
	tagPallet_INFO	Hit_Object_Pallet[2];										// �ı� ������Ʈ �ȷ�Ʈ
	tagPallet_INFO	Door_Pallet[2];												// ���� �ȷ�Ʈ
	tagPallet_INFO	Character_Pallet[2];										// ĳ���� �ȷ�Ʈ
	tagPallet_INFO	Item_Pallet[2];												// ������ �ȷ�Ʈ
	tagPallet_INFO  Trap_Pallet[2];												// Ʈ�� �ȷ�Ʈ
	tagPallet_INFO	back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY];	// �� �׶��� �ȷ�Ʈ
};


// ��� ���������� ����
struct tagLoop_Variable
{
	short LoopX_BG_0;		// �� �ڿ� �ִ� �� �׶��� ������ ����
	short LoopX_BG_1;		// �� �տ� �� �׶��� ������ ����
	short LoopX_BG_2;		// �� �տ� �ִ� �� �׶��� ������ ����

	void reset_Func()
	{
		LoopX_BG_0 = LoopX_BG_1 = LoopX_BG_2 = 0;
	}
};


// ���� ������ ���� �� ����ü
struct tagMapInfo
{
	string						mapName;											// ���� �̸��� �����Ѵ�.
	tag_U_Short					tile_Size;											// Ÿ�� ����� �����Ѵ�.
	tag_U_Short					tile_Count;											// Ÿ���� ������ �����Ѵ�.

	tagLoop_Variable*			loop;												// �������� ����� ����

	tagSaveBackGround			_saveVInfo[BACKGROUND_LAYER_COUNT][10];				// ��׶��� ���͸� ���̺�
	short						_layer_Cnt;											// ���̾� ī����
	short						_vSize[BACKGROUND_LAYER_COUNT];						// ���� ����� ��´�.
		
	// �� ���� �ʱ�ȭ
	void reset_MapInfo()
	{
		mapName = {};
		tile_Size.x = TILE_SIZE_X;		// ���̽� Ÿ���� ����� �����Ѵ�.
		tile_Size.y = TILE_SIZE_Y;		// ���̽� Ÿ���� ����� �����Ѵ�.
		tile_Count.x = TILE_COUNT_X;	// ���̽� Ÿ���� ������ �����Ѵ�.
		tile_Count.y = TILE_COUNT_Y;	// ���̽� Ÿ���� ������ �����Ѵ�.

		loop = new tagLoop_Variable;
		loop->reset_Func();

		for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)	_vSize[i] = 0;

		_layer_Cnt = 0;

		// ���� ���� �ҷ����� Ÿ�� ����, ���� ����� �������ش�.
		CAMERAMANAGER->Use_Func()->set_Tile_CountX(tile_Count.x);														// ���� ������ ���� (�ʸ��� ���μ��ΰ� �ٸ��ϱ�)
		CAMERAMANAGER->Use_Func()->set_Tile_CountY(tile_Count.y);														// ���� ������ ����
		CAMERAMANAGER->Use_Func()->set_World_Size(tile_Count.x * TILE_SIZE_X, tile_Count.y * TILE_SIZE_Y);				// ���μ��ο� �°� ���� ������ ����
	}

};


// Ÿ���� �̹��� �������� ���� ���� ����ü
struct tagTileFrame
{
	tag_U_Short		ground;					// ���� �̹��� �������� ��°�
	tag_U_Short		backGround;				// �� �׶��� �̹��� �������� ��°�
};


// Ÿ�� ������ ���� �� ����ü
struct tagTileInfo
{
	POINTFLOAT			center;					// Ÿ���� ������ ��´�.
	RECT				rc;						// Ÿ���� ��Ʈ�� ��´�.
	tag_U_Short			index;					// Ÿ���� �ε����� ��´�. (���� : 0 ~ 65535)

	TILE_TYPE			tile_Type;				// Ÿ���� Ÿ���� ��´�.
	COLLISION_TILE_TYPE	tile_Collision_Type;	// Ÿ���� �浹 Ÿ���� ��´�.
	tagTileName			tileName;				// Ÿ�� �̹��� �̸��� ��´�.

	tagTileFrame 	    frame;					// �̹��� �������� ��´�.

	bool				useTile;				// �̹����� �ִ� Ÿ������ �ƴ���

	// Ÿ���� �⺻ ���� ���ش�. (����ش�)
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

// �ȷ�Ʈ�� ������ ��´�.
struct tagPallets
{
	tagPalletBar			palletBar;						// �ȷ�Ʈ ��
	tagPalletKinds			pallet;							// �ȷ�Ʈ
	tagPallet_INFO			current;						// Ŭ�� �� �̹��� ����
	string					ImgName;						// �̹��� �̸�
	RECT					Layer[5];						// �� �׶��� ���̾� �̹��� ��Ʈ
	

	// ����� ���� �ʱ�ȭ
	void reset()
	{
		current.reset_Type();

		ImgName = "tutorial_Tile";
	}

	// ��ȣ�� �´� �̹��� �̸��� ã�´�.
	void findImg(BUTTON_TYPE type, IMAGE_COUNT imgNum)
	{
		// ���� �̹��� ��ȣ�� �´� �̹��� ������ �־��ش�.
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

	// ��ȣ�� �´� �̹��� �̸��� ã�´�.
	void findImg_BG(BUTTON_TYPE type, IMAGE_COUNT imgNum, short x, short y)
	{
		// ���� �̹��� ��ȣ�� �´� �̹��� ������ �־��ش�.
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

	// �ȷ�Ʈ �⺻ ����
	void setting_Pallet(BUTTON_TYPE type, IMAGE_COUNT imgNum, RECT* BT_Prev, RECT* BT_Next, RECT* BT_Up, RECT* BT_Down, RECT* BT_RectPlus, RECT* BT_Minus)
	{
		findImg(type, imgNum);	// ��ȣ�� �´� �̹��� �̸��� ã�´�.
	
		switch (type)
		{
			case BUTTON_TYPE::GROUND:

				// ������������������������������������������������� ���� ���� ����������������������������������������������������������
				// �ȷ�Ʈ ���� ��ġ�� �����ش�.
				// ���� �ȷ�Ʈ �� ����
				palletBar.Ground_Pallet_Bar = RectMake(WINSIZEX - IMAGEMANAGER->findImage("tutorial_Tile")->getWidth(), 10,
					IMAGEMANAGER->findImage("tutorial_Tile")->getWidth(), 20);

				// �ȷ�Ʈ ���� �Ʒ��� �ȷ�Ʈ�� ��Ʈ�� �׷��ش�.
				// ���� �ȷ�Ʈ ����
				for (int y = 0; y < GROUND_SIZEY; ++y)
				{
					for (int x = 0; x < GROUND_SIZEX; ++x)
					{
						// ������ ���� �־��ش�.
						pallet.Ground_Pallet[x + y * GROUND_SIZEX].frame.x = x;
						pallet.Ground_Pallet[x + y * GROUND_SIZEX].frame.y = y;

						// ��Ʈ ��ġ�� �����. (�ȷ�Ʈ ���� left, bottom ��������)
						pallet.Ground_Pallet[x + y * GROUND_SIZEX].rc =
							RectMake(palletBar.Ground_Pallet_Bar.left + x * TILE_SIZE_X, palletBar.Ground_Pallet_Bar.bottom + y * TILE_SIZE_Y,
								TILE_SIZE_X, TILE_SIZE_Y);

						// �ѷ��� �� �����̹��� �̸�
						pallet.Ground_Pallet[x + y * GROUND_SIZEX].imageName.groundName = ImgName;
					}
				}
				// ��������������������������������������������������������������������������������������������������������������
			break;

			case BUTTON_TYPE::BACKGROUND:

				// ����������������������������������������������� �� �׶��� ���� �����������������������������������������������������������
				// �ȷ�Ʈ ���� ��ġ�� �����ش�.
				// �� �׶��� �� ����

				short width, height;
				width = IMAGEMANAGER->findImage("backGround_Pallet_0")->getWidth();
				height = IMAGEMANAGER->findImage("backGround_Pallet_0")->getHeight();

				palletBar.Back_Ground_Bar = RectMake(WINSIZEX - width, 10, width, 20);

				// �ȷ�Ʈ ���� �Ʒ��� �ȷ�Ʈ�� ��Ʈ�� �׷��ش�.
				// �� �׶��� �ȷ�Ʈ ����
				for (int y = 0; y < BACKGROUND_COUNTY; ++y)
				{
					for (int x = 0; x < BACKGROUND_COUNTX; ++x)
					{
						// ������ ���� �־��ش�.
						pallet.back_Ground_Pallet[x + y * BACKGROUND_COUNTX].frame.x = x;
						pallet.back_Ground_Pallet[x + y * BACKGROUND_COUNTX].frame.y = y;

						// ��Ʈ ��ġ�� �����. (�ȷ�Ʈ ���� left, bottom ��������)
						pallet.back_Ground_Pallet[x + y * BACKGROUND_COUNTX].rc =
							RectMake(palletBar.Back_Ground_Bar.left + (x * (width / BACKGROUND_COUNTX)), palletBar.Back_Ground_Bar.bottom + (y * (height / BACKGROUND_COUNTY)),
								width / BACKGROUND_COUNTX, height / BACKGROUND_COUNTY);

						// �ѷ��� �� ���� �̹��� �̸�
						pallet.back_Ground_Pallet[x + y * BACKGROUND_COUNTX].imageName.backGroundName = ImgName;
					}
				}

				// ��׶��� �ȷ�Ʈ ���ʿ� ���̾��� ��ġ�� ǥ���ϴ� �̹��� ��ġ�� ����ش�.
				Layer[0] = RectMake(pallet.back_Ground_Pallet[0].rc.left - 32, pallet.back_Ground_Pallet[0].rc.top + 32 * 2, 32, 32);
				Layer[1] = RectMake(Layer[0].left, Layer[0].top + 32 * 1, 32, 32);
				Layer[2] = RectMake(Layer[0].left, Layer[0].top + 32 * 2, 32, 32);
				Layer[3] = RectMake(Layer[0].left, Layer[0].top + 32 * 3, 32, 32);
				Layer[4] = RectMake(Layer[0].left, Layer[0].top + 32 * 4, 32, 32);

				// ���̾� ���� ��ư ��ġ�� �����.
				*BT_Minus = RectMake(Layer[0].left, Layer[0].top + 32 * 5 + 3, 32, 30);
				
				break;

			case BUTTON_TYPE::RECT_ADD_OR_MINUS:

				// ��,��,��,�� ��ư�� ��ġ�� �ٽ� ������ش�. (��Ʈ �߰� ��ư �Ʒ���?)
				*BT_Prev = RectMake(BT_RectPlus->left - 32, BT_RectPlus->bottom, 32, 30);
				*BT_Next = RectMake(BT_Prev->right, BT_RectPlus->bottom, 32, 30);
				*BT_Up = RectMake(BT_Next->right, BT_RectPlus->bottom, 32, 30);
				*BT_Down = RectMake(BT_Up->right, BT_RectPlus->bottom, 32, 30);

				break;
		}
	}

	// �ȷ�Ʈ ���� �Լ� (�ȷ�Ʈ �̵� �� ������ ��ǥ ����)
	void pallet_Update()
	{
		// �ȷ�Ʈ ���� �Ʒ��� �ȷ�Ʈ�� ��Ʈ�� �׷��ش�.
		// ���� �ȷ�Ʈ ����
		for (int y = 0; y < GROUND_SIZEY; ++y)
		{
			for (int x = 0; x < GROUND_SIZEX; ++x)
			{
				// ��Ʈ ��ġ�� �����. (�ȷ�Ʈ ���� left, bottom ��������)
				pallet.Ground_Pallet[x + y * GROUND_SIZEX].rc =
					RectMake(palletBar.Ground_Pallet_Bar.left + x * TILE_SIZE_X, palletBar.Ground_Pallet_Bar.bottom + y * TILE_SIZE_Y,
						TILE_SIZE_X, TILE_SIZE_Y);
			}
		}


	}

	// �ȷ�Ʈ ��� �Լ�
	void show_Pallet(HDC getMem, BUTTON_TYPE button)
	{
		// ��ư Ÿ�Կ� ���� �ٸ� �ȷ�Ʈ �� ���
		switch (button)
		{
			case BUTTON_TYPE::GROUND:
				// �ȷ�Ʈ �� ��Ʈ ���
				Rectangle(getMem, palletBar.Ground_Pallet_Bar);

				// �ȷ�Ʈ �׵θ� ��Ʈ ���
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
				// �ȷ�Ʈ �� ��Ʈ ���
				Rectangle(getMem, palletBar.Back_Ground_Bar);

				// �ȷ�Ʈ �׵θ� ��Ʈ ���
				Rectangle(getMem, palletBar.Back_Ground_Bar.left, palletBar.Back_Ground_Bar.bottom,
					palletBar.Back_Ground_Bar.right, palletBar.Back_Ground_Bar.bottom + BACKGROUND_COUNTY * BACKGROUND_SIZEY);
				break;
		}
	}

	// Ŭ�� �� �ȷ�Ʈ�� ������ �����Ѵ�.
	void click_PalletInfo_Save(BUTTON_TYPE button, IMAGE_COUNT imgNum, bool* click, bool* findNoTile)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			switch (button)
			{
				case BUTTON_TYPE::GROUND:
					// Ground �ȷ�Ʈ�� ��Ʈ�� ���콺�� Ŭ�� �ߴٸ�, �� Ŭ�� �� �ȷ�Ʈ�� ������ ��´�.
					for (int i = 0; i < GROUND_SIZEX * GROUND_SIZEY; ++i)
					{
						if (PtInRect(&pallet.Ground_Pallet[i].rc, _ptMouse))
						{
							current.frame.x = pallet.Ground_Pallet[i].frame.x;
							current.frame.y = pallet.Ground_Pallet[i].frame.y;

							current.imageName.groundName = pallet.Ground_Pallet[i].imageName.groundName;	// �̹��� �̸��� �־��ش�.

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
					// BackGround �ȷ�Ʈ�� ��Ʈ�� ���콺�� Ŭ�� �ߴٸ�, �� Ŭ�� �� �ȷ�Ʈ�� ������ ��´�.
					for (int i = 0; i < BACKGROUND_COUNTX * BACKGROUND_COUNTY; ++i)
					{
						if (PtInRect(&pallet.back_Ground_Pallet[i].rc, _ptMouse))
						{
							current.frame.x = pallet.back_Ground_Pallet[i].frame.x;
							current.frame.y = pallet.back_Ground_Pallet[i].frame.y;

							findImg_BG(button, imgNum, current.frame.x, current.frame.y);								// ���� �̹��� �ѹ��� �´� �̹��� �̸��� ã�´�.

							current.imageName.backGroundImgName = ImgName;												// �̹��� �̸��� �־��ش�.

							*click = true;
							*findNoTile = true;
						}
					}
					break;

				case BUTTON_TYPE::FOOTHOLDTYPE_CHECK: case BUTTON_TYPE::WALLTYPE_CHECK: case BUTTON_TYPE::TRAPTYPE_CHECK:
					*click = true;
					break;
			}

			KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// Ű �����°� �����ϱ� ����
		}
	}
};



// ��ư ������ ��� ����ü
struct tagButton_Info
{
	// ��� ��ư
	RECT			BT_Save;			// ���̺� ��ư
	RECT			BT_Load;			// �ε� ��ư
	RECT			BT_Eraser;			// ���찳 ��ư
	RECT			BT_Next;			// ���� ��ư
	RECT			BT_Prev;			// ���� ��ư
	RECT			BT_Up;				// �� ��ư (���� ���� ���� ������ �� �ּ� ����)
	RECT			BT_Down;			// �ٿ� ��ư (���� ���� ���� ������ �� �ּ� ����)
	RECT			BT_Minus;			// ���̾� ���� ��ư
	RECT			BT_RectPlus;		// ��Ʈ �߰� ��ư
	RECT			BT_FootHold_Check;	// ���� �Ӽ� üũ ��ư
	RECT			BT_Wall_Check;		// �� �Ӽ� üũ ��ư
	RECT			BT_Trap_Check;		// ���� �Ӽ� üũ ��ư

	// �ȷ�Ʈ ��ư
	RECT			BT_Ground;			// ���� �̹��� ��ư
	RECT			BT_Decoration;		// ���ڷ��̼� �̹��� ��ư
	RECT			BT_Hit_Object;		// �ı� ���� �̹��� ��ư
	RECT			BT_Door;			// �� �̹��� ��ư
	RECT			BT_Character;		// ĳ���� �̹��� ��ư
	RECT			BT_Item;			// ������ �̹��� ��ư
	RECT			BT_Trap;			// ���� �̹��� ��ư
	RECT			BT_BackGround;		// ��׶��� �̹��� ��ư

	// ��� ����
	BUTTON_TYPE		BT_Type;			// Ŭ���� ��ư�� �����Ѵ�.

	// ���� ����
	bool			BT_start_Draw;		// �׸��� ���� �ߴٸ� true
	bool			BT_Click_Eraser;	// ���찳 ��ư�� Ŭ�� �ߴٸ�
	bool			BT_FindNoTile;		// �׸��� �ȵǴ� Ÿ���� ã�´�.

	IMAGE_COUNT		BT_ImgNumber;		// �̹��� ��ȣ�� ���� �Ѵ�.
	short			ImgNumber;			// �̹��� ��ȣ
	short			ImgCnt;				// �̹��� ����
	bool			next_Prev_Push_Okay;	// ����, ���� ��ư ���͹�
	short			next_Prev_Push_Timer;	// ���͹� ī����

	// �ʱ�ȭ �Լ�
	void reset()
	{
		// ���� �ʱ�ȭ
		BT_start_Draw = false;
		BT_Click_Eraser = false;
		BT_FindNoTile = false;
		next_Prev_Push_Okay = false;
		BT_ImgNumber = IMAGE_COUNT::Zero_Img;
		ImgNumber = 0;
		ImgCnt = 0;
		next_Prev_Push_Timer = 0;

		// �ƹ��͵� Ŭ������ ���� ���´� NONE
		BT_Type = BUTTON_TYPE::NONE;

		short start_Pos, button_Size;
		start_Pos = 10; button_Size = 52;	// ����, ��ư ����� �����Ѵ�.

		// ��ư ��Ʈ�� ��ġ�� ��´�.
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

	// ����, ���� ��ư�� ��ġ�� ���� ���ش�.
	void reset_Next_Prev_Pos(tagPalletKinds pallet)
	{
		switch (BT_Type)
		{
		case BUTTON_TYPE::GROUND:
			// prev ��ư ��ġ
			BT_Prev = RectMake(pallet.Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY - 1].rc.left, pallet.Ground_Pallet[GROUND_SIZEX *GROUND_SIZEY - 1].rc.bottom,
				32, 30);

			// next ��ư ��ġ
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
			// prev ��ư ��ġ
			BT_Prev = RectMake(pallet.back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY - 1].rc.left, pallet.back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY - 1].rc.bottom,
				32, 30);

			// next ��ư ��ġ
			BT_Next = RectMake(pallet.back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY - 1].rc.left + 33, pallet.back_Ground_Pallet[BACKGROUND_COUNTX * BACKGROUND_COUNTY - 1].rc.bottom,
				32, 30);

			// up ��ư ��ġ
			BT_Up = RectMake(pallet.back_Ground_Pallet[0].rc.left - 32, pallet.back_Ground_Pallet[0].rc.top, 32, 30);

			// down ��ư ��ġ
			BT_Down = RectMake(pallet.back_Ground_Pallet[0].rc.left - 32, pallet.back_Ground_Pallet[0].rc.top + 30, 32, 30);

			break;
		}
	}

	// ��ư �̹����� �׷��ش�. (+ ��Ʈ)
	void show_Button(HDC getDC)
	{
		// �׽�Ʈ�� ��Ʈ ���
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

		// ��ư �̹��� ���
		IMAGEMANAGER->findImage("save_Icon")->render(getDC, BT_Save.left, BT_Save.top);
		IMAGEMANAGER->findImage("load_Icon")->render(getDC, BT_Load.left, BT_Load.top);
		IMAGEMANAGER->findImage("eraser_Icon")->render(getDC, BT_Eraser.left, BT_Eraser.top);
		IMAGEMANAGER->findImage("rect_Plus_Icon")->render(getDC, BT_RectPlus.left, BT_RectPlus.top);
		IMAGEMANAGER->findImage("footHoldType_Check_Button")->render(getDC, BT_FootHold_Check.left, BT_FootHold_Check.top);
		IMAGEMANAGER->findImage("wallType_Check_Button")->render(getDC, BT_Wall_Check.left, BT_Wall_Check.top);
		IMAGEMANAGER->findImage("trapType_Check_Button")->render(getDC, BT_Trap_Check.left, BT_Trap_Check.top);

		// ���찳 ��ư�� Ŭ�� ���� �ʾ�����
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

		// ���찳 ��ư�� Ŭ�� ������
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

	// ��ư Ŭ�� �Լ�
	void click_Button(tagMapInfo* mapInfo, vector<tagSaveBackGround>* vBackGround, vector<tagTileInfo>* _vTileList)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			BT_FindNoTile = false;		// ��ư, �ȷ�Ʈ ���ʿ� ������ �ʰ� �ϱ� ���ؼ� ���� bool��

			// ��ư�� Ŭ���ϸ� �ش� Ÿ������ �����Ѵ�.
			if (PtInRect(&BT_Save, _ptMouse)) { BT_Type = BUTTON_TYPE::SAVE; BT_FindNoTile = true; }
			if (PtInRect(&BT_Load, _ptMouse)) { BT_Type = BUTTON_TYPE::LOAD; BT_FindNoTile = true; }
			if (PtInRect(&BT_Eraser, _ptMouse) && !next_Prev_Push_Okay)
			{ BT_Type = BUTTON_TYPE::ERASER; BT_Click_Eraser = !BT_Click_Eraser; BT_FindNoTile = true; next_Prev_Push_Okay = true; }					// ���찳�� �����ٸ� Bool���� ���� ���Ѵ�.




			if (PtInRect(&BT_Ground, _ptMouse)) { BT_Type = BUTTON_TYPE::GROUND; BT_ImgNumber = IMAGE_COUNT::Zero_Img; ImgNumber = 0; BT_FindNoTile = true; ImgCnt = GROUND_IMAGE_CONUT - 1; }	// Ŭ�� �Ҷ����� ù �̹����� �����Ѿ� �ϱ� ������ ���� �ʱ�ȭ ���ش�.
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

			// ���� ��ư�� �����ٸ� ���� ����
			if (PtInRect(&BT_Next, _ptMouse) && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true;

				// ��Ʈ �߰� ��ư�� ������ �ʾ�����
				if (BT_Type != BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{
					ImgNumber++;
					if (ImgNumber > ImgCnt) ImgNumber = (int)IMAGE_COUNT::Zero_Img;
					BT_ImgNumber = (IMAGE_COUNT)ImgNumber;
				}

				// ��Ʈ �߰� ��ư�� ��������
				if (BT_Type == BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{
					// Ÿ�� ��Ʈ�� x ������ 1�� �þ��.

					// x�� ������ ���� �ڿ� �� Ÿ�� ������ �߰����ش�. 
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

			// ���� ��ư�� �����ٸ� ���� ����
			if (PtInRect(&BT_Prev, _ptMouse) && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true;

				// ��Ʈ �߰� ��ư�� ������ �ʾ�����
				if (BT_Type != BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{
					ImgNumber--;
					if (ImgNumber < (int)IMAGE_COUNT::Zero_Img) ImgNumber = ImgCnt;
					BT_ImgNumber = (IMAGE_COUNT)ImgNumber;
				}

				// ��Ʈ �߰� ��ư�� ��������
				if (BT_Type == BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{

					if (mapInfo->tile_Count.x > TILE_COUNT_X)
					{

						int delete_Tile_Index = mapInfo->tile_Count.x * mapInfo->tile_Count.y - 1;	// Ÿ���� �ִ� ���� - 1�� �ϸ� ���� ������ �ε����� �� �� �ִ�.

						// Ÿ�� ��Ʈ�� x ������ 1�� �پ���.
						// x�� ������ ���͸� y ������ŭ �����Ѵ�.
						for (int y = 0; y < mapInfo->tile_Count.y; ++y)
						{
							(*_vTileList).erase((*_vTileList).begin() + delete_Tile_Index);			// ������ �ε��� ����
							delete_Tile_Index -= mapInfo->tile_Count.x;								// ������ �ε������� ���� ������ ���� �ٷ� ���� �ε����� ���´�.
						}

						mapInfo->tile_Count.x--;													// ������ ��� ��������� ���� Ÿ�� ������ �ϳ� �ٿ��ش�.

						CAMERAMANAGER->Use_Func()->set_Tile_CountX(mapInfo->tile_Count.x);
						CAMERAMANAGER->Use_Func()->set_World_Size(mapInfo->tile_Count.x * TILE_SIZE_X, mapInfo->tile_Count.y * TILE_SIZE_Y);
					}
				}

				BT_FindNoTile = true;
			}

			// �� ��ư�� �����ٸ�
			if (PtInRect(&BT_Up, _ptMouse) && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true; // �ߺ� Ŭ�� ���� ���͹�

				// ��׶��� ��ư�� �������� ����
				if (BT_Type == BUTTON_TYPE::BACKGROUND)
				{
					// ��׶��� ���̾� ī��Ʈ�� �ٲ��.
					mapInfo->_layer_Cnt--;
					if (mapInfo->_layer_Cnt < 0) mapInfo->_layer_Cnt = BACKGROUND_LAYER_COUNT - 1;	// ���� ī��Ʈ�� 0 ���Ϸ� �ȴٸ� ī��Ʈ �ִ�ġ�� �ٲ��ش�.
				}

				// ��Ʈ ���� ��ư�� �������� ����
				if (BT_Type == BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{

					if (mapInfo->tile_Count.y > TILE_COUNT_Y)
					{
						// Ÿ�� ��Ʈ�� y ������ 1�� �پ���.

						// y���� ����
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

			// �ٿ� ��ư�� �����ٸ�
			if (PtInRect(&BT_Down, _ptMouse) && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true; // �ߺ� Ŭ�� ���� ���͹�

				// ��׶��� ��ư�� �������� ����
				if (BT_Type == BUTTON_TYPE::BACKGROUND)
				{
					// ��׶��� ���̾� ī��Ʈ�� �ٲ��.
					mapInfo->_layer_Cnt++;
					if (mapInfo->_layer_Cnt == BACKGROUND_LAYER_COUNT)	mapInfo->_layer_Cnt = 0;	// ���� ī��Ʈ�� �ִ밡 �ȴٸ� 0���� �ǵ��ư���.
				}

				// ��Ʈ �߰� ��ư�� �������� ����
				if (BT_Type == BUTTON_TYPE::RECT_ADD_OR_MINUS)
				{
					// Ÿ�� ��Ʈ�� y ������ 1�� �þ��.

					// y���� �߰������ش�.
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

			// ���̾� ���̳ʽ� ��ư�� �����ٸ�
			if (PtInRect(&BT_Minus, _ptMouse) && BT_Type == BUTTON_TYPE::BACKGROUND && !next_Prev_Push_Okay)
			{
				next_Prev_Push_Okay = true; // �ߺ� Ŭ�� ���� ���͹�

				// ���� ���̾� ī��Ʈ�� �ִ� ���͸� �Ѱ� �����ش�. (���� ����� 0 �̻��϶���)
				if (vBackGround[mapInfo->_layer_Cnt].size() > 0) vBackGround[mapInfo->_layer_Cnt].erase(vBackGround[mapInfo->_layer_Cnt].end()-1);

				BT_FindNoTile = true;
			}

		
			KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// Ű �����°� �����ϱ� ����
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


// ���� �Լ�
class mapTool_Func
{
private:
	// ���꿡 ���� �Լ�
	bool	draw_Ready_BG;													// ��׶��� �׸��� �غ�
	short	draw_Cnt_BG;													// ��׶��� �׸��� ���͹�
	vector<tagSaveBackGround>	_vBackGround_Info[BACKGROUND_LAYER_COUNT];	// ��׶��� ������ �����Ѵ�.

public:
	vector<tagSaveBackGround>* get_VBackGround_Info_Address() { return _vBackGround_Info; }
	

public:
	// ����ϱ� ���� ���� �ʱ�ȭ
	void reset()
	{
		draw_Ready_BG = false;
		draw_Cnt_BG = 0;

		for (int i = 0; i < BACKGROUND_BACKCOUNT; ++i)
		{
			_vBackGround_Info[i].clear();
		}
	}


	// �⺻ Ÿ���� ����� �ش�.
	void make_Base_TileList(vector<tagTileInfo>* tileList)
	{
		tileList->clear();

		// Ÿ���� �⺻ ��Ʈ�� ����� �ش�.
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

	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.
	void camera_In_FindTile()
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.
	}

	// ī�޶� �ȿ� ���� ��Ʈ�� ��� �Ѵ�.
	void show_Camera_In_Tile(unsigned short sizeX, unsigned short sizeY, HDC getMemDC, vector<tagTileInfo>* _vTileList)
	{
		// ī�޶��� ������ �����Ѵ�. (�����Ҷ� �����ϰ� ����ϱ� ���ؼ�)
		POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

		char testNum[100];

		// ��Ʈ�� ����Ѵ�.
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

	

	// �ȷ�Ʈ�� ��� �Ѵ�.
	void show_Pallet(HDC getMemDC, BUTTON_TYPE button, tagPallets* pallet, short layerCnt)
	{
		switch (button)
		{
		case BUTTON_TYPE::SAVE:

			break;

		case BUTTON_TYPE::LOAD:

			break;

		case BUTTON_TYPE::GROUND:

			// �ȷ�Ʈ �׵θ� ���
			pallet->show_Pallet(getMemDC, button);

			for (int i = 0; i < GROUND_SIZEX * GROUND_SIZEY; ++i)
			{
				// ���� �̹��� ��� 
				IMAGEMANAGER->findImage(pallet->ImgName)->frameRender(getMemDC, pallet->pallet.Ground_Pallet[i].rc.left, pallet->pallet.Ground_Pallet[i].rc.top,
					pallet->pallet.Ground_Pallet[i].frame.x, pallet->pallet.Ground_Pallet[i].frame.y);
				

				// ��Ʈ ���
				IMAGEMANAGER->findImage("tile_Rect")->render(getMemDC, pallet->pallet.Ground_Pallet[i].rc.left, pallet->pallet.Ground_Pallet[i].rc.top);
			}
			break;

		case BUTTON_TYPE::BACKGROUND:

			// �ȷ�Ʈ �׵θ� ���
			pallet->show_Pallet(getMemDC, button);

			for (int i = 0; i < BACKGROUND_COUNTX * BACKGROUND_COUNTY; ++i)
			{
				// ���� �̹��� ��� 
				IMAGEMANAGER->findImage(pallet->ImgName)->frameRender(getMemDC, pallet->pallet.back_Ground_Pallet[i].rc.left, pallet->pallet.back_Ground_Pallet[i].rc.top,
					pallet->pallet.back_Ground_Pallet[i].frame.x, pallet->pallet.back_Ground_Pallet[i].frame.y);


				// ��Ʈ ���
				IMAGEMANAGER->findImage("tile_Rect_200")->render(getMemDC, pallet->pallet.back_Ground_Pallet[i].rc.left, pallet->pallet.back_Ground_Pallet[i].rc.top);
			}

			// ���̾� ��ġ ���
			for (int i = 0; i < 5; ++i)
			{
				// ���̾� ��ġ ��Ʈ
				//Rectangle(getMemDC, pallet->Layer[i]);

				// ���̾� �̹��� ���
				if (i == layerCnt)	IMAGEMANAGER->findImage("back_Ground_Select_Pointer")->render(getMemDC, pallet->Layer[i].left, pallet->Layer[i].top);
				else				IMAGEMANAGER->findImage("back_Ground_Select")->render(getMemDC, pallet->Layer[i].left, pallet->Layer[i].top);
			}



			break;
		}
	}
	
	// ������ �̹����� Ÿ�Ͽ� �����Ѵ�.
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
								(*TileList)[i].useTile = true;	// �� Ÿ���� ������̶�� ��
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

								// �� Ÿ���� ��ǥ�� �� �׳� �׷������°� ���?
								// �� ��ǥ�� ���Ϳ� �����ϰ� �̹��� ������ ������ �ִ� ����
								// ���ﶧ�� �ڿ������� �ϳ��� ����°����� 
								// Ŭ���Ҷ����� �þ�⸸ �ϰ� 
								// �ѹ����� Ŭ���ϰ� �ٲ����
								draw_Ready_BG = true;

								tagSaveBackGround BG_Info;
								BG_Info.imageName = pallet.imageName.backGroundImgName;
								BG_Info.rc = (*TileList)[i].rc;	// ����� �ѷ��� ��ǥ
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
								// ���� �Ӽ��� �־��ش�.
								(*TileList)[i].tile_Collision_Type = COLLISION_TILE_TYPE::FOOTHOLD_TYPE;
							}
						}
						break;

					case BUTTON_TYPE::WALLTYPE_CHECK:
						for (int i = 0; i < mapInfo->tile_Count.x * mapInfo->tile_Count.y; ++i)
						{
							if (PtInRect(&(*TileList)[i].rc, _ptMouse_Ver2))
							{
								// �� �Ӽ��� �־��ش�.
								(*TileList)[i].tile_Collision_Type = COLLISION_TILE_TYPE::WALL_TYPE;
							}
						}
						break;

					case BUTTON_TYPE::TRAPTYPE_CHECK:
						for (int i = 0; i < mapInfo->tile_Count.x * mapInfo->tile_Count.y; ++i)
						{
							if (PtInRect(&(*TileList)[i].rc, _ptMouse_Ver2))
							{
								// ���� �Ӽ��� �־��ش�.
								(*TileList)[i].tile_Collision_Type = COLLISION_TILE_TYPE::TRAP_TYPE;
							}
						}
						break;
				}

				KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// Ű �����°� �����ϱ� ����
			}
		}
	}




	// ���̴� �κ��� Ÿ���� ������ش�.
	void show_TileImg(HDC getMemDC ,vector<tagTileInfo>* _vTileList, tagMapInfo mapInfo)
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.

		// ��׶��带 �׷��ش�.
		for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
		{
			if (_vBackGround_Info[i].size() > 0)	// �ش� ���Ͱ� 0�̻��̿��߸� ����.
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

		// ���콺�� Ŭ���� Ÿ���� ã���ش�. (�� ȭ�鿡 �ִ� Ÿ�ϸ� ã�Ƽ�)
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

				// �� ���� Ÿ���� �����Ѵ�.
				if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
				{
					// �� �׶��带 �׷��ش�.
					//if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::BACKGROUND)
					//{
					//	if ((*_vTileList)[y * mapInfo.tile_Count.x + x].useTile)
					//	{
					//		IMAGEMANAGER->findImage((*_vTileList)[y * mapInfo.tile_Count.x + x].tileName.backGroundImgName)->render(getMemDC, rc.left, rc.top);
					//		
					//	}
					//}

					// ������ �׷��ش�.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
					{
						if ((*_vTileList)[y * mapInfo.tile_Count.x + x].useTile)
						{
						
							IMAGEMANAGER->findImage((*_vTileList)[y * mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
								(*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.x, (*_vTileList)[y * mapInfo.tile_Count.x + x].frame.ground.y);
						}
					}

					// ���ڸ� �׷��ش�.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
					{
					
					}
				}

				// �浹 Ÿ���� ���ٸ� �����Ѵ�.
				if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Collision_Type != COLLISION_TILE_TYPE::NONE_TYPE)
				{
					// ���� Ÿ���� ǥ�����ش�.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
					{
						IMAGEMANAGER->findImage("footHoldType_Check")->render(getMemDC, (*_vTileList)[y * mapInfo.tile_Count.x + x].rc.left, (*_vTileList)[y * mapInfo.tile_Count.x + x].rc.top);
					}

					// �� Ÿ���� ǥ�����ش�.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
					{
						IMAGEMANAGER->findImage("wallType_Check")->render(getMemDC, (*_vTileList)[y * mapInfo.tile_Count.x + x].rc.left, (*_vTileList)[y * mapInfo.tile_Count.x + x].rc.top);
					}

					// ���� Ÿ���� ǥ�����ش�.
					if ((*_vTileList)[y * mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::TRAP_TYPE)
					{
						IMAGEMANAGER->findImage("trapType_Check")->render(getMemDC, (*_vTileList)[y * mapInfo.tile_Count.x + x].rc.left, (*_vTileList)[y * mapInfo.tile_Count.x + x].rc.top);
					}
				}
			}
		}
	}
};