#include "stdafx.h"
#include "test_Room.h"

test_Room::test_Room()
{
}

test_Room::~test_Room()
{
}

HRESULT test_Room::init()
{
	_DM.map_Load(&tileList, &mapInfo, &vMapInfo);

	return S_OK;
}

void test_Room::release()
{
}

void test_Room::update()
{
}

void test_Room::render()
{
	for (int i = 0; i < mapInfo.tile_Count.x * mapInfo.tile_Count.y; ++i)
	{
		if (tileList[i].tile_Type == TILE_TYPE::GROUND)	IMAGEMANAGER->findImage(tileList[i].tileName.groundName)->
			frameRender(getMemDC(), tileList[i].rc.left, tileList[i].rc.top, tileList[i].frame.ground.x, tileList[i].frame.ground.y);
	}
}
