#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager()
{
	_mapInfo.reset_MapInfo();
}

DataManager::~DataManager()
{
}

HRESULT DataManager::init()
{

	return S_OK;
}

void DataManager::release()
{
}

void DataManager::update()
{
	// 스컬 대쉬 쿨타임 함수
	_skul->set_Info()->dash_CoolTime();

	// 스컬 상태 업데이트
	_skul->update();

	// 테스트용 캐릭터 클래스 체인지
	if (KEYMANAGER->isOnceKeyDown('I'))
	{
		_skul->set_Info()->type.skul_Type = SKUL_TYPE::SKUL_NOWEAPON;
		_skul->set_Info()->ani_Changer("Idle", _skul->get_InputKey());
		_skul->set_Info()->img.ani->start();
	}

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		_skul->set_Info()->type.skul_Type = SKUL_TYPE::SKUL_WEAPON;
		_skul->set_Info()->ani_Changer("Idle", _skul->get_InputKey());
		_skul->set_Info()->img.ani->start();
	}

	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		_skul->set_Info()->type.skul_Type = SKUL_TYPE::SKUL_WEAPON_NOHEAD;
		_skul->set_Info()->ani_Changer("Idle", _skul->get_InputKey());
		_skul->set_Info()->img.ani->start();
	}
}

