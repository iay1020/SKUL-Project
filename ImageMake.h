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

	// �̹��� ���� (�Ű����� : ��ǥx, y, �̹���Ű��, ����, ����������� �ð�
	void Create_Img(float posX, float posY, string imgName);

	// �̹��� ���
	void Show_Img();

};

