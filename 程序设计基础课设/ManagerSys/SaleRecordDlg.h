#pragma once
#include "afxcmn.h"

#include "SaleRecord.h"
#include "afxdtctl.h"
#include "afxwin.h"
// CSaleRecordDlg 对话框

class CSaleRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaleRecordDlg)

public:
	CSaleRecordDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSaleRecordDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	ListContext* m_pSaleRecords;

	virtual BOOL OnInitDialog();
//	CListCtrl m_SaleDlg;
	CListCtrl m_SaleRecordList;

	SaleRecords*	m_pCurRecord;			//日期框选中天数对应的记录.

	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	CDateTimeCtrl m_DateCtrl;
	virtual void OnOK();
	CComboBox m_FilterList;
	CString m_Filter;

	void InsertRecord(Record&record);
	bool Filter(Record&record);
	void UpdateSaleRecordListView();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
};
