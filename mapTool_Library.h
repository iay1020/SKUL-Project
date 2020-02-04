#pragma once

// Ÿ���� ����
#define TILE_COUNT_X 100
#define TILE_COUNT_Y 100

// �� Ÿ���� ������
#define TILE_SIZE_X 50
#define TILE_SIZE_Y 50

// Ÿ���� Ÿ��
enum class TILE_TYPE
{
	EMPTY,			// NULL
	PLAYER,			// �÷��̾�
	ENEMY,			// ���ʹ�
	START_DOOR,		// ��ŸƮ ����	
	EXIT_DOOR,		// Ż�� ����
	TERRAIN,		// ����
	DECORATION,		// ���ڷ��̼� ������Ʈ
	ITEM			// ������ ������Ʈ

};

// ���ʹ� Ÿ��


// ���� �̹����� ����

// ������Ʈ �̹����� ����

// ĳ���� �̹����� ����



// Ÿ�� ������ ���� �� ����ü
struct tagTileInfo
{
	POINTFLOAT			center;		// Ÿ���� ������ ��´�.
	RECT				rc;			// Ÿ���� ��Ʈ�� ��´�.
	unsigned short		idx, idy;	// Ÿ���� �ε����� ��´�. (���� : 0 ~ 65535)
	
};