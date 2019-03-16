#pragma once
#include "afxwin.h"
#include <vector>

/** ��������� - ����������� �����.*/
struct cmplx
{
	float real;
	float image;
};

class Paint : public CStatic
{
private:
	// ������ ��� ������������� GDI+
	ULONG_PTR _token;

	float _xmin, _xmax,   // ����������� � ������������ �������� �� �
		_ymin, _ymax,   // ����������� � ������������ �������� �� �
		_step_x, _step_y;   // ��� �� � � �

	/** �������� �����������(������).*/
	std::vector<std::vector<float>> _vecImage;
	/** ��������������� �������.*/
	std::vector<std::vector<float>> _vecTomographicProjection;
	/** ��������������� �����������(������).*/
	std::vector<std::vector<float>> _vecImageRestored;
	/** FFT.*/
	std::vector<std::vector<float>> _vecFFT;
	/** FFT translated.*/
	std::vector<std::vector<float>> _vecFFTTranslated;


public:
	/** �����������.*/
	Paint();
	/** ����������.*/
	~Paint();

	/** ������� ������ ����������� ����� ��������.*/
	void exchange(float left, float right, float low, float up);

	/** ������� �������������� � � ����������� �������.*/
	Gdiplus::REAL Trans_X(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL x);
	/** ������� �������������� � � ����������� �������.*/
	Gdiplus::REAL Trans_Y(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL y);

	Gdiplus::REAL Width(LPDRAWITEMSTRUCT lpDrawItemStruct, float width);
	Gdiplus::REAL Height(LPDRAWITEMSTRUCT lpDrawItemStruct, float width);
	Gdiplus::REAL Paint::W_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, float width);
	Gdiplus::REAL Paint::H_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, float height);

	/** ���������������� �������� �����������.*/
	void setImage(const std::vector<std::vector<float>> & vec);

	/** ���������������� ��������.*/
	void setProjection(const std::vector<std::vector<float>> & vec);

	/** ���������������� ��������������� �����������.*/
	void setImageRestored(const std::vector<std::vector<float>> & vec);

	/** ���������������� ��������������� �����������.*/
	void setFFT(const std::vector<std::vector<float>> & vec);

	/** ���������������� ��������������� �����������.*/
	void setFFTTranslated(const std::vector<std::vector<float>> & vec);
	
	/** ������ ���������.*/
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};