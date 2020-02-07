#pragma once

// 타일의 갯수(가장 기본 타일의 갯수이다. 맵툴에서 변경 가능하다. 정확한 타일의 갯수는 맵 정보에 넣어둘 것)
// 최소 사이즈 x 33, y 28 (WINSIZEX, WINSIZEY 예외처리에 걸리는 최소 사이즈)
#define TILE_COUNT_X 90
#define TILE_COUNT_Y 28
#define TILE_TOTAL TILE_COUNT_X * TILE_COUNT_Y

// 한 타일의 사이즈
#define TILE_SIZE_X 64
#define TILE_SIZE_Y 64

// 땅(지형) 이미지의 갯수
#define GROUND_SIZEX 9
#define GROUND_SIZEY 4

// 오브젝트 이미지의 갯수

// 캐릭터 이미지의 갯수