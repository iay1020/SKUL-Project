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
	for (int i = 0; i < (vMapInfo[0]).size(); ++i)
	{
		mapInfo->_saveVInfo[0][i] = (vMapInfo[0])[i];
	}

	mapInfo->_vSize = (vMapInfo[0]).size();	// 불러올때 벡터를 재생성 하기 위해 현재 사이즈를 저장한다.
	
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

	
	// 배열에 있던 정보를 벡터에 옴겨담는다.
	vector<tagSaveBackGround>	_moveData;

	// 저장되어 있던 사이즈만큼 반복한다.
	for (int i = 0; i < mapInfo->_vSize; ++i)
	{
		tagSaveBackGround new_Data;
		new_Data.imageName = mapInfo->_saveVInfo[0][i].imageName;
		new_Data.rc = mapInfo->_saveVInfo[0][i].rc;
		_moveData.push_back(new_Data);
	}

	// 기존 벡터에 정보를 옴겨준다.
	*vMapInfo = _moveData;


	// 맵을 받아 올 변수를 만든다.
	tagTileInfo* tile;
	tile = new tagTileInfo[mapInfo->tile_Count.x * mapInfo->tile_Count.y];			//	타일의 크기만큼 할당 받는다.

	file = CreateFile("tutorial.map", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, tile, sizeof(tagTileInfo) * mapInfo->tile_Count.x * mapInfo->tile_Count.y, &read, NULL);

	CloseHandle(file);

	// 맵이 들어있는 타일을 벡터에 넣어준다.
	for (int i = 0; i < (*tileList).size(); ++i)
	{
		(*tileList)[i] = tile[i];
	}

}
