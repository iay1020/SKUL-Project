#pragma once
#include "gameNode.h"
#include "DataManager.h"

struct playerInfo
{
	POINTFLOAT	center;
	RECT		rc;
	float		speed;
	image*		img;
	animation*	ani;
};

class test_Room : public gameNode
{
private:

	vector<tagTileInfo>			tileList;							// Ÿ�ϸ� ������ ��´�.
	tagMapInfo					mapInfo;							// ���� ������ ��´�.
	vector<tagSaveBackGround>	vMapInfo[BACKGROUND_LAYER_COUNT];	// ���� ����� ��´�.

	playerInfo					testP;
	short						loopSpeed[5];

public:
	test_Room();
	~test_Room();

	HRESULT init();
	void release();
	void update();
	void render();

	void testControl();
	void testSetting_Player();

};

