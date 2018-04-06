
// saoleiDlg.h : 头文件
//

#pragma once

typedef struct
{
	BOOL islei;
	BOOL isLTurned;
	BOOL isRTurned;
	int isTurning;
	int DisplayNum;
	CRect rect;
}point;
// CsaoleiDlg 对话框
class CsaoleiDlg : public CDialogEx
{
// 构造
public:
	CsaoleiDlg(CWnd* pParent = NULL);	// 标准构造函数
	void initPoint();
	void displaynum();
	CPoint ixtopoint(int x,int y);
	void initGame();

// 对话框数据
	enum { IDD = IDD_SAOLEI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	int m_width,m_height;
// 实现
protected:
	HICON m_hIcon;
	point *m_pt;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
