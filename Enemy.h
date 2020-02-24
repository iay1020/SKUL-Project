#pragma once

class EnemyState;

class Enemy
{
	EnemyState*		state;		// 에너미 상태
	EnemyInfo		info;		// 에너미 정보

public:
	Enemy();

	void init();
	void update();
	void render();

	// 겟터 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 에너미 정보 주소를 받아온다.
	EnemyInfo* info_Address() { return &info; }

	// 에너미의 상태를 받아온다.
	EnemyState* get_State() { return state; }

	// 셋터 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	// 에너미의 상태를 수정한다.
	void set_State(EnemyState* state);
		

};

