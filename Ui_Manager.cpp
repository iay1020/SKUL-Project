#include "stdafx.h"
#include "Ui_Manager.h"

Ui_Manager::Ui_Manager()
{
}


Ui_Manager::~Ui_Manager()
{
}

HRESULT Ui_Manager::init(Player* player_Address)
{
	// 플레이어 주소를 받아 저장한다.
	skul_Address = player_Address;

	// 기본 ui 초기화
	skul_UI_Info.base_Setting(player_Address);


	return S_OK;
}

void Ui_Manager::release()
{
}

void Ui_Manager::update()
{
}

void Ui_Manager::render()
{
	skul_UI_Info.show_Rect(getMemDC());

}
