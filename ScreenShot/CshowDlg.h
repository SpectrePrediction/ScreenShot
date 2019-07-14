#pragma once


// CshowDlg 对话框

class CshowDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CshowDlg)

public:
	CshowDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CshowDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHOW_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	int nWidth;				//屏幕宽
	int nHeight;			//屏幕高
	CDC m_memDC;			//内存DC
	CRectTracker m_tracker;	//橡皮筋

public:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};
