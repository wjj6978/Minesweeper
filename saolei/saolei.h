
// saolei.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CsaoleiApp:
// �йش����ʵ�֣������ saolei.cpp
//

class CsaoleiApp : public CWinApp
{
public:
	CsaoleiApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CsaoleiApp theApp;