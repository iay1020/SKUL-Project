#pragma once
#include "stdafx.h"

#include "mapTool.h"

class tagSceneFunc	// scene 함수를 모아둔 클래스
{
public:
	// 씬 추가를 해주는 함수
	void addScene()
	{
		SCENEMANAGER->addScene("mapTool", new mapTool);
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
	}
};
