#include "stdafx.h"
#include "ChangeGoodsDlg.h"


CChangeGoodsDlg::CChangeGoodsDlg(Goods&	goods):
CAddGoodsDlg(goods)
{

}


CChangeGoodsDlg::~CChangeGoodsDlg()
{
}


BOOL CChangeGoodsDlg::OnInitDialog()
{
	CAddGoodsDlg::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(L"�޸ļ�¼");
	//�ѵ�ǰ��Ϣ��ʾ���ؼ���
	CString Text;
	//��ֹ�޸�ID
	Text.Format(L"%d", m_goods.nID);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(Text);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	//Name
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(CA2W(m_goods.szName));
	//Type
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(CA2W(m_goods.szType));
	//Unit
	((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(m_goods.nUnit);
	//Purchase Price
	Text.Format(L"%.2llf", m_goods.Purchaseprice);
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(Text);
	//Sellprice
	Text.Format(L"%.2llf", m_goods.Sellingprice);
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(Text);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}
