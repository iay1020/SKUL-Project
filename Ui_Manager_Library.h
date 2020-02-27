#pragma once
#include "Player.h"


// ü���� �������� ���ǵ�
#define HP_MINUS_SPEED	2

// ü���� �ö󰡴� ���ǵ�
#define HP_PLUS_SPEED	2



// ü�� ���� ���� Enum
enum class HP_UPDATE_STATE
{
	EMPTY,		// NULL
	HEAL,		// ȸ����
	HIT			// �ǰ���
};


// ĳ���� UI ��Ʈ
struct Character_UI_Img
{
	RECT rc;					// ĳ���� UI�� �׸� ��Ʈ

	image* img;					// ĳ���� UI �̹����� ������ ����

};

// ĳ���� Ÿ�� �̹���
struct Character_Type_Img
{
	RECT rc;					// ĳ���� Ÿ���� �׸� ��Ʈ

	image* img;					// ĳ���� Ÿ�� �̹����� ������ ����

};

// ĳ���� ��ų �̹���
struct Character_Skill_Img
{
	RECT rc_A;					// ��ų A ��Ʈ
	RECT rc_B;					// ��ų B ��Ʈ

	image* img_A;				// ��ų A �̹����� ������ ����
	string img_A_Name;			// ��ų A �̹����� Ű���� ������ ����

	image* img_B;				// ��ų B �̹����� ������ ����
	string img_B_Name;			// ��ų B �̹����� Ű���� ������ ����

};

// ĳ���� ü�� �̹���
struct Character_Hp_Img
{
	RECT					rc_HP_BG;			// ü�¹� ���
	RECT					rc_HP_Back;			// ü�¹� ��
	RECT					rc_HP_Front;		// ü�¹� ��

	image*					img_HP_BG;			// ü�¹� ���
	image*					img_HP_Back;			// ü�¹� �� �̹����� ������ ����
	string					img_HP_Back_Name;	// ü�¹� �� �̹��� Ű���� ������ ����
	image*					img_HP_Front;		// ü�¹� �� �̹����� ������ ����

	HP_UPDATE_STATE			state;				// ü�� ������Ʈ ����

	short					maxHP;				// �ƽ� HP ������ ��´�.
	short					curHP;				// ���� HP ������ ��´�.
	short					backHP;				// �� HP ������ ��´�.

};

// ĳ���� �������ͽ� UI
struct CharacterStatusUI
{
	Character_UI_Img			ui;			// ui ����
	Character_Type_Img			type;		// type ����
	Character_Skill_Img			skill;		// ��ų ����
	Character_Hp_Img			hp;			// ü�� ����

	// �⺻ �̹��� ����
	void base_Setting(Player* skul)
	{
		// ui ����
		ui.img = new image;
		ui.img = IMAGEMANAGER->findImage("status_UI");
		ui.rc = RectMake(50, WINSIZEY - ui.img->getHeight(), ui.img->getWidth(), ui.img->getHeight());

		// Ÿ�� ����
		type.img = new image;
		type.img = IMAGEMANAGER->findImage("skul_Icon");
		type.rc = RectMake(ui.rc.left + 4, ui.rc.top + 7, type.img->getWidth(), type.img->getHeight());

		// ��ų ����
		skill.img_A_Name = "skul_ThrowHead_Skill";
		skill.img_A = new image;
		skill.img_A = IMAGEMANAGER->findImage(skill.img_A_Name);
		skill.rc_A = RectMake(ui.rc.left + 114, ui.rc.top + 18, skill.img_A->getWidth(), skill.img_A->getHeight());

		skill.img_B_Name = "skill_Null";
		skill.img_B = new image;
		skill.img_B = IMAGEMANAGER->findImage(skill.img_B_Name);
		skill.rc_B = RectMake(ui.rc.left + 188, ui.rc.top + 18, skill.img_A->getWidth(), skill.img_A->getHeight());

		// hp ����
		hp.img_HP_BG = new image;
		hp.img_HP_BG = IMAGEMANAGER->findImage("skul_HP_Null");
		hp.rc_HP_BG = RectMake(ui.rc.left + 76, ui.rc.top + 78, hp.img_HP_BG->getWidth(), hp.img_HP_BG->getHeight());

		hp.img_HP_Front = new image;
		hp.img_HP_Front = IMAGEMANAGER->findImage("skul_HP");
		hp.rc_HP_Front = RectMake(ui.rc.left + 76, ui.rc.top + 78, 0, hp.img_HP_Front->getHeight());

		hp.img_HP_Back_Name = "skul_HP_Hit";
		hp.img_HP_Back = new image;
		hp.img_HP_Back = IMAGEMANAGER->findImage(hp.img_HP_Back_Name);
		hp.rc_HP_Back = RectMake(ui.rc.left + 76, ui.rc.top + 78, 0, hp.img_HP_Back->getHeight());
		
		hp.maxHP = skul->get_Info().status.HP;
		hp.curHP = skul->get_Info().status.HP;
		hp.backHP = skul->get_Info().status.HP;
		
		// ó������ ȸ���� �ؾ��Ѵ�.
		hp.state = HP_UPDATE_STATE::HEAL;

	}

