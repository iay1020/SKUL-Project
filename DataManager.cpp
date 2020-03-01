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
	// 투사체 매니저 할당
	_flyObj_Manager = new FlyingObject;
	_effect_Maker = new EffectMaker;
	_enemyManager = new EnemyManager;
	_ui_Manager = new Ui_Manager;


	return S_OK;
}

void DataManager::release()
{
}

void DataManager::update()
{
	// 에너미 매니저 업데이트
	_enemyManager->update();

	// 스컬 상태 업데이트
	_skul->update();

	// UI 업데이트
	_ui_Manager->update();

	// 투사체 매니저 업데이트
	_flyObj_Manager->update();

	// 투사체 충돌 함수
	Collision_Skul_Head();

	// 키애니매니저 업데이트
	KEYANIMANAGER->update();

	// 이펙트매니저 업데이트
	EFFECTMANAGER->update();

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
	file = CreateFile("Intro.map", GENERIC_WRITE, 0, NULL,
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
	file = CreateFile("Intro_Info.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	
	WriteFile(file, mapInfo, sizeof(tagMapInfo), &write, NULL);
	
	CloseHandle(file);
}

void DataManager::map_Load(vector<tagTileInfo>* tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo)
{

	HANDLE file;
	DWORD read;

	file = CreateFile("Stage_1_Info.map", GENERIC_READ, 0, NULL,
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

	file = CreateFile("Stage_1.map", GENERIC_READ, 0, NULL,
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

void DataManager::map_Load(vector<tagTileInfo>* tileList, tagMapInfo * mapInfo, vector<tagSaveBackGround>* vMapInfo, string mapName, string mapInfoName)
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

	file = CreateFile(strMapName, GENERIC_READ, 0, NULL,
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
	
	file = CreateFile(strMapName, GENERIC_READ, 0, NULL,
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

void DataManager::map_Render_Datamanager_Loop(HDC getMemDC)
{
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// 카메라 안에 들어온 타일을 찾아서 저장한다.

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

				IMAGEMANAGER->findImage((_vMapInfo[i])[j].imageName)->loopRender(getMemDC, &rc, CAMERAMANAGER->Use_Func()->get_CameraXY().x * i * 0.1f, 0);
			}
		}
	}

	// 마우스가 클릭한 타일을 찾아준다. (내 화면에 있는 타일만 찾아서)
	for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
	{
		for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
		{
			RECT rc = _tileList[y * _mapInfo.tile_Count.x + x].rc;
			//RECT mRc = minimap[y * _mapInfo.tile_Count.x + x].rc;
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


	//for (int y = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().y; y <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().y; y++)
	//{
	//	for (int x = CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_Start_Index().x; x <= CAMERAMANAGER->Use_Func()->get_Find_Tile()->get_End_Index().x; x++)
	//	{
	//		RECT mRc = minimap[y * _mapInfo.tile_Count.x + x].rc;
	//		//mRc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x / 4.f;
	//		//mRc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x / 4.f;
	//		//mRc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y / 4.f - 250;
	//		//mRc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y / 4.f - 250;
	//
	//		// 미니맵 출력 출력
	//		// 안 쓰는 타입은 제외한다.
	//		if (minimap[y * _mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
	//		{
	//
	//			// 지형을 그려준다.
	//			if (minimap[y * _mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
	//			{
	//				if (minimap[y * _mapInfo.tile_Count.x + x].useTile)
	//				{
	//				
	//					IMAGEMANAGER->findImage(minimap[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, mRc.left , mRc.top ,
	//						minimap[y * _mapInfo.tile_Count.x + x].frame.ground.x, minimap[y * _mapInfo.tile_Count.x + x].frame.ground.y);
	//
	//					//Rectangle(getMemDC, mRc.left, mRc.top, mRc.right, mRc.bottom);
	//				}
	//			}
	//
	//
	//		}
	//	}
	//}

	// 플레이어 렉트
	//int index = (int)((_skul->get_Info().pos.center.x / TILE_SIZE_X)) +
	//	((int)(_skul->get_Info().pos.center.y) / TILE_SIZE_Y * _mapInfo.tile_Count.x);
	//
	//IMAGEMANAGER->findImage("miniMap_Player")->render(getMemDC, minimap[index].rc.left , minimap[index].rc.top - 8);
	////Rectangle(getMemDC, minimap[index].rc.left + 1280, minimap[index].rc.top - 8 + 680, minimap[index].rc.right + 1280, minimap[index].rc.bottom + 680);
	//
	//// 미니맵 프레임
	//IMAGEMANAGER->findImage("miniMap_Frame")->render(getMemDC, 1175, 700);
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

void DataManager::scene_Changer()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		// 맵툴 씬으로 이동한다.
		SCENEMANAGER->changeScene("mapTool");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		// 맵툴 씬으로 이동한다.
		SCENEMANAGER->changeScene("Stage_0");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		// 맵툴 씬으로 이동한다.
		SCENEMANAGER->changeScene("Stage_1");
	}
}

void DataManager::create_Skul()
{
	// 스컬 기본 셋팅
	_skul = new Player();
}

void DataManager::skul_Attack_Range_Enemy(Enemy* enemy_Address)
{
	// 스컬의 공격 렉트가 에너미의 렉트와 충돌 했을 경우 연산

	RECT temp;
	RECT SkulRC = _skul->get_Info().pos.Attack_RC;
	//SkulRC.left += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	//SkulRC.right += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	//SkulRC.top += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	//SkulRC.bottom += CAMERAMANAGER->Use_Func()->get_CameraXY().y;

	// 렉트 충돌용
	if (IntersectRect(&temp, &SkulRC, &enemy_Address->info_Address()->pos.hit_Range_Rc))
	{
		short RNum;
		RNum = RND->getInt(10) + 1;

		bool isCritical = false;

		if (RNum == 1 || RNum == 2 || RNum == 3 || RNum == 4 || RNum == 5) isCritical = true;

		// 아직 맞기 전이라면
		if (!enemy_Address->info_Address()->bool_V.player_Attack_Hit)
		{
			// 피격 데미지가 출력 될 위치를 잡아준다.
			enemy_Address->info_Address()->pos.damege_Center.x = enemy_Address->info_Address()->pos.center.x;
			enemy_Address->info_Address()->pos.damege_Center.y = enemy_Address->info_Address()->pos.ani_Rc.top;

			// 피격 이펙트
			if (!isCritical)
			{
				enemy_Address->info_Address()->bool_V.Critical_Hit = false;

				if (_skul->get_InputKey() == PRESS_RIGHT)
				{
					EFFECTMANAGER->play("skul_Base_Attack_Right",
						enemy_Address->info_Address()->pos.center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
						enemy_Address->info_Address()->pos.center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
				}
				if (_skul->get_InputKey() == PRESS_LEFT)
				{
					EFFECTMANAGER->play("skul_Base_Attack_Left",
						enemy_Address->info_Address()->pos.center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
						enemy_Address->info_Address()->pos.center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
				}

				// 최소 공격력 ~ 최대 공격력까지 랜덤으로 받는다.
				short RndAttack = 0;
				RndAttack = RND->getInt(_skul->get_Info().status.Atk) + (_skul->get_Info().status.Atk - 5);

				// 출력되는 데미지를 넣어준다.
				enemy_Address->info_Address()->status.show_Attack = RndAttack;

				// 에너미의 체력이 단다. (스컬의 데미지 만큼)
				enemy_Address->info_Address()->status.hp -= RndAttack;
				enemy_Address->info_Address()->hp.curHP = enemy_Address->info_Address()->status.hp;

			}

			if (isCritical)
			{
				enemy_Address->info_Address()->bool_V.Critical_Hit = true;

				RNum = RND->getInt(2);

				if (_skul->get_InputKey() == PRESS_RIGHT)
				{
					if (RNum == 0) EFFECTMANAGER->play("skul_Base_Attack_Cri_1", 
						enemy_Address->info_Address()->pos.center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
						enemy_Address->info_Address()->pos.center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
					if(RNum == 1) EFFECTMANAGER->play("skul_Base_Attack_Cri_2", 
						enemy_Address->info_Address()->pos.center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
						enemy_Address->info_Address()->pos.center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
				}
				if (_skul->get_InputKey() == PRESS_LEFT)
				{
					if (RNum == 0) EFFECTMANAGER->play("skul_Base_Attack_Cri_1",
						enemy_Address->info_Address()->pos.center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
						enemy_Address->info_Address()->pos.center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
					if (RNum == 1) EFFECTMANAGER->play("skul_Base_Attack_Cri_2",
						enemy_Address->info_Address()->pos.center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
						enemy_Address->info_Address()->pos.center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
				}

				// 최소 공격력 ~ 최대 공격력까지 랜덤으로 받는다.
				short RndAttack = 0;
				RndAttack = RND->getInt(_skul->get_Info().status.Atk) + (_skul->get_Info().status.Atk - 5);

				// 출력되는 데미지를 넣어준다.
				enemy_Address->info_Address()->status.show_Attack = RndAttack;

				// 에너미의 체력이 단다. (스컬의 데미지 만큼)
				enemy_Address->info_Address()->status.hp -= RndAttack * 2;
				enemy_Address->info_Address()->hp.curHP = enemy_Address->info_Address()->status.hp;
			}

			// 피격 bool값을 true로 바꿔준다.
			enemy_Address->info_Address()->bool_V.player_Attack_Hit = true;
			
			enemy_Address->info_Address()->hp.state = HP_UPDATE_STATE_E::HIT;
			enemy_Address->info_Address()->bool_V.im_Hit = true;

			// 에너미의 피격 시작 시간을 넣어준다.
			enemy_Address->info_Address()->pos.lerp_Start = TIMEMANAGER->getWorldTime();

			// 만약 체력이 0 이하라면
			if (enemy_Address->info_Address()->status.hp <= 0)
			{
				// 체력 0으로 보정
				enemy_Address->info_Address()->status.hp = 0;

				// 에너미 사망 bool값 넣어주기.
				enemy_Address->info_Address()->bool_V.im_Death = true;

			}
		}

	}

}

void DataManager::skul_Collision_Event(RECT eventRC)
{
	// 스컬이 이벤트지역에 들어갔다면

	// 해당 이벤트 위치로 순간이동한다.


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

bool DataManager::Collision_PlayerJump_Ground()
{
	// 캐릭터의 타일 인덱스를 저장할 공간
	short player_TilePos_X, player_TilePos_Y;

	// 캐릭터가 위치한 타일의 인덱스를 구한다.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// 플레이어의 위 타일이 땅이라면
	if (_tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND &&
		_tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].tile_Collision_Type != COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{

		// 플레이어의 bottom이 땅 top보다 작을때만
		if ((_skul->get_Info().pos.rc.top + CAMERAMANAGER->Use_Func()->get_CameraXY().y) - 10 < _tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].rc.bottom)
		{
			// 플레이어가 벽에 충돌 했을때 점프 수치를 없애준다.
			_skul->set_Info()->jump.jump_Value = 0;

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

		_skul->set_Info()->jump.jump_Value = 0;
	}

}

void DataManager::Lerp_Enemy(Enemy* enemy, float time_, float range_)
{
	// 경과시간
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	// 스피드 구하기
	float lerp_Speed = (elapsedTime / time_) * range_;

	// 피격 중일때
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// 이동 (벽이 없을때만 이동 연산을 한다.)
		if (DATAMANAGER->enemy_Move_Wall(enemy, enemy->info_Address()->status.dir, true))
		{
			//if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)
			if(_skul->get_Info().status.direction == CharacterDirection::DIRECTION_RIGHT)
			{
				enemy->info_Address()->pos.center.x += cosf(0) * lerp_Speed;
			}
			//if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT)
			if (_skul->get_Info().status.direction == CharacterDirection::DIRECTION_LEFT)
			{
				enemy->info_Address()->pos.center.x += cosf(3.14) * lerp_Speed;
			}

			// 렉트 갱신
			enemy->info_Address()->update_Rect();
		}
	}

	if (!enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// 이동 (벽이 없을때만 이동 연산을 한다.)
		if (DATAMANAGER->enemy_Move_Wall(enemy, enemy->info_Address()->status.dir))
		{
			if (enemy->info_Address()->status.dir == EnemyDirection::LEFT)
			{
				enemy->info_Address()->pos.center.x += cosf(3.14) * lerp_Speed;
			}
			if (enemy->info_Address()->status.dir == EnemyDirection::RIGHT)
			{
				enemy->info_Address()->pos.center.x += cosf(0) * lerp_Speed;
			}

			// 렉트 갱신
			enemy->info_Address()->update_Rect();
		}
	}

	// 멈추는 조건
	if (enemy->info_Address()->pos.lerp_Start + time_ <= TIMEMANAGER->getWorldTime())
	{
	
		// 현재 시간으로 초기화
		enemy->info_Address()->pos.lerp_Start = TIMEMANAGER->getWorldTime();
	
		// bool 값 끄기
		enemy->info_Address()->bool_V.hitCheck = false;
		enemy->info_Address()->bool_V.lerping = false;

		enemy->info_Address()->cool_Time.attack_CoolTime_Cnt = 0;
		enemy->info_Address()->bool_V.attackCheck = false;

		enemy->info_Address()->bool_V.Attack_Hit = false;

		// 공격 끝이라면 
		enemy->info_Address()->bool_V.atk_End = true;

		// 공격 후딜레이클 켜준다.
		enemy->info_Address()->bool_V.next_Atk_Delay = true;

	}
}

RECT DataManager::plus_CameraPos(RECT rc)
{
	RECT v_RC = rc;
	v_RC.left += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	v_RC.right += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	v_RC.top += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	v_RC.bottom += CAMERAMANAGER->Use_Func()->get_CameraXY().y;

	return v_RC;
}

RECT DataManager::minus_CameraPos(RECT rc)
{
	RECT v_RC = rc;
	v_RC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	v_RC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	v_RC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	v_RC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

	return v_RC;
}

bool DataManager::Collision_FlyingObject_Wall(FlyingObjectInfo* fObj)
{
	// 투사체의 타일 인덱스를 저장할 공간
	int fObj_TilePos_X, fObj_TilePos_Y;

	// 투사체가 위치한 타일의 인덱스를 구한다.
	fObj_TilePos_X = (int)fObj->center.x / TILE_SIZE_X;
	fObj_TilePos_Y = (int)fObj->center.y / TILE_SIZE_Y;

	// 투사체가 날아가는 방향에 따라 다른 연산
	if (fObj->dir == FLYINGOBJECT_DIRECTION::LEFT)
	{
		// 투사체가 바라보는 방향에 벽이 있다면
		if (_tileList[(fObj_TilePos_X - 1) + fObj_TilePos_Y * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
		{
			if (_tileList[(fObj_TilePos_X - 1) + fObj_TilePos_Y * _mapInfo.tile_Count.x].rc.right > fObj->rc.left - PLAYER_HEAD_SPEED)
			{
				return true;
			}
		
		}
	}

	// 투사체가 날아가는 방향에 따라 다른 연산
	if (fObj->dir == FLYINGOBJECT_DIRECTION::RIGHT)
	{
		// 투사체가 바라보는 방향에 벽이 있다면
		if (_tileList[(fObj_TilePos_X + 1) + fObj_TilePos_Y * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
		{
			if (_tileList[(fObj_TilePos_X + 1) + fObj_TilePos_Y * _mapInfo.tile_Count.x].rc.left < fObj->rc.right + PLAYER_HEAD_SPEED)
			{
				return true;
			}
			
		}
	}


	//투사체가 충돌하지 않았다면 false 반환
	return false;
}

bool DataManager::Collision_FlyingObject_Ground(FlyingObjectInfo* fObj)
{
	// 투사체의 타일 인덱스를 저장할 공간
	short fObj_TilePos_X, fObj_TilePos_Y;

	// 투사체가 위치한 타일의 인덱스를 구한다.
	fObj_TilePos_X = fObj->center.x / TILE_SIZE_X;
	fObj_TilePos_Y = fObj->center.y / TILE_SIZE_Y;

	// 투사체의 아래 타일이 땅이라면
	if (_tileList[fObj_TilePos_X + (fObj_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND ||
		_tileList[fObj_TilePos_X + (fObj_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE &&
		_tileList[fObj_TilePos_X + (fObj_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type != COLLISION_TILE_TYPE::WALL_TYPE)
	{
		if (_tileList[fObj_TilePos_X + (fObj_TilePos_Y + 1) * _mapInfo.tile_Count.x].rc.top < fObj->rc.bottom)	return true;

	}

	// 투사체의 아래에 땅이 없을 경우.
	return false;
}

void DataManager::Collision_Skul_Head()
{
	// 스컬이 자신의 머리와 충돌 했을 경우에는
	// 스컬이 머리가 있는 상태로 바꿔줘야한다.
	// 또한 스킬을 사용 가능하게 만들어야 하고, 쿨타임 또한 초기화 해야한다.
	// 투사체로 사용한 스컬 머리 또한 삭제 해야한다.

	// 투사체 벡터 정보를 받아온다.
	vector<FlyingObjectInfo>* vFObj = _flyObj_Manager->get_vFlyingObj_Address();
	vector<FlyingObjectInfo>::iterator viFObj, viEnd;
	RECT tempRC;

	viEnd = vFObj->end();

	for (viFObj = vFObj->begin(); viFObj != viEnd;)
	{
		// 투사체의 타입이 스컬의 머리라면
		if ((*viFObj).type == FLYINFOBJECT_TYPE::SKUL_HEAD)
		{
			tempRC = (*viFObj).rc;
			tempRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
			tempRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

			// 스컬과 충돌을 했다면
			RECT temp;
			if (IntersectRect(&temp, &tempRC, &_skul->set_Info()->pos.rc) && (*viFObj).isFalling)
			{
				// 투사체 삭제
				viFObj = vFObj->erase(viFObj);

				// 스컬의 쿨타임 초기화, 스컬의 스킬 사용 초기화, 스컬의 상태 이미지 변화
				_skul->set_Info()->bool_V.useing_Skill_A = false;
				_skul->set_Info()->skill.skill_A_CoolTime_Cnt = 0;

				_skul->set_Info()->type.skul_Type = SKUL_TYPE::SKUL_WEAPON;
				_skul->set_Info()->bool_V.now_Ani_Change = true;

				_skul->set_Info()->bool_State_Reset();
				_skul->set_State(IdleState::getInstance());

				// 스킬 리셋 이펙트
				EFFECTMANAGER->play("throw_Head_Reset_Effct", 
					(_ui_Manager->get_UI_Address()->skill.rc_A.left + _ui_Manager->get_UI_Address()->skill.rc_A.right) / 2,
					(_ui_Manager->get_UI_Address()->skill.rc_A.top + _ui_Manager->get_UI_Address()->skill.rc_A.bottom) / 2);

				break;
			}

			//else viFObj++;
		}

		// 투사체의 타입이 화살이라면
		if ((*viFObj).type == FLYINFOBJECT_TYPE::ARROW)
		{
			tempRC = (*viFObj).rc;
			tempRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
			tempRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

			// 스컬과 충돌을 했다면
			RECT temp;
			if (IntersectRect(&temp, &tempRC, &_skul->set_Info()->pos.rc))
			{
				// 화살이 스컬과 충돌하면 이펙트를 만든다.
				if ((*viFObj).angle == 0)
				{
					EFFECTMANAGER->play("throw_Head_Effect_R",
						(*viFObj).center.x - 10 - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
						(*viFObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
				}
				
				if ((*viFObj).angle == 3.14f)
				{
					EFFECTMANAGER->play("throw_Head_Effect_L",
						(*viFObj).center.x + 40 - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
						(*viFObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
				}

				// 스컬의 체력을 감소
				// 공격을 실행하고, 공격을 했다는 bool값을 변경해준다.
				_skul->set_Info()->status.HP -= (*viFObj).attack;
				_ui_Manager->get_UI_Address()->hp.curHP = _skul->get_Info().status.HP;
				_ui_Manager->get_UI_Address()->hp.state = HP_UPDATE_STATE::HIT;

				// 투사체 삭제
				viFObj = vFObj->erase(viFObj);

				break;
			}
			//else viFObj++;

		}

		viFObj++;
	}

}

void DataManager::Collision_Skul_Head_Enemy(Enemy * enemy)
{
	// 투사체 벡터 정보를 받아온다.
	vector<FlyingObjectInfo>* vFObj = _flyObj_Manager->get_vFlyingObj_Address();
	vector<FlyingObjectInfo>::iterator viFObj, viEnd;
	RECT tempRC;
	RECT enemyRC = enemy->info_Address()->pos.hit_Range_Rc;

	viEnd = vFObj->end();

	for (viFObj = vFObj->begin(); viFObj != viEnd;)
	{
		// 투사체의 타입이 스컬의 머리라면
		if ((*viFObj).type == FLYINFOBJECT_TYPE::SKUL_HEAD)
		{
			tempRC = (*viFObj).rc;
			//tempRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			//tempRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			//tempRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
			//tempRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;


			// 에너미와 충돌 했다면
			RECT temp;
			if (IntersectRect(&temp, &tempRC, &enemyRC) && !(*viFObj).isHit)
			{
				// 투사체 튕기게하기
				// 추락중이지 않을때
				if (!(*viFObj).isFalling && !(*viFObj).isHit)
				{

					// 투사체의 방향에 따라 다른 연산
					if ((*viFObj).dir == FLYINGOBJECT_DIRECTION::LEFT)
					{
						(*viFObj).angle = 0;								// 반대 각도로 바꿔준다.
						(*viFObj).speed = 5;
						(*viFObj).isFalling = true;						// 추락중으로 바꿔준다.
						(*viFObj).isHit = true;

						// 투사체와 충돌한 벽에 이펙트를 만든다.
						EFFECTMANAGER->play("throw_Head_Effect_R",
							(*viFObj).center.x - 10 - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
							(*viFObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
					}


					else if ((*viFObj).dir == FLYINGOBJECT_DIRECTION::RIGHT)
					{
						(*viFObj).angle = 3.14;							// 반대 각도로 바꿔준다.
						(*viFObj).speed = 5;
						(*viFObj).isFalling = true;						// 추락중으로 바꿔준다.
						(*viFObj).isHit = true;

						// 투사체와 충돌한 벽에 이펙트를 만든다.
						EFFECTMANAGER->play("throw_Head_Effect_R",
							(*viFObj).center.x - 10 - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
							(*viFObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
					}
				}
			

				// 에너미 체력 감소
				// 출력되는 데미지를 넣어준다.
				enemy->info_Address()->status.show_Attack = 40;

				// 에너미의 체력이 단다. (스컬의 데미지 만큼)
				enemy->info_Address()->status.hp -= 40;
				enemy->info_Address()->hp.curHP = enemy->info_Address()->status.hp;

				// 피격 bool값을 true로 바꿔준다.
				enemy->info_Address()->bool_V.player_Attack_Hit = true;

				enemy->info_Address()->hp.state = HP_UPDATE_STATE_E::HIT;
				enemy->info_Address()->bool_V.im_Hit = true;

				// 에너미의 피격 시작 시간을 넣어준다.
				enemy->info_Address()->pos.lerp_Start = TIMEMANAGER->getWorldTime();

				// 만약 체력이 0 이하라면
				if (enemy->info_Address()->status.hp <= 0)
				{
					// 체력 0으로 보정
					enemy->info_Address()->status.hp = 0;

					// 에너미 사망 bool값 넣어주기.
					enemy->info_Address()->bool_V.im_Death = true;

				}

				break;
			}

			else viFObj++;
		}

		else viFObj++;

	}
}

void DataManager::enemy_Range_Check(Enemy* enemy_)
{
	RECT tempRC;
	RECT skulRC = _skul->get_Info().pos.rc;
	skulRC = plus_CameraPos(skulRC);
	RECT enemy_Short_Atk = enemy_->info_Address()->pos.attack_Range_Rc;
	RECT enemy_Long_Atk = enemy_->info_Address()->pos.long_Attack_Ranger_RC;
	RECT enemy_find_Range = enemy_->info_Address()->pos.find_Range_Rc;
	float skul_PosX = _skul->get_Info().pos.center.x;

	enemy_->info_Address()->status.state = EnemyStateEnum::IDLE;

	// 플레이어가 근접 공격 범위에 들어왔을 경우
	if (IntersectRect(&tempRC, &skulRC, &enemy_Short_Atk))
	{
		// 플레이어를 찾았다. 경계상태이기 때문에 인식 범위가 늘어난다.
		enemy_->info_Address()->bool_V.find_Player = true;

		// 에너미의 방향을 정해준다.
		// 스컬이 왼쪽에 있을 경우
		if (skul_PosX < enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::LEFT;
		// 스컬이 오른쪽에 있을 경우
		if (skul_PosX > enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::RIGHT;

		// 에너미는 근접 상태로 변경
		enemy_->info_Address()->status.state = EnemyStateEnum::ATK_A;

		return;
	}

	// 플레이어가 원거리 공격 범위에 들어왔을 경우
	if (IntersectRect(&tempRC, &skulRC, &enemy_Long_Atk))
	{
		// 플레이어를 찾았다. 경계상태이기 때문에 인식 범위가 늘어난다.
		enemy_->info_Address()->bool_V.find_Player = true;

		// 에너미의 방향을 정해준다.
		// 스컬이 왼쪽에 있을 경우
		if (skul_PosX < enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::LEFT;
		// 스컬이 오른쪽에 있을 경우
		if (skul_PosX > enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::RIGHT;

		// 원거리 상태로 변경c
		enemy_->info_Address()->status.state = EnemyStateEnum::ATK_B;
	
		return;
	}

	// 플레이어가 인식 범위에 들어왔을 경우
	if (IntersectRect(&tempRC, &skulRC, &enemy_find_Range))
	{
		// 플레이어를 찾았다. 경계상태이기 때문에 인식 범위가 늘어난다.
		enemy_->info_Address()->bool_V.find_Player = true;

		// 에너미의 방향을 정해준다.
		// 스컬이 왼쪽에 있을 경우
		if (skul_PosX < enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::LEFT;
		// 스컬이 오른쪽에 있을 경우
		if (skul_PosX > enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::RIGHT;

		//	이동 상태로 변경
		enemy_->info_Address()->status.state = EnemyStateEnum::WALK;

		return;
	}


}

bool DataManager::find_Player(Enemy* enemy_Address)
{
	// 플레이어가 인식범위 안에 있을때
	RECT tempRC;
	RECT skulRC = _skul->set_Info()->pos.rc;
	skulRC.left += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	skulRC.right += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	skulRC.top += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	skulRC.bottom += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	RECT enemyRC = enemy_Address->info_Address()->pos.find_Range_Rc;

	// 스컬이 인식범위에 들어와 있지만 공격 범위 밖에 있을때
	if (IntersectRect(&tempRC, &skulRC, &enemyRC) && !IntersectRect(&tempRC, &skulRC, &enemy_Address->info_Address()->pos.hit_Range_Rc))
	{
		// 플레이어의 x좌표를 비교하여 왼쪽에 있는지 오른쪽에 있는지 방향값을 넣어준다.
		// 스컬이 왼쪽에 있을때
		if (_skul->get_Info().pos.center.x <= enemy_Address->info_Address()->pos.center.x)
		{
			enemy_Address->info_Address()->status.dir = EnemyDirection::LEFT;
			
			return true;
		}

		// 스컬이 오른쪽에 있을때
		if (_skul->get_Info().pos.center.x  > enemy_Address->info_Address()->pos.center.x)
		{
			enemy_Address->info_Address()->status.dir = EnemyDirection::RIGHT;
			
			return true;
		}
	}

	// 스컬이 공격 범위 안에 들어왔을때
	if (IntersectRect(&tempRC, &skulRC, &enemy_Address->info_Address()->pos.hit_Range_Rc))
	{
		// 에너미가 공격 상태로 바뀐다.
		enemy_Address->info_Address()->bool_V.attackCheck = true;
		
		return true;
	}


	// 플레이어가 인식범위 밖에 있을떄
	return false;
}

bool DataManager::find_Attack_Range(Enemy * enemy_Address)
{
	RECT tempRC;
	RECT skulRC = _skul->set_Info()->pos.rc;
	skulRC.left += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	skulRC.right += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	skulRC.top += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	skulRC.bottom += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	RECT enemyRC = enemy_Address->info_Address()->pos.find_Range_Rc;

	// 스컬이 공격 범위 안에 들어왔을때
	if (IntersectRect(&tempRC, &skulRC, &enemy_Address->info_Address()->pos.hit_Range_Rc))
	{
		// 에너미가 공격 상태로 바뀐다.
		enemy_Address->info_Address()->bool_V.attackCheck = true;

		return true;
	}

	// 그렇지 않다면 false
	return false;
}

bool DataManager::escape_Player(Enemy * enemy_Address)
{
	RECT tempRC;
	RECT skulRC = _skul->set_Info()->pos.rc;
	skulRC.left += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	skulRC.right += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	skulRC.top += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	skulRC.bottom += CAMERAMANAGER->Use_Func()->get_CameraXY().y;

	// 플레이어가 왼쪽에서 사라졌을 경우
	if (enemy_Address->info_Address()->status.dir == EnemyDirection::LEFT)
	{
		// 플레이어의 x가 크다는건 에너미의 오른쪽에 있다는 뜻이다. 
		if (_skul->get_Info().pos.center.x > enemy_Address->info_Address()->pos.center.x)
		{
			return true;
		}

	}

	// 플레이어가 오른쪽에서 사라졌을 경우
	if (enemy_Address->info_Address()->status.dir == EnemyDirection::RIGHT)
	{
		// 플레이어의 x가 작다는건 에너미의 왼쪽에 있다는 뜻이다. 
		if (_skul->get_Info().pos.center.x  < enemy_Address->info_Address()->pos.center.x)
		{
			return true;
		}

	}

	// 에너미가 바라보는 방향에 에너미가 그대로 있을 경우
	return false;
}

bool DataManager::enemy_Find_Ground(Enemy * enemy_Address)
{
	// 에너미의 타일 인덱스를 저장할 공간
	int enemy_TilePos_X, enemy_TilePos_Y;

	// 에너미가 위치한 타일의 인덱스를 구한다.
	enemy_TilePos_X = (int)enemy_Address->info_Address()->pos.center.x / TILE_SIZE_X;
	enemy_TilePos_Y = (int)enemy_Address->info_Address()->pos.center.y / TILE_SIZE_Y;


	// 에너미의 방향이 왼쪽일때
	if (enemy_Address->info_Address()->status.dir == EnemyDirection::LEFT)
	{
		// 왼쪽 대각선 타일이 속성이 땅일 경우
		if (_tileList[(enemy_TilePos_X - 1) + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND)
		{
			// 에너미의 대각선 타일이 땅일 경우에는 ture 
			return true;
		}
	}

	// 에너미의 방향이 오른쪽일때
	if (enemy_Address->info_Address()->status.dir == EnemyDirection::RIGHT)
	{
		// 오른쪽 대각선 타일이 속성이 땅일 경우
		if (_tileList[(enemy_TilePos_X + 1) + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND)
		{
			// 에너미의 대각선 타일이 땅일 경우에는 ture 
			return true;
		}
	}

	// 땅이 아니라면 false
	return false;
}

void DataManager::enemy_Attack_Hit(Enemy * enemy_Address)
{
	// 아직 공격 받지 않았다면
	if (!enemy_Address->info_Address()->bool_V.Attack_Hit)
	{
		RECT temp;

		RECT skulRC = _skul->get_Info().pos.rc;
		skulRC.left += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		skulRC.right += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		skulRC.top += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		skulRC.bottom += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		
		// 에너미의 공격 렉트에 플레이어가 있었다면 
		if (IntersectRect(&temp, &enemy_Address->info_Address()->pos.Attack_Rc, &skulRC))
		{
			// 공격을 실행하고, 공격을 했다는 bool값을 변경해준다.
			_skul->set_Info()->status.HP -= enemy_Address->info_Address()->status.attack;
			_ui_Manager->get_UI_Address()->hp.curHP = _skul->get_Info().status.HP;
			_ui_Manager->get_UI_Address()->hp.state = HP_UPDATE_STATE::HIT;

			// 피격 이펙트
			EFFECTMANAGER->play("skul_Hit_Damage",
				_skul->get_Info().pos.center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x, _skul->get_Info().pos.center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);

			// 스컬의 체력이 0 이하로 내려갔다면 0으로 만들어준다.
			if (_skul->get_Info().status.HP < 0)
			{
				// 체력을 0으로 만들어준다.
				_skul->set_Info()->status.HP = 0;

				// 스컬이 죽었다.
				SCENEMANAGER->changeScene("GameOver");

			}

			// 공격을 성공했다면 true의 값을 가진다.
			enemy_Address->info_Address()->bool_V.Attack_Hit = true;

			// 공격이 끝났다면 다음 공격까지 렉트를 초기화한다.
			enemy_Address->info_Address()->pos.Attack_Rc = { 0,0,0,0 };
		}

	}


	
}

bool DataManager::enemy_Move_Wall(Enemy * enemy_Address, EnemyDirection dir, bool isBack)
{
	// 에너미의 타일 인덱스를 저장할 공간
	int enemy_TilePos_X, enemy_TilePos_Y;

	// 에너미가 위치한 타일의 인덱스를 구한다.
	enemy_TilePos_X = (int)enemy_Address->info_Address()->pos.center.x / TILE_SIZE_X;
	enemy_TilePos_Y = (int)enemy_Address->info_Address()->pos.center.y / TILE_SIZE_Y;


	if (isBack)
	{
		// 에너미의 등 뒤에 벽이 있는지
		if (dir == EnemyDirection::LEFT)
		{

			if (_tileList[(enemy_TilePos_X + 1) + enemy_TilePos_Y * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
			{
				if (enemy_Address->info_Address()->pos.hit_Range_Rc.right + enemy_Address->info_Address()->status.speed >= _tileList[(enemy_TilePos_X + 1) + enemy_TilePos_Y * _mapInfo.tile_Count.x].rc.left + 30)
				{
					return false;
				}
			}
		}

		if (dir == EnemyDirection::RIGHT)
		{
			if (_tileList[(enemy_TilePos_X - 1) + enemy_TilePos_Y * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
			{
				if (enemy_Address->info_Address()->pos.hit_Range_Rc.left - enemy_Address->info_Address()->status.speed <= _tileList[(enemy_TilePos_X - 1) + enemy_TilePos_Y * _mapInfo.tile_Count.x].rc.right - 30)
				{
					return false;
				}
			}
		}
	}

	if (!isBack)
	{
		// 에너미가 이동하려는 곳에 벽이 있는지
		if (dir == EnemyDirection::LEFT)
		{

			if (_tileList[(enemy_TilePos_X - 1) + enemy_TilePos_Y * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
			{
				if (enemy_Address->info_Address()->pos.hit_Range_Rc.left - enemy_Address->info_Address()->status.speed <= _tileList[(enemy_TilePos_X - 1) + enemy_TilePos_Y * _mapInfo.tile_Count.x].rc.right - 30)
				{
					return false;
				}
				
			}
		}

		if (dir == EnemyDirection::RIGHT)
		{
			if (_tileList[(enemy_TilePos_X + 1) + enemy_TilePos_Y * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
			{
				if (enemy_Address->info_Address()->pos.hit_Range_Rc.right + enemy_Address->info_Address()->status.speed >= _tileList[(enemy_TilePos_X + 1) + enemy_TilePos_Y * _mapInfo.tile_Count.x].rc.left + 30)
				{
					return false;
				}
			}
		}
	}


	// 에너미가 이동 하려는 방향에 타일이 벽이 아니라면 true
	return true;

}

bool DataManager::enemy_find_Down_Gorund(Enemy * enemy_Address)
{
	// 에너미의 타일 인덱스를 저장할 공간
	int enemy_TilePos_X, enemy_TilePos_Y;

	// 에너미가 위치한 타일의 인덱스를 구한다.
	enemy_TilePos_X = (int)enemy_Address->info_Address()->pos.center.x / TILE_SIZE_X;
	enemy_TilePos_Y = (int)enemy_Address->info_Address()->pos.center.y / TILE_SIZE_Y;

	// 에너미의 바닥이 땅이라면 true
	if (_tileList[enemy_TilePos_X + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND ||
		_tileList[enemy_TilePos_X + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{
		// 바닥이 땅이라면 바닥으로 값을 보정해주어야 한다.
		enemy_Address->info_Address()->pos.center.y = _tileList[enemy_TilePos_X + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].center.y - 69;

		return true;
	}

	// 에너미의 바닥이 땅이 아니라면
	return false;
}
