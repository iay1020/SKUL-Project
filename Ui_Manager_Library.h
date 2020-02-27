#pragma once
#include "Player.h"


// 체력이 떨어지는 스피드
#define HP_MINUS_SPEED	2

// 체력이 올라가는 스피드
#define HP_PLUS_SPEED	2



// 체력 피해 상태 Enum
enum class HP_UPDATE_STATE
{
	EMPTY,		// NULL
	HEAL,		// 회복중
	HIT			// 피격중
};


// 캐릭터 UI 렉트
struct Character_UI_Img
{
	RECT rc;					// 캐릭터 UI를 그릴 렉트

	image* img;					// 캐릭터 UI 이미지를 저장할 변수

};

// 캐릭터 타입 이미지
struct Character_Type_Img
{
	RECT rc;					// 캐릭터 타입을 그릴 렉트

	image* img;					// 캐릭터 타입 이미지를 저장할 변수

};

// 캐릭터 스킬 이미지
struct Character_Skill_Img
{
	RECT rc_A;					// 스킬 A 렉트
	RECT rc_B;					// 스킬 B 렉트

	image* img_A;				// 스킬 A 이미지를 저장할 변수
	string img_A_Name;			// 스킬 A 이미지의 키값을 저장할 변수

	image* img_B;				// 스킬 B 이미지를 저장할 변수
	string img_B_Name;			// 스킬 B 이미지의 키값을 저장할 변수

};

// 캐릭터 체력 이미지
struct Character_Hp_Img
{
	RECT					rc_HP_BG;			// 체력바 배경
	RECT					rc_HP_Back;			// 체력바 뒤
	RECT					rc_HP_Front;		// 체력바 앞

	image*					img_HP_BG;			// 체력바 배경
	image*					img_HP_Back;			// 체력바 뒤 이미지를 저장할 변수
	string					img_HP_Back_Name;	// 체력바 뒤 이미지 키값을 저장할 변수
	image*					img_HP_Front;		// 체력바 앞 이미지를 저장할 변수

	HP_UPDATE_STATE			state;				// 체력 업데이트 상태

	short					maxHP;				// 맥스 HP 정보를 담는다.
	short					curHP;				// 현재 HP 정보를 담는다.
	short					backHP;				// 백 HP 정보를 담는다.

};

// 캐릭터 스테이터스 UI
struct CharacterStatusUI
{
	Character_UI_Img			ui;			// ui 정보
	Character_Type_Img			type;		// type 정보
	Character_Skill_Img			skill;		// 스킬 정보
	Character_Hp_Img			hp;			// 체력 정보

	// 기본 이미지 셋팅
	void base_Setting(Player* skul)
	{
		// ui 셋팅
		ui.img = new image;
		ui.img = IMAGEMANAGER->findImage("status_UI");
		ui.rc = RectMake(50, WINSIZEY - ui.img->getHeight(), ui.img->getWidth(), ui.img->getHeight());

		// 타입 셋팅
		type.img = new image;
		type.img = IMAGEMANAGER->findImage("skul_Icon");
		type.rc = RectMake(ui.rc.left + 4, ui.rc.top + 7, type.img->getWidth(), type.img->getHeight());

		// 스킬 셋팅
		skill.img_A_Name = "skul_ThrowHead_Skill";
		skill.img_A = new image;
		skill.img_A = IMAGEMANAGER->findImage(skill.img_A_Name);
		skill.rc_A = RectMake(ui.rc.left + 114, ui.rc.top + 18, skill.img_A->getWidth(), skill.img_A->getHeight());

		skill.img_B_Name = "skill_Null";
		skill.img_B = new image;
		skill.img_B = IMAGEMANAGER->findImage(skill.img_B_Name);
		skill.rc_B = RectMake(ui.rc.left + 188, ui.rc.top + 18, skill.img_A->getWidth(), skill.img_A->getHeight());

		// hp 셋팅
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
		
		// 처음에는 회복을 해야한다.
		hp.state = HP_UPDATE_STATE::HEAL;

	}

