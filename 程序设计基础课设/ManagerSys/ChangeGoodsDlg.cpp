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

	// TODO:  在此添加额外的初始化
	SetWindowText(L"修改记录");
	//把当前信息显示到控件上
	CString Text;
	//禁止修改ID
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
	// 异常:  OCX 属性页应返回 FALSE
}
