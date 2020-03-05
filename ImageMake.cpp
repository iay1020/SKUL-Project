#include "stdafx.h"
#include "ImageMake.h"

HRESULT ImageMake::init()
{

	return S_OK;
}

void ImageMake::release()
{
}

void ImageMake::update()
{
}

void ImageMake::render()
{
	Show_Img();

}

void ImageMake::Create_Img(float posX, float posY, string imgName)
{
	ImageInfo new_Img;
	new_Img.reset();
	new_Img.center.x = posX;
	new_Img.center.y = posY;
	new_Img.imgName = imgName;

	vImgInfo.push_back(new_Img);

}

void ImageMake::Show_Img()
{
	float x, y;

	if (vImgInfo.size() > 0)
	{
		for (viImgInfo = vImgInfo.begin(); viImgInfo != vImgInfo.end(); viImgInfo++)
		{
			x = viImgInfo->center.x - CAMERAMANAGER->Use_Func()->get_CameraXY().x;
			y = viImgInfo->center.y - CAMERAMANAGER->Use_Func()->get_CameraXY().y;

			if (viImgInfo->imgName == "paladin_Die_Right" || viImgInfo->imgName == "paladin_Die_Left") y -= 30;
			
			IMAGEMANAGER->findImage(viImgInfo->imgName)->render(getMemDC(), x, y + 5);
		}
	}

}
