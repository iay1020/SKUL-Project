#include "stdafx.h"
#include "D2DImage.h"
/*
void Image::Initialize(std::string filePath)
{
	info.path = filePath;
	CreateImage();
}

void Image::Initialize(std::string filePath, int inputFrameMaxX, int inputFrameMaxY)
{
	info.path = filePath;
	info.frameMaxX = inputFrameMaxX;
	info.frameMaxY = inputFrameMaxY;
	CreateImage();
}
*/
void Image::Initialize(std::string filePath, int inputFrameMaxX, int inputFrameMaxY)
{
	info.path = filePath;
	info.frameMaxX = inputFrameMaxX;
	info.frameMaxY = inputFrameMaxY;
	CreateImage();
}

void Image::CreateImage()
{
	HRESULT hr = S_OK;


	// Decoder 생성
	IWICBitmapDecoder* decoder = nullptr;
	hr = D2DRENDER.GetWICFactory()->CreateDecoderFromFilename
	(
		std::wstring(info.path.begin(), info.path.end()).c_str(),
		nullptr, 
		GENERIC_READ, 
		WICDecodeMetadataCacheOnDemand, 
		&decoder
	);
	assert(hr == S_OK);

	// Frame 추출
	IWICBitmapFrameDecode* frame = nullptr;
	hr = decoder->GetFrame(0, &frame);
	assert(hr == S_OK);

	//srcBitmap 초기화
	IWICFormatConverter* srcBitmap = nullptr;
	hr = D2DRENDER.GetWICFactory()->CreateFormatConverter(&srcBitmap);
	assert(hr == S_OK);

	//Frame에 따른 컨버터 생성
	hr = srcBitmap->Initialize(
		frame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);
	
	assert(hr == S_OK);

	//컨버터 이미지로 실제 이미지 생성
	info.D2DBitmap = nullptr;
	hr = D2DRENDER.GetRenderTarget()->CreateBitmapFromWicBitmap(srcBitmap, nullptr, &info.D2DBitmap);
	assert(hr == S_OK);

	SafeRelease(decoder);
	SafeRelease(frame);

	info.width = info.D2DBitmap->GetSize().width;
	info.height = info.D2DBitmap->GetSize().height;
}

void Image::Render(float x, float y, float sizeX, float sizeY, float alpha, float radian, int frameX, int frameY)
{
	if (info.D2DBitmap != nullptr)
	{
		info.frameWidth = info.width / info.frameMaxX;
		info.frameHeight = info.height / info.frameMaxY;

		/* Area Define */
		float left, top, right, bottom;
		left = x - sizeX / 2.f;
		top = y - sizeY / 2.f;
		right = x + sizeX / 2.f;
		bottom = y + sizeY / 2.f;

		::D2D1_RECT_F renderArea = D2D1::RectF(left, top, right, bottom);

		/* Convert Radian to Degree */
		float tempDegree = radian * 180 / M_PI;
		D2D1::Matrix3x2F tempRotateMatrix = D2D1::Matrix3x2F::Rotation(tempDegree, D2D1::Point2F(x, y));

		::D2D1_RECT_F cropArea = D2D1::RectF(info.frameWidth*frameX, info.frameHeight*frameY, info.frameWidth*(frameX + 1), info.frameHeight * (frameY + 1));

		D2DRENDER.GetRenderTarget()->SetTransform(tempRotateMatrix);
		D2DRENDER.GetRenderTarget()->DrawBitmap(
			info.D2DBitmap,
			renderArea,
			alpha,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			cropArea
		);
		D2DRENDER.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
	}
}
//
//void Image::Render(float x, float y, float sizeX, float sizeY, float alpha = 1.f)
//{
//	if (info.D2DBitmap != nullptr)
//	{
//		/* Area Define */
//		float left, top, right, bottom;
//		left = x - sizeX / 2.f;
//		top = y - sizeY / 2.f;
//		right = x + sizeX / 2.f;
//		bottom = y + sizeY / 2.f;
//		::D2D1_RECT_F renderArea =  D2D1::RectF(left, top, right, bottom);
//
//		/* Render */
//		RENDER.GetRenderTarget()->DrawBitmap(info.D2DBitmap, renderArea, alpha);
//		RENDER.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//	}
//}
//
//void Image::Render(float x, float y, float sizeX, float sizeY, float radian, float alpha = 1.f)
//{
//	if (info.D2DBitmap != nullptr)
//	{
//		/* Area Define */
//		float left, top, right, bottom;
//		left = x - sizeX / 2.f;
//		top = y - sizeY / 2.f;
//		right = x + sizeX / 2.f;
//		bottom = y + sizeY / 2.f;
//		::D2D1_RECT_F renderArea = D2D1::RectF(left, top, right, bottom);
//
//		/* Convert Radian to Degree */
//		float tempDegree = radian * 180 / M_PI;
//		D2D1::Matrix3x2F tempRotateMatrix = D2D1::Matrix3x2F::Rotation(tempDegree, D2D1::Point2F(x, y));
//
//		/* Render */
//		RENDER.GetRenderTarget()->SetTransform(tempRotateMatrix);
//		RENDER.GetRenderTarget()->DrawBitmap(info.D2DBitmap, renderArea, alpha);
//		RENDER.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//	}
//}
//
//void Image::FrameRender(float x, float y, float sizeX, float sizeY, int frameX, int frameY, float alpha)
//{
//	if (info.D2DBitmap != nullptr)
//	{
//		info.frameWidth = info.width / info.frameMaxX;
//		info.frameHeight = info.height / info.frameMaxY;
//		
//		/* Area Define */
//		float left, top, right, bottom;
//		left = x - sizeX / 2.f;
//		top = y - sizeY / 2.f;
//		right = x + sizeX / 2.f;
//		bottom = y + sizeY / 2.f;
//		::D2D1_RECT_F renderArea = D2D1::RectF(left, top, right, bottom);
//
//		::D2D1_RECT_F cropArea = D2D1::RectF(info.frameWidth*(frameX), info.frameHeight*frameY, info.frameWidth*(frameX + 1), info.frameHeight * (frameY + 1));
//
//		RENDER.GetRenderTarget()->DrawBitmap(
//			info.D2DBitmap,
//			renderArea,
//			alpha,
//			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//			cropArea
//			);
//		RENDER.GetRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
//	}
//}
//
//void Image::FrameRender(float x, float y, float sizeX, float sizeY, float radian, int frameX, int frameY, float alpha)
//{
//	if (info.D2DBitmap != nullptr)
//	{
//		info.frameWidth = info.width / info.frameMaxX;
//		info.frameHeight = info.height / info.frameMaxY;
//	}
//}
