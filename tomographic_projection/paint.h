#pragma once
#include "afxwin.h"
#include <vector>
#include <complex>

struct Projection
{
	// ������ �������� �������� ��� ����������� ���� theta
	std::vector<double> vecSpecificProjection;
	// ���������� ����
	double theta;
	// ������ ��������
	std::vector<double> s;
	// ������� ������������� (� 0 � 1)
	std::vector<std::vector<std::vector<int>>> vecCoeffs;
};


class Paint : public CStatic
{
private:
	// ������ ��� ������������� GDI+
	ULONG_PTR _token;

	double _xmin, _xmax,   // ����������� � ������������ �������� �� �
		_ymin, _ymax,   // ����������� � ������������ �������� �� �
		_step_x, _step_y;   // ��� �� � � �

	/** �������� �����������(������).*/
	std::vector<std::vector<double>> _vecImage;
	/** ��������������� �������.*/
	std::vector<std::vector<double>> _vecTomographicProjection;
	/** ��������������� �����������(������).*/
	std::vector<std::vector<double>> _vecImageRestored;
	/** FFT.*/
	std::vector<std::vector<double>> _vecFFT;
	/** FFT translated.*/
	std::vector<std::vector<double>> _vecFFTTranslated;
	/** FFT 2D.*/
	std::vector<std::vector<double>> _vecFFT2D;


public:
	/** �����������.*/
	Paint();
	/** ����������.*/
	~Paint();

	/** ������� ������ ����������� ����� ��������.*/
	void exchange(double left, double right, double low, double up);

	/** ������� �������������� � � ����������� �������.*/
	Gdiplus::REAL Trans_X(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL x);
	/** ������� �������������� � � ����������� �������.*/
	Gdiplus::REAL Trans_Y(LPDRAWITEMSTRUCT lpDrawItemStruct, Gdiplus::REAL y);

	Gdiplus::REAL Width(LPDRAWITEMSTRUCT lpDrawItemStruct, double width);
	Gdiplus::REAL Height(LPDRAWITEMSTRUCT lpDrawItemStruct, double width);
	Gdiplus::REAL Paint::W_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, double width);
	Gdiplus::REAL Paint::H_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, double height);

	/** ���������������� �������� �����������.*/
	void setImage(const std::vector<std::vector<double>> & vec);

	/** ���������������� ��������.*/
	void setProjection(const std::vector<std::vector<double>> & vec);

	/** ���������������� ��������������� �����������.*/
	void setImageRestored(const std::vector<std::vector<double>> & vec);

	/** ���������������� ��������������� �����������.*/
	void setFFT(const std::vector<std::vector<double>> & vec);

	/** ���������������� ��������������� �����������.*/
	void setFFTTranslated(const std::vector<std::vector<double>> & vec);

	/** ���������������� FFT 2D.*/
	void setFFT2D(const std::vector<std::vector<double>> & vec);
	
	/** ������ ���������.*/
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};