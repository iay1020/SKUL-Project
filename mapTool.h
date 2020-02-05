#pragma once
#include "gameNode.h"
#include "mapTool_Library.h"


class mapTool : public gameNode
{
private:
	vector<tagTileInfo*>	_vTileList;			// ��ü Ÿ�� ����Ʈ

	tagPalletBar			_pallet_Bar;		// �ȷ�Ʈ �̵��� ���� �ȷ�Ʈ ��
	tagPallets				_pallets;			// ���� �ȷ�Ʈ�� ������ ��´�.

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void testMove();
};

