
// ETCMeetingClientDlg.h : ͷ�ļ�
//

#pragma once

#define WM_UPDATEPIC 10001
#include "ScrollWnd.h"
#include "afxwin.h"

class ThreadData
{
public:
	CImage* m_pImage;
	CWnd* m_pDlg;
};

// CETCMeetingClientDlg �Ի���
class CETCMeetingClientDlg : public CDialog
{
// ����
public:
	CETCMeetingClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ETCMEETINGCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	int m_nHorzMaxSize;
	int m_nVertMaxSize;
	int m_nHorzPageSize;
	int m_nVertPageSize;
	int m_nOneStep;
	int m_nHorzPos;
	int m_nVertPos;
	void DrawPic();

public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	LRESULT OnUpdatePic(WPARAM wParam, LPARAM lParam);
	CStatic m_Pic;
};
