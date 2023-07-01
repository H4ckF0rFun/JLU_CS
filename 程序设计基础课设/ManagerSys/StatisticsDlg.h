#pragma once
#include "afxcmn.h"
#include "SaleRecord.h"

// CStatisticsDlg 对话框

class CStatisticsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisticsDlg)

public:
	CStatisticsDlg(SaleRecords*pRecord,CString Today,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatisticsDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_Today;
	SaleRecords*	m_pRecord;
	CListCtrl m_List;
};
