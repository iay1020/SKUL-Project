#include "stdafx.h"
#include "DataManager.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

HRESULT DataManager::init()
{

	return S_OK;
}

void DataManager::map_Save(vector<tagTileInfo> tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo)
{
	HANDLE file;
	DWORD write;

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
	for (int i = 0; i < (vMapInfo[0]).size(); ++i)
	{
		mapInfo->_saveVInfo[0][i] = (vMapInfo[0])[i];
	}

	mapInfo->_vSize = (vMapInfo[0]).size();	// �ҷ��ö� ���͸� ����� �ϱ� ���� ���� ����� �����Ѵ�.
	
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

	
	// �迭�� �ִ� ������ ���Ϳ� �Ȱܴ�´�.
	vector<tagSaveBackGround>	_moveData;

	// ����Ǿ� �ִ� �����ŭ �ݺ��Ѵ�.
	for (int i = 0; i < mapInfo->_vSize; ++i)
	{
		tagSaveBackGround new_Data;
		new_Data.imageName = mapInfo->_saveVInfo[0][i].imageName;
		new_Data.rc = mapInfo->_saveVInfo[0][i].rc;
		_moveData.push_back(new_Data);
	}

	// ���� ���Ϳ� ������ �Ȱ��ش�.
	*vMapInfo = _moveData;


	// ���� �޾� �� ������ �����.
	tagTileInfo* tile;
	tile = new tagTileInfo[mapInfo->tile_Count.x * mapInfo->tile_Count.y];			//	Ÿ���� ũ�⸸ŭ �Ҵ� �޴´�.

	file = CreateFile("tutorial.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, tile, sizeof(tagTileInfo) * mapInfo->tile_Count.x * mapInfo->tile_Count.y, &read, NULL);

	CloseHandle(file);

	// ���� ����ִ� Ÿ���� ���Ϳ� �־��ش�.
	for (int i = 0; i < (*tileList).size(); ++i)
	{
		(*tileList)[i] = tile[i];
	}

}
