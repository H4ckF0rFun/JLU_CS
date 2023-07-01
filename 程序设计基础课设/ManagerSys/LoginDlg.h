#pragma once
#include "afxwin.h"
#include "user.h"
#include "resource.h"
// CLoginDlg �Ի���


class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLoginDlg();

// �Ի�������
	enum { IDD = IDD_LOGIN_DLG };

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	ListContext*	m_pUserData;

	CString m_User;
	CString m_Password;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
