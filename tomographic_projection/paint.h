#pragma once
#include "afxwin.h"
#include <vector>
#include <complex>

struct Projection
{
	// массив значений проекции для конкретного угла theta
	std::vector<double> vecSpecificProjection;
	// конкретный угол
	double theta;
	// массив значений
	std::vector<double> s;
	// матрица коэффициентов (с 0 и 1)
	std::vector<std::vector<std::vector<int>>> vecCoeffs;
};


class Paint : public CStatic
{
private:
	// Объект для инициализации GDI+
	ULONG_PTR _token;

	double _xmin, _xmax,   // Минимальное и максимальное значение по х
		_ymin, _ymax,   // Минимальное и максимальное значение по у
		_step_x, _step_y;   // Шаг по х и у

	/** Исходное изображение(сигнал).*/
	std::vector<std::vector<double>> _vecImage;
	/** Томографическая проеция.*/
	std::vector<std::vector<double>> _vecTomographicProjection;
	/** Восстановленное изображение(сигнал).*/
	std::vector<std::vector<double>> _vecImageRestored;
	/** FFT.*/
	std::vector<std::vector<double>> _vecFFT;
	/** FFT translated.*/
	std::vector<std::vector<double>> _vecFFTTranslated;
	/** FFT 2D.*/
	std::vector<std::vector<double>> _vecFFT2D;


public:
	/** Конструктор.*/
	Paint();
	/** Деструктор.*/
	~Paint();

	/** Функция обмена информацией между классами.*/
	void exchange(double left, double right, double low, double up);

	/** Функция преобразования х к пиксельному формату.*/
	Gdiplus::REAL Trans_X(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL x);
	/** Функция преобразования у к пиксельному формату.*/
	Gdiplus::REAL Trans_Y(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL y);

	Gdiplus::REAL Width(LPDRAWITEMSTRUCT lpDrawItemStruct, double width);
	Gdiplus::REAL Height(LPDRAWITEMSTRUCT lpDrawItemStruct, double width);
	Gdiplus::REAL Paint::W_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, double width);
	Gdiplus::REAL Paint::H_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, double height);

	/** Инициализировать исходное изображение.*/
	void setImage(const std::vector<std::vector<double>> & vec);

	/** Инициализировать проекцию.*/
	void setProjection(const std::vector<std::vector<double>> & vec);

	/** Инициализировать восстановленное изображение.*/
	void setImageRestored(const std::vector<std::vector<double>> & vec);

	/** Инициализировать восстановленное изображение.*/
	void setFFT(const std::vector<std::vector<double>> & vec);

	/** Инициализировать восстановленное изображение.*/
	void setFFTTranslated(const std::vector<std::vector<double>> & vec);

	/** Инициализировать FFT 2D.*/
	void setFFT2D(const std::vector<std::vector<double>> & vec);
	
	/** Функия отрисовки.*/
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};