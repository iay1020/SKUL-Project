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

		// 만약 죽은 에너미는 삭제한다.
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
	// 에너미 타입 할당
	Enemy* new_Enemy = new Enemy;

	// 에너미 변수 초기화
	new_Enemy->info_Address()->All_ReSet();

	// 에너미 정보를 넣어준다.
	new_Enemy->info_Address()->Create_Enemy(type_V, dir_V, imgName, aniName, x_V, y_V);

	// 에너미의 기본 상태를 넣어준다.
	new_Enemy->set_State(IdleState_E::getInstance());

	// 에너미 정보를 벡터에 저장한다.
	_vEnemyList.push_back(new_Enemy);

}
