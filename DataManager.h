#pragma once
#include "singletonBase.h"
#include "mapTool_Library.h"
#include "Player.h"
#include "CharacterState.h"
#include "Enemy.h"
#include "EnemyState.h"
#include "FlyingObject.h"
#include "EffectMaker.h"
#include "EnemyManager.h"
#include "Ui_Manager.h"

class DataManager : public singletonBase<DataManager>
{
private:
	vector<tagTileInfo>			_tileList;								// Ÿ�ϸ� ������ ��´�.
	tagMapInfo					_mapInfo;								// ���� ������ ��´�.
	vector<tagSaveBackGround>	_vMapInfo[BACKGROUND_LAYER_COUNT];		// ���� ����� ��´�.

	Player*						_skul;									// ���� ����

	FlyingObject*				_flyObj_Manager;						// ����ü �Ŵ���
	EffectMaker*				_effect_Maker;							// ����Ʈ �Ŵ���

	EnemyManager*				_enemyManager;							// ���ʹ� �Ŵ���

	Ui_Manager*					_ui_Manager;							// ui �Ŵ���
	vector<tagTileInfo>			minimap;								// �̴ϸ�

public:
	DataManager();		// ������
	~DataManager();		// �Ҹ���

	HRESULT init();
	void release();
	void update();

	// �������������������������������������������������������������������������������������������������� �� �Լ� ��������������������������������������������������������������������������������������������������������������������

	// �Ű������� �ִ� ���� ������ map ���Ϸ� ����ų�, map ������ �Ű������� �ִ´�.
	void map_Save(vector<tagTileInfo> tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo);	// ���� �����Ѵ�. (�Ű����� : Ÿ�ϸ���Ʈ, �� ����)
	void map_Load(vector<tagTileInfo>* tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo);	// ���� �ҷ��´�. (�Ű����� : Ÿ�ϸ���Ʈ �ּ�, �� ����) (Ÿ�ϸ���Ʈ�� �ּҰ� �ʿ��� ������ �� ������ ���� �־���� �ϱ� ������)