void DataManager::map_Save(vector<tagTileInfo> tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo)
{
	HANDLE file;
	DWORD write;

	// 타일 갯수가 추가 되면서 인덱스가 바뀐 타일들을 다시 갱신 시켜준다.
	for (int y = 0; y < mapInfo->tile_Count.y; ++y)
	{
		for (int x = 0; x < mapInfo->tile_Count.x; ++x)
		{
			tileList[x + y * mapInfo->tile_Count.x].index.x = x;
			tileList[x + y * mapInfo->tile_Count.x].index.y = y;
		}
	}

	// 벡터의 정보를 배열로 옴겨 담는다. (데이터를 세이브 하려면 직렬화 시켜야하는데, 벡터 자체로는 안됐다)
	tagTileInfo* tile;
	tile = new tagTileInfo[mapInfo->tile_Count.x * mapInfo->tile_Count.y];	// 타일의 크기만큼 할당 받는다.
																			// 배열로 크기를 정해 줄 경우는 상수로만 가능하기 때문에

	for (int i = 0; i < tileList.size(); ++i)									// 벡터 사이즈만큼 반복하며 tile에 맵을 담아준다.
	{
		tile[i] = tileList[i];													// 배열에 벡터 정보를 모두 옴긴다.
	}

	// 맵을 저장한다.
	file = CreateFile("tutorial.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, tile, sizeof(tagTileInfo) * mapInfo->tile_Count.x * mapInfo->tile_Count.y, &write, NULL);
	
	CloseHandle(file);



	// 백그라운드 정보를 맥 정보 배열에 옴겨 담는다.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		for (int j = 0; j < (vMapInfo[i]).size(); ++j)
		{
			mapInfo->_saveVInfo[i][j] = (vMapInfo[i])[j];
		}
		mapInfo->_vSize[i] = (vMapInfo[i]).size();	// 불러올때 벡터를 재생성 하기 위해 현재 사이즈를 저장한다.
	}
	
	// 맵의 정보를 저장한다. (맵에 대한 정보 여러가지 있다. 이후에 여기에 저장 되어 있는 맵 이름을 가지고 만들어야 함)
	file = CreateFile("tutorial_Info.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	WriteFile(file, mapInfo, sizeof(tagMapInfo), &write, NULL);
	
	CloseHandle(file);
}

void DataManager::map_Load(vector<tagTileInfo>* tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo)
{

	HANDLE file;
	DWORD read;

	file = CreateFile("tutorial_Info.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	ReadFile(file, mapInfo, sizeof(tagMapInfo), &read, NULL);						// 맵 정보를 먼저 받아 온 이유는 맵을 받아올때 맵의 크기 정보가 필요하기 때문에

	CloseHandle(file);

	// 새로 맵을 불러오면 타일 갯수, 월드 사이즈를 갱신해준다.
	CAMERAMANAGER->Use_Func()->set_Tile_CountX(mapInfo->tile_Count.x);														// 가로 사이즈 설정 (맵마다 가로세로가 다르니까)
	CAMERAMANAGER->Use_Func()->set_Tile_CountY(mapInfo->tile_Count.y);														// 세로 사이즈 설정
	CAMERAMANAGER->Use_Func()->set_World_Size(mapInfo->tile_Count.x * TILE_SIZE_X, mapInfo->tile_Count.y * TILE_SIZE_Y);	// 가로세로에 맞게 월드 사이즈 설정


	// 기존에 있던 벡터는 비워준다. (새로운 정보를 넣기 위해)
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		if (vMapInfo[i].size() > 0)
		{
			for (int j = 0; j < vMapInfo[i].size();)
			{
				//vMapInfo[i].erase(vMapInfo[i].begin());
				vMapInfo[i].clear();
			}
		}
	}
	

	// 배열에 있던 정보를 벡터에 옴겨담는다.
	vector<tagSaveBackGround>	_moveData[BACKGROUND_LAYER_COUNT];

	// 저장되어 있던 사이즈만큼 반복한다.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		for (int j = 0; j < mapInfo->_vSize[i]; ++j)
		{
			
			tagSaveBackGround new_Data;
			new_Data.imageName = mapInfo->_saveVInfo[i][j].imageName;
			new_Data.rc = mapInfo->_saveVInfo[i][j].rc;
			vMapInfo[i].push_back(new_Data);
		}
	}

	// 맵을 받아 올 변수를 만든다.
	tagTileInfo* tile;
	tile = new tagTileInfo[mapInfo->tile_Count.x * mapInfo->tile_Count.y];			//	타일의 크기만큼 할당 받는다.

	file = CreateFile("tutorial.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, tile, sizeof(tagTileInfo) * mapInfo->tile_Count.x * mapInfo->tile_Count.y, &read, NULL);

	CloseHandle(file);

		// 타일리스트를 초기화 해준다.
	//while (tileList->size() > 0)
	//{
	//	tileList->erase(tileList->begin());
	//}
	tileList->clear();

	// 맵이 들어있는 타일을 벡터에 넣어준다.
	for (int i = 0; i < mapInfo->tile_Count.x * mapInfo->tile_Count.y; ++i)
	{
		tileList->push_back(tile[i]);
	}
	
}

void DataManager::map_Load_Datamanager(string mapName, string mapInfoName)
{
	// string을 char 배열로 옴겨 담았다.
	char* strMapName;
	strMapName = new char[mapName.size()];

	for (int i = 0; i <= mapName.size(); ++i)
	{
		strMapName[i] = mapName[i];

		if (i == mapName.size())
		{
			strMapName[i] = NULL;
		}
	}

	char* strMapInfoName;
	strMapInfoName = new char[mapName.size()];

	for (int i = 0; i <= mapInfoName.size(); ++i)
	{
		strMapInfoName[i] = mapInfoName[i];

		if (i == mapName.size())
		{
			strMapName[i] = NULL;
		}
	}

	HANDLE file;
	DWORD read;
	
	file = CreateFile(strMapInfoName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	ReadFile(file, &_mapInfo, sizeof(tagMapInfo), &read, NULL);						// 맵 정보를 먼저 받아 온 이유는 맵을 받아올때 맵의 크기 정보가 필요하기 때문에
	
	CloseHandle(file);
	
	// 새로 맵을 불러오면 타일 갯수, 월드 사이즈를 갱신해준다.
	CAMERAMANAGER->Use_Func()->set_Tile_CountX(_mapInfo.tile_Count.x);															// 가로 사이즈 설정 (맵마다 가로세로가 다르니까)
	CAMERAMANAGER->Use_Func()->set_Tile_CountY(_mapInfo.tile_Count.y);															// 세로 사이즈 설정
	CAMERAMANAGER->Use_Func()->set_World_Size(_mapInfo.tile_Count.x * TILE_SIZE_X, _mapInfo.tile_Count.y * TILE_SIZE_Y);		// 가로세로에 맞게 월드 사이즈 설정
	
	
	// 기존에 있던 벡터는 비워준다. (새로운 정보를 넣기 위해)
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		if (_vMapInfo[i].size() > 0)
		{
			for (int j = 0; j < _vMapInfo[i].size();)
			{
				_vMapInfo[i].clear();
			}
		}
	}
	
	// 배열에 있던 정보를 벡터에 옴겨담는다.
	vector<tagSaveBackGround>	_moveData[BACKGROUND_LAYER_COUNT];

	
	// 저장되어 있던 사이즈만큼 반복한다.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		for (int j = 0; j < _mapInfo._vSize[i]; ++j)
		{
			tagSaveBackGround new_Data;
			new_Data.imageName = _mapInfo._saveVInfo[i][j].imageName;
			new_Data.rc = _mapInfo._saveVInfo[i][j].rc;
			_vMapInfo[i].push_back(new_Data);
		}
	}
	
	// 맵을 받아 올 변수를 만든다.
	tagTileInfo* tile;
	tile = new tagTileInfo[_mapInfo.tile_Count.x * _mapInfo.tile_Count.y];			//	타일의 크기만큼 할당 받는다.
	
	file = CreateFile("tutorial.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	ReadFile(file, tile, sizeof(tagTileInfo) * _mapInfo.tile_Count.x * _mapInfo.tile_Count.y, &read, NULL);
	
	CloseHandle(file);
	
	_tileList.clear();
	
	// 맵이 들어있는 타일을 벡터에 넣어준다.
	for (int i = 0; i < _mapInfo.tile_Count.x * _mapInfo.tile_Count.y; ++i)
	{
		_tileList.push_back(tile[i]);
	}

}

void DataManager::map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo)
{
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// 카메라 안에 들어온 타일을 찾아서 저장한다.

		// 백그라운드를 그려준다.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		if (vMapInfo[i].size() > 0)	// 해당 벡터가 0이상이여야만 들어간다.
		{
			for (int j = 0; j < vMapInfo[i].size(); ++j)
			{
				RECT rc = (vMapInfo[i])[j].rc;
				rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
				rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
				IMAGEMANAGER->findImage((vMapInfo[i])[j].imageName)->render(getMemDC, rc.left, rc.top);
			}
		}
	}

	// 마우스가 클릭한 타일을 찾아준다. (내 화면에 있는 타일만 찾아서)
	for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
	{
		for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
		{
			//cout << y * mapInfo.tile_Count.x + x << ":" << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.x << "," << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.y << endl;

			RECT rc = (*tileList)[y * mapInfo.tile_Count.x + x].rc;
			POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

			rc.left -= camera.x;
			rc.right -= camera.x;
			rc.top -= camera.y;
			rc.bottom -= camera.y;

			// 안 쓰는 타입은 제외한다.
			if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
			{

				// 지형을 그려준다.
				if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
				{
					if ((*tileList)[y * mapInfo.tile_Count.x + x].useTile)
					{

						IMAGEMANAGER->findImage((*tileList)[y * mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							(*tileList)[y * mapInfo.tile_Count.x + x].frame.ground.x, (*tileList)[y * mapInfo.tile_Count.x + x].frame.ground.y);
					}
				}

				// 데코를 그려준다.
				if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
				{

				}
			}
		}
	}
}

