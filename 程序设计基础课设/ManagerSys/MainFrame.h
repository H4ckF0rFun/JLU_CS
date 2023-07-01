#pragma once
#include "afxwin.h"
#include "StoreMgrDlg.h"
#include "SaleRecordDlg.h"
#include "PurchaseDlg.h"

#define ICON_COUNT	6

class CLoginDlg;
class CMainFrame :
	public CFrameWnd
{
public:

	CLoginDlg*	m_pLoginDlg;


	CStatusBar m_StatuBar;


	CStoreMgrDlg m_StoreDlg;
	CSaleRecordDlg m_SaleDlg;
	CPurchaseDlg m_PurchaseDlg;

	CWnd*		m_pForegroundWnd;
	CToolBar	m_ToolBar;

	HICON		m_Icons[ICON_COUNT];
	CImageList	m_ImageList;

	CRect		m_SubWndRect;
	CMainFrame(CLoginDlg*pLoginDlg);
	~CMainFrame();
	DECLARE_MESSAGE_MAP()


	void OnUserMgr();
	void OnSaleMgr();
	void OnPurchaseMgr();
	void OnStoreMgr();
	void OnAbout();
	void OnTendency();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnOperation32777();
};

