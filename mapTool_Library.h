#pragma once
#include "stdafx.h"

// Ÿ���� Ÿ��
enum class TILE_TYPE
{
	EMPTY,									// NULL
	PLAYER,									// �÷��̾�
	ENEMY,									// ���ʹ�
	DOOR,									// ����	
	GROUND,									// ��
	DECORATION,								// ���ڷ��̼� ������Ʈ
	HIT_OBJECT,								// Ÿ�� ������ ������Ʈ
	TRAP,									// ���� Ÿ��
	ITEM									// ������ ������Ʈ

};

// ���ʹ� Ÿ��

// ��(����) Ÿ��
enum class GROUND_TYPE
{
	EMPTY_GROUND,							// NULL
	TUTORIAL_GROUND,						// Ʃ�丮�� ��
	STAGE1_GROUND,							// �������� 1 ��
	STAGE2_GROUND							// �������� 2 ��
};



// ��� �̹��� ī��Ʈ��
enum BACKGROUND_CNT
{
	NONE,				// �������
	ONE,				// �Ѱ�
	TWO,				// �ΰ�
	THREE				// ����
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
	TRAP							// Ʈ�� ��ư�� �����ٸ�
};

// �ȷ�Ʈ �̵��� ���� ��Ʈ
struct tagPalletBar
{
	RECT Ground_Pallet_Bar;												// �ٴ� �ȷ�Ʈ ��
	RECT Dcoration_Pallet_Bar;											// ���� �ȷ�Ʈ ��
	RECT Hit_Object_Bar;												// �ı� ������Ʈ ��
	RECT Door_Pallet_Bar;												// ���� �ȷ�Ʈ ��
	RECT Character_Pallet_Bar;											// ĳ���� �ȷ�Ʈ ��
	RECT Item_Bar;														// ������ ������Ʈ ��
	RECT Trap_Bar;														// Ʈ�� �ȷ�Ʈ ��

	// �ȷ�Ʈ �ٸ� �̵� ��ų �Լ� (��� �ߴ�)
	void move_Bar()
	{

	}
};

// �ȷ�Ʈ�� ������ ��´�.
struct tagPallet_INFO
{
	RECT		rc;														// ��Ʈ�� ������ ��´�.
	tag_U_Short	frame;													// ������ x, y�� ��´�.
	GROUND_TYPE	ground_Type;											// �׶��� Ÿ���� ��´�.

	// �Ź� Ÿ���� ������ ���� Ÿ���� �ʱ�ȭ �Ҷ� ���
	void reset_Type()
	{
		ground_Type = GROUND_TYPE::EMPTY_GROUND;
	}
};

