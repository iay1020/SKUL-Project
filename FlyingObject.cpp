#include "stdafx.h"
#include "FlyingObject.h"

FlyingObject::FlyingObject()
{
}

FlyingObject::~FlyingObject()
{
}

void FlyingObject::Release()
{
	// ������ (���� ������ ������ �ϴ� �ּ�)
	//while (vFlyingObj.size() != 0)
	//{
	//	delete vFlyingObj.begin()->img;
	//	delete vFlyingObj.begin()->ani;
	//	vFlyingObj.erase(vFlyingObj.begin);
	//}
}

void FlyingObject::update()
{
	// ����ü �̵� �Լ�
	Move_FlyingObj();

}

void FlyingObject::render()
{
	// ����ü ������Ʈ ���
	Show_FlyingObj();
}

void FlyingObject::Create_FlyingObj(string imgName, string aniName, FLYINFOBJECT_TYPE type_V, FLYINGOBJECT_DIRECTION dir,
	float x, float y, float angle_V, float speed_V, bool Frame)
{
	// ����ü ������Ʈ�� �����.
	FlyingObjectInfo new_FlyingObj;
	new_FlyingObj.reset();
	new_FlyingObj.setting_Info(imgName, aniName, type_V, dir, x, y, angle_V, speed_V, Frame);

	vFlyingObj.push_back(new_FlyingObj);

}

void FlyingObject::Move_FlyingObj()
{
	for (viFlyingObj = vFlyingObj.begin(); viFlyingObj != vFlyingObj.end();)
	{
		// ����ü�� Ÿ���� ������ �Ӹ��̰�, ���� �߰��ϸ� �ݴ� ������ �ٲ��ش�. ���� �߷��� �߰��ؼ� ���������� �Ѵ�. �߶������� �ٲ��ش�.
		if ((*viFlyingObj).type == FLYINFOBJECT_TYPE::SKUL_HEAD)
		{
			// �߶������� ������
			if (!(*viFlyingObj).isFalling)
			{
				// ���� �߰��ϸ� ������ �ݴ밢���� �ٲ��ְ�, �߷��� �߰��Ͽ� ���������� �Ѵ�. ���� �߶������� �ٲ��ش�.
				if(DATAMANAGER->Collision_FlyingObject_Wall(&(*viFlyingObj)))
				{
					// ����ü�� ���⿡ ���� �ٸ� ����
					if ((*viFlyingObj).dir == FLYINGOBJECT_DIRECTION::LEFT)
					{
						(*viFlyingObj).angle = 0;								// �ݴ� ������ �ٲ��ش�.
						(*viFlyingObj).speed = 5;
						(*viFlyingObj).gravity = FLYINGOBJECT_GRAVITY;			// �߷� �߰�
						(*viFlyingObj).dir = FLYINGOBJECT_DIRECTION::RIGHT;		// ������ �ݴ�� �ٲ��ش�.
						(*viFlyingObj).isFalling = true;						// �߶������� �ٲ��ش�.
					}
					

					else if ((*viFlyingObj).dir == FLYINGOBJECT_DIRECTION::RIGHT)
					{
						(*viFlyingObj).angle = 3.14;							// �ݴ� ������ �ٲ��ش�.
						(*viFlyingObj).speed = 5;
						(*viFlyingObj).gravity = FLYINGOBJECT_GRAVITY;			// �߷� �߰�
						(*viFlyingObj).dir = FLYINGOBJECT_DIRECTION::LEFT;		// ������ �ݴ�� �ٲ��ش�.
						(*viFlyingObj).isFalling = true;						// �߶������� �ٲ��ش�.
					}
				}
			}

			// ����ü�� Ÿ���� ������ �Ӹ��̰�, �߶����̸� ���� �߰��ϸ� ���ǵ带 ���ֹ�����. ���� �ִϸ��̼��� ����.
			if ((*viFlyingObj).isFalling)
			{
				// ���� �߰��ϸ� ���ǵ带 ���ֹ�����, �ִϸ��̼��� �����Ѵ�.
				(*viFlyingObj).gravity += FLYINGOBJECT_GRAVITY;

			}

		}

		// ����ü �̵�
		(*viFlyingObj).center.x += cosf((*viFlyingObj).angle) * (*viFlyingObj).speed;
		(*viFlyingObj).center.y += -sinf((*viFlyingObj).angle) * (*viFlyingObj).speed + (*viFlyingObj).gravity;

		// ��Ʈ ����
		(*viFlyingObj).update_Rect();

		// ����ü ���� ī��Ʈ ����
		(*viFlyingObj).Delete_Timer++;

		// ����ü ���� ī��Ʈ ���ǿ� �����ϸ�
		if ((*viFlyingObj).Delete_Timer >= (*viFlyingObj).get_Timer_Count())
		{
			viFlyingObj = vFlyingObj.erase(viFlyingObj);
		}

		// �������� �ʴ´ٸ� ��������
		else viFlyingObj++;
	}
}

void FlyingObject::Show_FlyingObj()
{
	// ī�޶� ��ǥ��ŭ �� ���� ��� ����
	RECT tempRC;

	for (viFlyingObj = vFlyingObj.begin(); viFlyingObj != vFlyingObj.end(); ++viFlyingObj)
	{
		// ī�޶� ����
		tempRC = (*viFlyingObj).rc;
		tempRC.left -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		tempRC.right -= CAMERAMANAGER->Use_Func()->get_CameraXY().x;
		tempRC.top -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
		tempRC.bottom -= CAMERAMANAGER->Use_Func()->get_CameraXY().y;
	
		// ������ �̹����� �ƴ϶��
		if (!(*viFlyingObj).isFrame)
		{
			(*viFlyingObj).img->render(getMemDC(), tempRC.left, tempRC.top);
		}

		// ������ �̹������ �ִϸ��̼��̶�� ��
		if ((*viFlyingObj).isFrame)
		{
			IMAGEMANAGER->findImage((*viFlyingObj).aniName)->aniRender(getMemDC(), 
				(*viFlyingObj).center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x, 
				(*viFlyingObj).center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y,
				(*viFlyingObj).ani);

		}
	}
}
