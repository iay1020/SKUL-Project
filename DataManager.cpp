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
	// ���� �뽬 ��Ÿ�� �Լ�
	_skul->set_Info()->dash_CoolTime();

	// ���� ���� ������Ʈ
	_skul->update();

	// �׽�Ʈ�� ĳ���� Ŭ���� ü����
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

	// Ÿ�� ������ �߰� �Ǹ鼭 �ε����� �ٲ� Ÿ�ϵ��� �ٽ� ���� �����ش�.
	for (int y = 0; y < mapInfo->tile_Count.y; ++y)
	{
		for (int x = 0; x < mapInfo->tile_Count.x; ++x)
		{
			tileList[x + y * mapInfo->tile_Count.x].index.x = x;
			tileList[x + y * mapInfo->tile_Count.x].index.y = y;
		}
	}

	// ������ ������ �迭�� �Ȱ� ��´�. (�����͸� ���̺� �Ϸ��� ����ȭ ���Ѿ��ϴµ�, ���� ��ü�δ� �ȵƴ�)
	tagTileInfo* tile;
	tile = new tagTileInfo[mapInfo->tile_Count.x * mapInfo->tile_Count.y];	// Ÿ���� ũ�⸸ŭ �Ҵ� �޴´�.
																			// �迭�� ũ�⸦ ���� �� ���� ����θ� �����ϱ� ������

	for (int i = 0; i < tileList.size(); ++i)									// ���� �����ŭ �ݺ��ϸ� tile�� ���� ����ش�.
	{
		tile[i] = tileList[i];													// �迭�� ���� ������ ��� �ȱ��.
	}

	// ���� �����Ѵ�.
	file = CreateFile("tutorial.map", GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, tile, sizeof(tagTileInfo) * mapInfo->tile_Count.x * mapInfo->tile_Count.y, &write, NULL);
	
	CloseHandle(file);



	// ��׶��� ������ �� ���� �迭�� �Ȱ� ��´�.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		for (int j = 0; j < (vMapInfo[i]).size(); ++j)
		{
			mapInfo->_saveVInfo[i][j] = (vMapInfo[i])[j];
		}
		mapInfo->_vSize[i] = (vMapInfo[i]).size();	// �ҷ��ö� ���͸� ����� �ϱ� ���� ���� ����� �����Ѵ�.
	}
	
	// ���� ������ �����Ѵ�. (�ʿ� ���� ���� �������� �ִ�. ���Ŀ� ���⿡ ���� �Ǿ� �ִ� �� �̸��� ������ ������ ��)
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
	
	ReadFile(file, mapInfo, sizeof(tagMapInfo), &read, NULL);						// �� ������ ���� �޾� �� ������ ���� �޾ƿö� ���� ũ�� ������ �ʿ��ϱ� ������

	CloseHandle(file);

	// ���� ���� �ҷ����� Ÿ�� ����, ���� ����� �������ش�.
	CAMERAMANAGER->Use_Func()->set_Tile_CountX(mapInfo->tile_Count.x);														// ���� ������ ���� (�ʸ��� ���μ��ΰ� �ٸ��ϱ�)
	CAMERAMANAGER->Use_Func()->set_Tile_CountY(mapInfo->tile_Count.y);														// ���� ������ ����
	CAMERAMANAGER->Use_Func()->set_World_Size(mapInfo->tile_Count.x * TILE_SIZE_X, mapInfo->tile_Count.y * TILE_SIZE_Y);	// ���μ��ο� �°� ���� ������ ����


	// ������ �ִ� ���ʹ� ����ش�. (���ο� ������ �ֱ� ����)
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
	

	// �迭�� �ִ� ������ ���Ϳ� �Ȱܴ�´�.
	vector<tagSaveBackGround>	_moveData[BACKGROUND_LAYER_COUNT];

	// ����Ǿ� �ִ� �����ŭ �ݺ��Ѵ�.
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

	// ���� �޾� �� ������ �����.
	tagTileInfo* tile;
	tile = new tagTileInfo[mapInfo->tile_Count.x * mapInfo->tile_Count.y];			//	Ÿ���� ũ�⸸ŭ �Ҵ� �޴´�.

	file = CreateFile("tutorial.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, tile, sizeof(tagTileInfo) * mapInfo->tile_Count.x * mapInfo->tile_Count.y, &read, NULL);

	CloseHandle(file);

		// Ÿ�ϸ���Ʈ�� �ʱ�ȭ ���ش�.
	//while (tileList->size() > 0)
	//{
	//	tileList->erase(tileList->begin());
	//}
	tileList->clear();

	// ���� ����ִ� Ÿ���� ���Ϳ� �־��ش�.
	for (int i = 0; i < mapInfo->tile_Count.x * mapInfo->tile_Count.y; ++i)
	{
		tileList->push_back(tile[i]);
	}
	
}

