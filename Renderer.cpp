#include "stdafx.h"
#include "Renderer.h"


SINGLETONCPP(Renderer)

void Renderer::Initialize()
{
	InitializeD2D();
	CreateRenderTarget();

	isDebugMode = false;
}

void Renderer::BeginDraw()
{
	D2DRenderTarget->BeginDraw();
	D2DRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	D2DRenderTarget->SetTransform(D2D1::IdentityMatrix());
}

void Renderer::EndDraw()
{
	D2DRenderTarget->EndDraw();
}

void Renderer::DrawLine(float x, float y, float dx, float dy, D2D1_COLOR_F color)
{
	HRESULT hr = E_FAIL;
	D2D_POINT_2F beginPoint = D2D1::Point2F(x, y);
	D2D_POINT_2F endPoint = D2D1::Point2F(dx, dy);

	D2DRenderTarget->CreateSolidColorBrush(color, &brush);
	D2DRenderTarget->DrawLine(beginPoint, endPoint, brush);
}

void Renderer:: DrawRectangle(D2D1_RECT_F rect, D2D1_COLOR_F color, float thikness, float radian)
{
	float tempDegree = radian * 180 / M_PI;
	D2D1::Matrix3x2F tempRotateMatrix = D2D1::Matrix3x2F::Rotation(tempDegree, D2D1::Point2F(
		(rect.right + rect.left) / 2.f, (rect.top + rect.bottom) / 2.f));

	D2DRenderTarget->SetTransform(tempRotateMatrix);
	D2DRenderTarget->CreateSolidColorBrush(color, &brush);
	D2DRenderTarget->DrawRectangle(rect, brush, thikness);
	D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

}

void Renderer::DrawRectangle(float x, float y, float sizeX, float sizeY, D2D1_COLOR_F color, float thikness, float radian)
{
	float tempDegree = radian * 180 / M_PI;
	D2D1::Matrix3x2F tempRotateMatrix = D2D1::Matrix3x2F::Rotation(tempDegree, D2D1::Point2F(x, y));

	D2DRenderTarget->SetTransform(tempRotateMatrix);
	D2DRenderTarget->CreateSolidColorBrush(color, &brush);
	D2DRenderTarget->DrawRectangle(D2D1::RectF(x - sizeX * 0.5f, y - sizeY * 0.5f, x + sizeX * 0.5f, y + sizeY * 0.5f), brush, thikness);
	D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Renderer::DrawElipse(D2D1_RECT_F rect, D2D1_COLOR_F color, float thikness, float radian)
{
	float tempDegree = radian * 180 / M_PI;
	D2D1::Matrix3x2F tempRotateMatrix = D2D1::Matrix3x2F::Rotation(tempDegree, D2D1::Point2F(
		(rect.right + rect.left) / 2.f, (rect.top + rect.bottom) / 2.f));

	D2DRenderTarget->SetTransform(tempRotateMatrix);
	D2DRenderTarget->CreateSolidColorBrush(color, &brush);
	D2DRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F((rect.right + rect.left) / 2.f,(rect.bottom + rect.top)/2.f),
		(rect.right - rect.left) / 2.f, (rect.bottom - rect.top) / 2.f), brush, thikness);
	D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Renderer::DrawElipse(float x, float y, float sizeX, float sizeY, D2D1_COLOR_F color, float thikness, float radian)
{
	float tempDegree = radian * 180 / M_PI;
	D2D1::Matrix3x2F tempRotateMatrix = D2D1::Matrix3x2F::Rotation(tempDegree, D2D1::Point2F(x, y));

	D2DRenderTarget->SetTransform(tempRotateMatrix);
	D2DRenderTarget->CreateSolidColorBrush(color, &brush);
	D2DRenderTarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y),
		x - sizeX / 2.f,y - sizeY / 2.f),brush,thikness);
	D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void Renderer::InitializeD2D()
{
	CoInitialize(NULL);

	HRESULT hr = E_FAIL;
	//D2D Factory 생성
	hr = ::D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);
	assert(hr == S_OK);

	// Windows Imaging Component Factory 생성
	hr = ::CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&WICFactory));
	assert(hr == S_OK);
}

void Renderer::CreateRenderTarget()
{
	HRESULT hr = E_FAIL;

	//윈도우 클라이언트 영역
	RECT tempRc;
	::GetClientRect(_hWnd, &tempRc);

	//윈도우 클라이언트 영역의 크기 구하기
	D2D1_SIZE_U size = D2D1::SizeU(tempRc.right - tempRc.left, tempRc.bottom - tempRc.top);

	//렌더타겟 생성
	hr = D2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(_hWnd, size),
		&D2DRenderTarget);
	assert(hr == S_OK);
}
