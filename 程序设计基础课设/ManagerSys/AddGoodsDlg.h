#pragma once
#include "afxwin.h"

#include "stock.h"
#include "resource.h"
// CAddGoodsDlg 对话框

class CAddGoodsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddGoodsDlg)

public:

	Goods&	m_goods;

	CAddGoodsDlg(Goods&	goods,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddGoodsDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_SellTypeList;
	virtual BOOL OnInitDialog();
	CString m_Name;
	CString m_Type;
	double m_Purchaseprice;
	double m_Sellprice;
	afx_msg void OnBnClickedOk();
	DWORD m_ID;
};
