
// tomographic_projection.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CtomographicprojectionApp:
// Сведения о реализации этого класса: tomographic_projection.cpp
//

class CtomographicprojectionApp : public CWinApp
{
public:
	CtomographicprojectionApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CtomographicprojectionApp theApp;
