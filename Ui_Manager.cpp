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
	// �÷��̾� �ּҸ� �޾� �����Ѵ�.
	skul_Address = player_Address;

	// �⺻ ui �ʱ�ȭ
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
