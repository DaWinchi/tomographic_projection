
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

	/** Дополнить изображение нулями со всех сторон.
	* @param heightOld - высота исходного изображения.
	* @param widthOld - ширина исходного изображения.
	* @param vecExtendedImage - расширенное изображение.
	*/
	void extendImage(int heightOld, int widthOld, std::vector<std::vector<double>> & vecExtendedImage);

	/** Повернуть изображение.
	* @param angle - угол, на которое нужно повернуть исходное изображение.
	* @param vecImageIn - исходное изображение.
	* @param vecImageOut - повернутое изображение.
	*/
	void rotateImage(double angle, const std::vector<std::vector<double>> & vecImageIn, std::vector<std::vector<double>> & vecImageOut);

	/** Матрица поворота.
	* @param x - координата x.
	* @param y - координата y.
	* @param angle - угол поворота.
	*/
	void transformMatrix(double& x, double& y, double angle);

	/** Вычислить томографическую проекцию.*/
	void computeProjection();
	
	/** Произвести одномерное ПФ.
	* @param data - данные, над котромыми производится ПФ.
	* @param n - размер данных.
	* @param is - прямое/обратное ПФ (-1 или 1).
	*/
	void fourier1D(std::vector<cmplx> *data, int n, int is);

	/** Вычислить ПФ от томографической проекции.*/
	void fourierFromProjection();


private:
	/** Отрисовщик исходного изображения.*/
	Paint _paintImage;
	/** Отрисовщик томографической проекции.*/
	Paint _paintTomographicProjection;
	/** Отрисовщик восстановленного изображения.*/
	Paint _paintRestoredImage;

	/** Изображение(сигнал).*/
	std::vector<std::vector<double>> _vecImage;
	/** Расширенное изображение(сигнал).*/
	std::vector<std::vector<double>> _vecExtendedImage;
	/** Томографическая проекция.*/
	std::vector<std::vector<double>> _vecProjection;
	
	/** Радиус окружности, описанной вокруг изображения.*/
	int _radius;
	/** Максимальный угол.*/
	const double _maxAngle;
	/** Угловой шаг.*/
	double _stepAngle;
	/** Линейный шаг.*/
	int _stepDistance;
	

public:
	/** Обработчик загрузки ихображения.*/
	afx_msg void OnBnClickedButton1();
	/** Обработчик получения проекции.*/
	afx_msg void OnBnClickedButton2();
};
