// SellDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "SellDlg.h"
#include "afxdialogex.h"


// CSellDlg 对话框

IMPLEMENT_DYNAMIC(CSellDlg, CDialogEx)

CSellDlg::CSellDlg(Goods&goods,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSellDlg::IDD, pParent),
	m_goods(goods)
	, m_SellCount(L"")
	, m_Comment(_T(""))
	, m_Rate(_T("1.0"))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT4, m_SellCount);
	DDX_Text(pDX, IDC_EDIT6, m_Comment);
	DDX_Control(pDX, IDC_CHECK1, m_Discount);
	DDX_Text(pDX, IDC_EDIT10, m_Rate);
}


BEGIN_MESSAGE_MAP(CSellDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT4, &CSellDlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_CHECK1, &CSellDlg::OnBnClickedCheck1)
	ON_EN_CHANGE(IDC_EDIT10, &CSellDlg::OnEnChangeEdit10)
	ON_BN_CLICKED(IDCANCEL, &CSellDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CSellDlg 消息处理程序


BOOL CSellDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString Text;
	Text.Format(L"%d", m_goods.nID);
	//
	GetDlgItem(IDC_EDIT1)->SetWindowTextW(Text);		//编号
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(CA2W(m_goods.szName).m_szBuffer);		//名称
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(CA2W(m_goods.szType).m_szBuffer);		//品种

	//
	GetDlgItem(IDC_EDIT8)->SetWindowTextW(((m_goods.nUnit == 0) ? L"个" : L"斤"));
	//售价
	Text.Format(L"%.2lf 元", m_goods.Sellingprice);
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(Text);
	//进价
	Text.Format(L"%.2lf 元", m_goods.Purchaseprice);
	GetDlgItem(IDC_EDIT9)->SetWindowTextW(Text);


	GetDlgItem(IDC_EDIT4)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CSellDlg::OnEnChangeEdit4()
{
	UpdateData();
	if (!m_Discount.GetCheck())
		m_Rate = L"1.0";

	CString Text;
	double Total = atof(CW2A(m_SellCount)) * m_goods.Sellingprice * atof(CW2A(m_Rate));
	Text.Format(L"%.2lf 元", Total);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(Text);
}


void CSellDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	UpdateData();
	double SellCount = atof(CW2A(m_SellCount));
	if ( SellCount < 0|| SellCount > m_goods.Stock)
	{
		MessageBox(L"库存不足", L"Error", MB_OK | MB_ICONASTERISK);
		return;
	}
	m_goods.Stock -= atof(CW2A(m_SellCount));
	m_goods.Sell += atof(CW2A(m_SellCount));
	CDialogEx::OnOK();
}


void CSellDlg::OnBnClickedCheck1()
{
	GetDlgItem(IDC_EDIT10)->EnableWindow(m_Discount.GetCheck());
}


void CSellDlg::OnEnChangeEdit10()
{
	UpdateData();
	//
	CString Text;
	double Total = atof(CW2A(m_SellCount)) * m_goods.Sellingprice * atof(CW2A(m_Rate));
	Text.Format(L"%.2lf 元", Total);
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(Text);
}


void CSellDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
