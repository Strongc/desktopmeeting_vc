// SetDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ETCMeetingClient.h"
#include "SetDialog.h"


// CSetDialog �Ի���

IMPLEMENT_DYNAMIC(CSetDialog, CDialog)

CSetDialog::CSetDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDialog::IDD, pParent)
	, m_nMeetingID(0)
	, m_nPort(8001)
{

}

CSetDialog::~CSetDialog()
{
}

void CSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_CMB_MEETINGID, m_nMeetingID);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
}


BEGIN_MESSAGE_MAP(CSetDialog, CDialog)
END_MESSAGE_MAP()


// CSetDialog ��Ϣ�������
