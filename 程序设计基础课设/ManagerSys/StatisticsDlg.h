#pragma once
#include "afxcmn.h"
#include "SaleRecord.h"

// CStatisticsDlg �Ի���

class CStatisticsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStatisticsDlg)

public:
	CStatisticsDlg(SaleRecords*pRecord,CString Today,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStatisticsDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG7 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_Today;
	SaleRecords*	m_pRecord;
	CListCtrl m_List;
};
