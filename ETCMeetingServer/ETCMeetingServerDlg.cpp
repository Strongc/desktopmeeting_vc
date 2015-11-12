
// ETCMeetingServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ETCMeetingServer.h"
#include "ETCMeetingServerDlg.h"
#include "ScreenCapturer.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CETCMeetingServerDlg �Ի���c

BOOL gShouldExit = FALSE;
BOOL gHasExited = FALSE;
int gInterval;
int gMeetingID;
int gPort;

CETCMeetingServerDlg::CETCMeetingServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CETCMeetingServerDlg::IDD, pParent)
	,m_nInteval(300)
	, m_nMeetingID(0)
	, m_nPort(8001)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CETCMeetingServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INTERVAL, m_nInteval);
	DDX_CBIndex(pDX, IDC_CMB_MEETINGID, m_nMeetingID);
	DDX_Text(pDX, IDC_EDIT_PORT, m_nPort);
}

BEGIN_MESSAGE_MAP(CETCMeetingServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_START, &CETCMeetingServerDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, &CETCMeetingServerDlg::OnBnClickedBtnStop)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CETCMeetingServerDlg ��Ϣ�������

BOOL CETCMeetingServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CETCMeetingServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CETCMeetingServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

UINT SendPictureProc(LPVOID pParam);

void CETCMeetingServerDlg::OnBnClickedBtnStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	gShouldExit = false;
	gHasExited = false;

	UpdateData(TRUE);
	gInterval = m_nInteval;
	gMeetingID = m_nMeetingID;
	gPort = m_nPort;
	AfxBeginThread(SendPictureProc,NULL);

	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_CMB_MEETINGID)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_INTERVAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
}

void CETCMeetingServerDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	gShouldExit = true;
	while (!gHasExited)
	{
		Sleep(500);
	}
	

	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_CMB_MEETINGID)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_INTERVAL)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);
}

UINT SendPictureProc(LPVOID pParam)
{
	// ��������Socket
	SOCKET sendSocket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, 0, 0, 0);

	// �����鲥��ַ
	ip_mreq mcast;  
    mcast.imr_interface.S_un.S_addr = INADDR_ANY;  
    mcast.imr_multiaddr.S_un.S_addr = inet_addr(MULTICASTADDRESS[gMeetingID]);  
    int n =setsockopt(sendSocket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&mcast,sizeof(mcast));
	// �����鲥TTL
	int optval = 8;  
    n = setsockopt(sendSocket,IPPROTO_IP,IP_MULTICAST_TTL,(char*)&optval,sizeof(int));  
	// �����Ƿ��͸��Լ�
    int loop = 1;  
    n = setsockopt(sendSocket,IPPROTO_IP,IP_MULTICAST_LOOP,(char*)&loop,sizeof(int));  

	// �����鲥��Ϣ���͵�Ŀ�ĵ�
	sockaddr_in remote;  
    remote.sin_addr.S_un.S_addr = inet_addr(MULTICASTADDRESS[gMeetingID]);  
    remote.sin_family = AF_INET;  
    remote.sin_port = htons(gPort);  


	CScreenCapturer cap;
	LPBYTE pBits = NULL;
	ULONG size = 0;
	int length = -1;	
	
	while(!gShouldExit)
	{
		// ץȡ��ĻͼƬ
		size = cap.GetPicture(&pBits);

		// ������ʼ����
		//sprintf(buf, "%s%d:%d", START_CODE, cap.GetScreenWidth(), cap.GetScreenHeight());
		//cap.GetScreenWidth();
		sendto(sendSocket, START_CODE, START_CODE_LENGTH, 0, (SOCKADDR*)&remote, sizeof(remote));

		// ���͸���Ļ���ݰ�
		int nums = size / MAX_SEND_SIZE + (size % MAX_SEND_SIZE == 0 ? 0 : 1);
		for(int i=0;i<nums-1;i++)
		{
			length = sendto(sendSocket, (char*)pBits, MAX_SEND_SIZE, 0, 
				(SOCKADDR*)&remote, sizeof(remote));
			pBits += length;
		}
		int remains = size % MAX_SEND_SIZE;
		if (remains != 0)
		{
			length = sendto(sendSocket, (char*)pBits, remains, 0, 
				(SOCKADDR*)&remote, sizeof(remote));
		}

		// ���ͽ�������
		sendto(sendSocket, END_CODE, END_CODE_LENGTH, 0, (SOCKADDR*)&remote, sizeof(remote));

		Sleep(gInterval);
	}
	gHasExited = true;
	
	return 0;
}

void CETCMeetingServerDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	while (gShouldExit && !gHasExited)
	{
		Sleep(500);
	}
	CDialog::OnClose();
}
