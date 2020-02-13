#pragma once
#include "singletonBase.h"
#include "mapTool_Library.h"

class DataManager : public singletonBase<DataManager>
{
private:

public:
	DataManager();		// ������
	~DataManager();		// �Ҹ���

	HRESULT init();

	void map_Save(vector<tagTileInfo> tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo);	// ���� �����Ѵ�. (�Ű����� : Ÿ�ϸ���Ʈ, �� ����)
	void map_Load(vector<tagTileInfo>* tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo);	// ���� �ҷ��´�. (�Ű����� : Ÿ�ϸ���Ʈ �ּ�, �� ����) (Ÿ�ϸ���Ʈ�� �ּҰ� �ʿ��� ������ �� ������ ���� �־���� �ϱ� ������)
	void map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo);	// ���� �׷��ش�. (�Ű����� : ������ ����ִ� ������)
	void map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo,	// ���� �׷��ְ�, ���������ش�. (�Ű����� : �ӵ����� ����ִ� �迭5��)
		short loopSpd[]);
};

