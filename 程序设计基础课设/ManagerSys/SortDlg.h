#pragma once
#include "afxwin.h"


// CSortDlg �Ի���

class CSortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSortDlg)

public:
	CSortDlg(DWORD Type,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSortDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	unsigned int m_SortType;
	DWORD m_Type;

	CComboBox m_KeyList;
	CComboBox m_SortTypeList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	virtual void OnOK();
};
