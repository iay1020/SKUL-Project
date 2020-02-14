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

	testSetting_Player();

	for (int i = 0; i < 5; ++i)	// ���������� ����
	{
		loopSpeed[i] = 0;
	}

	// ���� ���� �ҷ����� ī�޶� ������ �ؾ��Ѵ�. (ī�޶� ��ġ, Ÿ�� ����, �� ũ�� ����)
	CAMERAMANAGER->Use_Func()->set_CameraXY(testP.center.x, testP.center.y, true);	// �⺻ ī�޶� ��ġ ���� (�÷��̾� ��������)

	_player = new Player();

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

	testP.rc.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	testP.rc.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
	testP.rc.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	testP.rc.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	Rectangle(getMemDC(), testP.rc);
}

void test_Room::testControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		testP.center.x -= testP.speed;
		for (int i = 0; i < 5; ++i)
		{
			loopSpeed[i] -= 6 - i * 2;		// 0��° ���̾�� 6�� ���� ������, �������� �Ѿ���� -2�� ����
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		testP.center.y -= testP.speed;
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		testP.center.x += testP.speed;
		for (int i = 0; i < 5; ++i)
		{
			loopSpeed[i] += 6 - i * 2;		// 0��° ���̾�� 6�� ���� ������, �������� �Ѿ���� +2�� ����
		}
	}

	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		testP.center.y += testP.speed;
	}

	CAMERAMANAGER->Use_Func()->set_CameraXY(testP.center.x, testP.center.y, true);	// ī�޶� ����
	testP.rc = RectMakeCenter(testP.center.x, testP.center.y, 30, 50);

}

void test_Room::testSetting_Player()
{
	//POINTFLOAT	center;
	//RECT		rc;
	//float		speed;
	//image*		img;
	//animation*	ani;

	// �׽�Ʈ �÷��̾��� ��ġ�� ��´�.
	testP.center.x = 100;
	testP.center.y = WINSIZEY - 100;

	testP.rc = RectMakeCenter(testP.center.x, testP.center.y, 30, 50);

	testP.speed = 10;
}
