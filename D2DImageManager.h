#pragma once

#include "D2DImage.h"

class ImageManager
{
	SINGLETONHEADER(ImageManager)
public:
	void Initialize();

	Image* Add(std::string key, std::string path, int inputFrameMaxX = 1, int inputFrameMaxY = 1);
	//Image* Add(std::string key, std::string path);
	//Image* FrameAdd(std::string key, std::string path, int inputFrameMaxX, int inputFrameMaxY);
	Image* Find(std::string key);
	void Del(std::string key);

	std::unordered_map<std::string, Image*> GetStorage() { return imageStorage; }
private:
	std::unordered_map<std::string, Image*> imageStorage;
	typedef std::unordered_map<std::string, Image*>::iterator ImgIter;
};

#define D2DIMAGE ImageManager::Get()
