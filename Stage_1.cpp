#include "stdafx.h"
#include "Stage_1.h"

Stage_1::Stage_1()
{
}

Stage_1::~Stage_1()
{
}

HRESULT Stage_1::init()
{
	// ���� �ҷ��� �����͸Ŵ����� �ִ� ������ �����Ѵ�.
	DATAMANAGER->map_Load_Datamanager("Stage_1.map", "Stage_1_Info.map");

	_skul = DATAMANAGER->skul_Address();	// ���� ������ ����
	_skul->update_Pos(4, 25);

	// �̺�Ʈ �Ŵ��� ����
	eventM = new eventManager;
	//eventM->create_Event(eventType::GIVE_WEAPON_NPC, 28, 19, 4, false, false);
	eventM->create_Event(eventType::START_GATE, 3, 25, 1, false, true, 0);
	eventM->create_Event(eventType::NEXT_GATE, 58, 25, 1, false, true, 2);

	// ���ʹ� ����
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 27, 25);
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 29, 25);
	DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::RIGHT, "archer_Idle", "archer_Idle_Left_Ani", 32, 25);
	DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::RIGHT, "archer_Idle", "archer_Idle_Left_Ani", 34, 25);
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 32, 19);
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 44, 14);
	DATAMANAGER->Create_Enemy(EnemyType::ARCHER, EnemyDirection::RIGHT, "archer_Idle", "archer_Idle_Left_Ani", 47, 14);

	// ���� ���� �ҷ����� ī�޶� ������ �ؾ��Ѵ�. (ī�޶� ��ġ, Ÿ�� ����, �� ũ�� ����)
	// �⺻ ī�޶� ��ġ ���� (�÷��̾� ��������)
	CAMERAMANAGER->Use_Func()->set_CameraXY(_skul->get_Info().pos.center.x, _skul->get_Info().pos.center.y, true);

	return S_OK;
}

void Stage_1::release()
{
}

void Stage_1::update()
{
	// �÷��̾� ����
	DATAMANAGER->update();

	eventM->update();

	// ĳ���� Ÿ�� ��ġ
	cout << "x : " << (int)(_skul->get_Info().pos.center.x / TILE_SIZE_X) << ", y : " << (int)(_skul->get_Info().pos.center.y / TILE_SIZE_Y) << endl;

}

void Stage_1::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	// �� ���
	DATAMANAGER->map_Render_Datamanager_Loop(getMemDC());

	//showRect(getMemDC());	// �׽�Ʈ�� ��Ʈ

	eventM->render();

	// ���ʹ� ���
	DATAMANAGER->show_Enemy();

	// �̹��� ���
	DATAMANAGER->Render_ImageMaker();


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

void Stage_1::testControl()
{
}

void Stage_1::showRect(HDC getMemDC)
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