void DataManager::map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo, short loopSpd[])
{
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// 카메라 안에 들어온 타일을 찾아서 저장한다.

	short loopSpeed[5];

	for (int i = 0; i < 5; ++i)
	{
		loopSpeed[i] = loopSpd[i];
	}

	// 맨날 치킨 먹는다면서 치킨 안먹는 사람 
	// 저요 저요!

	// 백그라운드를 그려준다.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{ 
		if (vMapInfo[i].size() > 0)	// 해당 벡터가 0이상이여야만 들어간다.
		{
			for (int j = 0; j < vMapInfo[i].size(); ++j)
			{
				RECT rc = RectMake((vMapInfo[i])[j].rc.left, (vMapInfo[i])[j].rc.top,
					IMAGEMANAGER->findImage((vMapInfo[i])[j].imageName)->getWidth(), IMAGEMANAGER->findImage((vMapInfo[i])[j].imageName)->getHeight());
				rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
				rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

				IMAGEMANAGER->findImage((vMapInfo[i])[j].imageName)->loopRender(getMemDC, &rc, loopSpeed[i], 0);
			}
		}
	}

	// 마우스가 클릭한 타일을 찾아준다. (내 화면에 있는 타일만 찾아서)
	for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
	{
		for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
		{
			//cout << y * mapInfo.tile_Count.x + x << ":" << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.x << "," << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.y << endl;

			RECT rc = (*tileList)[y * mapInfo.tile_Count.x + x].rc;
			POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

			rc.left -= camera.x;
			rc.right -= camera.x;
			rc.top -= camera.y;
			rc.bottom -= camera.y;

			// 안 쓰는 타입은 제외한다.
			if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
			{

				// 지형을 그려준다.
				if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
				{
					if ((*tileList)[y * mapInfo.tile_Count.x + x].useTile)
					{

						IMAGEMANAGER->findImage((*tileList)[y * mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							(*tileList)[y * mapInfo.tile_Count.x + x].frame.ground.x, (*tileList)[y * mapInfo.tile_Count.x + x].frame.ground.y);
					}
				}

				// 데코를 그려준다.
				if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
				{

				}
			}
		}
	}
}

