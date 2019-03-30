
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

	/** Вычислить томографическую проекцию.*/
	void computeProjectionFft();

	/** Найти ближайшее сверху число к x, равное степени двойки.
	* @param x - значение, которое необходимо дополнить до степени двойки.
	* @return - значение, равное степени двойки.
	*/
	unsigned int pow_2(unsigned int x);

	/** Произвести одномерное ПФ.
	* @param data - данные, над котромыми производится ПФ.
	* @param n - размер данных.
	* @param is - прямое/обратное ПФ (-1 или 1).
	*/
	void fourier1D(std::vector<std::complex<double>> *data, int n, int is);

	/** Произвести двухмерное ПФ.
	* @param data - данные, над которыми производится ПФ.
	* @param is - прямое/обратное ПФ (-1 или 1).
	*/
	void CtomographicprojectionDlg::fourier2D(std::vector<std::vector<std::complex<double>>> &data, int is);

	/** Вычислить ПФ от томографической проекции.*/
	void fourierFromProjection();

	/** Интерполировать, методом ближайшего соседа.*/
	void interpolateNearNeigh(std::vector<std::vector<std::complex<double>>> & vecOut,
		const std::vector<std::vector<std::complex<double>>> & vecIn,
		int w1,
		int h1,
		int w2,
		int h2);

	/** Интерполировать, методом из MKL.*/
	void interpolationMKL(std::vector<std::vector<std::complex<double>>> & vecRes, std::vector<std::vector<std::complex<double>>> & vecIn);

	/** Определить четность число.
	* @param n - определяемое число.
	* @return - 1 - нечентное, 0 - четное.
	*/
	template<typename T> 
	inline int isOdd(const T& n) 
	{ 
		return n & 1;
	};

	/** Привести изображение к диапазону от 0 до 255.
	* @param image - редактируемое изображение.
	*/
	void imageNormalization(std::vector<std::vector<double>> & image);

	/** Преобразовать координаты s, t в x, y.
	* @param s - координата по s.
	* @param t - координата по t.
	* @param x - координата по Ох.
	* @param y - координата по Оу.
	* @param theta - угол поворота.
	*/
	void coordTransform(double s, double t, int&x, int&y, double theta);

	Projection getSpecificProjection(const std::vector<std::vector<double>> & vecImage, double angle);

	/** Вычислить преобразование Радона.
	* @param vecImage - изображение для вычисления преобразования.
	* @param numberAngles - число углов.
	* @param numberPoints - число точек.
	*/
	std::vector<Projection> getRadonTransform(const std::vector<std::vector<double>> & vecImage, int anglesNumber);

	/** Линеаризовать систему уравнений.*/
	void linearizeEquationsSystem(const std::vector<Projection> &p, std::vector<std::vector<int>> & a, std::vector<double> & y);

	/** Метод Качмаржа.
	* @param a - вытянутая в строку матрица весовых коэффициентов.
	* @param b - вектор правой части.
	* @param x - буфер под запись решения.
	* @param nn - количество неизвестных.
	* @param ny - количество уравнений.
	*/
	void kaczmarzMethod(std::vector<int> & a, std::vector<double> & b, std::vector<double> & x, int nn, int ny);


private:
	/** Отрисовщик исходного изображения.*/
	Paint _paintImage;
	/** Отрисовщик томографической проекции.*/
	Paint _paintTomographicProjection;
	/** Отрисовщик восстановленного изображения.*/
	Paint _paintRestoredImage;
	/** Отрисовщик FFT.*/
	Paint _paintFFT;
	/** Отрисовщик FFT translated.*/
	Paint _paintFFTTranslated;
	/** Отрисовщик FFT 2D.*/
	Paint _paintFFT2D;

	/** Изображение(сигнал).*/
	std::vector<std::vector<double>> _vecImage;
	/** Расширенное изображение(сигнал).*/
	std::vector<std::vector<double>> _vecExtendedImage;
	/** Томографическая проекция.*/
	std::vector<std::vector<double>> _vecProjectionFft;
	/** FFT от томографической проекции.*/
	std::vector<std::vector<std::complex<double>>> _vecProjectionFFT;
	/** Восстановленное изображение(сигнал).*/
	std::vector<std::vector<double>> _vecImageRestored;
	/** FFT.*/
	std::vector<std::vector<double>> _vecFFT;
	/** FFT translated.*/
	std::vector<std::vector<double>> _vecFFTTranslated;
	/** FFT 2D.*/
	std::vector<std::vector<double>> _vecFFT2D;
	/** Вектор проекций для Качмаржа.*/
	std::vector<std::vector<double>> _vecProjectionsKaczmarz;
	/** Вектор структур для Качмаржа.*/
	std::vector<Projection> _vecRadonTransform;

	/** Радиус окружности, описанной вокруг изображения.*/
	int _radius;
	/** Максимальный угол.*/
	const double _maxAngle;
	/** Угловой шаг.*/
	double _stepAngle;
	/** Линейный шаг.*/
	int _stepDistance;
	/** Fourier method*/
	BOOL _isFourier;
	/** Kaczmarz method*/
	BOOL _isKaczmarz;


public:
	/** Обработчик загрузки изображения.*/
	afx_msg void OnBnClickedButton1();
	/** Обработчик получения проекции.*/
	afx_msg void OnBnClickedButton2();
	/** Обработчик получения восстановленного изображения.*/
	afx_msg void OnBnClickedButton3();
};
