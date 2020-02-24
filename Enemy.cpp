#include "stdafx.h"
#include "Enemy.h"


Enemy::Enemy()
{
	// 기본 상태 초기화

}

void Enemy::set_State(EnemyState* state)
{
	this->state = state;
}

void Enemy::init()
{
}

void Enemy::update()
{
}

void Enemy::render()
{
}
