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
	while (_vEnemyList.size() > 0)
	{
		_vEnemyList.erase(_vEnemyList.begin());
	}
}

void EnemyManager::update()
{
	for (_viEnemyList = _vEnemyList.begin(); _viEnemyList != _vEnemyList.end();)
	{

		(*_viEnemyList)->update();

		// ���� ���� ���ʹ̴� �����Ѵ�.
		if ((*_viEnemyList)->info_Address()->bool_V.im_Death)
		{
			EFFECTMANAGER->play("enemy_Die_Effect", 
				(*_viEnemyList)->info_Address()->pos.center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x, 
				(*_viEnemyList)->info_Address()->pos.center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y);
			_viEnemyList = _vEnemyList.erase(_viEnemyList);
		}
		else
			++_viEnemyList;
	}
}

void EnemyManager::render()
{
	for (_viEnemyList = _vEnemyList.begin(); _viEnemyList != _vEnemyList.end(); ++_viEnemyList)
	{
		(*_viEnemyList)->render(getMemDC());
	}
}

void EnemyManager::Create_Enemy(EnemyType type_V, EnemyDirection dir_V, string imgName, string aniName, float x_V, float y_V)
{
	// ���ʹ� Ÿ�� �Ҵ�
	Enemy* new_Enemy = new Enemy;

	// ���ʹ� ���� �ʱ�ȭ
	new_Enemy->info_Address()->All_ReSet();

	// ���ʹ� ������ �־��ش�.
	new_Enemy->info_Address()->Create_Enemy(type_V, dir_V, imgName, aniName, x_V, y_V);

	// ���ʹ��� �⺻ ���¸� �־��ش�.
	new_Enemy->set_State(IdleState_E::getInstance());

	// ���ʹ� ������ ���Ϳ� �����Ѵ�.
	_vEnemyList.push_back(new_Enemy);

}
