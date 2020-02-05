#pragma once

// 타일의 갯수
#define TILE_COUNT_X 100
#define TILE_COUNT_Y 100
#define TILE_TOTAL TILE_COUNT_X * TILE_COUNT_Y

// 한 타일의 사이즈
#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64

// 타일의 타입
enum class TILE_TYPE
{
	EMPTY,									// NULL
	PLAYER,									// 플레이어
	ENEMY,									// 에너미
	START_DOOR,								// 스타트 지점	
	EXIT_DOOR,								// 탈출 지점
	GROUND,									// 땅
	DECORATION,								// 데코레이션 오브젝트
	HIT_OBJECT,								// 타격 가능한 오브젝트
	ITEM									// 아이템 오브젝트

};

// 에너미 타입

// 땅(지형) 이미지의 갯수
#define GROUND_SIZEX 9
#define GROUND_SIZEY 4

// 땅(지형) 타입
enum class GROUND_TYPE
{
	EMPTY_GROUND,							// NULL
	TUTORIAL_GROUND,						// 튜토리얼 땅
	STAGE1_GROUND,							// 스테이지 1 땅
	STAGE2_GROUND							// 스테이지 2 땅
};

// 오브젝트 이미지의 갯수

// 캐릭터 이미지의 갯수



// 타일 정보를 저장 할 구조체
struct tagTileInfo
{
	POINTFLOAT			center;				// 타일의 중점을 담는다.
	RECT				rc;					// 타일의 렉트를 담는다.
	unsigned short		idx, idy;			// 타일의 인덱스를 담는다. (범위 : 0 ~ 65535)

	TILE_TYPE			tile_Type;			// 타일의 타입을 담는다.
	GROUND_TYPE			ground;				// 땅(지형) 타입을 담는다.

	unsigned short	    frameX, frameY;		// 이미지 프레임을 담는다.

	void reset_Tile()
	{
		center.x = center.y = 0;
		idx = idy = 0;
		frameX = frameY = 0;
		tile_Type = TILE_TYPE::EMPTY;
		ground = GROUND_TYPE::EMPTY_GROUND;
	}
};