void DataManager::map_Load_Datamanager(string mapName, string mapInfoName)
{
	// string�� char �迭�� �Ȱ� ��Ҵ�.
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
	
	ReadFile(file, &_mapInfo, sizeof(tagMapInfo), &read, NULL);						// �� ������ ���� �޾� �� ������ ���� �޾ƿö� ���� ũ�� ������ �ʿ��ϱ� ������
	
	CloseHandle(file);
	
	// ���� ���� �ҷ����� Ÿ�� ����, ���� ����� �������ش�.
	CAMERAMANAGER->Use_Func()->set_Tile_CountX(_mapInfo.tile_Count.x);															// ���� ������ ���� (�ʸ��� ���μ��ΰ� �ٸ��ϱ�)
	CAMERAMANAGER->Use_Func()->set_Tile_CountY(_mapInfo.tile_Count.y);															// ���� ������ ����
	CAMERAMANAGER->Use_Func()->set_World_Size(_mapInfo.tile_Count.x * TILE_SIZE_X, _mapInfo.tile_Count.y * TILE_SIZE_Y);		// ���μ��ο� �°� ���� ������ ����
	
	
	// ������ �ִ� ���ʹ� ����ش�. (���ο� ������ �ֱ� ����)
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
	
	// �迭�� �ִ� ������ ���Ϳ� �Ȱܴ�´�.
	vector<tagSaveBackGround>	_moveData[BACKGROUND_LAYER_COUNT];

	
	// ����Ǿ� �ִ� �����ŭ �ݺ��Ѵ�.
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
	
	// ���� �޾� �� ������ �����.
	tagTileInfo* tile;
	tile = new tagTileInfo[_mapInfo.tile_Count.x * _mapInfo.tile_Count.y];			//	Ÿ���� ũ�⸸ŭ �Ҵ� �޴´�.
	
	file = CreateFile("tutorial.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	ReadFile(file, tile, sizeof(tagTileInfo) * _mapInfo.tile_Count.x * _mapInfo.tile_Count.y, &read, NULL);
	
	CloseHandle(file);
	
	_tileList.clear();
	
	// ���� ����ִ� Ÿ���� ���Ϳ� �־��ش�.
	for (int i = 0; i < _mapInfo.tile_Count.x * _mapInfo.tile_Count.y; ++i)
	{
		_tileList.push_back(tile[i]);
	}

}

void DataManager::map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo)
{
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.

		// ��׶��带 �׷��ش�.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		if (vMapInfo[i].size() > 0)	// �ش� ���Ͱ� 0�̻��̿��߸� ����.
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

	// ���콺�� Ŭ���� Ÿ���� ã���ش�. (�� ȭ�鿡 �ִ� Ÿ�ϸ� ã�Ƽ�)
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

			// �� ���� Ÿ���� �����Ѵ�.
			if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
			{

				// ������ �׷��ش�.
				if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
				{
					if ((*tileList)[y * mapInfo.tile_Count.x + x].useTile)
					{

						IMAGEMANAGER->findImage((*tileList)[y * mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							(*tileList)[y * mapInfo.tile_Count.x + x].frame.ground.x, (*tileList)[y * mapInfo.tile_Count.x + x].frame.ground.y);
					}
				}

				// ���ڸ� �׷��ش�.
				if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
				{

				}
			}
		}
	}
}

