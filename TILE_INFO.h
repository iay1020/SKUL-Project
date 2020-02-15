#pragma once

// 타일의 갯수(가장 기본 타일의 갯수이다. 맵툴에서 변경 가능하다. 정확한 타일의 갯수는 맵 정보에 넣어둘 것)
// 최소 사이즈 x 33, y 28 (WINSIZEX, WINSIZEY 예외처리에 걸리는 최소 사이즈)
#define TILE_COUNT_X 25
#define TILE_COUNT_Y 15
#define TILE_TOTAL TILE_COUNT_X * TILE_COUNT_Y

// 한 타일의 사이즈
#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64

// 땅(지형) 가로 세로 크기
#define GROUND_SIZEX 9
#define GROUND_SIZEY 5
#define GROUND_IMAGE_CONUT 5	 // 땅(지형) 이미지 수량

// 오브젝트 이미지의 갯수

// 캐릭터 이미지의 갯수

// 백그라운드 가로 세로 크기
#define BACKGROUND_COUNTX 3
#define BACKGROUND_COUNTY 3
#define BACKGROUND_BACKCOUNT	3	 // 백그라운드 백이미지 수량
#define BACKGROUND_CENTERCOUNT	3	 // 백그라운드 센터이미지 수량
#define BACKGROUND_FRONTCOUNT	3	 // 백그라운드 앞 이미지 수량
#define BACKGROUND_SIZEX 200
#define BACKGROUND_SIZEY 200
#define BACKGROUND_LAYER_COUNT 5		// 백그라운드 레이어 갯수


// 타일의 타입
enum class TILE_TYPE
{
	EMPTY,									// NULL
	PLAYER,									// 플레이어
	ENEMY,									// 에너미
	DOOR,									// 도어	
	GROUND,									// 땅
	DECORATION,								// 데코레이션 오브젝트
	HIT_OBJECT,								// 타격 가능한 오브젝트
	ITEM,									// 아이템 오브젝트
	TRAP,									// 함정 타일
	BACKGROUND								// 백그라운드 타일
};