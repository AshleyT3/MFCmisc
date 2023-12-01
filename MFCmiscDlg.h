
// MFCmiscDlg.h : header file
//

#pragma once

#include "ProgressPie/ProgressPieStaticCtrl.h"
#include "ProgressPie/ProgressPieCtrl.h"
#include "WindowsMisc/InvokeGuiThreadSupport.h"

// CMFCmiscDlg dialog
class CMFCmiscDlg : public CDialogEx, public CInvokeGuiThreadSupport
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
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnClickedButtonProgerssPie();
    afx_msg void OnClickedCheckFulloutline();
    afx_msg void OnClickedButtonRunworkerthread();
    afx_msg LRESULT OnInvokeOnGuiThread(WPARAM, LPARAM);
    DECLARE_MESSAGE_MAP()
public:
    CProgressPieCtrl m_btnProgressPie;
    CProgressPieStaticCtrl m_staticProgressPie;
    CButton m_checkFullCircleOutline;
    CStatic m_staticWorkerThreadMessage;
};
