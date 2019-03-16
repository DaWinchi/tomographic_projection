#include "stdafx.h"
#include "Paint.h"
#include "Gdiplus.h"

using namespace Gdiplus;

/** Инициализация GDI+.*/
Paint::Paint()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&_token, &input, NULL);
	if (s != Ok)
		MessageBox(L"Don't Open", L"Warning", MB_ICONERROR);
}

/** Деинициализация GDI+.*/
Paint::~Paint()
{
	GdiplusShutdown(_token);
}

/** Функция обмена информацией между классами.*/
void Paint::exchange(float left, float right, float low, float up)
{
	_xmin = left;
	_xmax = right;
	_ymin = low;
	_ymax = up;
	RedrawWindow();
}

/** Преобразование х к пиксельному формату.*/
Gdiplus::REAL Paint::Trans_X(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL x)
{
	return (Gdiplus::REAL)(lpDrawItemStruct->rcItem.right) / (Gdiplus::REAL)(_xmax - _xmin) * ((x)-_xmin);
}

/** Преобразование у к пиксельному формату.*/
Gdiplus::REAL Paint::Trans_Y(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL y)
{
	return -(Gdiplus::REAL)(lpDrawItemStruct->rcItem.bottom) / (Gdiplus::REAL)(_ymax - _ymin) * ((y)-_ymax);
}

Gdiplus::REAL Paint::Width(LPDRAWITEMSTRUCT lpDrawItemStruct, float width)
{
	return (REAL)(lpDrawItemStruct->rcItem.right) / (_xmax - _xmin) * width;
}

Gdiplus::REAL Paint::Height(LPDRAWITEMSTRUCT lpDrawItemStruct, float height)
{
	return (REAL)(lpDrawItemStruct->rcItem.bottom) / (_ymax - _ymin) * height;
}

Gdiplus::REAL Paint::W_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, float width)
{
	return (REAL)(lpDrawItemStruct->rcItem.right) / (_xmax - _xmin) * width;
}

Gdiplus::REAL Paint::H_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, float height)
{
	return -(REAL)(lpDrawItemStruct->rcItem.bottom) / (_ymax - _ymin) * height;
}

/** Инициализировать исходное изображение.*/
void Paint::setImage(const std::vector<std::vector<float>> & vec)
{
	_vecImage.clear();
	_vecImage = vec;
}

/** Инициализировать проекцию.*/
void Paint::setProjection(const std::vector<std::vector<float>> & vec)
{
	_vecTomographicProjection.clear();
	_vecTomographicProjection = vec;
}

/** Инициализировать восстановленное изображение.*/
void Paint::setImageRestored(const std::vector<std::vector<float>> & vec)
{
	_vecImageRestored.clear();
	_vecImageRestored = vec;
}

/** Инициализировать FFT.*/
void Paint::setFFT(const std::vector<std::vector<float>> & vec)
{
	_vecFFT.clear();
	_vecFFT = vec;
}

/** Инициализировать FFT translated.*/
void Paint::setFFTTranslated(const std::vector<std::vector<float>> & vec)
{
	_vecFFTTranslated.clear();
	_vecFFTTranslated = vec;
}

