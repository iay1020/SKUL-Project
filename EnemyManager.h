#pragma once
class EnemyManager
{
private:
	vector<Enemy*>					_vEnemyList;		// ���ʹ� ������ ��� ����
	vector<Enemy*>::iterator		_viEnemyList;		// ���ʹ� ������ ��� ������ �ݺ���

public:
	EnemyManager();
	~EnemyManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// ���ʹ� ����
	void Create_Enemy(EnemyType type_V, EnemyDirection dir_V,
		string imgName, string aniName, float x_V, float y_V);

};

