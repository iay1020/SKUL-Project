#pragma once
#include "gameNode.h"
#include "mapTool_Library.h"


class mapTool : public gameNode
{
private:
	tagMapInfo				_mapInfo;			// 맵 정보 저장

	vector<tagTileInfo>		_vTileList;			// 전체 타일 리스트

	tagPallets				_pallet;			// 각종 팔렛트의 정보를 담는다.

	tagButton_Info			_button;			// 버튼 정보를 담는다.

	mapTool_Func			_mapTool_Func;		// 맵툴 함수

public:
	mapTool();
	~mapTool();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void testMove();							// 테스트 카메라 이동 함수
	void Find_Worker();							// 버튼에 따라 실행 해야 하는 함수를 호출한다.
};

