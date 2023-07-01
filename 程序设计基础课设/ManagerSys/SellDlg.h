#pragma once

#include"SaleRecord.h"
#include"stock.h"
#include "resource.h"
#include "afxwin.h"
// CSellDlg 对话框

class CSellDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSellDlg)

public:
	CSellDlg(Goods&goods,CWnd* pParent = NULL);   // 标准构造函数

	Goods&	m_goods;


	virtual ~CSellDlg();

// 对话框数据
	enum { IDD = IDD_SELL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CString m_SellCount;
	virtual afx_msg void OnEnChangeEdit4();
	virtual void OnOK();
	CString m_Comment;
	CButton m_Discount;
	CString m_Rate;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnBnClickedCancel();
};
