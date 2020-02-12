#pragma once
#include "gameNode.h"
#include "DataManager.h"

class test_Room : public gameNode
{
private:

	DataManager	_DM;
	vector<tagTileInfo>			tileList;	// Ÿ�ϸ� ������ ��´�.
	tagMapInfo					mapInfo;	// ���� ������ ��´�.
	vector<tagSaveBackGround>	vMapInfo;	// ���� ����� ��´�.

public:
	test_Room();
	~test_Room();

	HRESULT init();
	void release();
	void update();
	void render();
};

