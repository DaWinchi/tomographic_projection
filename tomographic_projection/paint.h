#pragma once
#include "afxwin.h"
#include <vector>

/** Структура - комплексное число.*/
struct cmplx
{
	float real;
	float image;
};

class Paint : public CStatic
{
private:
	// Объект для инициализации GDI+
	ULONG_PTR _token;

	float _xmin, _xmax,   // Минимальное и максимальное значение по х
		_ymin, _ymax,   // Минимальное и максимальное значение по у
		_step_x, _step_y;   // Шаг по х и у

	/** Исходное изображение(сигнал).*/
	std::vector<std::vector<float>> _vecImage;
	/** Томографическая проеция.*/
	std::vector<std::vector<float>> _vecTomographicProjection;
	/** Восстановленное изображение(сигнал).*/
	std::vector<std::vector<float>> _vecImageRestored;
	/** FFT.*/
	std::vector<std::vector<float>> _vecFFT;
	/** FFT translated.*/
	std::vector<std::vector<float>> _vecFFTTranslated;


public:
	/** Конструктор.*/
	Paint();
	/** Деструктор.*/
	~Paint();

	/** Функция обмена информацией между классами.*/
	void exchange(float left, float right, float low, float up);

	/** Функция преобразования х к пиксельному формату.*/
	Gdiplus::REAL Trans_X(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL x);
	/** Функция преобразования у к пиксельному формату.*/
	Gdiplus::REAL Trans_Y(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL y);

	Gdiplus::REAL Width(LPDRAWITEMSTRUCT lpDrawItemStruct, float width);
	Gdiplus::REAL Height(LPDRAWITEMSTRUCT lpDrawItemStruct, float width);
	Gdiplus::REAL Paint::W_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, float width);
	Gdiplus::REAL Paint::H_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, float height);

	/** Инициализировать исходное изображение.*/
	void setImage(const std::vector<std::vector<float>> & vec);

	/** Инициализировать проекцию.*/
	void setProjection(const std::vector<std::vector<float>> & vec);

	/** Инициализировать восстановленное изображение.*/
	void setImageRestored(const std::vector<std::vector<float>> & vec);

	/** Инициализировать восстановленное изображение.*/
	void setFFT(const std::vector<std::vector<float>> & vec);

	/** Инициализировать восстановленное изображение.*/
	void setFFTTranslated(const std::vector<std::vector<float>> & vec);
	
	/** Функия отрисовки.*/
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};