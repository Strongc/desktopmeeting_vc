
// ETCMeetingServerDlg.h : ͷ�ļ�
//

#pragma once


// CETCMeetingServerDlg �Ի���
class CETCMeetingServerDlg : public CDialog
{
// ����
public:
	CETCMeetingServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ETCMEETINGSERVER_DIALOG };

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

public:
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnStop();
	int m_nInteval;
	int m_nMeetingID;
	UINT m_nPort;
	afx_msg void OnClose();
};