void DataManager::map_Render_Datamanager(HDC getMemDC)
{
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// 카메라 안에 들어온 타일을 찾아서 저장한다.

		// 백그라운드를 그려준다.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		if (_vMapInfo[i].size() > 0)	// 해당 벡터가 0이상이여야만 들어간다.
		{
			for (int j = 0; j < _vMapInfo[i].size(); ++j)
			{
				RECT rc = (_vMapInfo[i])[j].rc;
				rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
				rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
				IMAGEMANAGER->findImage((_vMapInfo[i])[j].imageName)->render(getMemDC, rc.left, rc.top);
			}
		}
	}

	// 마우스가 클릭한 타일을 찾아준다. (내 화면에 있는 타일만 찾아서)
	for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
	{
		for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
		{
			//cout << y * mapInfo.tile_Count.x + x << ":" << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.x << "," << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.y << endl;

			RECT rc = _tileList[y * _mapInfo.tile_Count.x + x].rc;
			POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

			rc.left -= camera.x;
			rc.right -= camera.x;
			rc.top -= camera.y;
			rc.bottom -= camera.y;

			// 안 쓰는 타입은 제외한다.
			if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
			{

				// 지형을 그려준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
				{
					if (_tileList[y * _mapInfo.tile_Count.x + x].useTile)
					{

						IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);
					}
				}

				// 데코를 그려준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
				{

				}
			}

			// 충돌 타입이 없다면 제외한다.
			if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type != COLLISION_TILE_TYPE::NONE_TYPE)
			{
				// 발판 타입을 표시해준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);
					
				}

				// 벽 타입을 표시해준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);
					
				}

				// 함정 타입을 표시해준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::TRAP_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);
					
				}
			}
		}
	}
}

