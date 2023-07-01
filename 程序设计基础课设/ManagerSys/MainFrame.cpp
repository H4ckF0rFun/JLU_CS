#include "stdafx.h"
#include "MainFrame.h"
#include "resource.h"
#include "UserMgrDlg.h"
#include "SaleRecordDlg.h"
#include "PurchaseDlg.h"
#include "LoginDlg.h"
#include "AboutDlg.h"
#include "TendencyDlg.h"

CMainFrame::CMainFrame(CLoginDlg*pLoginDlg)
{
	m_pLoginDlg = pLoginDlg;
}


CMainFrame::~CMainFrame()
{
	delete m_pLoginDlg;				//
	m_pLoginDlg = NULL;				//
}


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_USER_MGR,OnUserMgr)
	ON_COMMAND(ID_SALE_MGR,OnSaleMgr)
	ON_COMMAND(ID_PURCHASE_MGR, OnPurchaseMgr)
	ON_COMMAND(ID_STORE_MGR,OnStoreMgr)
	ON_WM_CLOSE()
	ON_COMMAND(ID_OPERATION_32777, &CMainFrame::OnOperation32777)
	ON_COMMAND(ID_ABOUT_SYS,OnAbout)
	ON_COMMAND(ID_TENDENCY, OnTendency)
END_MESSAGE_MAP()


static UINT indicators[] =
{
	IDS_CURRENT_USER,
	IDS_CURRENT_VERSION,
	IDS_CURRENT_TIME
};
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_StatuBar.Create(this);
	m_StatuBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	m_StatuBar.SetPaneInfo(0, IDS_CURRENT_USER, SBPS_STRETCH, 0);
	m_StatuBar.SetPaneInfo(1, IDS_CURRENT_VERSION, SBPS_NORMAL, 160);
	m_StatuBar.SetPaneInfo(2, IDS_CURRENT_TIME, SBPS_NORMAL, 160);

	CString CurrentUser;
	CurrentUser.Format(L"当前用户: %s", m_pLoginDlg->m_User);
	m_StatuBar.SetPaneText(0, CurrentUser);

	//
	CRect rect;
	//工具栏
	if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT | TBSTYLE_LIST,
		WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS) ||
		!m_ToolBar.LoadToolBar(IDR_MENU))
	{
		TRACE0("Failed to Create Dialog ToolBar\n");
		DWORD err = GetLastError();
	}

	m_ToolBar.ShowWindow(SW_SHOW);

	VERIFY(m_ToolBar.SetButtonText(0, L"用户管理"));
	VERIFY(m_ToolBar.SetButtonText(1, L"库存管理"));
	VERIFY(m_ToolBar.SetButtonText(2, L"销售记录"));
	VERIFY(m_ToolBar.SetButtonText(3, L"进货记录"));
	VERIFY(m_ToolBar.SetButtonText(4, L"销售趋势"));
	VERIFY(m_ToolBar.SetButtonText(5, L"关于系统"));

	m_ImageList.Create(32, 32, ILC_COLOR32 | ILC_MASK, 0, 0);
	//加载工具栏图标.
	m_Icons[0] = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_ICON3));
	m_Icons[1] = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_ICON5));
	m_Icons[2] = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_ICON6));
	m_Icons[3] = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_ICON7));
	m_Icons[4] = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_ICON8));
	m_Icons[5] = LoadIcon(GetModuleHandleA(NULL), MAKEINTRESOURCE(IDI_ICON4));

	m_ImageList.Add(m_Icons[0]);
	m_ImageList.Add(m_Icons[1]);
	m_ImageList.Add(m_Icons[2]);
	m_ImageList.Add(m_Icons[3]);
	m_ImageList.Add(m_Icons[4]);
	m_ImageList.Add(m_Icons[5]);
	
	//
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	
	//
	GetClientRect(m_SubWndRect);

	m_SubWndRect.top += 40;
	m_SubWndRect.bottom -= 20;

	m_StoreDlg.Create(IDD_DIALOG1, this);
	m_StoreDlg.SetParent(this);

	//
	m_SaleDlg.Create(IDD_DIALOG2, this);
	m_SaleDlg.SetParent(this);
	
	//
	m_PurchaseDlg.Create(IDD_DIALOG3, this);
	m_PurchaseDlg.SetParent(this);
	
	if (m_pLoginDlg->m_User != L"admin")
	{
		//非管理员用户无法点击这些按钮.
		m_StoreDlg.GetDlgItem(IDC_BUTTON4)->EnableWindow(0);
		m_StoreDlg.GetDlgItem(IDC_BUTTON1)->EnableWindow(0);
		m_StoreDlg.GetDlgItem(IDC_BUTTON2)->EnableWindow(0);
		m_StoreDlg.GetDlgItem(IDC_BUTTON5)->EnableWindow(0);

		m_SaleDlg.GetDlgItem(IDC_BUTTON1)->EnableWindow(0);
		m_SaleDlg.GetDlgItem(IDC_BUTTON2)->EnableWindow(0);

		m_PurchaseDlg.GetDlgItem(IDC_BUTTON1)->EnableWindow(0);
		m_PurchaseDlg.GetDlgItem(IDC_BUTTON2)->EnableWindow(0);
	}

	m_pForegroundWnd = &m_StoreDlg;
	//显示第一个界面
	m_pForegroundWnd->MoveWindow(m_SubWndRect);
	m_pForegroundWnd->ShowWindow(SW_SHOW);
	//
	SetTimer(10086, 1000,NULL);
	//设置大小图标
	HICON hIcon = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);
	return 0;
}

