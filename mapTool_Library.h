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
	tag_U_INT	index;						// �ε����� ������ ��´�. (unsigned int��)
	RECT		rc;							// ��Ʈ�� ������ ��´�.
	tag_U_INT	frame;						// ������ x, y�� ��´�.
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
