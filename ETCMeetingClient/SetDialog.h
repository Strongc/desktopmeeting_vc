#pragma once


// CSetDialog �Ի���

class CSetDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetDialog)

public:
	CSetDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nMeetingID;
	UINT m_nPort;
};