/*
	1.用户管理 icon
	2.库存管理 
	3.销售记录
	4.进货记录
*/
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CTime time = CTime::GetTickCount();
	CString Text = time.Format(L"[%Y-%m-%d %H:%M:%S]");
	m_StatuBar.SetPaneText(2, Text);
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnUserMgr()
{
	if (m_pLoginDlg->m_User != L"admin")
	{
		MessageBox(L"非管理员无法进行此操作", L"用户管理", MB_OK | MB_ICONASTERISK);
		return;
	}
	CUserMgrDlg dlg(m_pLoginDlg->m_pUserData);
	dlg.DoModal();
}

void CMainFrame::OnSaleMgr()
{
	m_pForegroundWnd->ShowWindow(SW_HIDE);
	m_pForegroundWnd = &m_SaleDlg;
	m_pForegroundWnd->MoveWindow(m_SubWndRect);
	m_pForegroundWnd->ShowWindow(SW_SHOW);
}

void CMainFrame::OnPurchaseMgr()
{
	m_pForegroundWnd->ShowWindow(SW_HIDE);
	m_pForegroundWnd = &m_PurchaseDlg;
	m_pForegroundWnd->MoveWindow(m_SubWndRect);
	m_pForegroundWnd->ShowWindow(SW_SHOW);
}

void CMainFrame::OnStoreMgr()
{
	m_pForegroundWnd->ShowWindow(SW_HIDE);
	m_pForegroundWnd = &m_StoreDlg;
	m_pForegroundWnd->MoveWindow(m_SubWndRect);
	m_pForegroundWnd->ShowWindow(SW_SHOW);
}

void CMainFrame::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (IDYES == MessageBox(L"确定要退出系统吗?", L"Tips", MB_YESNO | MB_ICONQUESTION))
	{
		return CFrameWnd::OnClose();
	}
}


void CMainFrame::OnOperation32777()
{
	if (m_pLoginDlg->m_User != L"admin")
	{
		return;
	}
}

void CMainFrame::OnAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CMainFrame::OnTendency()
{
	CTendencyDlg dlg(m_StoreDlg.m_pStockList,m_SaleDlg.m_pSaleRecords);
	dlg.DoModal();
}