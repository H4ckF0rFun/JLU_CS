#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "stock.h"
#include "resource.h"
// CStoreMgrDlg 对话框

class CStoreMgrDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStoreMgrDlg)

public:
	CStoreMgrDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStoreMgrDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	ListContext*	m_pStockList;

	void UpdateStockListView();
	void InsertGoods(Goods&goods);
	bool Filter(Goods&goods);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnCbnSelchangeCombo1();
	CListCtrl m_List;
	CComboBox m_DropList;
	CString m_Filter;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnOperation32776();
	afx_msg void OnOperation32777();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