// �ȷ�Ʈ�� ������ ��´�.
struct tagPalletKinds
{
	tagPallet_INFO	Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY];			// ���� �ȷ�Ʈ
	tagPallet_INFO	Dcoration_Pallet[2];								// ��� �ȷ�Ʈ
	tagPallet_INFO	Hit_Object_Pallet[2];								// �ı� ������Ʈ �ȷ�Ʈ
	tagPallet_INFO	Door_Pallet[2];										// ���� �ȷ�Ʈ
	tagPallet_INFO	Character_Pallet[2];								// ĳ���� �ȷ�Ʈ
	tagPallet_INFO	Item_Pallet[2];										// ������ �ȷ�Ʈ
	tagPallet_INFO  Trap_Pallet[2];										// Ʈ�� �ȷ�Ʈ
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
	string				mapName;					// ���� �̸��� �����Ѵ�.
	tag_U_Short			tile_Size;					// Ÿ�� ����� �����Ѵ�.
	tag_U_Short			tile_Count;					// Ÿ���� ������ �����Ѵ�.
	
	char				backGround_Count;			// ����� ���� (�ִ� ������ 3���ϱ� char����)
	string				backImgName;				// �� ���� ��� �̹��� Ű��
	string				centerImgName;				// �߰� ��� �̹��� Ű��
	string				frontImgName;				// ���� ��� �̹��� Ű��

	tagLoop_Variable*	loop;						// �������� ����� ����
		
	// �� ���� �ʱ�ȭ
	void reset_MapInfo()
	{
		mapName = {};
		tile_Size.x = TILE_SIZE_X;		// ���̽� Ÿ���� ����� �����Ѵ�.
		tile_Size.y = TILE_SIZE_Y;		// ���̽� Ÿ���� ����� �����Ѵ�.
		tile_Count.x = TILE_COUNT_X;	// ���̽� Ÿ���� ������ �����Ѵ�.
		tile_Count.y = TILE_COUNT_Y;	// ���̽� Ÿ���� ������ �����Ѵ�.

		backGround_Count = 0;
		backImgName = {};
		centerImgName = {};
		frontImgName = {};

		loop = new tagLoop_Variable;
		loop->reset_Func();
	}

	// �� ��� �߰�
	void add_BackGround(string mapName)
	{
		// ī��Ʈ ���� ���������� ��쿡�� �Լ��� ����������.
		if (backGround_Count == 4) return;

		backGround_Count++;	// ������ �߰� �߶����� �����Ѵ�.

		if (backGround_Count == ONE)
		{
			backImgName = mapName;		// ���� �̸��� �־��ش�.
		}

		if (backGround_Count == TWO)
		{
			centerImgName = mapName;	// ���� �̸��� �־��ش�.
		}

		if (backGround_Count == THREE)
		{
			frontImgName = mapName;		// ���� �̸��� �־��ش�.
		}

	}

	// �� ��� ��ü
	void change_BackGround(string mapName, signed short num)
	{
		// ��ü�ϱ� ���ϴ� �� �̸���, ��ü �Ϸ��� ��ġ�� �޾ƿ´�.
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


// Ÿ���� �̹��� �������� ���� ���� ����ü
struct tagTileFrame
{
	tag_U_Short		ground;					// ���� �̹��� �������� ��°�
};


// Ÿ�� ������ ���� �� ����ü
struct tagTileInfo
{
	POINTFLOAT			center;				// Ÿ���� ������ ��´�.
	RECT				rc;					// Ÿ���� ��Ʈ�� ��´�.
	tag_U_Short			index;				// Ÿ���� �ε����� ��´�. (���� : 0 ~ 65535)

	TILE_TYPE			tile_Type;			// Ÿ���� Ÿ���� ��´�.
	GROUND_TYPE			ground;				// ��(����) Ÿ���� ��´�.

	tagTileFrame 	    frame;				// �̹��� �������� ��´�.

	// Ÿ���� �⺻ ���� ���ش�. (����ش�)
	void reset_Tile()
	{
		center.x = center.y = 0;
		index.x  = index.y = 0;
		frame.ground.x = frame.ground.y = 0;
		tile_Type = TILE_TYPE::EMPTY;
		ground = GROUND_TYPE::EMPTY_GROUND;
	}
};

// �ȷ�Ʈ�� ������ ��´�.
struct tagPallets
{
	tagPalletBar	palletBar;											// �ȷ�Ʈ ��
	tagPalletKinds	pallet;												// �ȷ�Ʈ
	tagPallet_INFO	current;											// Ŭ�� �� �̹��� ����

	// �ȷ�Ʈ �⺻ ����
	void setting()
	{
		// ��������������������������������������������������� ������������������������������������������������������������
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

				// �ȷ�Ʈ �⺻ �ѹ�
				pallet.Ground_Pallet->ground_Type = GROUND_TYPE::TUTORIAL_GROUND;
			}
		}
		// ��������������������������������������������������������������������������������������������������������������

		// Ŭ�� �� ������ ��� ������ ����ش�.
		current.frame.x = current.frame.y = 0;
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

	// Ŭ�� �� �ȷ�Ʈ�� ������ �����Ѵ�.
	void click_PalletInfo_Save(BUTTON_TYPE button)
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
							current.reset_Type();	// Ÿ���� ���� �ϱ� ���� ���� ������ ����

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

	// �ȷ�Ʈ ��ư
	RECT			BT_Ground;			// ���� �̹��� ��ư
	RECT			BT_Decoration;		// ���ڷ��̼� �̹��� ��ư
	RECT			BT_Hit_Object;		// �ı� ���� �̹��� ��ư
	RECT			BT_Door;			// �� �̹��� ��ư
	RECT			BT_Character;		// ĳ���� �̹��� ��ư
	RECT			BT_Item;			// ������ �̹��� ��ư
	RECT			BT_Trap;			// ���� �̹��� ��ư

	// ��� ����
	BUTTON_TYPE		BT_Type;			// Ŭ���� ��ư�� �����Ѵ�.

	// ���� ����
	bool			BT_Type_B;			// � ��ư�� Ŭ�� �ߴ��� üũ �Ҷ� ���


	// �ʱ�ȭ �Լ�
	void reset()
	{
		// ���� �ʱ�ȭ
		BT_Type_B = false;

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

	}

	// ����, ���� ��ư�� ��ġ�� ���� ���ش�.
	void reset_Next_Prev_Pos(tagPalletKinds pallet)
	{
		switch (BT_Type)
		{
		case BUTTON_TYPE::GROUND:
			// prev ��ư ��ġ
			BT_Prev = RectMake(pallet.Ground_Pallet[GROUND_SIZEX * (GROUND_SIZEY - 1)].rc.left, pallet.Ground_Pallet[GROUND_SIZEX * (GROUND_SIZEY - 1)].rc.bottom,
				32, 30);

			// next ��ư ��ġ
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
			Rectangle(getDC, BT_Next);
			Rectangle(getDC, BT_Prev); 
		}

		// ��ư �̹��� ���
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

	// ��ư Ŭ�� �Լ�
	void click_Button()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// ��ư�� Ŭ���ϸ� �ش� Ÿ������ �����Ѵ�.
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

			KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// Ű �����°� �����ϱ� ����
		}	
	}
};


