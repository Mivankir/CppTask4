﻿
// MyDictApp.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMyDictAppApp:
// Сведения о реализации этого класса: MyDictApp.cpp
//

class CMyDictAppApp : public CWinApp
{
public:
	CMyDictAppApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMyDictAppApp theApp;
