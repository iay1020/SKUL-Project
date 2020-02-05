#pragma once
#include "stdafx.h"

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
	TRAP,									// 함정 타일
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

// 팔렛트 이동에 쓰일 렉트
struct tagPalletBar
{
	RECT Character_Pallet_Bar;				// 캐릭터 팔렛트 바
	RECT Door_Pallet_Bar;					// 도어 팔렛트 바
	RECT Ground_Pallet_Bar;					// 바닥 팔렛트 바
	RECT Dcoration_Pallet_Bar;				// 데코 팔렛트 바
	RECT Hit_Object_Bar;					// 파괴 오브젝트 바
	RECT Item_Bar;							// 아이템 오브젝트 바
};

// 팔렛트의 정보를 담는다.
struct tagPallet_INFO
{
	tag_U_INT	index;						// 인덱스의 정보를 담는다. (unsigned int형)
	RECT		rc;							// 렉트의 정보를 담는다.
	tag_U_INT	frame;						// 프레임 x, y를 담는다.
};

// 팔렛트의 종류를 담는다.
struct tagPallets
{
	tagPallet_INFO Character_Pallet;		// 캐릭터 팔렛트
	tagPallet_INFO Door_Pallet;				// 도어 팔렛트
	tagPallet_INFO Ground_Pallet;			// 지형 팔렛트
	tagPallet_INFO Dcoration_Pallet;		// 장식 팔렛트
	tagPallet_INFO Hit_Object_Pallet;		// 파괴 오브젝트 팔렛트
	tagPallet_INFO Item_Bar;				// 아이템 팔렛트
};
