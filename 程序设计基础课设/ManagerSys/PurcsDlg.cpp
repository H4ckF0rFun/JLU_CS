#include "stdafx.h"
#include "PurcsDlg.h"

CPurcsDlg::CPurcsDlg(Goods&goods) :
CSellDlg(goods)
{
}


CPurcsDlg::~CPurcsDlg()
{
}


BOOL CPurcsDlg::OnInitDialog()
{
	CSellDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(L"����");
	//���ش��۴���
	GetDlgItem(IDC_EDIT10)->ShowWindow(SW_HIDE);
	m_Discount.ShowWindow(SW_HIDE);
	//
	return FALSE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CPurcsDlg::OnEnChangeEdit4()
{
	UpdateData();
	CString Text;
	double Total = atof(CW2A(m_SellCount)) * m_goods.Purchaseprice;
	Text.Format(L"%.2lf Ԫ", Total);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(Text);
}

void CPurcsDlg::OnOK()
{
	// TODO:  UpdateData();
	double SellCount = atof(CW2A(m_SellCount));
	m_goods.Stock += atof(CW2A(m_SellCount));
	CDialogEx::OnOK();
}
