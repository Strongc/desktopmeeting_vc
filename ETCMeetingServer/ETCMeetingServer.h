
// ETCMeetingServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CETCMeetingServerApp:
// �йش����ʵ�֣������ ETCMeetingServer.cpp
//

class CETCMeetingServerApp : public CWinAppEx
{
public:
	CETCMeetingServerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CETCMeetingServerApp theApp;