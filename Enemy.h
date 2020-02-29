#pragma once

class EnemyState;

class Enemy
{
	EnemyState*		state;		// ���ʹ� ����
	EnemyInfo		info;		// ���ʹ� ����

public:
	Enemy();

	void init();
	void update();
	void render(HDC getMemDC);

	// ���� ���������������������������������������������������������������������
	// ���ʹ� ���� �ּҸ� �޾ƿ´�.
	EnemyInfo* info_Address() { return &info; }

	// ���ʹ��� ���¸� �޾ƿ´�.
	EnemyState* get_State() { return state; }

	// ���� ���������������������������������������������������������������������
	// ���ʹ��� ���¸� �����Ѵ�.
	void set_State(EnemyState* state);
		
	// ���ʹ��� ���� �Լ��� ȣ���Ѵ�.
	void call_StateFunc(EnemyStateEnum state_, EnemyState* state);
};

