// ViewPointDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Exp3.h"
#include "ViewPointDlg.h"
#include "afxdialogex.h"


// CViewPointDlg �Ի���

IMPLEMENT_DYNAMIC(CViewPointDlg, CDialogEx)

CViewPointDlg::CViewPointDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewPointDlg::IDD, pParent)
	, m_X(_T(""))
	, m_Y(_T(""))
	, m_Z(_T(""))
{

}

CViewPointDlg::~CViewPointDlg()
{
}

void CViewPointDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_X);
	DDX_Text(pDX, IDC_EDIT2, m_Y);
	DDX_Text(pDX, IDC_EDIT3, m_Z);
}


BEGIN_MESSAGE_MAP(CViewPointDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &CViewPointDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CViewPointDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CViewPointDlg ��Ϣ�������


void CViewPointDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CViewPointDlg::OnBnClickedOk()
{
	UpdateData();
	CDialogEx::OnOK();
}
