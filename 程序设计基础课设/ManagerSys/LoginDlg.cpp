// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "LoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_User(_T("admin"))
{
	m_pUserData = ReadUserData("user.dat");//读取用户密码
}

CLoginDlg::~CLoginDlg()
{
	//保存数据.
	WriteUserData("user.dat", m_pUserData);
	//释放链表数据.
	dellist(m_pUserData);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_User);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序
void CLoginDlg::OnBnClickedOk()
{
	UpdateData();
	if (m_User.GetLength() == 0 || m_Password.GetLength() == 0)
	{
		MessageBox(L"账号或密码为空",L"tips",MB_OK|MB_ICONASTERISK);
		return;
	}

	UserData Target;
	strcpy(Target.szPassword, CW2A(m_Password));
	strcpy(Target.szUserName, CW2A(m_User));
	//登录.
	if (!Login(m_pUserData, &Target))
	{
		MessageBox(L"用户名或密码错误!", L"tips", MB_OK | MB_ICONASTERISK);
		return;
	}
	CDialogEx::OnOK();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HICON hIcon = LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));
	SetIcon(hIcon, TRUE);
	SetIcon(hIcon, FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
