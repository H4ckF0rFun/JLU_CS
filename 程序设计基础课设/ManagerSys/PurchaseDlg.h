#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"
#include "afxwin.h"

#include "PurchaseRecord.h"
// CParchaseDlg 对话框

class CPurchaseDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPurchaseDlg)

public:
	CPurchaseDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPurchaseDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_PurchaseList;
	CDateTimeCtrl m_DateCtrl;
	CComboBox m_FilterList;
	CString m_Filter;

	PurchaseRecords*	m_pCurRecord;
	ListContext* m_pPurchaseRecords;


	void InsertRecord(Record&record);
	void UpdatePurchaseRecordListView();
	bool Filter(Record&record);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton6();
	virtual void OnOK();
};
