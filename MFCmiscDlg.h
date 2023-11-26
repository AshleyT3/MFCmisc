
// MFCmiscDlg.h : header file
//

#pragma once

#include "ProgressPie/ProgressPieStaticCtrl.h"
#include "ProgressPie/ProgressPieCtrl.h"

// CMFCmiscDlg dialog
class CMFCmiscDlg : public CDialogEx
{
// Construction
public:
	CMFCmiscDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCMISC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CProgressPieCtrl m_btnProgressPie;
	CProgressPieStaticCtrl m_staticProgressPie;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedButtonProgerssPie();
};
