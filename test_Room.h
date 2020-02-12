#pragma once
#include "gameNode.h"
#include "DataManager.h"

class test_Room : public gameNode
{
private:

	DataManager	_DM;
	vector<tagTileInfo>			tileList;	// 타일맵 정보를 담는다.
	tagMapInfo					mapInfo;	// 맵의 정보를 담는다.
	vector<tagSaveBackGround>	vMapInfo;	// 맵의 배경을 담는다.

public:
	test_Room();
	~test_Room();

	HRESULT init();
	void release();
	void update();
	void render();
};

