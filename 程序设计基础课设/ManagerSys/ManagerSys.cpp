
// ManagerSys.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "LoginDlg.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CManagerSysApp

BEGIN_MESSAGE_MAP(CManagerSysApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CManagerSysApp 构造

CManagerSysApp::CManagerSysApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CManagerSysApp 对象

CManagerSysApp theApp;


// CManagerSysApp 初始化

BOOL CManagerSysApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	//
	//登录成功
	
	CLoginDlg* pLoginDlg = new CLoginDlg;
	int Response = pLoginDlg->DoModal();

	if (Response != IDOK)
		return FALSE;

	CRect WndRect;
	WndRect.left = 440;
	WndRect.top = 200;
	WndRect.right = 440+ 1100;
	WndRect.bottom = 200 +  730;
	CMainFrame*pMainFrame = new CMainFrame(pLoginDlg);


	m_pMainWnd = pMainFrame;
	((CMainFrame*)m_pMainWnd)->Create(NULL, L"果蔬管理系统", WS_DLGFRAME | WS_CAPTION |WS_SYSMENU |WS_MINIMIZEBOX|WS_OVERLAPPED,WndRect);
	m_pMainWnd->ShowWindow(SW_SHOW);
	return TRUE;
	
}

