#pragma once
#include "gameNode.h"

class Ui_Manager : public gameNode
{
	CharacterStatusUI	skul_UI_Info;
	Player*				skul_Address;

public:
	Ui_Manager();
	~Ui_Manager();

	HRESULT init(Player* player_Address);
	void release();
	void update();
	void render();


};

