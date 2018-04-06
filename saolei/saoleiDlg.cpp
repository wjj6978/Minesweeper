
// saoleiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "saolei.h"
#include "saoleiDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsaoleiDlg 对话框




CsaoleiDlg::CsaoleiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CsaoleiDlg::IDD, pParent)
{
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pt=new point[256];
	
}

void CsaoleiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CsaoleiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()


// CsaoleiDlg 消息处理程序

BOOL CsaoleiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	
	srand((unsigned)time(NULL));
	initGame();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CsaoleiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsaoleiDlg::OnPaint()
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
	
	initPoint();
	displaynum();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CsaoleiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CsaoleiDlg::initPoint()
{
	CClientDC dc(this);
	
	CBrush brush(RGB(0,255,0));
	CBrush *pOldBrush;
	pOldBrush=dc.SelectObject(&brush);
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CPen *pOldPen;
	pOldPen=dc.SelectObject(&pen);
	for(int i=0;i<16;++i)
	{
		for(int j=0;j<16;++j)
		{
			dc.Rectangle(&m_pt[i*16+j].rect);
		}
	}
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);

}

void CsaoleiDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int x=0,y=0;
	x=(point.x-10)/m_width;
	y=(point.y-10)/m_height;
	if(m_pt[y*16+x].isLTurned)
		return;
	if(m_pt[y*16+x].isRTurned)
	{
		m_pt[y*16+x].isRTurned=FALSE;
	}
	m_pt[y*16+x].isTurning=1;
	m_pt[y*16+x].isLTurned=TRUE;
	if(m_pt[y*16+x].islei)
	{
		MessageBox("Game Over ! ! !");
		initGame();
		Invalidate();
		return;
	}
	if(m_pt[y*16+x].DisplayNum==0)
	{
		for(int m=-1;m<2;++m)
		{
			for(int n=-1;n<2;++n)
			{
				if((y+m>=0)&&(y+m<16)&&(x+n>=0)&&(x+n<16)&&!(m==0&&n==0))
				{
					CPoint pt;
					pt=ixtopoint(x+n,y+m);
					OnLButtonDown(nFlags,pt);
				}
			}
		}
	}
	int l=0,r=0;
	for(int i=0;i<256;i++)
	{
		if(m_pt[i].isLTurned)
			++l;
		if(m_pt[i].isRTurned)
			++r;
		if(l==216&&r==40)
		{
			MessageBox("You Win ! ! !");
			initGame();
			Invalidate();
			return;
		}
		
	}
	this->Invalidate();

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CsaoleiDlg::displaynum()
{
	for(int i=0;i<16;++i)
	{
		for(int j=0;j<16;++j)
		{
			
			if(m_pt[i*16+j].isTurning==1&&!m_pt[i*16+j].islei)
			{
				int val=m_pt[i*16+j].DisplayNum;
				CString str;
				if(val<10&&val>0)
					str.Format("%d ",val);
				else if(val==0)
					str.Format("  ",val);
				else
					str.Format("%d",val);
				CClientDC dc(this);
				CFont font;
				font.CreatePointFont((m_height-12)*10,"仿宋",NULL);
				CBrush brush(RGB(0,255,255));
				CBrush *pOldBrush=dc.SelectObject(&brush);
				CFont *pOldFont=dc.SelectObject(&font);
				dc.Rectangle(m_pt[i*16+j].rect);
				dc.DrawText(str,&m_pt[i*16+j].rect,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				dc.SelectObject(pOldFont);
				dc.SelectObject(pOldBrush);
			}
			if(m_pt[i*16+j].isTurning==-1)
			{
				CClientDC dc(this);
				CBrush brush(RGB(0,0,255));
				CBrush *pOldBrush=dc.SelectObject(&brush);
				dc.Rectangle(m_pt[i*16+j].rect);
				dc.SelectObject(pOldBrush);
			}
		}
	}
}

CPoint CsaoleiDlg::ixtopoint(int x,int y)
{
	CPoint pt;
	pt.x=10+m_width/2+x*m_width;
	pt.y=10+m_height/2+y*m_height;
	return pt;
}

void CsaoleiDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	int x=0,y=0;
	x=(point.x-10)/m_width;
	y=(point.y-10)/m_height;
	if(m_pt[y*16+x].isLTurned)
		return;
	if(m_pt[y*16+x].isRTurned)
	{
		m_pt[y*16+x].isRTurned=FALSE;
		m_pt[y*16+x].isTurning=0;
	}
	else
	{
		m_pt[y*16+x].isTurning=-1;
		m_pt[y*16+x].isRTurned=TRUE;
	}
	int l=0,r=0;
	for(int i=0;i<81;i++)
	{
		if(m_pt[i].isLTurned)
			++l;
		if(m_pt[i].isRTurned)
			++r;
		if(l==216&&r==40)
		{
			MessageBox("You Win ! ! !");
			initGame();
			Invalidate();
			return;
		}
		
	}
	
	this->Invalidate();

	CDialogEx::OnRButtonDown(nFlags, point);
}

void CsaoleiDlg::initGame()
{
	CMenu menu;
	menu.LoadMenuA(IDR_MENU1);
	SetMenu(&menu);
	menu.Detach();
	CRect rect;
	GetWindowRect(&rect);

	rect.bottom=rect.top+(rect.right-rect.left);
	this->SetWindowPos(NULL,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top,SWP_DRAWFRAME);
	
	
	this->GetClientRect(&rect);
	m_width=(rect.right-rect.left-20)/16;
	m_height=(rect.bottom-rect.top-20)/16;
	for(int i=0;i<16;++i)
	{
		for(int j=0;j<16;++j)
		{
			m_pt[i*16+j].rect.left=rect.left+m_width*j+10;
			m_pt[i*16+j].rect.right=rect.left+m_width*(j+1)+10;
			m_pt[i*16+j].rect.top=rect.top+m_height*i+10;
			m_pt[i*16+j].rect.bottom=rect.top+m_height*(i+1)+10;
			m_pt[i*16+j].islei=FALSE;
			m_pt[i*16+j].isLTurned=FALSE;
			m_pt[i*16+j].isRTurned=FALSE;
			m_pt[i*16+j].isTurning=0;
			m_pt[i*16+j].DisplayNum=0;
		}
	}
	LONG oldtemp[40]={0};
	LONG Temp=0;
	int ix=0;
	BOOL flag=FALSE;
	srand((unsigned)time(NULL));
	for(int i=0;i<40;++i)
	{
		Temp=rand();
		Temp=Temp%256;
		for(int j=0;j<=i;j++)
		{
			if(Temp==oldtemp[j])
			{
				i--;
				flag=TRUE;
				break;
			}
		}
		if(flag)
		{
			
			flag=FALSE;
			continue;
		}
		oldtemp[ix++]=Temp;
		m_pt[Temp].islei=TRUE;
	}
	for(int i=0;i<16;++i)
	{
		for(int j=0;j<16;++j)
		{
			for(int m=-1;m<2;++m)
			{
				for(int n=-1;n<2;++n)
				{
					if((i+m>=0)&&(i+m<16)&&(j+n>=0)&&(j+n<16)&&!(m==0&&n==0))
					{
						if(m_pt[(i+m)*16+j+n].islei)
							m_pt[i*16+j].DisplayNum++;
					}
				}
			}
		}
	}
}