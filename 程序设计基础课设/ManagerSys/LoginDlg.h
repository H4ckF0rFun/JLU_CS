#pragma once
#include "afxwin.h"
#include "user.h"
#include "resource.h"
// CLoginDlg 对话框


class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGIN_DLG };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	ListContext*	m_pUserData;

	CString m_User;
	CString m_Password;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
