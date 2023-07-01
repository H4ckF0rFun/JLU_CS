#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "user.h"

// CUserMgrDlg �Ի���

class CUserMgrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUserMgrDlg)

public:
	CUserMgrDlg(ListContext*pUserData,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUserMgrDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	ListContext*	m_pUserData;

	HICON	m_hIconPass;
	HICON	m_hIconAdd;
	HICON	m_hIconDel;

	CButton m_ChangePass;
	CButton m_DelUser;
	CButton m_AddUsers;

	virtual BOOL OnInitDialog();
	
	CListCtrl m_UserList;

	afx_msg void OnBnClickedOk4();
	CString m_UserName;
	CString m_Password;
	CString m_Password2;
	afx_msg void OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk3();
	afx_msg void OnBnClickedOk2();
};
