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
	ITEM							// ������ ��ư�� �����ٸ�
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

	POINTFLOAT			center;						// ���� ��ǥ�� ����
	RECT				rc;							// ��Ʈ ��ǥ�� ����
		
	// �� ���� �ʱ�ȭ
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

	void reset_Tile()
	{
		center.x = center.y = 0;
		index.x  = index.y = 0;
		frame.ground.x = frame.ground.y = 0;
		tile_Type = TILE_TYPE::EMPTY;
		ground = GROUND_TYPE::EMPTY_GROUND;
	}
};

// �ȷ�Ʈ �̵��� ���� ��Ʈ
struct tagPalletBar
{
	RECT Character_Pallet_Bar;											// ĳ���� �ȷ�Ʈ ��
	RECT Door_Pallet_Bar;												// ���� �ȷ�Ʈ ��
	RECT Ground_Pallet_Bar;												// �ٴ� �ȷ�Ʈ ��
	RECT Dcoration_Pallet_Bar;											// ���� �ȷ�Ʈ ��
	RECT Hit_Object_Bar;												// �ı� ������Ʈ ��
	RECT Item_Bar;														// ������ ������Ʈ ��

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
};

// �ȷ�Ʈ�� ������ ��´�.
struct tagPalletKinds
{
	tagPallet_INFO	Character_Pallet;									// ĳ���� �ȷ�Ʈ
	tagPallet_INFO	Door_Pallet;										// ���� �ȷ�Ʈ
	tagPallet_INFO	Ground_Pallet[GROUND_SIZEX * GROUND_SIZEY];			// ���� �ȷ�Ʈ
	tagPallet_INFO	Dcoration_Pallet;									// ��� �ȷ�Ʈ
	tagPallet_INFO	Hit_Object_Pallet;									// �ı� ������Ʈ �ȷ�Ʈ
	tagPallet_INFO	Item_Bar;											// ������ �ȷ�Ʈ
};

// �ȷ�Ʈ�� ������ ��´�.
struct tagPallets
{
	tagPalletBar	palletBar;											// �ȷ�Ʈ ��
	tagPalletKinds	pallet;												// �ȷ�Ʈ

	// �ȷ�Ʈ �⺻ ����
	void setting()
	{
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
			}
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
	void show_Pallet(HDC getMem)
	{
		// �ȷ�Ʈ �� ��Ʈ ���
		Rectangle(getMem, palletBar.Ground_Pallet_Bar);

		// �ȷ�Ʈ ��Ʈ ���
		for (int i = 0; i < GROUND_SIZEX * GROUND_SIZEY; ++i)
			Rectangle(getMem, pallet.Ground_Pallet[i].rc);
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
		ITEM							// ������ ��ư�� �����ٸ�
	};

	// ��� ����
	BUTTON_TYPE		BT_Type;			// Ŭ���� ��ư�� �����Ѵ�.

	// �ʱ�ȭ �Լ�
	void reset()
	{
		// �ƹ��͵� Ŭ������ ���� ���´� NONE
		BT_Type = BUTTON_TYPE::NONE;

		// ��ư ��Ʈ�� ��ġ�� ��´�.
		BT_Save = RectMake(10, 10, 52, 52);
		BT_Load = RectMake(72, 10, 52, 52);
		BT_Ground = RectMake(10 * 3 + 52 * 2, 10, 52, 52);
	}

	// ��ư �̹����� �׷��ش�. (+ ��Ʈ)
	void show_Button(HDC getDC)
	{
		// �׽�Ʈ�� ��Ʈ ���
		if (KEYMANAGER->isToggleKey(VK_NUMPAD2))
		{
			Rectangle(getDC, BT_Save);
			Rectangle(getDC, BT_Load);
			Rectangle(getDC, BT_Ground);
		}

		// ��ư �̹��� ���
		IMAGEMANAGER->findImage("save_Icon")->render(getDC, BT_Save.left, BT_Save.top);
		IMAGEMANAGER->findImage("load_Icon")->render(getDC, BT_Load.left, BT_Load.top);
		IMAGEMANAGER->findImage("ground_Icon")->render(getDC, BT_Ground.left, BT_Ground.top);
	}

	// ��ư Ŭ�� �Լ�
	void click_Button()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			// ��ư�� Ŭ���ϸ� �ش� Ÿ������ �����Ѵ�.
			if (PtInRect(&BT_Save, _ptMouse)) BT_Type = BUTTON_TYPE::SAVE;
			if (PtInRect(&BT_Load, _ptMouse)) BT_Type = BUTTON_TYPE::LOAD;
			if (PtInRect(&BT_Ground, _ptMouse)) BT_Type = BUTTON_TYPE::GROUND;
		}	
	}
};


// ���� �Լ�
class mapTool_Func
{

public:
	// �⺻ Ÿ���� ����� �ش�.
	void make_Base_TileList(vector<tagTileInfo*>* tileList)
	{
		// Ÿ���� �⺻ ��Ʈ�� ����� �ش�.
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

	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.
	void camera_In_FindTile()
	{
		CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.
	}

	// ī�޶� �ȿ� ���� ��Ʈ�� ��� �Ѵ�.
	void show_Camera_In_Tile(unsigned short sizeX, unsigned short sizeY, HDC getMemDC, vector<tagTileInfo*> _vTileList)
	{
		// ī�޶��� ������ �����Ѵ�. (�����Ҷ� �����ϰ� ����ϱ� ���ؼ�)
		POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

		// ���ϴ� ��ġ�� �׷����� �� ��Ʈ�� ����� �ش�.
		RECT camera_Rc = RectMake(0, 0, sizeX, sizeY);
		camera_Rc.left -= camera.x;
		camera_Rc.right -= camera.x;
		camera_Rc.top -= camera.y;
		camera_Rc.bottom -= camera.y;

		// ��Ʈ�� ����Ѵ�.
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

	// ����� ��� �Ѵ�.
	void show_BackImg(tagMapInfo* mapInfo, HDC getMemDC)
	{
		// ī�޶��� ������ �����Ѵ�. (�����Ҷ� �����ϰ� ����ϱ� ���ؼ�)
		POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

		// ����� ���� ��Ʈ ũ�⸦ ���Ѵ�.
		RECT camera_Rc = RectMake(0, 0, IMAGEMANAGER->findImage(mapInfo->backImgName)->getWidth(), IMAGEMANAGER->findImage(mapInfo->backImgName)->getHeight());
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
};