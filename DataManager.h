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
	vector<tagTileInfo>			_tileList;								// 타일맵 정보를 담는다.
	tagMapInfo					_mapInfo;								// 맵의 정보를 담는다.
	vector<tagSaveBackGround>	_vMapInfo[BACKGROUND_LAYER_COUNT];		// 맵의 배경을 담는다.

	Player*						_skul;									// 스컬 정보

	FlyingObject*				_flyObj_Manager;						// 투사체 매니저
	EffectMaker*				_effect_Maker;							// 이펙트 매니저

	EnemyManager*				_enemyManager;							// 에너미 매니저

	Ui_Manager*					_ui_Manager;							// ui 매니저
	vector<tagTileInfo>			minimap;								// 미니맵

public:
	DataManager();		// 생성자
	~DataManager();		// 소멸자

	HRESULT init();
	void release();
	void update();

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 맵 함수 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	// 매개변수에 있는 맵의 정보를 map 파일로 만들거나, map 파일을 매개변수에 넣는다.
	void map_Save(vector<tagTileInfo> tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo);	// 맵을 저장한다. (매개변수 : 타일리스트, 맵 정보)
	void map_Load(vector<tagTileInfo>* tileList, tagMapInfo* mapInfo, vector<tagSaveBackGround>* vMapInfo);	// 맵을 불러온다. (매개변수 : 타일리스트 주소, 맵 정보) (타일리스트의 주소가 필요한 이유는 맵 정보를 새로 넣어줘야 하기 때문에)

	// 매개변수에 있는 정보를 그린다.
	void map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo);	// 맵을 그려준다. (매개변수 : 정보가 들어있는 변수들)
	void map_Render(HDC getMemDC, vector<tagTileInfo>* tileList, tagMapInfo mapInfo, vector<tagSaveBackGround>* vMapInfo,	// 맵을 그려주고, 루프시켜준다. (매개변수 : 속도값이 들어있는 배열5개)
		short loopSpd[]);

	// 데이터 매니저에 있는 변수에 맵을 저장한다.
	void map_Load_Datamanager(string mapName, string mapInfoName);											// 맵을 데이터매니저에 저장한다. (매개변수 : 맵이름)

	// 데이터 매니저에 있는 변수의 맵을 출력한다.
	void map_Render_Datamanager(HDC getMemDC);																// 맵을 그려준다. (데이터 매니저에 저장되어 있는 맵을 그린다)
	void map_Render_Datamanager(HDC getMemDC, short loopSpd[]);												// 맵을 그려주고, 루프시켜준다. (매개변수 : 속도값이 들어있는 배열 5개)

	// 데이터 매니저에 저장 되어 있는 정보를 이용해 렉트 출력
	void Rect_Render_Datamanager(HDC getMemDC);

	// 데이터 매니저 정보 셋터
	vector<tagTileInfo>* set_TileList() { return &_tileList; }												// 타일맵 정보 주소

	// 데이터 매니저 정보 겟터
	vector<tagTileInfo> get_TileList() { return _tileList; }												// 타일맵 정보

	// 맵 정보 겟터
	tagMapInfo get_MapInfo() { return _mapInfo; }															// 맵 정보
	
	// 미니맵 셋팅
	void setting_MiniMap() { minimap = _ui_Manager->get_miniMap(); }

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 캐릭터 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	// 스컬을 생성한다.
	void create_Skul();

	// 스컬의 주소를 얻는다.
	Player* skul_Address() { return _skul; }

	// 스컬의 공격 렉트에 에너미의 렉트가 충돌 됐는지
	void skul_Attack_Range_Enemy(Enemy* enemy_Address);

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 충돌체크 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	
	// 플레이어 아래 타일에 땅이 있는지 체크 (플레이어가 추락 상태일때 사용)
	bool Collision_PlayerFall_Ground();		

	// 플레이어의 위 타일이 땅이 있는지 체크 (플레이어가 점프 상태일때 사용)
	bool Collision_PlayerJump_Ground();

	// 플레이어가 바라보는 방향에 벽이 있는지 체크
	bool Collision_Player_Wall();	

	// 플레이어의 위에 발판이 있는지 체크
	bool Collision_Player_FootHold();
	// 플레이어의 아래에 발판이 있는지 체크
	bool Collision_Player_FootHold_Down();

	// 플레이어의 렉트가 함정 렉트와 충돌 했는지 체크
	bool Collision_Player_Trab();																		

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 유틸 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	// 선형보간 함수 (플레이어)
	void Lerp_Player();

	// 선형보간 함수 (에너미)
	void Lerp_Enemy(Enemy* enemy);

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 투사체 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	// 투사체 매니저의 주소를 얻는다.
	FlyingObject* flyObj_Manager_Address() { return _flyObj_Manager; }

	// 투사체 출력
	void show_FlyingObject() { _flyObj_Manager->Show_FlyingObj(); }

	// 투사체가 날아가는 방향에 벽이 있는지 체크 (매개변수 : 투사체 주소)
	bool Collision_FlyingObject_Wall(FlyingObjectInfo* fObj);

	// 투사체가 떨어지는 곳에 땅이 있는지 체크 (매개변수 : 투사체 주소)
	bool Collision_FlyingObject_Ground(FlyingObjectInfo* fObj);

	// 투사체(스컬 머리)가 스컬과 충돌 했을 경우
	void Collision_Skul_Head();

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 이펙트 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	// 이펙트 매니저의 주소를 얻는다.
	EffectMaker* effect_Maker_Address() { return _effect_Maker; }

	// 이펙트 출력
	void show_Effect() { _effect_Maker->render(); }


	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 에너미 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	// 에너미 매니저의 주소를 얻는다.
	EnemyManager* enemyManager_Address() { return _enemyManager; }

	// 에너미 생성
	void Create_Enemy(EnemyType type_V, EnemyDirection dir_V, string imgName, string aniName, float x_V, float y_V) 
	{ _enemyManager->Create_Enemy(type_V, dir_V, imgName, aniName, x_V, y_V); }

	// 에너미 매니저 출력
	void show_Enemy() { _enemyManager->render(); }

	// 플레이어가 인식범위에 들어왔는지 체크
	bool find_Player(Enemy* enemy_Address);

	// 플레이어가 공격범위에 들어왔는지 체크
	bool find_Attack_Range(Enemy* enemy_Address);

	// 에너미가 이동하는 방향에서 플레이어가 사라졌을 경우
	bool escape_Player(Enemy* enemy_Address);

	// 에너미가 이동하려는 타일이 땅이 아닐 경우
	bool enemy_Find_Ground(Enemy* enemy_Address);

	// 에너미의 공격 렉트에 플레이어가 충돌 했을때
	void enemy_Attack_Hit(Enemy* enemy_Address);

	// 에너미가 이동하려는 타일이 벽이 아닐 경우
	bool enemy_Move_Wall(Enemy* enemy_Address, EnemyDirection dir);

	// 에너미의 아래 타일이 땅이 아닐 경우
	bool enemy_find_Down_Gorund(Enemy* enemy_Address);

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ Ui 매니저 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	// ui 매니저 주소 겟터
	Ui_Manager* ui_Address() { return _ui_Manager; }

	// ui 베이스 셋팅
	void setting_ui(Player* player_Address) { _ui_Manager->init(player_Address); }

	// ui 출력
	void show_Ui() { _ui_Manager->render(); }

	


};


