
// saoleiDlg.h : ͷ�ļ�
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
// CsaoleiDlg �Ի���
class CsaoleiDlg : public CDialogEx
{
// ����
public:
	CsaoleiDlg(CWnd* pParent = NULL);	// ��׼���캯��
	void initPoint();
	void displaynum();
	CPoint ixtopoint(int x,int y);
	void initGame();

// �Ի�������
	enum { IDD = IDD_SAOLEI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	int m_width,m_height;
// ʵ��
protected:
	HICON m_hIcon;
	point *m_pt;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
