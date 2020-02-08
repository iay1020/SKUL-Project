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

	void map_Save(vector<tagTileInfo> tileList, tagMapInfo* mapInfo);	// ���� �����Ѵ�. (�Ű����� : Ÿ�ϸ���Ʈ, �� ����)
	void map_Load(vector<tagTileInfo>* tileList, tagMapInfo* mapInfo);	// ���� �ҷ��´�. (�Ű����� : Ÿ�ϸ���Ʈ �ּ�, �� ����) (Ÿ�ϸ���Ʈ�� �ּҰ� �ʿ��� ������ �� ������ ���� �־���� �ϱ� ������)

};