	// ��Ʈ ���
	void show_Rect(HDC getMemDC)
	{
		// hp ���
		hp.img_HP_BG->render(getMemDC, hp.rc_HP_BG.left, hp.rc_HP_BG.top);

		hp.img_HP_Back->render(getMemDC, hp.rc_HP_Back.left, hp.rc_HP_Back.top,
			0, 0, hp.rc_HP_Back.right - hp.rc_HP_Back.left, hp.img_HP_Back->getHeight());

		hp.img_HP_Front->render(getMemDC, hp.rc_HP_Front.left, hp.rc_HP_Front.top,
			0, 0, hp.rc_HP_Front.right - hp.rc_HP_Front.left, hp.img_HP_Front->getHeight());
		
		// ui ���
		ui.img->render(getMemDC, ui.rc.left, ui.rc.top);

		// Ÿ�� ���
		type.img->render(getMemDC, type.rc.left, type.rc.top);

		// ��ų ���
		skill.img_A->render(getMemDC, skill.rc_A.left, skill.rc_A.top);
		skill.img_B->render(getMemDC, skill.rc_B.left, skill.rc_B.top);

		
		// ��Ʈ ���
		if (KEYMANAGER->isToggleKey(VK_NUMPAD9))
		{
			// HP ��Ʈ
			Rectangle(getMemDC, hp.rc_HP_Front);

			// status Ui ��Ʈ
			Rectangle(getMemDC, ui.rc);

			// type ��Ʈ
			Rectangle(getMemDC, type.rc);

			// skill ��Ʈ
			Rectangle(getMemDC, skill.rc_A);
			Rectangle(getMemDC, skill.rc_B);
		}
	}

	// ������ Ÿ�Կ� ���� �̹��� ������Ʈ
	void update_Img()
	{
		//// ������ Ÿ�Կ� ���� �̹����� ��ü���ش�.
		//switch (DATAMANAGER->skul_Address()->get_Info().type.skul_Type)
		//{
		//	// �⺻����, ���⽺��, �Ӹ����½��� �϶�
		//	case SKUL_TYPE::SKUL_NOWEAPON: case SKUL_TYPE::SKUL_WEAPON: case SKUL_TYPE::SKUL_WEAPON_NOHEAD:
		//		type.img = IMAGEMANAGER->findImage("skul_Icon");
		//
		//		skill.img_A_Name = "skul_ThrowHead_Skill";
		//		skill.img_A = IMAGEMANAGER->findImage(skill.img_A_Name);
		//
		//		skill.img_B_Name = "skill_Null";
		//		skill.img_B = IMAGEMANAGER->findImage(skill.img_B_Name);
		//
		//		break;
		//
		//	//
		//		
		//}
	}


	// ü�� ������ ������Ʈ
	void update_HP()
	{
		// ü���� ȸ���ϰ� �ִ���
		if (hp.state == HP_UPDATE_STATE::HEAL)
		{
			// ȸ�����϶� back �̹��� ��ü
			hp.img_HP_Back = IMAGEMANAGER->findImage("skul_HP_Heal");

			// ȸ�����϶��� back right�� �ٷ� ���� �ȴ�.
			hp.rc_HP_Back.right = hp.rc_HP_Back.left + (hp.curHP * hp.img_HP_Back->getWidth() / hp.maxHP);
			
			// ȸ�����϶��� front right�� õõ�� �����Ѵ�.
			hp.rc_HP_Front.right += HP_PLUS_SPEED;

			// front right�� back right�� ���ų� �� �̻��̶�� �ִ��� ��
			if (hp.rc_HP_Front.right >= hp.rc_HP_Back.right)
			{
				// �Ѿ�� ��� �� ����
				hp.rc_HP_Front.right = hp.rc_HP_Back.right;

				// ü�� ���¸� ��ü�Ѵ�.
				hp.state = HP_UPDATE_STATE::EMPTY;
			}
		}

		// ü���� �����ϴ� ���̴�.
		if (hp.state == HP_UPDATE_STATE::HIT)
		{
			// �������϶� back �̹��� ��ü
			hp.img_HP_Back = IMAGEMANAGER->findImage("skul_HP_Hit");

			// �������϶��� front right�� �ٷ� ���� �ȴ�.
			hp.rc_HP_Front.right = hp.rc_HP_Front.left + (hp.curHP * hp.img_HP_Front->getWidth() / hp.maxHP);

			// �������϶��� back right�� õõ�� �����Ѵ�.
			hp.rc_HP_Back.right -= HP_MINUS_SPEED;

			// back right�� front right�� ���ų� �� ���϶�� 
			if (hp.rc_HP_Back.right <= hp.rc_HP_Front.right)
			{
				// �Ѿ�� ��� �� ����
				hp.rc_HP_Back.right = hp.rc_HP_Front.right;

				// ü�� ���¸� ��ü�Ѵ�.
				hp.state = HP_UPDATE_STATE::EMPTY;
			}
		}
	}

};















// ���ʹ̴� �ƽ�ü�º��� ���� ��쿡 �ڽ��� ü�¹ٰ� ��µȴ�.

// �÷��̾�� �׻� ��µ�

// �÷��̾��� ���� UI�� �ʿ��Ѱ�

// �ϴ� �÷��̾� ��ü UI�� �׸� Ŀ�ٶ� ��Ʈ 

// ĳ������ Ÿ�Կ� ���� �̹����� �־��� ��Ʈ 

// ��ų�� �׸� ��Ʈ 2��

// ���������� ȭ�� ���������� ?

// ü�¹� ��Ʈ ���� ü��, �ǰ� ü�¹� 2��



