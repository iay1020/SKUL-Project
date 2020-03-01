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
	// ����ü �Ŵ��� �Ҵ�
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
	// ���ʹ� �Ŵ��� ������Ʈ
	_enemyManager->update();

	// ���� ���� ������Ʈ
	_skul->update();

	// UI ������Ʈ
	_ui_Manager->update();

	// ����ü �Ŵ��� ������Ʈ
	_flyObj_Manager->update();

	// ����ü �浹 �Լ�
	Collision_Skul_Head();

	// Ű�ִϸŴ��� ������Ʈ
	KEYANIMANAGER->update();

	// ����Ʈ�Ŵ��� ������Ʈ
	EFFECTMANAGER->update();

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
	file = CreateFile("Intro.map", GENERIC_WRITE, 0, NULL,
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

	file = CreateFile("Stage_1.map", GENERIC_READ, 0, NULL,
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

void DataManager::map_Load(vector<tagTileInfo>* tileList, tagMapInfo * mapInfo, vector<tagSaveBackGround>* vMapInfo, string mapName, string mapInfoName)
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

	file = CreateFile(strMapName, GENERIC_READ, 0, NULL,
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
	
	file = CreateFile(strMapName, GENERIC_READ, 0, NULL,
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

void DataManager::map_Render_Datamanager_Loop(HDC getMemDC)
{
	CAMERAMANAGER->Use_Func()->find_Tile(CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_X, CAMERAMANAGER->Use_Func()->get_Camera_Operation()._TILE_COUNT_Y);	// ī�޶� �ȿ� ���� Ÿ���� ã�Ƽ� �����Ѵ�.

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

				IMAGEMANAGER->findImage((_vMapInfo[i])[j].imageName)->loopRender(getMemDC, &rc, CAMERAMANAGER->Use_Func()->get_CameraXY().x * i * 0.1f, 0);
			}
		}
	}

	// ���콺�� Ŭ���� Ÿ���� ã���ش�. (�� ȭ�鿡 �ִ� Ÿ�ϸ� ã�Ƽ�)
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
	//		// �̴ϸ� ��� ���
	//		// �� ���� Ÿ���� �����Ѵ�.
	//		if (minimap[y * _mapInfo.tile_Count.x + x].tile_Type != TILE_TYPE::EMPTY)
	//		{
	//
	//			// ������ �׷��ش�.
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

	// �÷��̾� ��Ʈ
	//int index = (int)((_skul->get_Info().pos.center.x / TILE_SIZE_X)) +
	//	((int)(_skul->get_Info().pos.center.y) / TILE_SIZE_Y * _mapInfo.tile_Count.x);
	//
	//IMAGEMANAGER->findImage("miniMap_Player")->render(getMemDC, minimap[index].rc.left , minimap[index].rc.top - 8);
	////Rectangle(getMemDC, minimap[index].rc.left + 1280, minimap[index].rc.top - 8 + 680, minimap[index].rc.right + 1280, minimap[index].rc.bottom + 680);
	//
	//// �̴ϸ� ������
	//IMAGEMANAGER->findImage("miniMap_Frame")->render(getMemDC, 1175, 700);
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

void DataManager::scene_Changer()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		// ���� ������ �̵��Ѵ�.
		SCENEMANAGER->changeScene("mapTool");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		// ���� ������ �̵��Ѵ�.
		SCENEMANAGER->changeScene("Stage_0");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F3))
	{
		// ���� ������ �̵��Ѵ�.
		SCENEMANAGER->changeScene("Stage_1");
	}
}

void DataManager::create_Skul()
{
	// ���� �⺻ ����
	_skul = new Player();
}