void DataManager::map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo, short loopSpd[])
{
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.

	short loopSpeed[5];

	for (int i = 0; i < 5; ++i)
	{
		loopSpeed[i] = loopSpd[i];
	}

	// �ǳ� ġŲ �Դ´ٸ鼭 ġŲ �ȸԴ� ��� 
	// ���� ����!

	// ��׶��带 �׷��ش�.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{ 
		if (vMapInfo[i].size() > 0)	// �ش� ���Ͱ� 0�̻��̿��߸� ����.
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

	// ���콺�� Ŭ���� Ÿ���� ã���ش�. (�� ȭ�鿡 �ִ� Ÿ�ϸ� ã�Ƽ�)
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

			// �� ���� Ÿ���� �����Ѵ�.
			if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
			{

				// ������ �׷��ش�.
				if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
				{
					if ((*tileList)[y * mapInfo.tile_Count.x + x].useTile)
					{

						IMAGEMANAGER->findImage((*tileList)[y * mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							(*tileList)[y * mapInfo.tile_Count.x + x].frame.ground.x, (*tileList)[y * mapInfo.tile_Count.x + x].frame.ground.y);
					}
				}

				// ���ڸ� �׷��ش�.
				if ((*tileList)[y * mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
				{

				}
			}
		}
	}
}

void DataManager::map_Render_Datamanager(HDC getMemDC)
{
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.

		// ��׶��带 �׷��ش�.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		if (_vMapInfo[i].size() > 0)	// �ش� ���Ͱ� 0�̻��̿��߸� ����.
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

	// ���콺�� Ŭ���� Ÿ���� ã���ش�. (�� ȭ�鿡 �ִ� Ÿ�ϸ� ã�Ƽ�)
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

			// �� ���� Ÿ���� �����Ѵ�.
			if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
			{

				// ������ �׷��ش�.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
				{
					if (_tileList[y * _mapInfo.tile_Count.x + x].useTile)
					{

						IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);
					}
				}

				// ���ڸ� �׷��ش�.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
				{

				}
			}

			// �浹 Ÿ���� ���ٸ� �����Ѵ�.
			if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type != COLLISION_TILE_TYPE::NONE_TYPE)
			{
				// ���� Ÿ���� ǥ�����ش�.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);
					
				}

				// �� Ÿ���� ǥ�����ش�.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);
					
				}

				// ���� Ÿ���� ǥ�����ش�.
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
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.

	short loopSpeed[5];

	for (int i = 0; i < 5; ++i)
	{
		loopSpeed[i] = loopSpd[i];
	}

	// �ǳ� ġŲ �Դ´ٸ鼭 ġŲ �ȸԴ� ��� 
	// ���� ����!

	// ��׶��带 �׷��ش�.
	for (int i = 0; i < BACKGROUND_LAYER_COUNT; ++i)
	{
		if (_vMapInfo[i].size() > 0)	// �ش� ���Ͱ� 0�̻��̿��߸� ����.
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

	// ���콺�� Ŭ���� Ÿ���� ã���ش�. (�� ȭ�鿡 �ִ� Ÿ�ϸ� ã�Ƽ�)
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

			// �� ���� Ÿ���� �����Ѵ�.
			if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
			{

				// ������ �׷��ش�.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::GROUND)
				{
					if (_tileList[y * _mapInfo.tile_Count.x + x].useTile)
					{

						IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
							_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);
					}
				}

				// ���ڸ� �׷��ش�.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Type == TILE_TYPE::DECORATION)
				{

				}
			}

			// �浹 Ÿ���� ���ٸ� �����Ѵ�.
			if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type != COLLISION_TILE_TYPE::NONE_TYPE)
			{
				// ���� Ÿ���� ǥ�����ش�.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);

				}

				// �� Ÿ���� ǥ�����ش�.
				if (_tileList[y * _mapInfo.tile_Count.x + x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
				{
					IMAGEMANAGER->findImage(_tileList[y * _mapInfo.tile_Count.x + x].tileName.groundName)->frameRender(getMemDC, rc.left, rc.top,
						_tileList[y * _mapInfo.tile_Count.x + x].frame.ground.x, _tileList[y * _mapInfo.tile_Count.x + x].frame.ground.y);

				}

				// ���� Ÿ���� ǥ�����ش�.
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
	//  �׽�Ʈ�� ��Ʈ ���
	
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
	// ���� �⺻ ����
	_skul = new Player();
}

bool DataManager::Collision_PlayerFall_Ground()
{
	// ĳ������ Ÿ�� �ε����� ������ ����
	short player_TilePos_X, player_TilePos_Y;
	
	// ĳ���Ͱ� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// �÷��̾��� �Ʒ� Ÿ���� ���̶��
	if (_tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND ||
		_tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{
		
		// �÷��̾��� bottom�� �� top���� ��������
		if ((_skul->get_Info().pos.rc.bottom + CAMERAMANAGER->Use_Func()->get_CameraXY().y) - 20 < _tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].rc.top)
		{
			// �÷��̾��� ��ġ ����
			 _skul->set_Info()->pos.center.y = _tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].rc.top - TILE_SIZE_Y / 2;

			return true;
		}
	}

	// �÷��̾ �浹���� �ʾҴٸ� false ��ȯ
	return false;
}