void DataManager::map_Render_Datamanager(HDC getMemDC, short loopSpd[])
{
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// 카메라 안에 들어온 타일을 찾아서 저장한다.

	short loopSpeed[5];

	for (int i = 0; i < 5; ++i)
	{
		loopSpeed[i] = loopSpd[i];
	}

	// 맨날 치킨 먹는다면서 치킨 안먹는 사람 
	// 저요 저요!

	// 백그라운드를 그려준다.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		if (_vMapInfo[i].size() > 0)	// 해당 벡터가 0이상이여야만 들어간다.
		{
			for (int j = 0; j < _vMapInfo[i].size(); ++j)
			{
				RECT rc = RectMake((_vMapInfo[i])[j].rc.left, (_vMapInfo[i])[j].rc.top,
					IMAGEMANAGER->findImage((_vMapInfo[i])[j].imageName)->getWidth(), IMAGEMANAGER->findImage((_vMapInfo[i])[j].imageName)->getHeight());
				rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
				rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
				rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

				IMAGEMANAGER->findImage((_vMapInfo[i])[j].imageName)->loopRender(getMemDC, &rc, loopSpeed[i], 0);
			}
		}
	}

	// 마우스가 클릭한 타일을 찾아준다. (내 화면에 있는 타일만 찾아서)
	for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
	{
		for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
		{
			//cout << y * mapInfo.tile_Count.x + x << ":" << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.x << "," << (*_vTileList)[y * mapInfo.tile_Count.x + x].index.y << endl;

			RECT rc = _tileList[y * _mapInfo.tile_Count.x + x].rc;
			POINTFLOAT camera = CAMERAMANAGER->Use_Func()->get_CameraXY();

			rc.left -= camera.x;
			rc.right -= camera.x;
			rc.top -= camera.y;
			rc.bottom -= camera.y;

			// 안 쓰는 타입은 제외한다.
			if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
			{

				// 지형을 그려준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
				{
					if (_tileList[y * _mapInfo.tile_Count.x + x].useTile)
					{

						IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);
					}
				}

				// 데코를 그려준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
				{

				}
			}

			// 충돌 타입이 없다면 제외한다.
			if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type != COLLISION_TILE_TYPE::NONE_TYPE)
			{
				// 발판 타입을 표시해준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);

				}

				// 벽 타입을 표시해준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);

				}

				// 함정 타입을 표시해준다.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::TRAP_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);

				}
			}
		}
	}
}

void DataManager::Rect_Render_Datamanager(HDC getMemDC)
{
	//  테스트용 렉트 출력
	
	RECT testRc;

	for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
	{
		for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
		{
			testRc = _tileList[y * _mapInfo.tile_Count.x + x].rc;
			testRc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			testRc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			testRc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
			testRc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

			IMAGEMANAGER->findImage("tile_Rect")->render(getMemDC, testRc.left, testRc.top);
		}
	}
}

void DataManager::create_Skul()
{
	// 스컬 기본 셋팅
	_skul = new Player();
}

bool DataManager::Collision_PlayerFall_Ground()
{
	// 캐릭터의 타일 인덱스를 저장할 공간
	short player_TilePos_X, player_TilePos_Y;
	
	// 캐릭터가 위치한 타일의 인덱스를 구한다.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// 플레이어의 아래 타일이 땅이라면
	if (_tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND ||
		_tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{
		
		// 플레이어의 bottom이 땅 top보다 작을때만
		if ((_skul->get_Info().pos.rc.bottom + CAMERAMANAGER->Use_Func()->get_CameraXY().y) - 20 < _tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].rc.top)
		{
			// 플레이어의 위치 수정
			 _skul->set_Info()->pos.center.y = _tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].rc.top - TILE_SIZE_Y / 2;

			return true;
		}
	}

	// 플레이어가 충돌하지 않았다면 false 반환
	return false;
}

