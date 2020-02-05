#include "stdafx.h"
#include "mapTool.h"

mapTool::mapTool()
{
}

mapTool::~mapTool()
{
}

HRESULT mapTool::init()
{
	// 타일의 기본 렉트를 만들어 준다.
	for (int i = 0; i < TILE_TOTAL; ++i)
	{
		tagTileInfo* new_Tile = new tagTileInfo;
		new_Tile->reset_Tile();						// 타일에 쓰레기 값을 비워주는 함수.
		new_Tile->idx = i % TILE_COUNT_X;
		new_Tile->idy = i / TILE_COUNT_Y;
		new_Tile->rc = RectMake(new_Tile->idx * TILE_SIZE_X, new_Tile->idy * TILE_SIZE_Y, TILE_SIZE_X, TILE_SIZE_Y);
		new_Tile->center.x = (new_Tile->rc.left + new_Tile->rc.right) / 2.f;
		new_Tile->center.y = (new_Tile->rc.top + new_Tile->rc.bottom) / 2.f;

		_vTileList.push_back(new_Tile);
	}

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
}

void mapTool::render()
{
	// 타일의 렉트를 출력한다.
	for (int i = 0; i < _vTileList.size(); ++i)
	{
		Rectangle(getMemDC(), _vTileList[i]->rc);
	}
}
