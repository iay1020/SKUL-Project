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
	mapInfo.reset_MapInfo();	// �⺻ �� ���� �ʱ�ȭ

	// �ε忡 �ʿ��Ѱ� ����
	// vector<tagTileInfo>			�ڷ��� ����								Ÿ�� ������ ��´�.
	// tagMapInfo					�ڷ��� ����								���� ������ ��´�.
	// vector<tagSaveBackGround>	�ڷ��� ����[BACKGROUND_LAYER_COUNT]��		����� ������ ��´�.

	DATAMANAGER->map_Load(&tileList, &mapInfo, vMapInfo);	// ���� �ҷ��´�. (�ҷ����鼭 ���� ������ ī�޶�Ŵ����� ����)

	for (int i = 0; i < 5; ++i)	// ���������� ����
	{
		loopSpeed[i] = 0;
	}

	_player = new Player();

	// ���� ���� �ҷ����� ī�޶� ������ �ؾ��Ѵ�. (ī�޶� ��ġ, Ÿ�� ����, �� ũ�� ����)
	CAMERAMANAGER->Use_Func()->set_CameraXY(_player->get_Info().pos.center.x, _player->get_Info().pos.center.y, true);	// �⺻ ī�޶� ��ġ ���� (�÷��̾� ��������)

	return S_OK;
}

void test_Room::release()
{
}

void test_Room::update()
{
	testControl(); // �׽�Ʈ�� �̵�Ű

	_player->update();
}

void test_Room::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

	DATAMANAGER->map_Render(getMemDC(), &tileList, mapInfo, vMapInfo, loopSpeed); // �������ǵ�� 5���� �־���� �Ѵ�.

	IMAGEMANAGER->findImage(_player->get_Info().img.imgName)->aniRender(getMemDC(), 
		_player->get_Info().img.img_Rc.left, _player->get_Info().img.img_Rc.top, _player->get_Info().img.ani);
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

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_player->set_Info()->pos.center.y -= 10;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		for (int i = 0; i < 5; ++i)
		{
			loopSpeed[i] += 6 - i * 2;		// 0��° ���̾�� 6�� ���� ������, �������� �Ѿ���� +2�� ����
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_player->set_Info()->pos.center.y += 10;
	}
}

