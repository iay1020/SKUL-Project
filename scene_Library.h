#pragma once
#include "stdafx.h"
#include "mapTool.h"
#include "Stage_0.h"
#include "Stage_1.h"
#include "Stage_2.h"
#include "Intro_Scene.h"
#include "GameOver.h"

class tagSceneFunc	// scene �Լ��� ��Ƶ� Ŭ����
{
public:
	// �� �߰��� ���ִ� �Լ�
	void addScene()
	{
		SCENEMANAGER->addScene("mapTool", new mapTool);
		SCENEMANAGER->addScene("Stage_0", new Stage_0);
		SCENEMANAGER->addScene("Stage_1", new Stage_1);
		SCENEMANAGER->addScene("Stage_2", new Stage_2);
		SCENEMANAGER->addScene("Intro", new Intro_Scene);
		SCENEMANAGER->addScene("GameOver", new GameOver);
	}

	// �� ü������ ���ִ� �Լ�
	// �Ű����� : ��ü���� �ּ�, ���ϴ� �� ����
	void changeScene(string sceneName)
	{
		// �޾ƿ� �� ������ �̿��Ͽ� �� ü����
		SCENEMANAGER->changeScene(sceneName);
	}

	// [�׽�Ʈ] ���� �� ��ȯ �Լ�
	void TEST_SceneChange()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			// ���� ������ �̵��Ѵ�.
			SCENEMANAGER->changeScene("mapTool");
		}

		if (KEYMANAGER->isOnceKeyDown(VK_F2))
		{
			// ���� ������ �̵��Ѵ�.
			SCENEMANAGER->changeScene("Stage_0");
		}

		if (KEYMANAGER->isOnceKeyDown(VK_F3))
		{
			// ���� ������ �̵��Ѵ�.
			SCENEMANAGER->changeScene("Stage_1");
		}
	}
};
