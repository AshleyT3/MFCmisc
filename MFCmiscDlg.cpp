// Copyright 2023 Ashley R. Thomas
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// MFCmiscDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCmisc.h"
#include "MFCmiscDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_MFCMISC_DEMO_INVOKE_ON_GUI_THREAD (WM_USER + 0x100)

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CMFCmiscDlg dialog

CMFCmiscDlg::CMFCmiscDlg(CWnd* pParent /*=nullptr*/)
    :
    CDialogEx(IDD_MFCMISC_DIALOG, pParent),
    CInvokeGuiThreadSupport(WM_MFCMISC_DEMO_INVOKE_ON_GUI_THREAD)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCmiscDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BUTTON_PROGERSS_PIE, m_btnProgressPie);
    DDX_Control(pDX, IDC_STATIC_PROGRESS_PIE, m_staticProgressPie);
    DDX_Control(pDX, IDC_CHECK_FULLOUTLINE, m_checkFullCircleOutline);
    DDX_Control(pDX, IDC_STATIC_WORKTHREADMESSAGE, m_staticWorkerThreadMessage);
}

BEGIN_MESSAGE_MAP(CMFCmiscDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_BUTTON_PROGERSS_PIE, &CMFCmiscDlg::OnClickedButtonProgerssPie)
    ON_BN_CLICKED(IDC_CHECK_FULLOUTLINE, &CMFCmiscDlg::OnClickedCheckFulloutline)
    ON_BN_CLICKED(IDC_BUTTON_RUNWORKERTHREAD, &CMFCmiscDlg::OnClickedButtonRunworkerthread)
    ON_MESSAGE(WM_MFCMISC_DEMO_INVOKE_ON_GUI_THREAD, OnInvokeOnGuiThread)
END_MESSAGE_MAP()


// CMFCmiscDlg message handlers

BOOL CMFCmiscDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetGuiThreadId();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);			// Set big icon
    SetIcon(m_hIcon, FALSE);		// Set small icon

    SetWindowText(L"Progress Pie Example");
    SetTimer(1, USER_TIMER_MINIMUM, NULL);

    m_checkFullCircleOutline.SetCheck(BST_CHECKED);
    m_btnProgressPie.SetFullCircleOutline(true);
    m_staticProgressPie.SetFullCircleOutline(true);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCmiscDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCmiscDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // device context for painting

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Center icon in client rectangle
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Draw the icon
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCmiscDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CMFCmiscDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent != 1)
        CDialogEx::OnTimer(nIDEvent);

    // This example shows progress of periods of time.
    // The following defines the duration of each period in seconds.
    // The default is 10 seconds.
    // For real usage, the progress does not need to be time based.
    // Time is only used as an example here.
    const intmax_t example_interval_seconds = 10;

    const auto one_second_msecs = std::chrono::milliseconds::period::den;
    const auto interval_msecs = example_interval_seconds * one_second_msecs;
    const auto time_now = std::chrono::system_clock::now().time_since_epoch();
    const auto time_now_msecs = std::chrono::duration_cast<std::chrono::milliseconds>(time_now);
    auto ratio_expired = (time_now_msecs.count() % interval_msecs) / (double)(interval_msecs);

    m_btnProgressPie.SetPercent(100.0 * ratio_expired);
    m_staticProgressPie.SetPercent(100.0 * ratio_expired);
}


void CMFCmiscDlg::OnClickedButtonProgerssPie()
{
    MessageBox(L"You clicked on the CProgressPieCtrl button!", L"CProgressPieCtrl Test");
}


void CMFCmiscDlg::OnClickedCheckFulloutline()
{
    bool bFulLOutline = m_checkFullCircleOutline.GetCheck() == BST_CHECKED;
    m_staticProgressPie.SetFullCircleOutline(bFulLOutline);
    m_btnProgressPie.SetFullCircleOutline(bFulLOutline);
}

void SomeWorker(CMFCmiscDlg* pWnd)
{
    ::Sleep(3000);
    CString csMessage;
    csMessage.Format(L"Hello from worker thread having TID=%lu!\n", ::GetCurrentThreadId());
    pWnd->InvokeOnGuiThread(pWnd->m_hWnd, [&]() {
        pWnd->AssertValid();
        pWnd->m_staticWorkerThreadMessage.SetWindowText(csMessage);
        return 0; // LRESULT
    });
    ::Sleep(3000);
    pWnd->InvokeOnGuiThread(pWnd->m_hWnd, [&]() {
        pWnd->AssertValid();
        pWnd->m_staticWorkerThreadMessage.SetWindowText(L"Worker thread finished.");
        return 0; // LRESULT
    });
}

void CMFCmiscDlg::OnClickedButtonRunworkerthread()
{
    m_staticWorkerThreadMessage.SetWindowText(L"Worker thread running, waiting for a message...");
    std::thread(SomeWorker, this).detach();
}

LRESULT CMFCmiscDlg::OnInvokeOnGuiThread(WPARAM wParam, LPARAM)
{
   return OnHandleInvokeMessage(wParam);
}