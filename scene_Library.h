#pragma once
#include "stdafx.h"
#include "mapTool.h"
#include "Stage_0.h"
#include "Stage_1.h"
#include "Stage_2.h"
#include "Intro_Scene.h"
#include "GameOver.h"

class tagSceneFunc	// scene 함수를 모아둔 클래스
{
public:
	// 씬 추가를 해주는 함수
	void addScene()
	{
		SCENEMANAGER->addScene("mapTool", new mapTool);
		SCENEMANAGER->addScene("Stage_0", new Stage_0);
		SCENEMANAGER->addScene("Stage_1", new Stage_1);
		SCENEMANAGER->addScene("Stage_2", new Stage_2);
		SCENEMANAGER->addScene("Intro", new Intro_Scene);
		SCENEMANAGER->addScene("GameOver", new GameOver);
	}

	// 씬 체인지를 해주는 함수
	// 매개변수 : 씬체인저 주소, 원하는 씬 네임
	void changeScene(string sceneName)
	{
		// 받아온 씬 네임을 이용하여 씬 체인지
		SCENEMANAGER->changeScene(sceneName);
	}

	// [테스트] 강제 씬 전환 함수
	void TEST_SceneChange()
	{
		if (KEYMANAGER->isOnceKeyDown(VK_F1))
		{
			// 맵툴 씬으로 이동한다.
			SCENEMANAGER->changeScene("mapTool");
		}

		if (KEYMANAGER->isOnceKeyDown(VK_F2))
		{
			// 맵툴 씬으로 이동한다.
			SCENEMANAGER->changeScene("Stage_0");
		}

		if (KEYMANAGER->isOnceKeyDown(VK_F3))
		{
			// 맵툴 씬으로 이동한다.
			SCENEMANAGER->changeScene("Stage_1");
		}
	}
};
