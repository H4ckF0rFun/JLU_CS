// SortDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "SortDlg.h"
#include "afxdialogex.h"


// CSortDlg �Ի���

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


// CSortDlg ��Ϣ�������


BOOL CSortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (m_Type == 0)
	{
		//���
		m_KeyList.InsertString(0, L"���");
		m_KeyList.InsertString(1, L"����");
		m_KeyList.InsertString(2, L"Ʒ��");
		m_KeyList.InsertString(3, L"����");
		m_KeyList.InsertString(4, L"�ۼ�");
		m_KeyList.InsertString(5, L"�����");
		m_KeyList.InsertString(6, L"������");
	}
	else if (m_Type == 1)
	{
		//���ۼ�¼
		m_KeyList.InsertString(0, L"���");
		m_KeyList.InsertString(1, L"����");
		m_KeyList.InsertString(2, L"Ʒ��");
		m_KeyList.InsertString(3, L"����");
		m_KeyList.InsertString(4, L"����");
		m_KeyList.InsertString(5, L"�ۼ�");
		m_KeyList.InsertString(6, L"����");
		m_KeyList.InsertString(7, L"ʱ��");
	}
	else if (m_Type == 2)
	{

		//���ۼ�¼
		m_KeyList.InsertString(0, L"���");
		m_KeyList.InsertString(1, L"����");
		m_KeyList.InsertString(2, L"Ʒ��");
		m_KeyList.InsertString(3, L"����");
		m_KeyList.InsertString(4, L"����");
		m_KeyList.InsertString(5, L"�ۼ�");
		m_KeyList.InsertString(6, L"���");
		m_KeyList.InsertString(7, L"ʱ��");
	}
	m_KeyList.SetCurSel(0);


	m_SortTypeList.InsertString(0, L"����");
	m_SortTypeList.InsertString(1, L"����");
	m_SortTypeList.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CSortDlg::OnBnClickedOk()
{
	m_SortType = m_KeyList.GetCurSel()<<16 | m_SortTypeList.GetCurSel();
	CDialogEx::OnOK();
}


void CSortDlg::OnOK()
{
}
