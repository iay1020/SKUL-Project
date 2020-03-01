#include "stdafx.h"
#include "Stage_2.h"

Stage_2::Stage_2()
{
}

Stage_2::~Stage_2()
{
}

HRESULT Stage_2::init()
{
	// ���� �ҷ��� �����͸Ŵ����� �ִ� ������ �����Ѵ�.
	DATAMANAGER->map_Load_Datamanager("Stage_2.map", "Stage_2_Info.map");

	_skul = DATAMANAGER->skul_Address();	// ���� ������ ����
	_skul->update_Pos(4, 20);

	// �̺�Ʈ �Ŵ��� ����
	eventM = new eventManager;
	//eventM->create_Event(eventType::GIVE_WEAPON_NPC, 28, 19, 4, false, false);
	eventM->create_Event(eventType::START_GATE, 3, 25, 1, false, true, 0);
	eventM->create_Event(eventType::NEXT_GATE, 26, 25, 1, false, true, 3);

	// ���ʹ� ����
	DATAMANAGER->Create_Enemy(EnemyType::PALADIN, EnemyDirection::RIGHT, "paladin_Idle", "paladin_Idle_Right_Ani", 22, 25);
	DATAMANAGER->Create_Enemy(EnemyType::PALADIN, EnemyDirection::LEFT, "paladin_Idle", "paladin_Idle_Left_Ani", 30, 25);
	DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::LEFT, "archer_Idle", "archer_Idle_Left_Ani", 32, 25);
	DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::LEFT, "archer_Idle", "archer_Idle_Left_Ani", 34, 25);
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::RIGHT, "soldier_Idle", "soldier_Idle_Right_Ani", 19, 25);
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::RIGHT, "soldier_Idle", "soldier_Idle_Right_Ani", 17, 25);

	// ���� ���� �ҷ����� ī�޶� ������ �ؾ��Ѵ�. (ī�޶� ��ġ, Ÿ�� ����, �� ũ�� ����)
	// �⺻ ī�޶� ��ġ ���� (�÷��̾� ��������)
	CAMERAMANAGER->Use_Func()->set_CameraXY(_skul->get_Info().pos.center.x, _skul->get_Info().pos.center.y, true);

	return S_OK;
}

void Stage_2::release()
{
}

void Stage_2::update()
{
	// �÷��̾� ����
	DATAMANAGER->update();

	eventM->update();

	// ĳ���� Ÿ�� ��ġ
	cout << "x : " << (int)(_skul->get_Info().pos.center.x / TILE_SIZE_X) << ", y : " << (int)(_skul->get_Info().pos.center.y / TILE_SIZE_Y) << endl;

}

void Stage_2::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	// �� ���
	DATAMANAGER->map_Render_Datamanager_Loop(getMemDC());

	//showRect(getMemDC());	// �׽�Ʈ�� ��Ʈ

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

void Stage_2::testControl()
{
}

void Stage_2::showRect(HDC getMemDC)
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
