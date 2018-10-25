// Îå×ÓÆåDlg.h : header file
//
#if !defined(AFX_DLG_H__995F2CE5_290C_48E7_B134_BA1C3896BB5E__INCLUDED_)
#define AFX_DLG_H__995F2CE5_290C_48E7_B134_BA1C3896BB5E__INCLUDED_
#define black 1
#define white 0
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
	void Computer();
	void dostep();

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CBitmap * m_board, * m_white, * m_black, * m_temp ,*m_red;
	int m_byColour;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void Onrestart();
	afx_msg void Onstart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__995F2CE5_290C_48E7_B134_BA1C3896BB5E__INCLUDED_)
