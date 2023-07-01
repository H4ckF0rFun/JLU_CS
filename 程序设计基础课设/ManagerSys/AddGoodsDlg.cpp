// AddGoodsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "AddGoodsDlg.h"
#include "afxdialogex.h"


// CAddGoodsDlg 对话框

IMPLEMENT_DYNAMIC(CAddGoodsDlg, CDialogEx)

CAddGoodsDlg::CAddGoodsDlg(Goods&goods,CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddGoodsDlg::IDD, pParent),
	m_goods(goods)
	, m_Name(_T(""))
	, m_Type(_T(""))
	, m_Purchaseprice(0)
	, m_Sellprice(0)
	, m_ID(0)
{
}

CAddGoodsDlg::~CAddGoodsDlg()
{
}

void CAddGoodsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_SellTypeList);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT2, m_Type);
	DDX_Text(pDX, IDC_EDIT3, m_Purchaseprice);
	DDX_Text(pDX, IDC_EDIT4, m_Sellprice);
	DDX_Text(pDX, IDC_EDIT5, m_ID);
}


BEGIN_MESSAGE_MAP(CAddGoodsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddGoodsDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddGoodsDlg 消息处理程序


BOOL CAddGoodsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_SellTypeList.AddString(L"个");
	m_SellTypeList.AddString(L"斤");

	m_SellTypeList.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CAddGoodsDlg::OnBnClickedOk()
{
	UpdateData();
	if (!m_Name.GetLength() || !m_Type.GetLength())
		return;

	m_goods.nID = m_ID;
	strcpy(m_goods.szName, CW2A(m_Name));
	strcpy(m_goods.szType, CW2A(m_Type));
	m_goods.nUnit = m_SellTypeList.GetCurSel();
	m_goods.Purchaseprice = m_Purchaseprice;
	m_goods.Sellingprice = m_Sellprice;

	CDialogEx::OnOK();
}
