#pragma once
#include "gameNode.h"

class Ui_Manager : public gameNode
{
private:
	CharacterStatusUI	skul_UI;
	Player*				skul_Address;
	
	vector<tagTileInfo>	miniMap;

public:
	Ui_Manager();
	~Ui_Manager();

	HRESULT init(Player* player_Address);
	void release();
	void update();
	void render(Player* skul);

	// 스컬 UI 정보 주소
	CharacterStatusUI*	get_UI_Address() { return &skul_UI; }

	// 미니맵 렉트를 만든다.
	void setting_MiniMap();

	// 미니맵 정보 겟터
	//vector<tagTileInfo> get_miniMap() { return miniMap; }
	vector<tagTileInfo>& get_miniMap() { return miniMap; }

};

