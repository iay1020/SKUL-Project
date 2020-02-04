#pragma once

// 타일의 갯수
#define TILE_COUNT_X 100
#define TILE_COUNT_Y 100

// 한 타일의 사이즈
#define TILE_SIZE_X 50
#define TILE_SIZE_Y 50

// 타일의 타입
enum class TILE_TYPE
{
	EMPTY,			// NULL
	PLAYER,			// 플레이어
	ENEMY,			// 에너미
	START_DOOR,		// 스타트 지점	
	EXIT_DOOR,		// 탈출 지점
	TERRAIN,		// 지형
	DECORATION,		// 데코레이션 오브젝트
	ITEM			// 아이템 오브젝트

};

// 에너미 타입


// 지형 이미지의 갯수

// 오브젝트 이미지의 갯수

// 캐릭터 이미지의 갯수



// 타일 정보를 저장 할 구조체
struct tagTileInfo
{
	POINTFLOAT			center;		// 타일의 중점을 담는다.
	RECT				rc;			// 타일의 렉트를 담는다.
	unsigned short		idx, idy;	// 타일의 인덱스를 담는다. (범위 : 0 ~ 65535)
	
};