void DataManager::skul_Attack_Range_Enemy(Enemy* enemy_Address)
{
	// ������ ���� ��Ʈ�� ���ʹ��� ��Ʈ�� �浹 ���� ��� ����

	RECT temp;
	RECT SkulRC = _skul->get_Info().pos.Attack_RC;
	//SkulRC.left += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	//SkulRC.right += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	//SkulRC.top += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	//SkulRC.bottom += CAMERAMANAGER->Use_Func()->get_CameraXY().y;

	// ��Ʈ �浹��
	if (IntersectRect(&temp, &SkulRC, &enemy_Address->info_Address()->pos.hit_Range_Rc))
	{
		short RNum;
		RNum = RND->getInt(10) + 1;

		bool isCritical = false;

		if (RNum == 1 || RNum == 2 || RNum == 3 || RNum == 4 || RNum == 5) isCritical = true;

		// ���� �±� ���̶��
		if (!enemy_Address->info_Address()->bool_V.player_Attack_Hit)
		{
			// �ǰ� �������� ��� �� ��ġ�� ����ش�.
			enemy_Address->info_Address()->pos.damege_Center.x = enemy_Address->info_Address()->pos.center.x;
			enemy_Address->info_Address()->pos.damege_Center.y = enemy_Address->info_Address()->pos.ani_Rc.top;

			// �ǰ� ����Ʈ
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

				// �ּ� ���ݷ� ~ �ִ� ���ݷ±��� �������� �޴´�.
				short RndAttack = 0;
				RndAttack = RND->getInt(_skul->get_Info().status.Atk) + (_skul->get_Info().status.Atk - 5);

				// ��µǴ� �������� �־��ش�.
				enemy_Address->info_Address()->status.show_Attack = RndAttack;

				// ���ʹ��� ü���� �ܴ�. (������ ������ ��ŭ)
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

				// �ּ� ���ݷ� ~ �ִ� ���ݷ±��� �������� �޴´�.
				short RndAttack = 0;
				RndAttack = RND->getInt(_skul->get_Info().status.Atk) + (_skul->get_Info().status.Atk - 5);

				// ��µǴ� �������� �־��ش�.
				enemy_Address->info_Address()->status.show_Attack = RndAttack;

				// ���ʹ��� ü���� �ܴ�. (������ ������ ��ŭ)
				enemy_Address->info_Address()->status.hp -= RndAttack * 2;
				enemy_Address->info_Address()->hp.curHP = enemy_Address->info_Address()->status.hp;
			}

			// �ǰ� bool���� true�� �ٲ��ش�.
			enemy_Address->info_Address()->bool_V.player_Attack_Hit = true;
			
			enemy_Address->info_Address()->hp.state = HP_UPDATE_STATE_E::HIT;
			enemy_Address->info_Address()->bool_V.im_Hit = true;

			// ���ʹ��� �ǰ� ���� �ð��� �־��ش�.
			enemy_Address->info_Address()->pos.lerp_Start = TIMEMANAGER->getWorldTime();

			// ���� ü���� 0 ���϶��
			if (enemy_Address->info_Address()->status.hp <= 0)
			{
				// ü�� 0���� ����
				enemy_Address->info_Address()->status.hp = 0;

				// ���ʹ� ��� bool�� �־��ֱ�.
				enemy_Address->info_Address()->bool_V.im_Death = true;

			}
		}

	}

}

