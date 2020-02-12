//#include "../../stdafx.h"
#include "stdafx.h"
#include "D2DImageManager.h"

SINGLETONCPP(ImageManager)

void ImageManager::Initialize()
{

}

Image * ImageManager::Add(std::string key, std::string path, int inputFrameMaxX, int inputFrameMaxY)
{
	ImgIter tempIter;
	tempIter = imageStorage.find(key);

	if (tempIter != imageStorage.end())
	{
		return tempIter->second;
	}

	Image* newImage = new Image();
	newImage->Initialize(path, inputFrameMaxX, inputFrameMaxY);
	imageStorage.insert(make_pair(key, newImage));

	return newImage;
}
/*
Image * ImageManager::Add(std::string key, std::string path)
{
	ImgIter tempIter;
	tempIter = imageStorage.find(key);

	if (tempIter != imageStorage.end())
	{
		return tempIter->second;
	}

	Image* newImage = new Image();
	newImage->Initialize(path);
	imageStorage.insert(make_pair(key, newImage));

	return newImage;
}

Image * ImageManager::FrameAdd(std::string key, std::string path, int inputFrameMaxX = 1, int inputFrameMaxY = 1)
{
	ImgIter tempIter;
	tempIter = imageStorage.find(key);

	if (tempIter != imageStorage.end())
	{
		return tempIter->second;
	}
	
	Image* newImage = new Image();
	newImage->Initialize(path, inputFrameMaxX, inputFrameMaxY);
	imageStorage.insert(make_pair(key, newImage));

	return newImage;
}
*/
Image * ImageManager::Find(std::string key)
{
	ImgIter tempIter;
	tempIter = imageStorage.find(key);
	if (tempIter == imageStorage.end())
	{
		return nullptr;
	}
	return imageStorage[key];
}

void ImageManager::Del(std::string key)
{
	ImgIter tempIter;
	tempIter = imageStorage.find(key);
	if (tempIter != imageStorage.end())
	{
		imageStorage.erase(key);
	}
}