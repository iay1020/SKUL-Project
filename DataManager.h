#pragma once
#include "singletonBase.h"
#include "mapTool_Library.h"

class DataManager : public singletonBase<DataManager>
{
private:

public:
	DataManager();		// 생성자
	~DataManager();		// 소멸자

	HRESULT init();

	void map_Save(vector<tagTileInfo> tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround> vMapInfo);	// 맵을 저장한다. (매개변수 : 타일리스트, 맵 정보)
	void map_Load(vector<tagTileInfo>* tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo);	// 맵을 불러온다. (매개변수 : 타일리스트 주소, 맵 정보) (타일리스트의 주소가 필요한 이유는 맵 정보를 새로 넣어줘야 하기 때문에)

};

