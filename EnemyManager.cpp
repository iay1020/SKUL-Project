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
	// ���ʹ� Ÿ�� �Ҵ�
	Enemy* new_Enemy = new Enemy;

	// ���ʹ� ������ �־��ش�.
	new_Enemy->info_Address()->Create_Enemy(type_V, dir_V, imgName, aniName, x_V, y_V);

	// ���ʹ� ������ ���Ϳ� �����Ѵ�.
	_vEnemyList.push_back(new_Enemy);
}
