// CshowDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ScreenShot.h"
#include "CshowDlg.h"
#include "afxdialogex.h"


// CshowDlg 对话框

IMPLEMENT_DYNAMIC(CshowDlg, CDialogEx)

CshowDlg::CshowDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHOW_DLG, pParent)
{

	//获取屏幕宽高 GetSystemMetrics函数
	nWidth = GetSystemMetrics(SM_CXSCREEN);						//这个宏表示求屏幕的宽带
	nHeight = GetSystemMetrics(SM_CYSCREEN);					//表示高度

	/*	
				DC:表示设备上下文
				GDI：表示图形设备接口
		因为为了统一显示图像，显卡不同，接口不同
		window全部封装了，我们使用win提供的接口
		就能在不同的显卡上显示相同的图片
	*/

	//获取桌面DC 
	CDC* pDC = GetDesktopWindow()->GetDC();
	//创建位图
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, nWidth, nHeight);
	//创建内存DC
	m_memDC.CreateCompatibleDC(pDC);							//根据桌面创建一张图
	m_memDC.SelectObject(&bmp);									//与得到的图相关联
	m_memDC.BitBlt(0, 0, nWidth, nHeight, pDC, 0, 0, SRCCOPY);	//将图片全部复制到内存DC中
	//释放桌面DC
	pDC->DeleteDC();
	bmp.DeleteObject();


}

CshowDlg::~CshowDlg()
{
}

void CshowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CshowDlg, CDialogEx)
	
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CshowDlg 消息处理程序


BOOL CshowDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//调整窗口大小
	MoveWindow(0, 0, nWidth, nHeight);

	//初始化橡皮筋
	//分别为虚线 向里 实线solidLine
	m_tracker.m_nStyle = CRectTracker::dottedLine | CRectTracker::resizeInside;
	//虚线上正方形的大小
	m_tracker.m_nHandleSize = 5;
	//初始化橡皮筋为00
	m_tracker.m_rect.SetRect(0, 0, 0, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}




void CshowDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, nWidth, nHeight, &m_memDC, 0, 0, SRCCOPY);
	m_tracker.Draw(&dc);

}


void CshowDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 鼠标左键点击消息
	// 先判断是否点中橡皮筋
	if (m_tracker.HitTest(point) < 0)
	{
		//没有点中橡皮筋
		//重新画一个橡皮筋
		m_tracker.TrackRubberBand(this, point, TRUE);
		m_tracker.m_rect.NormalizeRect();//正常化，防止终点坐标小于起点发生错误
	}
	else
	{
		//如果点中了,允许可以拉大
		//同上的TRUE是允许反转的意思
		m_tracker.Track(this, point, TRUE);
	}

	Invalidate(FALSE);//刷新

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CshowDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// 获取选框大小
	int tk_Width = m_tracker.m_rect.Width();
	int tk_Hight = m_tracker.m_rect.Height();

	//创建位图
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&m_memDC, tk_Width, tk_Hight);

	//创建一个临时内存DC
	CDC memDC;
	memDC.CreateCompatibleDC(NULL);
	memDC.SelectObject(&bmp);
	memDC.BitBlt(0, 0, tk_Width, tk_Hight, &m_memDC, m_tracker.m_rect.left, m_tracker.m_rect.top, SRCCOPY);

	//打开剪切板
	OpenClipboard();
	//清空剪切板
	EmptyClipboard();
	//设置剪切板
	SetClipboardData(CF_BITMAP, bmp);
	//关闭剪切板
	CloseClipboard();

	//保存
	//获取时间
	CTime m_time = CTime::GetCurrentTime();
	srand(time(NULL));
	//设置随机数
	CString strPicName;
	strPicName.Format(L"截图%s %d.png", m_time.Format(L"%Y%m%d%H%M%S"),rand() % 900 + 100);

	//保存图片
	CImage img;
	img.Attach(bmp);
	img.Save(strPicName);
	img.Detach();

	//释放内存
	memDC.DeleteDC();
	bmp.DeleteObject();
	m_memDC.DeleteDC();

	//关闭截图窗口
	EndDialog(IDCANCEL);

	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CshowDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	EndDialog(IDCANCEL);

	CDialogEx::OnRButtonDown(nFlags, point);
}
