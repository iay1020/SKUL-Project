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
	skul_UI.base_Setting(player_Address);

	return S_OK;
}

void Ui_Manager::release()
{
}

void Ui_Manager::update()
{
	skul_UI.update_HP();

	skul_UI.update_Img(skul_Address);

	// 테스트용 치트키
	if (KEYMANAGER->isOnceKeyDown(VK_F9))
	{
		skul_UI.hp.curHP += 10;
		skul_UI.hp.state = HP_UPDATE_STATE::HEAL;
		skul_Address->set_Info()->status.HP += 10;
		if (skul_UI.hp.curHP >= skul_UI.hp.maxHP)
		{
			skul_UI.hp.curHP = skul_UI.hp.maxHP;
			skul_Address->set_Info()->status.HP = skul_UI.hp.maxHP;
		}

	}
}

void Ui_Manager::render(Player* skul)
{
	skul_UI.show_Ui(getMemDC(), skul);

}

void Ui_Manager::setting_MiniMap()
{
	// 만약 사용중이라면 비워준다. (새로운 스테이지에선 새로 받아야 한다.)
	if (miniMap.size() > 0) miniMap.clear();

	// 맵 리스트에 있는 정보를 옴겨온다.
	vector<tagTileInfo> map = DATAMANAGER->get_TileList();

	// 맵 정보를 미니맵에 옴긴다.
	for (int i = 0; i < map.size(); ++i)
	{
		tagTileInfo new_Info;

		new_Info.rc = RectMake(5 + map[i].index.x * 16 + 1175, 5 + map[i].index.y * 16 + 450, 16, 16);
		new_Info.index = map[i].index;
		new_Info.frame = map[i].frame;

		string tileN = map[i].tileName.groundName + "_S";

		new_Info.tileName.groundName = tileN;
		new_Info.tile_Type = map[i].tile_Type;
		new_Info.tile_Collision_Type = map[i].tile_Collision_Type;
		new_Info.useTile = map[i].useTile;

		miniMap.push_back(new_Info);
	}

}
