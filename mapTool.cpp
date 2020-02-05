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

	// 카메라매니저에 월드와 카메라 사이즈 정보를 넣어준다.
	CAMERAMANAGER->set_World_Size(200000, 300000);
	CAMERAMANAGER->set_Camera_Size(WINSIZEX, WINSIZEY);

	// 카메라의 좌표를 만들어준다.
	CAMERAMANAGER->set_CameraXY(2400, 1800, false);

	return S_OK;
}

void mapTool::release()
{
}

void mapTool::update()
{
	testMove();
	

}

void mapTool::render()
{
	// 타일의 렉트를 출력한다.
	/*for (int i = 0; i < _vTileList.size(); ++i)
	{
		Rectangle(CAMERAMANAGER->get_WorldDC(), _vTileList[i]->rc);
	}*/

	//RECT tempRC = RectMakeCenter(_tempCenter.x, _tempCenter.y, 50, 50);
	//Rectangle(CAMERAMANAGER->get_WorldDC(), tempRC);

	//RECT cameraRc = RectMake(CAMERAMANAGER->get_CameraXY().x, CAMERAMANAGER->get_CameraXY().y, WINSIZEX, WINSIZEY);
	//RECT temp;
	//for (int i = 0; i < _vTileList.size(); ++i)
	//{
	//	
	//	if (IntersectRect(&temp, &cameraRc, &_vTileList[i]->rc)) 
	//	{	
	//		RECT rc = RectMake(_vTileList[i]->rc.left - CAMERAMANAGER->get_CameraXY().x,
	//			_vTileList[i]->rc.top - CAMERAMANAGER->get_CameraXY().y,
	//			64, 64);
	//		Rectangle(getMemDC(), rc);
	//	}
	//}

	// 카메라 사이즈 만큼의 타일만 찾아서 출력을 한다.
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	POINTFLOAT start = CAMERAMANAGER->get_CameraXY();
	POINTFLOAT end = { WINSIZEX, WINSIZEY };
	end.x += start.x;
	end.y += start.y;

	POINT startIndex, endIndex;
	start.x /= TILE_SIZE_X;
	end.x /= TILE_SIZE_X;
	start.y /= TILE_SIZE_Y;
	end.y /= TILE_SIZE_Y;
	startIndex = { (LONG)start.x, (LONG)start.y };
	endIndex = { (LONG)end.x, (LONG)end.y };

	startIndex.x < 0 ? startIndex.x = 0 : startIndex.x;
	startIndex.y < 0 ? startIndex.y = 0 : startIndex.y;

	endIndex.x < 0 ? endIndex.x = 0 : endIndex.x;
	endIndex.y < 0 ? endIndex.y = 0 : endIndex.y;

	startIndex.x >= TILE_COUNT_X ? startIndex.x = TILE_COUNT_X - 1 : startIndex.x;
	startIndex.y >= TILE_COUNT_X ? startIndex.y = TILE_COUNT_X - 1 : startIndex.y;

	endIndex.x >= TILE_COUNT_X ? endIndex.x = TILE_COUNT_X - 1 : endIndex.x;
	endIndex.y >= TILE_COUNT_X ? endIndex.y = TILE_COUNT_X - 1 : endIndex.y;



	POINTFLOAT camera = CAMERAMANAGER->get_CameraXY();

	for (int y = startIndex.y; y <= endIndex.x; y++)
	{
		for (int x = startIndex.x; x <= endIndex.x; x++)
		{
			RECT rc = _vTileList[y * TILE_COUNT_X + x]->rc;

			rc.left -= camera.x;
			rc.right -= camera.x;
			rc.top -= camera.y;
			rc.bottom -= camera.y;

			Rectangle(getMemDC(), rc);

		}
	}





	//for (int y = CAMERAMANAGER->get_Find_Tile()->get_Start_Index().y; y < CAMERAMANAGER->get_Find_Tile()->get_End_Index().y; ++y)
	//{
	//	for (int x = CAMERAMANAGER->get_Find_Tile()->get_Start_Index().x; x < CAMERAMANAGER->get_Find_Tile()->get_End_Index().x; ++x)
	//	{
	//		RECT _tempRC;
	//		_tempRC = RectMake((int)_vTileList[(y * TILE_COUNT_X) + x]->rc.left % WINSIZEX, (int)_vTileList[_vTileList[(y * TILE_COUNT_Y) + x]->rc.right] % WINSIZEY, 50, 50);
	//		Rectangle(getMemDC(), _tempRC);
	//	}
	//}

	//cout << CAMERAMANAGER->get_Find_Tile()->get_Start_Index().x << endl;
	//cout << CAMERAMANAGER->get_Find_Tile()->get_Start_Index().y << endl;
	//cout << CAMERAMANAGER->get_Find_Tile()->get_End_Index().x << endl;
	//cout << CAMERAMANAGER->get_Find_Tile()->get_End_Index().y << endl;
	//cout << "===========================================" << endl;

	//CAMERAMANAGER->get_WorldImg()->render(getMemDC(), 0, 0, CAMERAMANAGER->get_CameraXY().x, CAMERAMANAGER->get_CameraXY().y, WINSIZEX, WINSIZEY);

	//cout << CAMERAMANAGER->get_CameraXY().x << endl;
	//cout << CAMERAMANAGER->get_CameraXY().y << endl;
	//cout << "==================================" << endl;
}

void mapTool::testMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		CAMERAMANAGER->set_CameraX(CAMERAMANAGER->get_CameraXY().x - 20);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		CAMERAMANAGER->set_CameraY(CAMERAMANAGER->get_CameraXY().y - 20);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		CAMERAMANAGER->set_CameraX(CAMERAMANAGER->get_CameraXY().x + 20);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		CAMERAMANAGER->set_CameraY(CAMERAMANAGER->get_CameraXY().y + 20);
	}

	CAMERAMANAGER->find_Tile();
}
