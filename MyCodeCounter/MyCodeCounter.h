// MyCodeCounter.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CMyCodeCounterApp:
// �йش����ʵ�֣������ MyCodeCounter.cpp
//

class CMyCodeCounterApp : public CWinApp
{
public:
	CMyCodeCounterApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyCodeCounterApp theApp;
