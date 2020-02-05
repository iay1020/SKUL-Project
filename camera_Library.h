#pragma once
#include "stdafx.h"

// unsigned int 타입의 정보를 2개 저장
struct tag_U_INT
{
	unsigned int x;
	unsigned int y;
};

// 출력 하기 원하는 타일의 인덱스를 담아둔다.
class tag_FindTile
{
protected:
	tag_U_INT start_Index;		// 시작 인덱스
	tag_U_INT end_Index;		// 마지막 인덱스
	tag_U_INT range;			// 출력 하기 원하는 범위 


public:
	tag_FindTile() {};
	~tag_FindTile() {};

	void init()
	{
		start_Index.x = start_Index.y = 0;
		end_Index.x = end_Index.y = 0;
		range.x = range.y = 0;

	}

	// 인덱스를 찾는다. (좌표를 받아와서 그 좌표가 위치한 인덱스를 구한다.)
	void Find_startIndex(float x, float y)
	{
		start_Index.x = x / TILE_SIZE_X;
		start_Index.y = y / TILE_SIZE_Y; 

		//cout << "start x : " << start_Index.x << endl;
		//cout << "start y : " << start_Index.y << endl;
		//cout << "=============================" << endl;
	}

	// 인덱스를 찾는다. (좌표를 받아와서 그 좌표가 위치한 인덱스를 구한다.)
	void Find_endIndex(float x, float y)
	{
		end_Index.x = (x + WINSIZEX) / TILE_SIZE_X;
		end_Index.y = (y + WINSIZEY) / TILE_SIZE_Y + 1;	// 화면 아래 쪽 살짝 빈 공간을 출력하기 위한 예외처리

		//cout << "end x : " << end_Index.x << endl;
		//cout << "end y : " << end_Index.y << endl;
		//cout << "=============================" << endl;
	}

	// 찾기 원하는 타일의 범위를 구한다.
	void Find_Tile_Range()
	{
		range.x = unsigned int(end_Index.x - start_Index.x);	// 찾아야 하는 x의 갯수
		range.y = unsigned int(end_Index.y - start_Index.y);	// 찾아야 하는 y의 갯수

		//cout << "range x : " << range.x << endl;
		//cout << "range y : " << range.y << endl;
		//cout << "=============================" << endl;
	}

	// 타일의 범위를 받아온다.
	tag_U_INT get_Start_Index() { return start_Index; }		// 스타트 인덱스를 받아온다.
	tag_U_INT get_End_Index() { return end_Index; }			// 엔드 인덱스를 받아온다.
	tag_U_INT get_Tile_Range() { return range; }			// 출력 타일 범위를 받아온다.

};
