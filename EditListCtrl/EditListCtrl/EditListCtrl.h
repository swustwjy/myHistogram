
// EditListCtrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEditListCtrlApp: 
// �йش����ʵ�֣������ EditListCtrl.cpp
//

class CEditListCtrlApp : public CWinApp
{
public:
	CEditListCtrlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEditListCtrlApp theApp;