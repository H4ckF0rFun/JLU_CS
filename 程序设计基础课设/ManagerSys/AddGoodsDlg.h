#pragma once
#include "afxwin.h"

#include "stock.h"
#include "resource.h"
// CAddGoodsDlg �Ի���

class CAddGoodsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddGoodsDlg)

public:

	Goods&	m_goods;

	CAddGoodsDlg(Goods&	goods,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddGoodsDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
