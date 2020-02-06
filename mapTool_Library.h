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

// ��(����) �̹����� ����
#define GROUND_SIZEX 9
#define GROUND_SIZEY 4

// ��(����) Ÿ��
enum class GROUND_TYPE
{
	EMPTY_GROUND,							// NULL
	TUTORIAL_GROUND,						// Ʃ�丮�� ��
	STAGE1_GROUND,							// �������� 1 ��
	STAGE2_GROUND							// �������� 2 ��
};

// ������Ʈ �̹����� ����

// ĳ���� �̹����� ����



// ��� �̹��� ī��Ʈ��
enum BACKGROUND_CNT
{
	NONE,				// �������
	ONE,				// �Ѱ�
	TWO,				// �ΰ�
	THREE				// ����
};

// ��� ���������� ����
struct tagLoop_Variable
{
	unsigned short LoopX_BG_0;		// �� �ڿ� �ִ� �� �׶��� ������ ����
	unsigned short LoopX_BG_1;		// �� �տ� �� �׶��� ������ ����
	unsigned short LoopX_BG_2;		// �� �տ� �ִ� �� �׶��� ������ ����

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

	tagLoop_Variable	loop;						// �������� ����� ����

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

		loop.LoopX_BG_0 = loop.LoopX_BG_1 = loop.LoopX_BG_2 = 0;
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


// Ÿ�� ������ ���� �� ����ü
struct tagTileInfo
{
	POINTFLOAT			center;				// Ÿ���� ������ ��´�.
	RECT				rc;					// Ÿ���� ��Ʈ�� ��´�.
	unsigned short		idx, idy;			// Ÿ���� �ε����� ��´�. (���� : 0 ~ 65535)

	TILE_TYPE			tile_Type;			// Ÿ���� Ÿ���� ��´�.
	GROUND_TYPE			ground;				// ��(����) Ÿ���� ��´�.

	unsigned short	    frameX, frameY;		// �̹��� �������� ��´�.

	void reset_Tile()
	{
		center.x = center.y = 0;
		idx = idy = 0;
		frameX = frameY = 0;
		tile_Type = TILE_TYPE::EMPTY;
		ground = GROUND_TYPE::EMPTY_GROUND;
	}
};

// �ȷ�Ʈ �̵��� ���� ��Ʈ
struct tagPalletBar
{
	RECT Character_Pallet_Bar;				// ĳ���� �ȷ�Ʈ ��
	RECT Door_Pallet_Bar;					// ���� �ȷ�Ʈ ��
	RECT Ground_Pallet_Bar;					// �ٴ� �ȷ�Ʈ ��
	RECT Dcoration_Pallet_Bar;				// ���� �ȷ�Ʈ ��
	RECT Hit_Object_Bar;					// �ı� ������Ʈ ��
	RECT Item_Bar;							// ������ ������Ʈ ��
};

// �ȷ�Ʈ�� ������ ��´�.
struct tagPallet_INFO
{
	tag_U_Short	index;						// �ε����� ������ ��´�. (unsigned int��)
	RECT		rc;							// ��Ʈ�� ������ ��´�.
	tag_U_Short	frame;						// ������ x, y�� ��´�.
};

// �ȷ�Ʈ�� ������ ��´�.
struct tagPallets
{
	tagPallet_INFO Character_Pallet;		// ĳ���� �ȷ�Ʈ
	tagPallet_INFO Door_Pallet;				// ���� �ȷ�Ʈ
	tagPallet_INFO Ground_Pallet;			// ���� �ȷ�Ʈ
	tagPallet_INFO Dcoration_Pallet;		// ��� �ȷ�Ʈ
	tagPallet_INFO Hit_Object_Pallet;		// �ı� ������Ʈ �ȷ�Ʈ
	tagPallet_INFO Item_Bar;				// ������ �ȷ�Ʈ
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
				new_Tile->idx = x;
				new_Tile->idy = y;
				new_Tile->rc = RectMake(new_Tile->idx * TILE_SIZE_X, new_Tile->idy * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y);
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
	void show_BackImg(tagMapInfo mapInfo, HDC getMemDC)
	{
		// ī�޶��� ������ �����Ѵ�. (�����Ҷ� �����ϰ� ����ϱ� ���ؼ�)
		POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

		// ����� ���� ��Ʈ ũ�⸦ ���Ѵ�.
		RECT camera_Rc = RectMake(0, 0, IMAGEMANAGER->findImage(mapInfo.backImgName)->getWidth(), IMAGEMANAGER->findImage(mapInfo.backImgName)->getHeight());
		camera_Rc.left -= camera.x;
		camera_Rc.right -= camera.x;
		camera_Rc.top -= camera.y;
		camera_Rc.bottom -= camera.y;

		// ��� ������ ���� ����� �ٸ���.
		if (mapInfo.backGround_Count >= 1)			// ��� ������ 3�� ����
		{
			IMAGEMANAGER->findImage(mapInfo.backImgName)->loopRender(getMemDC,
				&camera_Rc, mapInfo.loop.LoopX_BG_0, 0);
		}

		if (mapInfo.backGround_Count >= 2)		// ��� ������ 2�� ����
		{
			IMAGEMANAGER->findImage(mapInfo.centerImgName)->loopRender(getMemDC,
				&camera_Rc, mapInfo.loop.LoopX_BG_1, 0);
		}

		if (mapInfo.backGround_Count >= 3)		// ��� ������ 1�� ����
		{

		}IMAGEMANAGER->findImage(mapInfo.frontImgName)->loopRender(getMemDC,
			&camera_Rc, mapInfo.loop.LoopX_BG_2, 0);

	}
};