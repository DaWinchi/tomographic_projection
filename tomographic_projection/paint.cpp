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
void Paint::Exchange(double left, double right, double low, double up)
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
void Paint::set_image(const std::vector<std::vector<double>> & vec)
{
	_vec_image.clear();
	_vec_image = vec;
}

/** Функия отрисовки.*/
void Paint::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics gr(lpDrawItemStruct->hDC);
	Bitmap bmp(lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &gr);
	Graphics grBmp(&bmp);

	Pen penEllipse(Color::Red, 3);
	SolidBrush brushCathodRect(Color::Blue);
	SolidBrush brushAnodRect(Color::Red);
	SolidBrush brushConductorRect(Color::DarkKhaki);
	SolidBrush brushPoints(Color::Yellow);

	grBmp.Clear(Color::White);

	if (!_vec_image.empty())
	{
		size_t width = _vec_image[0].size();
		size_t height = _vec_image.size();
		for (size_t i = 0; i < height; ++i)
		{
			for (size_t j = 0; j < width; ++j)
			{
				double val = _vec_image[i][j];
				Color color;
				color = Color::MakeARGB(255 - val, 0, 0, 0);
				SolidBrush brush(color);
				grBmp.FillRectangle(&brush,
					Trans_X(lpDrawItemStruct, j),
					Trans_Y(lpDrawItemStruct, i),
					Width(lpDrawItemStruct, 1),
					Height(lpDrawItemStruct, 1));
			}
		}
	}
	
	gr.DrawImage(&bmp, 0, 0);
}
