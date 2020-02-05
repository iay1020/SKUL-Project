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
	// Ÿ���� �⺻ ��Ʈ�� ����� �ش�.
	for (int i = 0; i < TILE_TOTAL; ++i)
	{
		tagTileInfo* new_Tile = new tagTileInfo;
		new_Tile->reset_Tile();						// Ÿ�Ͽ� ������ ���� ����ִ� �Լ�.
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
	// Ÿ���� ��Ʈ�� ����Ѵ�.
	for (int i = 0; i < _vTileList.size(); ++i)
	{
		Rectangle(getMemDC(), _vTileList[i]->rc);
	}
}
