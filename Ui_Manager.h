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
	void render();

	// ���� UI ���� �ּ�
	CharacterStatusUI*	get_UI_Address() { return &skul_UI; }

	// �̴ϸ� ��Ʈ�� �����.
	void setting_MiniMap();

	// �̴ϸ� ���� ����
	//vector<tagTileInfo> get_miniMap() { return miniMap; }
	vector<tagTileInfo>& get_miniMap() { return miniMap; }

};

