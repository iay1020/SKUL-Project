#pragma once
#include "gameNode.h"
#include "mapTool_Library.h"


class mapTool : public gameNode
{
private:
	tagMapInfo*				_mapInfo;			// �� ���� ����
	vector<tagTileInfo*>	_vTileList;			// ��ü Ÿ�� ����Ʈ

	tagPallets*				_pallet;			// ���� �ȷ�Ʈ�� ������ ��´�.

	tagButton_Info			_button;			// ��ư ������ ��´�.

	mapTool_Func			_mapTool_Func;		// ���� �Լ�

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void testMove();							// �׽�Ʈ ī�޶� �̵� �Լ�
};

