
// flygomfc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CflygomfcApp:
// �йش����ʵ�֣������ flygomfc.cpp
//

class CflygomfcApp : public CWinApp
{
public:
	CflygomfcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
//	NOTIFYICONDATA m_nid;
};

extern CflygomfcApp theApp;