	// 렉트 출력
	void show_Rect(HDC getMemDC)
	{
		// hp 출력
		hp.img_HP_BG->render(getMemDC, hp.rc_HP_BG.left, hp.rc_HP_BG.top);

		hp.img_HP_Back->render(getMemDC, hp.rc_HP_Back.left, hp.rc_HP_Back.top,
			0, 0, hp.rc_HP_Back.right - hp.rc_HP_Back.left, hp.img_HP_Back->getHeight());

		hp.img_HP_Front->render(getMemDC, hp.rc_HP_Front.left, hp.rc_HP_Front.top,
			0, 0, hp.rc_HP_Front.right - hp.rc_HP_Front.left, hp.img_HP_Front->getHeight());
		
		// ui 출력
		ui.img->render(getMemDC, ui.rc.left, ui.rc.top);

		// 타입 출력
		type.img->render(getMemDC, type.rc.left, type.rc.top);

		// 스킬 출력
		skill.img_A->render(getMemDC, skill.rc_A.left, skill.rc_A.top);
		skill.img_B->render(getMemDC, skill.rc_B.left, skill.rc_B.top);

		
		// 렉트 출력
		if (KEYMANAGER->isToggleKey(VK_NUMPAD9))
		{
			// HP 렉트
			Rectangle(getMemDC, hp.rc_HP_Front);

			// status Ui 렉트
			Rectangle(getMemDC, ui.rc);

			// type 렉트
			Rectangle(getMemDC, type.rc);

			// skill 렉트
			Rectangle(getMemDC, skill.rc_A);
			Rectangle(getMemDC, skill.rc_B);
		}
	}

	// 스컬의 타입에 따라 이미지 업데이트
	void update_Img()
	{
		//// 스컬의 타입에 따라 이미지를 교체해준다.
		//switch (DATAMANAGER->skul_Address()->get_Info().type.skul_Type)
		//{
		//	// 기본스컬, 무기스컬, 머리없는스컬 일때
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


	// 체력 게이지 업데이트
	void update_HP()
	{
		// 체력이 회복하고 있는중
		if (hp.state == HP_UPDATE_STATE::HEAL)
		{
			// 회복중일때 back 이미지 교체
			hp.img_HP_Back = IMAGEMANAGER->findImage("skul_HP_Heal");

			// 회복중일때는 back right가 바로 갱신 된다.
			hp.rc_HP_Back.right = hp.rc_HP_Back.left + (hp.curHP * hp.img_HP_Back->getWidth() / hp.maxHP);
			
			// 회복중일때는 front right가 천천히 증가한다.
			hp.rc_HP_Front.right += HP_PLUS_SPEED;

			// front right가 back right와 같거나 그 이상이라면 최대라는 뜻
			if (hp.rc_HP_Front.right >= hp.rc_HP_Back.right)
			{
				// 넘어갔을 경우 값 보정
				hp.rc_HP_Front.right = hp.rc_HP_Back.right;

				// 체력 상태를 교체한다.
				hp.state = HP_UPDATE_STATE::EMPTY;
			}
		}

		// 체력이 감소하는 중이다.
		if (hp.state == HP_UPDATE_STATE::HIT)
		{
			// 감소중일때 back 이미지 교체
			hp.img_HP_Back = IMAGEMANAGER->findImage("skul_HP_Hit");

			// 감소중일때는 front right가 바로 갱신 된다.
			hp.rc_HP_Front.right = hp.rc_HP_Front.left + (hp.curHP * hp.img_HP_Front->getWidth() / hp.maxHP);

			// 감소중일때는 back right가 천천히 감소한다.
			hp.rc_HP_Back.right -= HP_MINUS_SPEED;

			// back right가 front right와 같거나 그 이하라면 
			if (hp.rc_HP_Back.right <= hp.rc_HP_Front.right)
			{
				// 넘어갔을 경우 값 보정
				hp.rc_HP_Back.right = hp.rc_HP_Front.right;

				// 체력 상태를 교체한다.
				hp.state = HP_UPDATE_STATE::EMPTY;
			}
		}
	}

};















// 에너미는 맥스체력보다 작을 경우에 자신의 체력바가 출력된다.

// 플레이어는 항상 출력됨

// 플레이어의 상태 UI에 필요한것

// 일단 플레이어 전체 UI를 그릴 커다란 렉트 

// 캐릭터의 타입에 따라 이미지를 넣어줄 렉트 

// 스킬을 그릴 렉트 2개

// 맞을때마다 화면 빨간색으로 ?

// 체력바 렉트 현재 체력, 피격 체력바 2개



