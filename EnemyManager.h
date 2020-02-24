#pragma once
#include "gameNode.h"

class EnemyManager : public gameNode
{
private:
	vector<Enemy*>					_vEnemyList;		// 에너미 정보를 담는 벡터
	vector<Enemy*>::iterator		_viEnemyList;		// 에너미 정보를 담는 벡터의 반복자

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// 에너미 생성
	void Create_Enemy(EnemyType type_V, EnemyDirection dir_V,
		string imgName, string aniName, float x_V, float y_V);

};

