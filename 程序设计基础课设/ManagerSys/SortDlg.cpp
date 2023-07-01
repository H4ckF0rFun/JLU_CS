// SortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "SortDlg.h"
#include "afxdialogex.h"


// CSortDlg 对话框

IMPLEMENT_DYNAMIC(CSortDlg, CDialogEx)

CSortDlg::CSortDlg(DWORD Type,CWnd* pParent /*=NULL*/)
	: CDialogEx(CSortDlg::IDD, pParent)
{
	m_Type = Type;
}

CSortDlg::~CSortDlg()
{
}

void CSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_KeyList);
	DDX_Control(pDX, IDC_COMBO2, m_SortTypeList);
}


BEGIN_MESSAGE_MAP(CSortDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSortDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSortDlg 消息处理程序


BOOL CSortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (m_Type == 0)
	{
		//库存
		m_KeyList.InsertString(0, L"编号");
		m_KeyList.InsertString(1, L"名称");
		m_KeyList.InsertString(2, L"品种");
		m_KeyList.InsertString(3, L"进价");
		m_KeyList.InsertString(4, L"售价");
		m_KeyList.InsertString(5, L"库存量");
		m_KeyList.InsertString(6, L"销售量");
	}
	else if (m_Type == 1)
	{
		//销售记录
		m_KeyList.InsertString(0, L"编号");
		m_KeyList.InsertString(1, L"名称");
		m_KeyList.InsertString(2, L"品种");
		m_KeyList.InsertString(3, L"数量");
		m_KeyList.InsertString(4, L"进价");
		m_KeyList.InsertString(5, L"售价");
		m_KeyList.InsertString(6, L"利润");
		m_KeyList.InsertString(7, L"时间");
	}
	else if (m_Type == 2)
	{

		//销售记录
		m_KeyList.InsertString(0, L"编号");
		m_KeyList.InsertString(1, L"名称");
		m_KeyList.InsertString(2, L"品种");
		m_KeyList.InsertString(3, L"数量");
		m_KeyList.InsertString(4, L"进价");
		m_KeyList.InsertString(5, L"售价");
		m_KeyList.InsertString(6, L"金额");
		m_KeyList.InsertString(7, L"时间");
	}
	m_KeyList.SetCurSel(0);


	m_SortTypeList.InsertString(0, L"降序");
	m_SortTypeList.InsertString(1, L"升序");
	m_SortTypeList.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CSortDlg::OnBnClickedOk()
{
	m_SortType = m_KeyList.GetCurSel()<<16 | m_SortTypeList.GetCurSel();
	CDialogEx::OnOK();
}


void CSortDlg::OnOK()
{
}
