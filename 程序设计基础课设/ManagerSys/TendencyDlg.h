#pragma once
#include "stock.h"
#include "SaleRecord.h"
#include "resource.h"
#include "afxwin.h"

// CTendencyDlg �Ի���

class CTendencyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTendencyDlg)

public:
	CTendencyDlg(ListContext*pStockList, ListContext*pSaleRecords, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTendencyDlg();

// �Ի�������
	enum { IDD = IDD_TENDENCY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	//
	ListContext*	m_pStockList;							//�������.
	ListContext*	m_pSaleRecords;							//���ۼ�¼.
	//
	int				m_DrawCount;

	void Draw(CPaintDC*pDc, Goods*pGoods, CTime StartTime);


	DECLARE_MESSAGE_MAP()



public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
//	CComboBox m_GoodsList;
	bool CTendencyDlg::Filter(Goods&goods);

	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_FilterOpt;
	CString m_sFilter;
	afx_msg void OnEnChangeEdit1();
};
