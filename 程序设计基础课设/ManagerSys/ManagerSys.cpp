
// ManagerSys.cpp : ����Ӧ�ó��������Ϊ��
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


// CManagerSysApp ����

CManagerSysApp::CManagerSysApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CManagerSysApp ����

CManagerSysApp theApp;


// CManagerSysApp ��ʼ��

BOOL CManagerSysApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	//
	//��¼�ɹ�
	
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
	((CMainFrame*)m_pMainWnd)->Create(NULL, L"���߹���ϵͳ", WS_DLGFRAME | WS_CAPTION |WS_SYSMENU |WS_MINIMIZEBOX|WS_OVERLAPPED,WndRect);
	m_pMainWnd->ShowWindow(SW_SHOW);
	return TRUE;
	
}

