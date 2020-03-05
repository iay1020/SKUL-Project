#pragma once
#include "gameNode.h"

struct ImageInfo
{
	string			imgName;
	POINTFLOAT		center;

	void reset()
	{
		imgName = "";
		center.x = center.y = 0;

	}

};

class ImageMake : public gameNode
{
	vector<ImageInfo>					vImgInfo;
	vector<ImageInfo>::iterator			viImgInfo;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	// 이미지 생성 (매개변수 : 좌표x, y, 이미지키값, 방향, 지워지기까지 시간
	void Create_Img(float posX, float posY, string imgName);

	// 이미지 출력
	void Show_Img();

};

