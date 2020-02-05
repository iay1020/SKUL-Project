#pragma once
#include "gameNode.h"
#include "mapTool_Library.h"


class mapTool : public gameNode
{
private:
	vector<tagTileInfo*>	_vTileList;			// 전체 타일 리스트

	tagPalletBar			_pallet_Bar;		// 팔렛트 이동에 쓰일 팔렛트 바
	tagPallets				_pallets;			// 각종 팔렛트의 정보를 담는다.

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void testMove();
};

