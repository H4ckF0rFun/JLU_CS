#pragma once
#include "afxwin.h"


// CSortDlg 对话框

class CSortDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSortDlg)

public:
	CSortDlg(DWORD Type,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSortDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
