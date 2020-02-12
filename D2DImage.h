#pragma once
class Image
{
	friend class ImageManager;

private:
	typedef struct imageInfo
	{
		std::string path;
		float width;
		float height;
		int frameMaxX;
		int frameMaxY;
		float frameWidth;
		float frameHeight;

		ID2D1Bitmap* D2DBitmap;

		imageInfo()
		{
			path = "";
			width = 0.f;
			height = 0.f;
			frameMaxX = 0;
			frameMaxY = 0;
			frameWidth = 0.f;
			frameHeight = 0.f;
		}
	};
	
	imageInfo info;
	
	
public:
	Image() {}
	~Image() {}
	/*
	void Initialize(std::string filePath);
	void Initialize(std::string filePath, int inputFrameMaxX, int inputFrameMaxY);
	*/
	void Initialize(std::string filePath, int inputFrameMaxX = 1, int inputFrameMaxY = 1);

	void CreateImage();

	void Render(float x, float y, float sizeX, float sizeY, float alpha = 1.f, float radian = 0.f, int frameX = 0, int frameY = 0);

	POINTFLOAT GetSize() { return { info.D2DBitmap->GetSize().width, info.D2DBitmap->GetSize().height }; }
	float GetWidth() { return info.D2DBitmap->GetSize().width; }
	float GetHeight() { return info.D2DBitmap->GetSize().height; }
	/*
	void Render(float x, float y, float sizeX, float sizeY, float alpha);
	void Render(float x, float y, float sizeX, float sizeY, float radian, float alpha);

	void FrameRender(float x, float y, float sizeX, float sizeY, int frameX, int frameY, float alpha);
	void FrameRender(float x, float y, float sizeX, float sizeY, float radian, int frameX, int frameY, float alpha);
	*/
};

// radian À» Degree·Î
// radian * 180 / pi;