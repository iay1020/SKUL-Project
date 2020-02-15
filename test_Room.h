#pragma once
#include "gameNode.h"
#include "DataManager.h"
#include "CharacterState.h"
#include "Player.h"

class test_Room : public gameNode
{
private:

	vector<tagTileInfo>			tileList;							// 타일맵 정보를 담는다.
	tagMapInfo					mapInfo;							// 맵의 정보를 담는다.
	vector<tagSaveBackGround>	vMapInfo[BACKGROUND_LAYER_COUNT];	// 맵의 배경을 담는다.

	short						loopSpeed[5];

	Player*	_player;

public:
	test_Room();
	~test_Room();

	HRESULT init();
	void release();
	void update();
	void render();

	void testControl();

};