bool DataManager::Collision_Player_Wall()
{
	// ĳ������ Ÿ�� �ε����� ������ ����
	short player_TilePos_X, player_TilePos_Y;

	// ĳ���Ͱ� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// ĳ���Ͱ� �ٶ󺸴� ���⿡ ���� �ٸ� ����
	if (_skul->get_InputKey() == PRESS_LEFT)
	{
		// �÷��̾ �ٶ󺸴� ���⿡ ���� �ִٸ�
		if (_tileList[(player_TilePos_X - 1) + player_TilePos_Y * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND)
		{
			// �÷��̾��� Left�� ���� Right���� ������
			if ((_skul->get_Info().pos.rc.left + CAMERAMANAGER->Use_Func()->get_CameraXY().x) - 5 < _tileList[(player_TilePos_X - 1) + player_TilePos_Y * _mapInfo.tile_Count.x].rc.right)
			{

				return true;
			}
		}
	}

	if (_skul->get_InputKey() == PRESS_RIGHT)
	{
		// �÷��̾ �ٶ󺸴� ���⿡ ���� �ִٸ�
		if (_tileList[(player_TilePos_X + 1) + player_TilePos_Y * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND)
		{
			// �÷��̾��� Right�� ���� Left���� ũ��
			if ((_skul->get_Info().pos.rc.right + CAMERAMANAGER->Use_Func()->get_CameraXY().x) + 5 > _tileList[(player_TilePos_X + 1) + player_TilePos_Y * _mapInfo.tile_Count.x].rc.left)
			{

				return true;
			}
		}
	}


	// �÷��̾ �浹���� �ʾҴٸ� false ��ȯ
	return false;
}

bool DataManager::Collision_Player_FootHold()
{
	// ĳ������ Ÿ�� �ε����� ������ ����
	short player_TilePos_X, player_TilePos_Y;

	// ĳ���Ͱ� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// �÷��̾��� ���� ������ �ִٸ�
	if (_tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{
		cout << "�÷��̾� bottom : " <<  _skul->get_Info().pos.rc.bottom + CAMERAMANAGER->Use_Func()->get_CameraXY().y << endl;
		cout << "������ bottom : " << _tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].rc.bottom << endl;

		// �÷��̾��� Top�� ���� Bottom���� ũ��
		if ((_skul->get_Info().pos.rc.bottom + CAMERAMANAGER->Use_Func()->get_CameraXY().y) > _tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].rc.bottom)
		{

			return true;
		}
	}

	// ������ ã�� ���ߴٸ�
	return false;
}

bool DataManager::Collision_Player_FootHold_Down()
{
	// ĳ������ Ÿ�� �ε����� ������ ����
	short player_TilePos_X, player_TilePos_Y;

	// ĳ���Ͱ� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// �÷��̾��� �Ʒ��� ������ �ִٸ�
	if (_tileList[player_TilePos_X + (player_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{
		return true;
		
	}

	// ������ ã�� ���ߴٸ�
	return false;
}

bool DataManager::Collision_Player_Trab()
{
	// �÷��̾ �浹�ߴٸ� true ��ȯ


	// �÷��̾ �浹���� �ʾҴٸ� false ��ȯ
	return false;
}

void DataManager::Lerp_Player()
{
	// ����ð�
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	// ���ǵ� ���ϱ�
	float lerp_Speed = (elapsedTime / PLAYER_DASH_TIME) * PLAYER_DASH_RANGE;

	// �̵� (���� �������� �̵� ������ �Ѵ�.)
	if (!DATAMANAGER->Collision_Player_Wall())
	{
		if (_skul->get_InputKey() == PRESS_RIGHT) _skul->set_Info()->pos.center.x += cosf(0) * lerp_Speed;
		if (_skul->get_InputKey() == PRESS_LEFT) _skul->set_Info()->pos.center.x += cosf(3.14) * lerp_Speed;

		// ī�޶� ��ġ ����
		CAMERAMANAGER->Use_Func()->set_CameraXY(_skul->get_Info().pos.center.x, _skul->get_Info().pos.center.y, true);

		// ��Ʈ ����
		_skul->update_Rect(PLAYER_RECT_SIZE_X, PLAYER_RECT_SIZE_Y);
		_skul->update_Ani_Rect();
	
	}

	// ���ߴ� ����
	if (_skul->get_Info().dash.Dash_StartTime + PLAYER_DASH_TIME < TIMEMANAGER->getWorldTime())
	{
		// ���� �ð����� �ʱ�ȭ
		_skul->set_Info()->dash.Dash_StartTime = TIMEMANAGER->getWorldTime();

		// bool �� ����
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
	// true�϶��� ���� (���ʹ� ����)

	// ƽ �ޱ�

	// ���ǵ� ���ϱ�

	// �̵�

	// ���ߴ� ����

	// bool �� ����
}
