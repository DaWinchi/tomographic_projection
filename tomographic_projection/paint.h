#pragma once
#include "afxwin.h"
#include <vector>

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
	Gdiplus::REAL Width(LPDRAWITEMSTRUCT lpDrawItemStruct, float width);
	Gdiplus::REAL Height(LPDRAWITEMSTRUCT lpDrawItemStruct, float width);
	Gdiplus::REAL Paint::W_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, float width);
	Gdiplus::REAL Paint::H_Ellipse(LPDRAWITEMSTRUCT lpDrawItemStruct, float height);
	/** ���������������� �������� �����������.*/
	void setImage(const std::vector<std::vector<double>> & vec);

	/** ���������������� ��������.*/
	void setProjection(const std::vector<std::vector<double>> & vec);
	
	/** ������ ���������.*/
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
};