
// tomographic_projectionDlg.h: файл заголовка
//

#pragma once

#include <vector>
#include "Paint.h"

using namespace Gdiplus;

// Диалоговое окно CtomographicprojectionDlg
class CtomographicprojectionDlg : public CDialogEx
{
// Создание
public:
	CtomographicprojectionDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOMOGRAPHIC_PROJECTION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	/** Загрузить изображение.*/
	int uploadImage();
	/** Матрица поворота.*/
	void transformMatrix(double& x, double& y, double angle);
	

private:
	/** Отрисовщик.*/
	Paint _paintTomograph;
	/** Изображение(сигнал).*/
	std::vector<std::vector<double>> _vec_image;
	double _stepAngle;
	double _stepDistance;
	int _widthProjection;
	int _heightProjection;

public:
	/** Обработчик загрузки ихображения.*/
	afx_msg void OnBnClickedButton1();
};