	// �Ű������� �ִ� ������ �׸���.
	void map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo);	// ���� �׷��ش�. (�Ű����� : ������ ����ִ� ������)
	void map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo,	// ���� �׷��ְ�, ���������ش�. (�Ű����� : �ӵ����� ����ִ� �迭5��)
		short loopSpd[]);

	// ������ �Ŵ����� �ִ� ������ ���� �����Ѵ�.
	void map_Load_Datamanager(string mapName, string mapInfoName);											// ���� �����͸Ŵ����� �����Ѵ�. (�Ű����� : ���̸�)

	// ������ �Ŵ����� �ִ� ������ ���� ����Ѵ�.
	void map_Render_Datamanager(HDC getMemDC);																// ���� �׷��ش�. (������ �Ŵ����� ����Ǿ� �ִ� ���� �׸���)
	void map_Render_Datamanager(HDC getMemDC, short loopSpd[]);												// ���� �׷��ְ�, ���������ش�. (�Ű����� : �ӵ����� ����ִ� �迭 5��)

	// ������ �Ŵ����� ���� �Ǿ� �ִ� ������ �̿��� ��Ʈ ���
	void Rect_Render_Datamanager(HDC getMemDC);

	// ������ �Ŵ��� ���� ����
	vector<tagTileInfo>* set_TileList() { return &_tileList; }												// Ÿ�ϸ� ���� �ּ�

	// ������ �Ŵ��� ���� ����
	vector<tagTileInfo> get_TileList() { return _tileList; }												// Ÿ�ϸ� ����

	// �� ���� ����
	tagMapInfo get_MapInfo() { return _mapInfo; }															// �� ����
	
	// �̴ϸ� ����
	void setting_MiniMap() { minimap = _ui_Manager->get_miniMap(); }

	// �������������������������������������������������������������������������������������������������� ĳ���� ���������������������������������������������������������������������������������������������������������������������

	// ������ �����Ѵ�.
	void create_Skul();

	// ������ �ּҸ� ��´�.
	Player* skul_Address() { return _skul; }

	// ������ ���� ��Ʈ�� ���ʹ��� ��Ʈ�� �浹 �ƴ���
	void skul_Attack_Range_Enemy(Enemy* enemy_Address);

	// �������������������������������������������������������������������������������������������������� �浹üũ ���������������������������������������������������������������������������������������������������������������������
	
	// �÷��̾� �Ʒ� Ÿ�Ͽ� ���� �ִ��� üũ (�÷��̾ �߶� �����϶� ���)
	bool Collision_PlayerFall_Ground();		

	// �÷��̾��� �� Ÿ���� ���� �ִ��� üũ (�÷��̾ ���� �����϶� ���)
	bool Collision_PlayerJump_Ground();

	// �÷��̾ �ٶ󺸴� ���⿡ ���� �ִ��� üũ
	bool Collision_Player_Wall();	

	// �÷��̾��� ���� ������ �ִ��� üũ
	bool Collision_Player_FootHold();
	// �÷��̾��� �Ʒ��� ������ �ִ��� üũ
	bool Collision_Player_FootHold_Down();

	// �÷��̾��� ��Ʈ�� ���� ��Ʈ�� �浹 �ߴ��� üũ
	bool Collision_Player_Trab();																		

	// ���������������������������������������������������������������������������������������������������� ��ƿ �������������������������������������������������������������������������������������������������������������������������

	// �������� �Լ� (�÷��̾�)
	void Lerp_Player();

	// �������� �Լ� (���ʹ�)
	void Lerp_Enemy(Enemy* enemy);

	// ���������������������������������������������������������������������������������������������������� ����ü �������������������������������������������������������������������������������������������������������������������������

	// ����ü �Ŵ����� �ּҸ� ��´�.
	FlyingObject* flyObj_Manager_Address() { return _flyObj_Manager; }

	// ����ü ���
	void show_FlyingObject() { _flyObj_Manager->Show_FlyingObj(); }

	// ����ü�� ���ư��� ���⿡ ���� �ִ��� üũ (�Ű����� : ����ü �ּ�)
	bool Collision_FlyingObject_Wall(FlyingObjectInfo* fObj);

	// ����ü�� �������� ���� ���� �ִ��� üũ (�Ű����� : ����ü �ּ�)
	bool Collision_FlyingObject_Ground(FlyingObjectInfo* fObj);

	// ����ü(���� �Ӹ�)�� ���ð� �浹 ���� ���
	void Collision_Skul_Head();

	// ���������������������������������������������������������������������������������������������������� ����Ʈ �������������������������������������������������������������������������������������������������������������������������

	// ����Ʈ �Ŵ����� �ּҸ� ��´�.
	EffectMaker* effect_Maker_Address() { return _effect_Maker; }

	// ����Ʈ ���
	void show_Effect() { _effect_Maker->render(); }


	// ���������������������������������������������������������������������������������������������������� ���ʹ� �������������������������������������������������������������������������������������������������������������������������

	// ���ʹ� �Ŵ����� �ּҸ� ��´�.
	EnemyManager* enemyManager_Address() { return _enemyManager; }

	// ���ʹ� ����
	void Create_Enemy(EnemyType type_V, EnemyDirection dir_V, string imgName, string aniName, float x_V, float y_V) 
	{ _enemyManager->Create_Enemy(type_V, dir_V, imgName, aniName, x_V, y_V); }

	// ���ʹ� �Ŵ��� ���
	void show_Enemy() { _enemyManager->render(); }

	// �÷��̾ �νĹ����� ���Դ��� üũ
	bool find_Player(Enemy* enemy_Address);

	// �÷��̾ ���ݹ����� ���Դ��� üũ
	bool find_Attack_Range(Enemy* enemy_Address);

	// ���ʹ̰� �̵��ϴ� ���⿡�� �÷��̾ ������� ���
	bool escape_Player(Enemy* enemy_Address);

	// ���ʹ̰� �̵��Ϸ��� Ÿ���� ���� �ƴ� ���
	bool enemy_Find_Ground(Enemy* enemy_Address);

	// ���ʹ��� ���� ��Ʈ�� �÷��̾ �浹 ������
	void enemy_Attack_Hit(Enemy* enemy_Address);

	// ���ʹ̰� �̵��Ϸ��� Ÿ���� ���� �ƴ� ���
	bool enemy_Move_Wall(Enemy* enemy_Address, EnemyDirection dir);

	// ���ʹ��� �Ʒ� Ÿ���� ���� �ƴ� ���
	bool enemy_find_Down_Gorund(Enemy* enemy_Address);

	// ���������������������������������������������������������������������������������������������������� Ui �Ŵ��� �������������������������������������������������������������������������������������������������������������������������

	// ui �Ŵ��� �ּ� ����
	Ui_Manager* ui_Address() { return _ui_Manager; }

	// ui ���̽� ����
	void setting_ui(Player* player_Address) { _ui_Manager->init(player_Address); }

	// ui ���
	void show_Ui() { _ui_Manager->render(); }

	


};


