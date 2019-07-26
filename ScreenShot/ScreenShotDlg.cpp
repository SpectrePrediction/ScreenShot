
// ScreenShotDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ScreenShot.h"
#include "ScreenShotDlg.h"
#include "afxdialogex.h"
#include "CshowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CScreenShotDlg 对话框



CScreenShotDlg::CScreenShotDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SCREENSHOT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenShotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenShotDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_SHOT, &CScreenShotDlg::OnBnClickedButShot)
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
END_MESSAGE_MAP()


// CScreenShotDlg 消息处理程序

BOOL CScreenShotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_nHotKeyID = GlobalAddAtomA("m_nHotKeyID") - 0xC000;
	if (RegisterHotKey(
		GetSafeHwnd(),
		m_nHotKeyID,
		MOD_CONTROL,// | MOD_ALT,
		'X'))
	{
		GetDlgItem(IDC_STATIC2)->SetWindowText(_T("使用ctrl+x快捷截图"));//成功
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScreenShotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CScreenShotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LONG CScreenShotDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	
	GetDlgItem(IDC_STATIC2)->SetWindowText(_T("正在使用快捷截图"));
	OnBnClickedButShot();
	GetDlgItem(IDC_STATIC2)->SetWindowText(_T("使用ctrl+x快捷截图"));
	
	return 0;
}


void CScreenShotDlg::OnBnClickedButShot()
{
	//弹出窗口
	CshowDlg dlg;
	dlg.DoModal();

	//
}



