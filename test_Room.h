#pragma once
#include "gameNode.h"
#include "DataManager.h"
#include "CharacterState.h"
#include "Player.h"

class test_Room : public gameNode
{
private:

	vector<tagTileInfo>			tileList;							// Ÿ�ϸ� ������ ��´�.
	tagMapInfo					mapInfo;							// ���� ������ ��´�.
	vector<tagSaveBackGround>	vMapInfo[BACKGROUND_LAYER_COUNT];	// ���� ����� ��´�.

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