void DataManager::skul_Collision_Event(RECT eventRC)
{
	// ������ �̺�Ʈ������ ���ٸ�

	// �ش� �̺�Ʈ ��ġ�� �����̵��Ѵ�.


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

bool DataManager::Collision_PlayerJump_Ground()
{
	// ĳ������ Ÿ�� �ε����� ������ ����
	short player_TilePos_X, player_TilePos_Y;

	// ĳ���Ͱ� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	player_TilePos_X = (int)_skul->get_Info().pos.center.x / TILE_SIZE_X;
	player_TilePos_Y = (int)_skul->get_Info().pos.center.y / TILE_SIZE_Y;

	// �÷��̾��� �� Ÿ���� ���̶��
	if (_tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND &&
		_tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].tile_Collision_Type != COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{

		// �÷��̾��� bottom�� �� top���� ��������
		if ((_skul->get_Info().pos.rc.top + CAMERAMANAGER->Use_Func()->get_CameraXY().y) - 10 < _tileList[player_TilePos_X + (player_TilePos_Y - 1) * _mapInfo.tile_Count.x].rc.bottom)
		{
			// �÷��̾ ���� �浹 ������ ���� ��ġ�� �����ش�.
			_skul->set_Info()->jump.jump_Value = 0;

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

		_skul->set_Info()->jump.jump_Value = 0;
	}

}

void DataManager::Lerp_Enemy(Enemy* enemy, float time_, float range_)
{
	// ����ð�
	float elapsedTime = TIMEMANAGER->getElapsedTime();

	// ���ǵ� ���ϱ�
	float lerp_Speed = (elapsedTime / time_) * range_;

	// �ǰ� ���϶�
	if (enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// �̵� (���� �������� �̵� ������ �Ѵ�.)
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

			// ��Ʈ ����
			enemy->info_Address()->update_Rect();
		}
	}

	if (!enemy->info_Address()->bool_V.player_Attack_Hit)
	{
		// �̵� (���� �������� �̵� ������ �Ѵ�.)
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

			// ��Ʈ ����
			enemy->info_Address()->update_Rect();
		}
	}

	// ���ߴ� ����
	if (enemy->info_Address()->pos.lerp_Start + time_ <= TIMEMANAGER->getWorldTime())
	{
	
		// ���� �ð����� �ʱ�ȭ
		enemy->info_Address()->pos.lerp_Start = TIMEMANAGER->getWorldTime();
	
		// bool �� ����
		enemy->info_Address()->bool_V.hitCheck = false;
		enemy->info_Address()->bool_V.lerping = false;

		enemy->info_Address()->cool_Time.attack_CoolTime_Cnt = 0;
		enemy->info_Address()->bool_V.attackCheck = false;

		enemy->info_Address()->bool_V.Attack_Hit = false;

		// ���� ���̶�� 
		enemy->info_Address()->bool_V.atk_End = true;

		// ���� �ĵ�����Ŭ ���ش�.
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
	// ����ü�� Ÿ�� �ε����� ������ ����
	int fObj_TilePos_X, fObj_TilePos_Y;

	// ����ü�� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	fObj_TilePos_X = (int)fObj->center.x / TILE_SIZE_X;
	fObj_TilePos_Y = (int)fObj->center.y / TILE_SIZE_Y;

	// ����ü�� ���ư��� ���⿡ ���� �ٸ� ����
	if (fObj->dir == FLYINGOBJECT_DIRECTION::LEFT)
	{
		// ����ü�� �ٶ󺸴� ���⿡ ���� �ִٸ�
		if (_tileList[(fObj_TilePos_X - 1) + fObj_TilePos_Y * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
		{
			if (_tileList[(fObj_TilePos_X - 1) + fObj_TilePos_Y * _mapInfo.tile_Count.x].rc.right > fObj->rc.left - PLAYER_HEAD_SPEED)
			{
				return true;
			}
		
		}
	}

	// ����ü�� ���ư��� ���⿡ ���� �ٸ� ����
	if (fObj->dir == FLYINGOBJECT_DIRECTION::RIGHT)
	{
		// ����ü�� �ٶ󺸴� ���⿡ ���� �ִٸ�
		if (_tileList[(fObj_TilePos_X + 1) + fObj_TilePos_Y * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::WALL_TYPE)
		{
			if (_tileList[(fObj_TilePos_X + 1) + fObj_TilePos_Y * _mapInfo.tile_Count.x].rc.left < fObj->rc.right + PLAYER_HEAD_SPEED)
			{
				return true;
			}
			
		}
	}


	//����ü�� �浹���� �ʾҴٸ� false ��ȯ
	return false;
}

bool DataManager::Collision_FlyingObject_Ground(FlyingObjectInfo* fObj)
{
	// ����ü�� Ÿ�� �ε����� ������ ����
	short fObj_TilePos_X, fObj_TilePos_Y;

	// ����ü�� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	fObj_TilePos_X = fObj->center.x / TILE_SIZE_X;
	fObj_TilePos_Y = fObj->center.y / TILE_SIZE_Y;

	// ����ü�� �Ʒ� Ÿ���� ���̶��
	if (_tileList[fObj_TilePos_X + (fObj_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND ||
		_tileList[fObj_TilePos_X + (fObj_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE &&
		_tileList[fObj_TilePos_X + (fObj_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type != COLLISION_TILE_TYPE::WALL_TYPE)
	{
		if (_tileList[fObj_TilePos_X + (fObj_TilePos_Y + 1) * _mapInfo.tile_Count.x].rc.top < fObj->rc.bottom)	return true;

	}

	// ����ü�� �Ʒ��� ���� ���� ���.
	return false;
}

void DataManager::Collision_Skul_Head()
{
	// ������ �ڽ��� �Ӹ��� �浹 ���� ��쿡��
	// ������ �Ӹ��� �ִ� ���·� �ٲ�����Ѵ�.
	// ���� ��ų�� ��� �����ϰ� ������ �ϰ�, ��Ÿ�� ���� �ʱ�ȭ �ؾ��Ѵ�.
	// ����ü�� ����� ���� �Ӹ� ���� ���� �ؾ��Ѵ�.

	// ����ü ���� ������ �޾ƿ´�.
	vector<FlyingObjectInfo>* vFObj = _flyObj_Manager->get_vFlyingObj_Address();
	vector<FlyingObjectInfo>::iterator viFObj, viEnd;
	RECT tempRC;

	viEnd = vFObj->end();

	for (viFObj = vFObj->begin(); viFObj != viEnd;)
	{
		// ����ü�� Ÿ���� ������ �Ӹ����
		if ((*viFObj).type == FLYINFOBJECT_TYPE::SKUL_HEAD)
		{
			tempRC = (*viFObj).rc;
			tempRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
			tempRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

			// ���ð� �浹�� �ߴٸ�
			RECT temp;
			if (IntersectRect(&temp, &tempRC, &_skul->set_Info()->pos.rc) && (*viFObj).isFalling)
			{
				// ����ü ����
				viFObj = vFObj->erase(viFObj);

				// ������ ��Ÿ�� �ʱ�ȭ, ������ ��ų ��� �ʱ�ȭ, ������ ���� �̹��� ��ȭ
				_skul->set_Info()->bool_V.useing_Skill_A = false;
				_skul->set_Info()->skill.skill_A_CoolTime_Cnt = 0;

				_skul->set_Info()->type.skul_Type = SKUL_TYPE::SKUL_WEAPON;
				_skul->set_Info()->bool_V.now_Ani_Change = true;

				_skul->set_Info()->bool_State_Reset();
				_skul->set_State(IdleState::getInstance());

				// ��ų ���� ����Ʈ
				EFFECTMANAGER->play("throw_Head_Reset_Effct", 
					(_ui_Manager->get_UI_Address()->skill.rc_A.left + _ui_Manager->get_UI_Address()->skill.rc_A.right) / 2,
					(_ui_Manager->get_UI_Address()->skill.rc_A.top + _ui_Manager->get_UI_Address()->skill.rc_A.bottom) / 2);

				break;
			}

			//else viFObj++;
		}

		// ����ü�� Ÿ���� ȭ���̶��
		if ((*viFObj).type == FLYINFOBJECT_TYPE::ARROW)
		{
			tempRC = (*viFObj).rc;
			tempRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			tempRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
			tempRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;

			// ���ð� �浹�� �ߴٸ�
			RECT temp;
			if (IntersectRect(&temp, &tempRC, &_skul->set_Info()->pos.rc))
			{
				// ȭ���� ���ð� �浹�ϸ� ����Ʈ�� �����.
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

				// ������ ü���� ����
				// ������ �����ϰ�, ������ �ߴٴ� bool���� �������ش�.
				_skul->set_Info()->status.HP -= (*viFObj).attack;
				_ui_Manager->get_UI_Address()->hp.curHP = _skul->get_Info().status.HP;
				_ui_Manager->get_UI_Address()->hp.state = HP_UPDATE_STATE::HIT;

				// ����ü ����
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
	// ����ü ���� ������ �޾ƿ´�.
	vector<FlyingObjectInfo>* vFObj = _flyObj_Manager->get_vFlyingObj_Address();
	vector<FlyingObjectInfo>::iterator viFObj, viEnd;
	RECT tempRC;
	RECT enemyRC = enemy->info_Address()->pos.hit_Range_Rc;

	viEnd = vFObj->end();

	for (viFObj = vFObj->begin(); viFObj != viEnd;)
	{
		// ����ü�� Ÿ���� ������ �Ӹ����
		if ((*viFObj).type == FLYINFOBJECT_TYPE::SKUL_HEAD)
		{
			tempRC = (*viFObj).rc;
			//tempRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			//tempRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			//tempRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
			//tempRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;


			// ���ʹ̿� �浹 �ߴٸ�
			RECT temp;
			if (IntersectRect(&temp, &tempRC, &enemyRC) && !(*viFObj).isHit)
			{
				// ����ü ƨ����ϱ�
				// �߶������� ������
				if (!(*viFObj).isFalling && !(*viFObj).isHit)
				{

					// ����ü�� ���⿡ ���� �ٸ� ����
					if ((*viFObj).dir == FLYINGOBJECT_DIRECTION::LEFT)
					{
						(*viFObj).angle = 0;								// �ݴ� ������ �ٲ��ش�.
						(*viFObj).speed = 5;
						(*viFObj).isFalling = true;						// �߶������� �ٲ��ش�.
						(*viFObj).isHit = true;

						// ����ü�� �浹�� ���� ����Ʈ�� �����.
						EFFECTMANAGER->play("throw_Head_Effect_R",
							(*viFObj).center.x - 10 - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
							(*viFObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
					}


					else if ((*viFObj).dir == FLYINGOBJECT_DIRECTION::RIGHT)
					{
						(*viFObj).angle = 3.14;							// �ݴ� ������ �ٲ��ش�.
						(*viFObj).speed = 5;
						(*viFObj).isFalling = true;						// �߶������� �ٲ��ش�.
						(*viFObj).isHit = true;

						// ����ü�� �浹�� ���� ����Ʈ�� �����.
						EFFECTMANAGER->play("throw_Head_Effect_R",
							(*viFObj).center.x - 10 - CAMERAMANAGER->Use_Func()->get_CameraXY().x,
							(*viFObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
					}
				}
			

				// ���ʹ� ü�� ����
				// ��µǴ� �������� �־��ش�.
				enemy->info_Address()->status.show_Attack = 40;

				// ���ʹ��� ü���� �ܴ�. (������ ������ ��ŭ)
				enemy->info_Address()->status.hp -= 40;
				enemy->info_Address()->hp.curHP = enemy->info_Address()->status.hp;

				// �ǰ� bool���� true�� �ٲ��ش�.
				enemy->info_Address()->bool_V.player_Attack_Hit = true;

				enemy->info_Address()->hp.state = HP_UPDATE_STATE_E::HIT;
				enemy->info_Address()->bool_V.im_Hit = true;

				// ���ʹ��� �ǰ� ���� �ð��� �־��ش�.
				enemy->info_Address()->pos.lerp_Start = TIMEMANAGER->getWorldTime();

				// ���� ü���� 0 ���϶��
				if (enemy->info_Address()->status.hp <= 0)
				{
					// ü�� 0���� ����
					enemy->info_Address()->status.hp = 0;

					// ���ʹ� ��� bool�� �־��ֱ�.
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

	// �÷��̾ ���� ���� ������ ������ ���
	if (IntersectRect(&tempRC, &skulRC, &enemy_Short_Atk))
	{
		// �÷��̾ ã�Ҵ�. �������̱� ������ �ν� ������ �þ��.
		enemy_->info_Address()->bool_V.find_Player = true;

		// ���ʹ��� ������ �����ش�.
		// ������ ���ʿ� ���� ���
		if (skul_PosX < enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::LEFT;
		// ������ �����ʿ� ���� ���
		if (skul_PosX > enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::RIGHT;

		// ���ʹ̴� ���� ���·� ����
		enemy_->info_Address()->status.state = EnemyStateEnum::ATK_A;

		return;
	}

	// �÷��̾ ���Ÿ� ���� ������ ������ ���
	if (IntersectRect(&tempRC, &skulRC, &enemy_Long_Atk))
	{
		// �÷��̾ ã�Ҵ�. �������̱� ������ �ν� ������ �þ��.
		enemy_->info_Address()->bool_V.find_Player = true;

		// ���ʹ��� ������ �����ش�.
		// ������ ���ʿ� ���� ���
		if (skul_PosX < enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::LEFT;
		// ������ �����ʿ� ���� ���
		if (skul_PosX > enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::RIGHT;

		// ���Ÿ� ���·� ����c
		enemy_->info_Address()->status.state = EnemyStateEnum::ATK_B;
	
		return;
	}

	// �÷��̾ �ν� ������ ������ ���
	if (IntersectRect(&tempRC, &skulRC, &enemy_find_Range))
	{
		// �÷��̾ ã�Ҵ�. �������̱� ������ �ν� ������ �þ��.
		enemy_->info_Address()->bool_V.find_Player = true;

		// ���ʹ��� ������ �����ش�.
		// ������ ���ʿ� ���� ���
		if (skul_PosX < enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::LEFT;
		// ������ �����ʿ� ���� ���
		if (skul_PosX > enemy_->info_Address()->pos.center.x) enemy_->info_Address()->status.dir = EnemyDirection::RIGHT;

		//	�̵� ���·� ����
		enemy_->info_Address()->status.state = EnemyStateEnum::WALK;

		return;
	}


}

bool DataManager::find_Player(Enemy* enemy_Address)
{
	// �÷��̾ �νĹ��� �ȿ� ������
	RECT tempRC;
	RECT skulRC = _skul->set_Info()->pos.rc;
	skulRC.left += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	skulRC.right += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	skulRC.top += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	skulRC.bottom += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	RECT enemyRC = enemy_Address->info_Address()->pos.find_Range_Rc;

	// ������ �νĹ����� ���� ������ ���� ���� �ۿ� ������
	if (IntersectRect(&tempRC, &skulRC, &enemyRC) && !IntersectRect(&tempRC, &skulRC, &enemy_Address->info_Address()->pos.hit_Range_Rc))
	{
		// �÷��̾��� x��ǥ�� ���Ͽ� ���ʿ� �ִ��� �����ʿ� �ִ��� ���Ⱚ�� �־��ش�.
		// ������ ���ʿ� ������
		if (_skul->get_Info().pos.center.x <= enemy_Address->info_Address()->pos.center.x)
		{
			enemy_Address->info_Address()->status.dir = EnemyDirection::LEFT;
			
			return true;
		}

		// ������ �����ʿ� ������
		if (_skul->get_Info().pos.center.x  > enemy_Address->info_Address()->pos.center.x)
		{
			enemy_Address->info_Address()->status.dir = EnemyDirection::RIGHT;
			
			return true;
		}
	}

	// ������ ���� ���� �ȿ� ��������
	if (IntersectRect(&tempRC, &skulRC, &enemy_Address->info_Address()->pos.hit_Range_Rc))
	{
		// ���ʹ̰� ���� ���·� �ٲ��.
		enemy_Address->info_Address()->bool_V.attackCheck = true;
		
		return true;
	}


	// �÷��̾ �νĹ��� �ۿ� ������
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

	// ������ ���� ���� �ȿ� ��������
	if (IntersectRect(&tempRC, &skulRC, &enemy_Address->info_Address()->pos.hit_Range_Rc))
	{
		// ���ʹ̰� ���� ���·� �ٲ��.
		enemy_Address->info_Address()->bool_V.attackCheck = true;

		return true;
	}

	// �׷��� �ʴٸ� false
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

	// �÷��̾ ���ʿ��� ������� ���
	if (enemy_Address->info_Address()->status.dir == EnemyDirection::LEFT)
	{
		// �÷��̾��� x�� ũ�ٴ°� ���ʹ��� �����ʿ� �ִٴ� ���̴�. 
		if (_skul->get_Info().pos.center.x > enemy_Address->info_Address()->pos.center.x)
		{
			return true;
		}

	}

	// �÷��̾ �����ʿ��� ������� ���
	if (enemy_Address->info_Address()->status.dir == EnemyDirection::RIGHT)
	{
		// �÷��̾��� x�� �۴ٴ°� ���ʹ��� ���ʿ� �ִٴ� ���̴�. 
		if (_skul->get_Info().pos.center.x  < enemy_Address->info_Address()->pos.center.x)
		{
			return true;
		}

	}

	// ���ʹ̰� �ٶ󺸴� ���⿡ ���ʹ̰� �״�� ���� ���
	return false;
}

bool DataManager::enemy_Find_Ground(Enemy * enemy_Address)
{
	// ���ʹ��� Ÿ�� �ε����� ������ ����
	int enemy_TilePos_X, enemy_TilePos_Y;

	// ���ʹ̰� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	enemy_TilePos_X = (int)enemy_Address->info_Address()->pos.center.x / TILE_SIZE_X;
	enemy_TilePos_Y = (int)enemy_Address->info_Address()->pos.center.y / TILE_SIZE_Y;


	// ���ʹ��� ������ �����϶�
	if (enemy_Address->info_Address()->status.dir == EnemyDirection::LEFT)
	{
		// ���� �밢�� Ÿ���� �Ӽ��� ���� ���
		if (_tileList[(enemy_TilePos_X - 1) + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND)
		{
			// ���ʹ��� �밢�� Ÿ���� ���� ��쿡�� ture 
			return true;
		}
	}

	// ���ʹ��� ������ �������϶�
	if (enemy_Address->info_Address()->status.dir == EnemyDirection::RIGHT)
	{
		// ������ �밢�� Ÿ���� �Ӽ��� ���� ���
		if (_tileList[(enemy_TilePos_X + 1) + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND)
		{
			// ���ʹ��� �밢�� Ÿ���� ���� ��쿡�� ture 
			return true;
		}
	}

	// ���� �ƴ϶�� false
	return false;
}

void DataManager::enemy_Attack_Hit(Enemy * enemy_Address)
{
	// ���� ���� ���� �ʾҴٸ�
	if (!enemy_Address->info_Address()->bool_V.Attack_Hit)
	{
		RECT temp;

		RECT skulRC = _skul->get_Info().pos.rc;
		skulRC.left += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		skulRC.right += CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		skulRC.top += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		skulRC.bottom += CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		
		// ���ʹ��� ���� ��Ʈ�� �÷��̾ �־��ٸ� 
		if (IntersectRect(&temp, &enemy_Address->info_Address()->pos.Attack_Rc, &skulRC))
		{
			// ������ �����ϰ�, ������ �ߴٴ� bool���� �������ش�.
			_skul->set_Info()->status.HP -= enemy_Address->info_Address()->status.attack;
			_ui_Manager->get_UI_Address()->hp.curHP = _skul->get_Info().status.HP;
			_ui_Manager->get_UI_Address()->hp.state = HP_UPDATE_STATE::HIT;

			// �ǰ� ����Ʈ
			EFFECTMANAGER->play("skul_Hit_Damage",
				_skul->get_Info().pos.center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x, _skul->get_Info().pos.center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);

			// ������ ü���� 0 ���Ϸ� �������ٸ� 0���� ������ش�.
			if (_skul->get_Info().status.HP < 0)
			{
				// ü���� 0���� ������ش�.
				_skul->set_Info()->status.HP = 0;

				// ������ �׾���.
				SCENEMANAGER->changeScene("GameOver");

			}

			// ������ �����ߴٸ� true�� ���� ������.
			enemy_Address->info_Address()->bool_V.Attack_Hit = true;

			// ������ �����ٸ� ���� ���ݱ��� ��Ʈ�� �ʱ�ȭ�Ѵ�.
			enemy_Address->info_Address()->pos.Attack_Rc = { 0,0,0,0 };
		}

	}


	
}

bool DataManager::enemy_Move_Wall(Enemy * enemy_Address, EnemyDirection dir, bool isBack)
{
	// ���ʹ��� Ÿ�� �ε����� ������ ����
	int enemy_TilePos_X, enemy_TilePos_Y;

	// ���ʹ̰� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	enemy_TilePos_X = (int)enemy_Address->info_Address()->pos.center.x / TILE_SIZE_X;
	enemy_TilePos_Y = (int)enemy_Address->info_Address()->pos.center.y / TILE_SIZE_Y;


	if (isBack)
	{
		// ���ʹ��� �� �ڿ� ���� �ִ���
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
		// ���ʹ̰� �̵��Ϸ��� ���� ���� �ִ���
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


	// ���ʹ̰� �̵� �Ϸ��� ���⿡ Ÿ���� ���� �ƴ϶�� true
	return true;

}

bool DataManager::enemy_find_Down_Gorund(Enemy * enemy_Address)
{
	// ���ʹ��� Ÿ�� �ε����� ������ ����
	int enemy_TilePos_X, enemy_TilePos_Y;

	// ���ʹ̰� ��ġ�� Ÿ���� �ε����� ���Ѵ�.
	enemy_TilePos_X = (int)enemy_Address->info_Address()->pos.center.x / TILE_SIZE_X;
	enemy_TilePos_Y = (int)enemy_Address->info_Address()->pos.center.y / TILE_SIZE_Y;

	// ���ʹ��� �ٴ��� ���̶�� true
	if (_tileList[enemy_TilePos_X + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Type == TILE_TYPE::GROUND ||
		_tileList[enemy_TilePos_X + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].tile_Collision_Type == COLLISION_TILE_TYPE::FOOTHOLD_TYPE)
	{
		// �ٴ��� ���̶�� �ٴ����� ���� �������־�� �Ѵ�.
		enemy_Address->info_Address()->pos.center.y = _tileList[enemy_TilePos_X + (enemy_TilePos_Y + 1) * _mapInfo.tile_Count.x].center.y - 69;

		return true;
	}

	// ���ʹ��� �ٴ��� ���� �ƴ϶��
	return false;
}
