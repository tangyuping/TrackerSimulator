
//////////////////////// TestDlg.cpp : implementation file
#include "stdafx.h"
#include <afxsock.h>
#include "Test.h"
#include "TestDlg.h"
#include "ws2def.h"

#include <iostream>  
#include <winsock.h>  
#include <stdio.h>  
  
#pragma comment(lib, "wsock32")  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTESTDlg �Ի���
CTESTDlg::CTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTESTDlg::IDD, pParent)
{
	 //{{AFX_DATA_INIT(CTESTDlg)
	  m_Info = _T("");
	  m_Output = _T("");
	  m_Input = _T("");
	  m_CNCInput = _T("");
	  m_Connect = _T("");
	  m_IPAddress = _T("");
	  m_Port = 0;
	  m_Status = -1;
	  //}}AFX_DATA_INIT
	  // Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	 //{{AFX_DATA_MAP(CTESTDlg)
	DDX_Text(pDX, IDC_OUTPUTEDIT, m_Output);
	DDX_Text(pDX, IDC_INPUTEDIT, m_Input);
	DDX_Text(pDX, IDC_CNCINPUT, m_CNCInput);
	DDX_Text(pDX, IDC_CONNECTEDIT, m_Connect);
	DDX_Text(pDX, IDC_IPADDRESS, m_IPAddress);
	DDV_MaxChars(pDX, m_IPAddress, 15);
	DDX_Text(pDX, IDC_PORT, m_Port);
	DDX_Radio(pDX, IDC_SERVERRADIO, m_Status);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTESTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECTBUTTON, OnConnect)
	ON_BN_CLICKED(IDC_DISCONNECTBUTTON, OnDisconnect)
	ON_BN_CLICKED(IDC_SENDBUTTON, OnSend)
	ON_BN_CLICKED(IDC_SERVERRADIO, OnServerradio)
	ON_BN_CLICKED(IDC_CLIENTRADIO, OnClientradio)
	ON_BN_CLICKED(IDC_SENDCLEARBUTTON, OnSendclear)
	ON_BN_CLICKED(IDC_RECEIVECLEARBUTTON, OnReceiveclear)
	//}}AFX_MSG_MAP
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_BUTTON6, &CTESTDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CTESTDlg ��Ϣ�������

BOOL CTESTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_Status=-1;
	m_ServerSocket=NULL;
	m_ClientSocket=NULL;
	m_arIn=NULL;
	m_arOut=NULL;
	m_file=NULL;
	m_Connect="";
	m_IPAddress="47.107.25.39";
	m_Port=9998;
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT)->EnableWindow(FALSE);
	UpdateData(FALSE);
	return TRUE; // return TRUE unless you set the focus to a control
}

void CTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTESTDlg::OnPaint()
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
HCURSOR CTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTESTDlg::OnConnect() 
{
	CString msg;
	UpdateData(TRUE); 
	if (m_Status==0 ) //server
	{
		if (m_ServerSocket)
		{
			MessageBox("WindowsSocket initial failed!","Connect",MB_ICONSTOP);
			m_Connect="Please disconnect!";
			UpdateData(FALSE);
		}
		else
		{
			m_Connect="Waiting for Client...";
			UpdateData(FALSE);
			if(!AfxSocketInit())
			{
				MessageBox("WindowsSocket initial failed!","Send",MB_ICONSTOP);
				return;
			}
			m_ServerSocket = new CNewSocket;
			m_ServerSocket->m_Status = m_Status;
			m_ServerSocket->GetDlg(this);
			if (!m_ServerSocket->Create(m_Port))
			{
				MessageBox("WindowsSocket Create failed!","Send",MB_ICONSTOP);
			}
			else
				m_ServerSocket->Listen();
		}
	}
	else
	{
		if (m_Status==1)//Client
		{
			if(m_ClientSocket)
			{
				m_Connect="Please disconnect!";
				UpdateData(FALSE);
			}
			else
			{
				m_Connect="Connect to the Server...";
				UpdateData(FALSE);
				if (!AfxSocketInit())
				{
					MessageBox("WindowsSocket initial failed!","Receive",MB_ICONSTOP);
					return;
				}
				m_ClientSocket = new CNewSocket;
				m_ClientSocket->GetDlg(this);
				m_ClientSocket->m_Status=m_Status;
				if(!m_ClientSocket->Create())
				{
					MessageBox("WindowsSocket create failed!","Receive",MB_ICONSTOP);
					return;
				}
				else
				{
					if (!m_ClientSocket->Connect(m_IPAddress,m_Port))
					{
						CString str = m_Connect;
						SocketReset();
						m_Connect=str;
						m_Connect+="Error!";
						UpdateData(FALSE);
					}
					else
					{
						m_Connect+="OK!";
						m_file = new CSocketFile(m_ClientSocket);
						m_arIn = new CArchive(m_file,CArchive::load);
						m_arOut = new CArchive(m_file,CArchive::store);
						
					}
					UpdateData(FALSE);
				}
			}
		}
	}
	if (m_Status==-1)
	{
		msg="Please choose the status!";
		AfxMessageBox(msg);
	}
		
}
//�ڸ��ͻ��˷�������ʱ�����Ԥ����
void CTESTDlg::OnSend() 
{
	 if (m_arOut)
	  {
		    if (m_Status==0)
			  {
				     UpdateData(TRUE);
					 *m_arOut<<m_Output;
					 m_arOut->Flush(); 
			  }
			  else 
			    {
					 UpdateData(TRUE);
					 *m_arOut<<m_Output;
					 m_arOut->Flush(); 
			  }
	  }
	  else AfxMessageBox("Not connected!");
}
//�����������󣬲������뷢����������Ŀͻ��˽���ͨ��Socket
//Ϊ�µ�Socketע���첽�¼���ע��û��Accept�¼�
void CTESTDlg::OnAccept()
{
	m_Connect+="OK!";
	UpdateData(FALSE);
	m_ClientSocket=new CNewSocket;
	m_ClientSocket->GetDlg(this);
	m_ServerSocket->Accept(*m_ClientSocket);
	m_ClientSocket->m_Status=m_ServerSocket->m_Status;
	m_file=new CSocketFile(m_ClientSocket); 
	m_arIn=new CArchive(m_file, CArchive::load); 
	m_arOut=new CArchive(m_file, CArchive::store); 
	
}
//�������绺�����е����ݰ�
void CTESTDlg::OnReceive()
{
	//*m_arIn>>m_Input; 
	//UpdateData(FALSE); 

	BYTE cbDataBuffer[1024],i=0;
	memset(cbDataBuffer,0,sizeof(cbDataBuffer));
	int ret = m_ClientSocket->Receive(cbDataBuffer,1024);
	
	if (ret <= 0)
	{
		MessageBox("�������ݲ������㣡");
	}
	else
	{	
		CString str;//ip
		CString strportValue;
		unsigned int port;//�˿�
		m_ClientSocket->GetPeerName(str,port);//��ȡIP
		strportValue.Format("%u",port);//��������ת��
		m_Input +=  CString(str)+":"+CString(strportValue)+":"+CString(cbDataBuffer)+"\r\n";
		UpdateData(FALSE);
		//MessageBox("�����������ݣ�");
		
	}
}

void CTESTDlg::OnDisconnect() 
{
	 if (m_arOut!=NULL)
	  {
			SocketReset();
			m_Connect="Disconnected!";
			UpdateData(FALSE);
	  }
}
//������Ӧ�ͻ��˵�ͨ�ţ��ͷ���Ӧ��Դ
void CTESTDlg::OnClose()
{
	if (m_ClientSocket->m_Status==0) 
		m_Connect="Client ";
	else 
		m_Connect="Server ";
	m_Connect+="has disconnected!"; 
	UpdateData(FALSE);
}

void CTESTDlg::SocketReset()
{
	if (m_arIn!=NULL) 
	{ 
		delete m_arIn;
		m_arIn=NULL;
	}
	if (m_arOut!=NULL) 
	{
		 delete m_arOut;
		 m_arOut=NULL;
	} 
	if (m_file!=NULL) 
	{
		delete m_file;
		m_file=NULL;
	}
	if (m_ClientSocket!=NULL) 
	{
		delete m_ClientSocket;
		m_ClientSocket=NULL;
	}
	if (m_ServerSocket!=NULL)
	{ 
		delete m_ServerSocket;
		m_ServerSocket=NULL;
	}
	m_Connect="";
	UpdateData(FALSE);
}

void CTESTDlg::OnServerradio() 
{
	UpdateData(TRUE);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_PORT)->EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CTESTDlg::OnClientradio() 
{ 
	UpdateData(TRUE);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_PORT)->EnableWindow(TRUE);
	UpdateData(FALSE);
}

void CTESTDlg::OnSendclear() 
{
	m_Output="";
	UpdateData(FALSE);
}

void CTESTDlg::OnReceiveclear() 
{
	m_Input="";
	UpdateData(FALSE);
}
void CTESTDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

