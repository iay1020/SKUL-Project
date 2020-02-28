#include "stdafx.h"
#include "test_Room.h"

test_Room::test_Room()
{
}

test_Room::~test_Room()
{
}

HRESULT test_Room::init()
{
	// ���� �ҷ��� �����͸Ŵ����� �ִ� ������ �����Ѵ�.
	DATAMANAGER->map_Load_Datamanager("tutorial.map", "tutorial_Info.map");

	for (int i = 0; i < 5; ++i)	// ���������� ����
	{
		loopSpeed[i] = 0;
	}

	DATAMANAGER->create_Skul();				// ���� ����
	_skul = DATAMANAGER->skul_Address();	// ���� ������ ����
	_skul->update_Pos(4, 26);

	// ui ����
	DATAMANAGER->setting_ui(_skul);
	// �̴ϸ� ���� ����
	DATAMANAGER->ui_Address()->setting_MiniMap();
	DATAMANAGER->setting_MiniMap();

	// �׽�Ʈ ���ʹ� ����
	DATAMANAGER->Create_Enemy(EnemyType::SOLDIER, EnemyDirection::LEFT, "soldier_Idle", "soldier_Idle_Left_Ani", 30, 17);

	// ���� ���� �ҷ����� ī�޶� ������ �ؾ��Ѵ�. (ī�޶� ��ġ, Ÿ�� ����, �� ũ�� ����)
	// �⺻ ī�޶� ��ġ ���� (�÷��̾� ��������)
	CAMERAMANAGER->Use_Func()->set_CameraXY(_skul->get_Info().pos.center.x, _skul->get_Info().pos.center.y, true);

	return S_OK;
}

void test_Room::release()
{
}

void test_Room::update()
{
	testControl(); // �׽�Ʈ�� �̵�Ű

	// �÷��̾� ����
	DATAMANAGER->update();
	
	// ĳ���� Ÿ�� ��ġ
	//cout << "x : " << (int)(_skul->get_Info().pos.center.x / TILE_SIZE_X) << ", y : " << (int)(_skul->get_Info().pos.center.y / TILE_SIZE_Y) << endl;
}

void test_Room::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	// �� ���
	DATAMANAGER->map_Render_Datamanager(getMemDC(), loopSpeed);

	showRect(getMemDC());	// �׽�Ʈ�� ��Ʈ

	// ���ʹ� ���
	DATAMANAGER->show_Enemy();

	// �÷��̾� ���
	IMAGEMANAGER->findImage(_skul->get_Info().img.imgName)->aniRender(getMemDC(),
		_skul->get_Info().img.img_Rc.left, _skul->get_Info().img.img_Rc.top, _skul->get_Info().img.ani);

	// �÷��̾� ���� ��Ʈ ���
	_skul->set_Info()->show_Attack_Rect(getMemDC());

	// ����ü ���
	DATAMANAGER->show_FlyingObject();

	// ����Ʈ ���
	DATAMANAGER->show_Effect();

	// ui ���
	DATAMANAGER->show_Ui();

	EFFECTMANAGER->render();

}

void test_Room::testControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		for (int i = 0; i < 5; ++i)
		{
			loopSpeed[i] -= 6 - i * 2;		// 0��° ���̾�� 6�� ���� ������, �������� �Ѿ���� -2�� ����
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		for (int i = 0; i < 5; ++i)
		{
			loopSpeed[i] += 6 - i * 2;		// 0��° ���̾�� 6�� ���� ������, �������� �Ѿ���� +2�� ����
		}
	}

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
}

void test_Room::showRect(HDC getMemDC)
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


