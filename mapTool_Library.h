#pragma once

// Ÿ���� ����
#define TILE_COUNT_X 100
#define TILE_COUNT_Y 100
#define TILE_TOTAL TILE_COUNT_X * TILE_COUNT_Y

// �� Ÿ���� ������
#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64

// Ÿ���� Ÿ��
enum class TILE_TYPE
{
	EMPTY,									// NULL
	PLAYER,									// �÷��̾�
	ENEMY,									// ���ʹ�
	START_DOOR,								// ��ŸƮ ����	
	EXIT_DOOR,								// Ż�� ����
	GROUND,									// ��
	DECORATION,								// ���ڷ��̼� ������Ʈ
	HIT_OBJECT,								// Ÿ�� ������ ������Ʈ
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