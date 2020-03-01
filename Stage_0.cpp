#include "stdafx.h"
#include "Stage_0.h"

Stage_0::Stage_0()
{
}

Stage_0::~Stage_0()
{
}

HRESULT Stage_0::init()
{
	// ���� �ҷ��� �����͸Ŵ����� �ִ� ������ �����Ѵ�.
	DATAMANAGER->map_Load_Datamanager("Stage_0.map", "Stage_0_Info.map");

	DATAMANAGER->create_Skul();				// ���� ����
	_skul = DATAMANAGER->skul_Address();	// ���� ������ ����
	_skul->update_Pos(4, 25);

	// ui ����
	DATAMANAGER->setting_ui(_skul);
	// �̴ϸ� ���� ����
	DATAMANAGER->ui_Address()->setting_MiniMap();
	DATAMANAGER->setting_MiniMap();

	// �̺�Ʈ �Ŵ��� ����
	eventM = new eventManager;
	eventM->create_Event(eventType::GIVE_WEAPON_NPC, 28, 19, 4, false, false, 0);
	eventM->create_Event(eventType::NEXT_GATE, 36, 25, 1, false, true, 1);
	eventM->create_Event(eventType::DOWN_HELP_NPC, 40, 18, 1, true, false, 0);

	// �׽�Ʈ ���ʹ� ����
	//DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 30, 17);

	// ���� ���� �ҷ����� ī�޶� ������ �ؾ��Ѵ�. (ī�޶� ��ġ, Ÿ�� ����, �� ũ�� ����)
	// �⺻ ī�޶� ��ġ ���� (�÷��̾� ��������)
	CAMERAMANAGER->Use_Func()->set_CameraXY(_skul->get_Info().pos.center.x, _skul->get_Info().pos.center.y, true);

	return S_OK;
}

void Stage_0::release()
{
}

void Stage_0::update()
{
	testControl(); // �׽�Ʈ�� �̵�Ű

	// �÷��̾� ����
	DATAMANAGER->update();

	eventM->update();

	// ĳ���� Ÿ�� ��ġ
	//cout << "x : " << (int)(_skul->get_Info().pos.center.x / TILE_SIZE_X) << ", y : " << (int)(_skul->get_Info().pos.center.y / TILE_SIZE_Y) << endl;


}

void Stage_0::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	// �� ���
	DATAMANAGER->map_Render_Datamanager_Loop(getMemDC());

	showRect(getMemDC());	// �׽�Ʈ�� ��Ʈ

	eventM->render();

	// ���ʹ� ���
	DATAMANAGER->show_Enemy();


	// �÷��̾� ���
	IMAGEMANAGER->findImage(_skul->get_Info().img.imgName)->aniRender(getMemDC(),
		_skul->get_Info().img.img_Rc.left, _skul->get_Info().img.img_Rc.top, _skul->get_Info().img.ani);


	// �÷��̾� ���� ��Ʈ ���
	//_skul->set_Info()->show_Attack_Rect(getMemDC());

	// ����ü ���
	DATAMANAGER->show_FlyingObject();

	// ����Ʈ ���
	DATAMANAGER->show_Effect();

	// ui ���
	DATAMANAGER->show_Ui();

	EFFECTMANAGER->render();

}

void Stage_0::testControl()
{

	if (KEYMANAGER->isOnceKeyDown(VK_F8))
	{
		if (_skul->get_InputKey() == PRESS_RIGHT)
			DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) + 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);

		if (_skul->get_InputKey() == PRESS_LEFT)
			DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) - 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F7))
	{
		if (_skul->get_InputKey() == PRESS_RIGHT)
			DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::LEFT, "archer_Idle", "archer_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) + 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);

		if (_skul->get_InputKey() == PRESS_LEFT)
			DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::LEFT, "archer_Idle", "archer_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) - 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		if (_skul->get_InputKey() == PRESS_RIGHT)
			DATAMANAGER->Create_Enemy(EnemyType::PALADIN, EnemyDirection::LEFT, "paladin_Idle", "paladin_Idle_Left_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) + 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);

		if (_skul->get_InputKey() == PRESS_LEFT)
			DATAMANAGER->Create_Enemy(EnemyType::PALADIN, EnemyDirection::RIGHT, "paladin_Idle", "paladin_Idle_Right_Ani",
			(_skul->get_Info().pos.center.x / TILE_SIZE_X) - 3, (int)(_skul->get_Info().pos.center.y) / TILE_SIZE_X);
	}
}

void Stage_0::showRect(HDC getMemDC)
{
	if (KEYMANAGER->isToggleKey(VK_NUMPAD9))
	{
		DATAMANAGER->Rect_Render_Datamanager(getMemDC);
	}

	if (KEYMANAGER->isToggleKey(VK_NUMPAD7))
	{
		// �÷��̾� �̹��� ��Ʈ
		Rectangle(getMemDC, _skul->get_Info().img.img_Rc.left, _skul->get_Info().img.img_Rc.top, _skul->get_Info().img.img_Rc.right, _skul->get_Info().img.img_Rc.bottom);
	}

	if (KEYMANAGER->isToggleKey(VK_NUMPAD8))
	{
		// �÷��̾� �ǰ� ��Ʈ
		Rectangle(getMemDC, _skul->get_Info().pos.rc.left, _skul->get_Info().pos.rc.top, _skul->get_Info().pos.rc.right, _skul->get_Info().pos.rc.bottom);
	}
}


