#pragma once
#include "singletonBase.h"
#include "mapTool_Library.h"
#include "Player.h"
#include "CharacterState.h"

class DataManager : public singletonBase<DataManager>
{
private:
	vector<tagTileInfo>			_tileList;								// 타일맵 정보를 담는다.
	tagMapInfo					_mapInfo;								// 맵의 정보를 담는다.
	vector<tagSaveBackGround>	_vMapInfo[BACKGROUND_LAYER_COUNT];		// 맵의 배경을 담는다.

	Player*						_skul;

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

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 캐릭터 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

	// 스컬을 생성한다.
	void create_Skul();

	// 스컬의 주소를 얻는다.
	Player* skul_Address() { return _skul; }

	// ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ 충돌체크 ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	
	// 플레이어 아래 타일에 땅이 있는지 체크 (플레이어가 추락 상태일때 사용)
	bool Collision_PlayerFall_Ground();		

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
	void Lerp_Enemy();

};

