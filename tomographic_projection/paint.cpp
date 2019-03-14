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
void Paint::exchange(double left, double right, double low, double up)
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
void Paint::setImage(const std::vector<std::vector<double>> & vec)
{
	_vecImage.clear();
	_vecImage = vec;
}

/** Инициализировать проекцию.*/
void Paint::setProjection(const std::vector<std::vector<double>> & vec)
{
	_vecTomographicProjection.clear();
	_vecTomographicProjection = vec;
}

/** Инициализировать восстановленное изображение.*/
void Paint::setImageRestored(const std::vector<std::vector<cmplx>> & vec)
{
	_vecImageRestored.clear();
	
	std::size_t height = vec.size();
	std::size_t width = vec[0].size();
	_vecImageRestored.resize(height, std::vector<cmplx>(width));

	for (std::size_t idxHeight{ 0U }; idxHeight < height; ++idxHeight)
	{
		for (std::size_t idxWidth{ 0U }; idxWidth < width; ++idxWidth)
		{
			_vecImageRestored[idxHeight][idxWidth].real = vec[idxHeight][idxWidth].real;
			_vecImageRestored[idxHeight][idxWidth].image = vec[idxHeight][idxWidth].image;
		}
	}
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
		Bitmap bmpBuffer(_xmax, _ymax);
		for (size_t idxHeight{ 0U }; idxHeight < height; ++idxHeight)
		{
			for (size_t idxWidth{ 0U }; idxWidth < width; ++idxWidth)
			{
				Color color;
				color = Color::MakeARGB(255, _vecImage[idxHeight][idxWidth], _vecImage[idxHeight][idxWidth], _vecImage[idxHeight][idxWidth]);
				bmpBuffer.SetPixel(idxWidth, height - 1 - idxHeight, color);
			}
		}

		Rect rect(0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
		gr.DrawImage(&bmpBuffer, rect);
	}

	if (!_vecTomographicProjection.empty())
	{
		std::size_t width = _vecTomographicProjection[0].size();
		std::size_t height = _vecTomographicProjection.size();
		Bitmap bmpBuffer(_xmax, _ymax);
		for (std::size_t idxHeight{ 0U }; idxHeight < height; ++idxHeight)
		{
			for (std::size_t idxWidth{ 0U }; idxWidth < width; ++idxWidth)
			{
				Color color;
				color = Color::MakeARGB(255, 
					_vecTomographicProjection[idxHeight][idxWidth], 
					_vecTomographicProjection[idxHeight][idxWidth], 
					_vecTomographicProjection[idxHeight][idxWidth]);
				bmpBuffer.SetPixel(idxWidth, idxHeight, color);
			}
		}

		Rect rect(0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
		gr.DrawImage(&bmpBuffer, rect);
	}

	if (!_vecImageRestored.empty())
	{
		std::size_t width = _vecImageRestored[0].size();
		std::size_t height = _vecImageRestored.size();
		Bitmap bmpBuffer(_xmax, _ymax);
		for (std::size_t idxHeight{ 0U }; idxHeight < height; ++idxHeight)
		{
			for (std::size_t idxWidth{ 0U }; idxWidth < width; ++idxWidth)
			{
				Color color;
				color = Color::MakeARGB(255,
					_vecImageRestored[idxHeight][idxWidth].real,
					_vecImageRestored[idxHeight][idxWidth].real,
					_vecImageRestored[idxHeight][idxWidth].real);
				bmpBuffer.SetPixel(idxWidth, idxHeight, color);
			}
		}

		Rect rect(0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom);
		gr.DrawImage(&bmpBuffer, rect);
	}
}
