////////////////////////////////////////////////// NewSocket.h : header file
#if !defined(AFX_NEWSOCKET_H__8CE2ED73_1D56_11D3_9928_00A0C98F3E85__INCLUDED_)
#define AFX_NEWSOCKET_H__8CE2ED73_1D56_11D3_9928_00A0C98F3E85__INCLUDED_
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
class CTESTDlg;
#include <afxsock.h>

class CNewSocket : public CSocket
{
	// Attributes
public:

	// Operations
public:
	CNewSocket();
	virtual ~CNewSocket();

	// Overrides
public:
	int m_Status;
	void GetDlg(CTESTDlg *dlg);
	CTESTDlg *m_dlg;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewSocket)
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL
	// Generated message map functions
	//{{AFX_MSG(CNewSocket)
	// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	// Implementation
protected:
};
#endif 