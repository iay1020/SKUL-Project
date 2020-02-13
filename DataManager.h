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

	void map_Save(vector<tagTileInfo> tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo);	// 맵을 저장한다. (매개변수 : 타일리스트, 맵 정보)
	void map_Load(vector<tagTileInfo>* tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo);	// 맵을 불러온다. (매개변수 : 타일리스트 주소, 맵 정보) (타일리스트의 주소가 필요한 이유는 맵 정보를 새로 넣어줘야 하기 때문에)
	void map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo);	// 맵을 그려준다. (매개변수 : 정보가 들어있는 변수들)
	void map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo,	// 맵을 그려주고, 루프시켜준다. (매개변수 : 속도값이 들어있는 배열5개)
		short loopSpd[]);
};