/** Функия отрисовки.*/
void Paint::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics gr(lpDrawItemStruct->hDC);
	Bitmap bmp(lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &gr);
	Graphics grBmp(&bmp);

	grBmp.Clear(Color::White);

	if (!_vecImage.empty())
	{
		size_t width = _vecImage[0].size();
		size_t height = _vecImage.size();
		Bitmap bmpBuffer(static_cast<INT>(_xmax), static_cast<INT>(_ymax));
		for (size_t idxHeight{ 0U }; idxHeight < height; ++idxHeight)
		{
			for (size_t idxWidth{ 0U }; idxWidth < width; ++idxWidth)
			{
				Color color;
				color = Color::MakeARGB(static_cast<BYTE>(255), 
					static_cast<BYTE>(_vecImage[idxHeight][idxWidth]), 
					static_cast<BYTE>(_vecImage[idxHeight][idxWidth]), 
					static_cast<BYTE>(_vecImage[idxHeight][idxWidth]));
				bmpBuffer.SetPixel(static_cast<INT>(idxWidth), static_cast<INT>(idxHeight), color);
			}
		}

		Rect rect(0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
		gr.DrawImage(&bmpBuffer, rect);
	}

	if (!_vecTomographicProjection.empty())
	{
		std::size_t width = _vecTomographicProjection[0].size();
		std::size_t height = _vecTomographicProjection.size();
		Bitmap bmpBuffer(static_cast<INT>(_xmax), static_cast<INT>(_ymax));
		for (std::size_t idxHeight{ 0U }; idxHeight < height; ++idxHeight)
		{
			for (std::size_t idxWidth{ 0U }; idxWidth < width; ++idxWidth)
			{
				Color color;
				color = Color::MakeARGB(static_cast<BYTE>(255),
					static_cast<BYTE>(_vecTomographicProjection[idxHeight][idxWidth]),
					static_cast<BYTE>(_vecTomographicProjection[idxHeight][idxWidth]),
					static_cast<BYTE>(_vecTomographicProjection[idxHeight][idxWidth]));
				bmpBuffer.SetPixel(static_cast<INT>(idxWidth), static_cast<INT>(idxHeight), color);
			}
		}

		Rect rect(0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
		gr.DrawImage(&bmpBuffer, rect);
	}

	if (!_vecImageRestored.empty())
	{
		std::size_t width = _vecImageRestored[0].size();
		std::size_t height = _vecImageRestored.size();
		Bitmap bmpBuffer(static_cast<INT>(_xmax), static_cast<INT>(_ymax));
		for (std::size_t idxHeight{ 0U }; idxHeight < height; ++idxHeight)
		{
			for (std::size_t idxWidth{ 0U }; idxWidth < width; ++idxWidth)
			{
				Color color;
				color = Color::MakeARGB(static_cast<BYTE>(255),
					static_cast<BYTE>(_vecImageRestored[idxHeight][idxWidth]),
					static_cast<BYTE>(_vecImageRestored[idxHeight][idxWidth]),
					static_cast<BYTE>(_vecImageRestored[idxHeight][idxWidth]));
				bmpBuffer.SetPixel(static_cast<INT>(idxWidth), static_cast<INT>(idxHeight), color);
			}
		}

		Rect rect(0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
		gr.DrawImage(&bmpBuffer, rect);
	}

	if (!_vecFFT.empty())
	{
		std::size_t width = _vecFFT[0].size();
		std::size_t height = _vecFFT.size();
		Bitmap bmpBuffer(static_cast<INT>(_xmax), static_cast<INT>(_ymax));
		for (std::size_t idxHeight{ 0U }; idxHeight < height; ++idxHeight)
		{
			for (std::size_t idxWidth{ 0U }; idxWidth < width; ++idxWidth)
			{
				Color color;
				color = Color::MakeARGB(static_cast<BYTE>(255),
					static_cast<BYTE>(_vecFFT[idxHeight][idxWidth]),
					static_cast<BYTE>(_vecFFT[idxHeight][idxWidth]),
					static_cast<BYTE>(_vecFFT[idxHeight][idxWidth]));
				bmpBuffer.SetPixel(static_cast<INT>(idxWidth), static_cast<INT>(idxHeight), color);
			}
		}

		Rect rect(0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
		gr.DrawImage(&bmpBuffer, rect);
	}

	if (!_vecFFTTranslated.empty())
	{
		std::size_t width = _vecFFTTranslated[0].size();
		std::size_t height = _vecFFTTranslated.size();
		Bitmap bmpBuffer(static_cast<INT>(_xmax), static_cast<INT>(_ymax));
		for (std::size_t idxHeight{ 0U }; idxHeight < height; ++idxHeight)
		{
			for (std::size_t idxWidth{ 0U }; idxWidth < width; ++idxWidth)
			{
				Color color;
				color = Color::MakeARGB(static_cast<BYTE>(255),
					static_cast<BYTE>(_vecFFTTranslated[idxHeight][idxWidth]),
					static_cast<BYTE>(_vecFFTTranslated[idxHeight][idxWidth]),
					static_cast<BYTE>(_vecFFTTranslated[idxHeight][idxWidth]));
				bmpBuffer.SetPixel(static_cast<INT>(idxWidth), static_cast<INT>(idxHeight), color);
			}
		}

		Rect rect(0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
		gr.DrawImage(&bmpBuffer, rect);
	}
}
