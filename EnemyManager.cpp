#include "stdafx.h"
#include "EnemyManager.h"


EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}

HRESULT EnemyManager::init()
{
	return S_OK;
}

void EnemyManager::release()
{
}

void EnemyManager::update()
{

}

void EnemyManager::render()
{
}

void EnemyManager::Create_Enemy(EnemyType type_V, EnemyDirection dir_V, string imgName, string aniName, float x_V, float y_V)
{
	// 에너미 타입 할당
	Enemy* new_Enemy = new Enemy;

	// 에너미 정보를 넣어준다.
	new_Enemy->info_Address()->Create_Enemy(type_V, dir_V, imgName, aniName, x_V, y_V);

	// 에너미 정보를 벡터에 저장한다.
	_vEnemyList.push_back(new_Enemy);
}
