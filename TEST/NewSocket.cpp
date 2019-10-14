//////////////////////////////////////////////////////// NewSocket.cpp : implementation file
#include "stdafx.h"
#include "Test.h"
#include "NewSocket.h"
#include "TestDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CNewSocket::CNewSocket()
{}

CNewSocket::~CNewSocket()
{}

#if 0
BEGIN_MESSAGE_MAP(CNewSocket, CSocket)
	//{{AFX_MSG_MAP(CNewSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif // 0

void CNewSocket::OnAccept(int nErrorCode) 
{
	 if (m_dlg->m_ClientSocket==NULL) m_dlg->OnAccept();
	  CSocket::OnAccept(nErrorCode);
}

void CNewSocket::OnReceive(int nErrorCode) 
{
	 m_dlg->OnReceive();
	  CSocket::OnReceive(nErrorCode);
}

void CNewSocket::GetDlg(CTESTDlg *dlg)
{
	 m_dlg=dlg;
}

void CNewSocket::OnClose(int nErrorCode) 
{
	 m_dlg->OnClose();
	  CSocket::OnClose(nErrorCode);
}