///////////////////////////////////////////////////////////////// TestDlg.h : header file
#if !defined(AFX_TESTDLG_H__EDDDE196_1BF1_11D3_BE77_0000B454AEE4__INCLUDED_)
#define AFX_TESTDLG_H__EDDDE196_1BF1_11D3_BE77_0000B454AEE4__INCLUDED_
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include "NewSocket.h"
#include "ws2def.h"
// CTESTDlg ¶Ô»°¿ò
class CTESTDlg : public CDialog
{
	// Construction
public:
	 void SocketReset();
	 void OnClose();
	 void OnReceive();
	 void OnAccept();

	 CSocketFile *m_file;
	 CArchive *m_arOut;
	 CArchive *m_arIn;
	 CNewSocket* m_ServerSocket;
	 CNewSocket* m_ClientSocket;
	 CTESTDlg(CWnd* pParent = NULL); // standard constructor
	 // Dialog Data
	 //{{AFX_DATA(CTESTDlg)
	 enum { IDD = IDD_TEST_DIALOG };
	 CString m_Info;
	 CString m_Output;
	 CString m_Input;
	 CString m_CNCInput;
	 CString m_Connect;
	 CString m_IPAddress;
	 UINT m_Port;
	 int m_Status;
	 //}}AFX_DATA
	 // ClassWizard generated virtual function overrides
	 //{{AFX_VIRTUAL(CTESTDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	//}}AFX_VIRTUAL
	// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CTESTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnSend();
	afx_msg void OnServerradio();
	afx_msg void OnClientradio();
	afx_msg void OnSendclear();
	afx_msg void OnReceiveclear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton6();
};
#endif 
