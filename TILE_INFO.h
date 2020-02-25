#pragma once

// Ÿ���� ����(���� �⺻ Ÿ���� �����̴�. �������� ���� �����ϴ�. ��Ȯ�� Ÿ���� ������ �� ������ �־�� ��)
// �ּ� ������ x 33, y 28 (WINSIZEX, WINSIZEY ����ó���� �ɸ��� �ּ� ������)
#define TILE_COUNT_X 25
#define TILE_COUNT_Y 15
#define TILE_TOTAL TILE_COUNT_X * TILE_COUNT_Y

// �� Ÿ���� ������
#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64

// ��(����) ���� ���� ũ��
#define GROUND_SIZEX 9
#define GROUND_SIZEY 5
#define GROUND_IMAGE_CONUT 5	 // ��(����) �̹��� ����



// ������Ʈ �̹����� ����

// ĳ���� �̹����� ����
#define CHARACTER_SIZEX 2
#define CHARACTER_SIZEY 2


// ��׶��� ���� ���� ũ��
#define BACKGROUND_COUNTX 3
#define BACKGROUND_COUNTY 3
#define BACKGROUND_BACKCOUNT	3	 // ��׶��� ���̹��� ����
#define BACKGROUND_CENTERCOUNT	3	 // ��׶��� �����̹��� ����
#define BACKGROUND_FRONTCOUNT	3	 // ��׶��� �� �̹��� ����
#define BACKGROUND_SIZEX 200
#define BACKGROUND_SIZEY 200
#define BACKGROUND_LAYER_COUNT 5		// ��׶��� ���̾� ����


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
	ITEM,									// ������ ������Ʈ
	TRAP,									// ���� Ÿ��
	BACKGROUND								// ��׶��� Ÿ��
};

// �浹�� Ÿ�� Ÿ��
enum class COLLISION_TILE_TYPE
{
	NONE_TYPE,			// �ƹ��͵� ���� Ÿ��
	FOOTHOLD_TYPE,		// ���� Ÿ��
	WALL_TYPE,			// �� Ÿ��
	TRAP_TYPE			// ���� Ÿ��
};