// ���� �Լ�
class mapTool_Func
{

public:
	// �⺻ Ÿ���� ����� �ش�.
	void make_Base_TileList(vector<tagTileInfo>* tileList)
	{
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

		// ��Ʈ�� ����Ѵ�.
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

	// ����� ��� �Ѵ�.
	void show_BackImg(tagMapInfo* mapInfo, HDC getMemDC)
	{
		// ī�޶��� ������ �����Ѵ�. (�����Ҷ� �����ϰ� ����ϱ� ���ؼ�)
		POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

		// ����� ���� ��Ʈ ũ�⸦ ���Ѵ�.
		RECT camera_Rc = RectMake(0, 0, IMAGEMANAGER->findImage(mapInfo->backImgName)->getWidth(), IMAGEMANAGER->findImage(mapInfo->backImgName)->getHeight());	

		camera.x > 560 ? camera.x = 560 : camera.x;
		camera.y > 890 ? camera.y = 890 : camera.y;

		camera_Rc.left -= camera.x;
		camera_Rc.right -= camera.x;
		camera_Rc.top -= camera.y;
		camera_Rc.bottom -= camera.y;

		// ��� ������ ���� ����� �ٸ���.
		if (mapInfo->backGround_Count >= 1)			// ��� ������ 3�� ����
		{
			IMAGEMANAGER->findImage(mapInfo->backImgName)->loopRender(getMemDC,
				&camera_Rc, mapInfo->loop->LoopX_BG_0, 0);
		}

		if (mapInfo->backGround_Count >= 2)			// ��� ������ 2�� ����
		{
			IMAGEMANAGER->findImage(mapInfo->centerImgName)->loopRender(getMemDC,
				&camera_Rc, mapInfo->loop->LoopX_BG_1, 0);
		}

		if (mapInfo->backGround_Count >= 3)			// ��� ������ 1�� ����
		{

		}IMAGEMANAGER->findImage(mapInfo->frontImgName)->loopRender(getMemDC,
			&camera_Rc, mapInfo->loop->LoopX_BG_2, 0);

	}

	// �ȷ�Ʈ�� ��� �Ѵ�.
	void show_Pallet(HDC getMemDC, BUTTON_TYPE button, tagPallets* pallet)
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
				IMAGEMANAGER->findImage("tutorial_Tile")->frameRender(getMemDC, pallet->pallet.Ground_Pallet[i].rc.left, pallet->pallet.Ground_Pallet[i].rc.top,
					pallet->pallet.Ground_Pallet[i].frame.x, pallet->pallet.Ground_Pallet[i].frame.y);

				// ��Ʈ ���
				IMAGEMANAGER->findImage("tile_Rect")->render(getMemDC, pallet->pallet.Ground_Pallet[i].rc.left, pallet->pallet.Ground_Pallet[i].rc.top);
			}
			break;
		}
	}

	// Ÿ���� ������ ��� ��Ʈ�� ���� �浹�� ���� �Լ�
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
			// �浹�� �ϳ��� �ִٸ� false
			return false;
		}

		// �浹�ϴ°� ���ٸ� true
		return true;
	}
	
	// ������ �̹����� Ÿ�Ͽ� �����Ѵ�.
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

			KEYMANAGER->setKeyDown(VK_LBUTTON, false);	// Ű �����°� �����ϱ� ����
		}
	}




	// ���̴� �κ��� Ÿ���� ������ش�.
	void show_TileImg(HDC getMemDC ,vector<tagTileInfo>* _vTileList)
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.

		// ���콺�� Ŭ���� Ÿ���� ã���ش�. (�� ȭ�鿡 �ִ� Ÿ�ϸ� ã�Ƽ�)
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

				// �� ���� Ÿ���� �����Ѵ�.
				if ((*_vTileList)[y * TILE_COUNT_X + x].tile_Type != TILE_TYPE::EMPTY)
				{

					// ������ �׷��ش�.
					if ((*_vTileList)[y * TILE_COUNT_X + x].tile_Type == TILE_TYPE::GROUND)
					{
						IMAGEMANAGER->findImage("tutorial_Tile")->frameRender(getMemDC, rc.left, rc.top,
							(*_vTileList)[y * TILE_COUNT_X + x].frame.ground.x, (*_vTileList)[y * TILE_COUNT_X + x].frame.ground.y);
					}

					// ���ڸ� �׷��ش�.
					if ((*_vTileList)[y * TILE_COUNT_X + x].tile_Type == TILE_TYPE::DECORATION)
					{

					}
				}
			}
		}
	}
};