bool DataManager::Collision_Player_Wall()
{
	// 캐릭터의 타일 인덱스를 저장할 공간
	short player_TilePos_X, player_TilePos_Y;

	// 캐릭터가 위치한 타일의 인덱스를 구한다.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// 캐릭터가 바라보는 방향에 따라 다른 연산
	if (_skul->get_InputKey() == PRESS_LEFT)
	{
		// 플레이어가 바라보는 방향에 벽이 있다면
		if (_tileList[(player_TilePos_X - 1) + player_TilePos_Y * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND)
		{
			// 플레이어의 Left가 벽의 Right보다 작으면
			if ((_skul->get_Info().pos.rc.left + CAMERAMANAGER->Use_Func()->get_CameraXY().x) - 5 < _tileList[(player_TilePos_X - 1) + player_TilePos_Y * _mapInfo.tile_Count.x].rc.right)
			{

				return true;
			}
		}
	}

	if (_skul->get_InputKey() == PRESS_RIGHT)
	{
		// 플레이어가 바라보는 방향에 벽이 있다면
		if (_tileList[(player_TilePos_X + 1) + player_TilePos_Y * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND)
		{
			// 플레이어의 Right가 벽의 Left보다 크면
			if ((_skul->get_Info().pos.rc.right + CAMERAMANAGER->Use_Func()->get_CameraXY().x) + 5 > _tileList[(player_TilePos_X + 1) + player_TilePos_Y * _mapInfo.tile_Count.x].rc.left)
			{

				return true;
			}
		}
	}


	// 플레이어가 충돌하지 않았다면 false 반환
	return false;
}

bool DataManager::Collision_Player_FootHold()
{
	// 캐릭터의 타일 인덱스를 저장할 공간
	short player_TilePos_X, player_TilePos_Y;

	// 캐릭터가 위치한 타일의 인덱스를 구한다.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// 플레이어의 위에 발판이 있다면
	if (_tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{
		cout << "플레이어 bottom : " <<  _skul->get_Info().pos.rc.bottom + CAMERAMANAGER->Use_Func()->get_CameraXY().y << endl;
		cout << "발판의 bottom : " << _tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].rc.bottom << endl;

		// 플레이어의 Top이 벽의 Bottom보다 크면
		if ((_skul->get_Info().pos.rc.bottom + CAMERAMANAGER->Use_Func()->get_CameraXY().y) > _tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].rc.bottom)
		{

			return true;
		}
	}

	// 발판을 찾지 못했다면
	return false;
}

bool DataManager::Collision_Player_FootHold_Down()
{
	// 캐릭터의 타일 인덱스를 저장할 공간
	short player_TilePos_X, player_TilePos_Y;

	// 캐릭터가 위치한 타일의 인덱스를 구한다.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// 플레이어의 아래에 발판이 있다면
	if (_tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{
		return true;
		
	}

	// 발판을 찾지 못했다면
	return false;
}

bool DataManager::Collision_Player_Trab()
{
	// 플레이어가 충돌했다면 true 반환


	// 플레이어가 충돌하지 않았다면 false 반환
	return false;
}

void DataManager::Lerp_Player()
{
	// 경과시간
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	// 스피드 구하기
	float lerp_Speed = (elapsedTime / PLAYER_DASH_TIME) * PLAYER_DASH_RANGE;

	// 이동 (벽이 없을때만 이동 연산을 한다.)
	if (!DATAMANAGER->Collision_Player_Wall())
	{
		if (_skul->get_InputKey() == PRESS_RIGHT) _skul->set_Info()->pos.center.x += cosf(0) * lerp_Speed;
		if (_skul->get_InputKey() == PRESS_LEFT) _skul->set_Info()->pos.center.x += cosf(3.14) * lerp_Speed;

		// 카메라 위치 갱신
		CAMERAMANAGER->Use_Func()->set_CameraXY(_skul->get_Info().pos.center.x, _skul->get_Info().pos.center.y, true);

		// 렉트 갱신
		_skul->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		_skul->update_Ani_Rect();
	
	}

	// 멈추는 조건
	if (_skul->get_Info().dash.Dash_StartTime + PLAYER_DASH_TIME < TIMEMANAGER->getWorldTime())
	{
		// 현재 시간으로 초기화
		_skul->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();

		// bool 값 끄기
		_skul->set_Info()->bool_V.dashing_Cheack = false;

		_skul->set_Info()->bool_V.walk_Cheack = false;
		_skul->set_Info()->bool_V.jumping_Cheack = false;
		_skul->set_Info()->bool_V.jump_Cheack = false;
		_skul->set_Info()->bool_V.falling_Cheack = false;
		_skul->set_Info()->bool_V.fall_Cheack = false;
	}

}

void DataManager::Lerp_Enemy()
{
	// true일때만 실행 (에너미 전용)

	// 틱 받기

	// 스피드 구하기

	// 이동

	// 멈추는 조건

	// bool 값 끄기
}
