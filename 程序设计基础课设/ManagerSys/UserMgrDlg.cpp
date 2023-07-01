// UserMgrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ManagerSys.h"
#include "UserMgrDlg.h"
#include "afxdialogex.h"


// CUserMgrDlg 对话框

IMPLEMENT_DYNAMIC(CUserMgrDlg, CDialogEx)

CUserMgrDlg::CUserMgrDlg(ListContext*pUserData,CWnd* pParent /*=NULL*/)
	: CDialogEx(CUserMgrDlg::IDD, pParent)
	, m_UserName(_T(""))
{
	m_pUserData = pUserData;
}

CUserMgrDlg::~CUserMgrDlg()
{
}

void CUserMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK3, m_ChangePass);
	DDX_Control(pDX, IDOK2, m_DelUser);
	DDX_Control(pDX, IDOK4, m_AddUsers);
	DDX_Control(pDX, IDC_LIST2, m_UserList);
	DDX_Text(pDX, IDC_EDIT1, m_UserName);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
	DDX_Text(pDX, IDC_EDIT3, m_Password2);
}


BEGIN_MESSAGE_MAP(CUserMgrDlg, CDialogEx)
	ON_BN_CLICKED(IDOK4, &CUserMgrDlg::OnBnClickedOk4)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CUserMgrDlg::OnNMClickList2)
	ON_BN_CLICKED(IDOK3, &CUserMgrDlg::OnBnClickedOk3)
	ON_BN_CLICKED(IDOK2, &CUserMgrDlg::OnBnClickedOk2)
END_MESSAGE_MAP()


// CUserMgrDlg 消息处理程序


BOOL CUserMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_hIconPass = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON2));
	m_hIconAdd = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ADD));
	m_hIconDel = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_DELETE));

	m_ChangePass.SetIcon(m_hIconPass);
	m_AddUsers.SetIcon(m_hIconAdd);
	m_DelUser.SetIcon(m_hIconDel);
	
	//
	m_UserList.SetExtendedStyle((m_UserList.GetExStyle() | LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES)&(~LVS_EX_CHECKBOXES));
	m_UserList.InsertColumn(0, L"用户名",LVCFMT_LEFT,120);
	m_UserList.InsertColumn(1, L"密码", LVCFMT_LEFT, 120);
	//
	m_UserList.DeleteAllItems();
	m_UserList.SetRedraw(0);
	int idx = 0;
	for (Node*pIt = m_pUserData->Head.next; pIt != &m_pUserData->Head; pIt = pIt->next)
	{
		UserData*pUser = (UserData*)pIt;
		m_UserList.InsertItem(idx, CA2W(pUser->szUserName));
		m_UserList.SetItemText(idx, 1, CA2W(pUser->szPassword));
	}
	m_UserList.SetRedraw(1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//添加新用户
void CUserMgrDlg::OnBnClickedOk4()
{
	//检测是否已有该用户
	UpdateData();
	//
	if (m_UserName.GetLength() == 0)
		return;

	Node*pIt = NULL;
	//
	UserData NewUser;
	strcpy(NewUser.szUserName, CW2A(m_UserName));
	//
	UserData*pUser = (UserData*)search(m_pUserData, m_pUserData->Head.next, Compare, (UserData*)&NewUser);
	if (pUser)
	{
		MessageBox(L"该用户已存在", L"Error", MB_OK | MB_ICONASTERISK);
		return;
	}
	//
	if (m_Password != m_Password2)
	{
		MessageBox(L"两次密码不相同", L"Error", MB_OK | MB_ICONASTERISK);
		return;
	}
	//插入到链表中.
	UserData*pNewUser = (UserData*)malloc(sizeof(UserData));
	strcpy(pNewUser->szUserName, CW2A(m_UserName));
	strcpy(pNewUser->szPassword, CW2A(m_Password));
	insertback(m_pUserData, (Node*)pNewUser);
	//
	WriteUserData("user.dat", m_pUserData);
	//
	int idx = m_UserList.GetItemCount();
	m_UserList.InsertItem(idx, m_UserName);
	m_UserList.SetItemText(idx, 1, m_Password);
}


void CUserMgrDlg::OnNMClickList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	if (m_UserList.GetItemCount() == 0)
		return;
	//
	POSITION pos = m_UserList.GetFirstSelectedItemPosition();
	if (pos)
	{
		int idx = m_UserList.GetNextSelectedItem(pos);

		m_UserName = m_UserList.GetItemText(idx, 0);
		m_Password = m_UserList.GetItemText(idx, 1);
		m_Password2 = m_UserList.GetItemText(idx, 1);
		UpdateData(FALSE);
	}
}

//修改密码
void CUserMgrDlg::OnBnClickedOk3()
{
	// TODO:  在此添加控件通知处理程序代码

	//检测是否已有该用户
	UpdateData();
	//
	if (m_UserName.GetLength() == 0)
		return;
	//查找用户.
	UserData Target;
	strcpy(Target.szUserName, CW2A(m_UserName));

	UserData*pUser = (UserData*)search(m_pUserData, m_pUserData->Head.next, Compare, (Node*)&Target);
	//
	if (pUser)
	{
		if (m_Password != m_Password2)
		{
			MessageBox(L"两次密码不相同", L"Error", MB_OK | MB_ICONASTERISK);
			return;
		}
		//修改链表内的东西
		strcpy(pUser->szPassword, CW2A(m_Password));

		//修改列表显示的内容.
		POSITION pos = m_UserList.GetFirstSelectedItemPosition();
		while (pos)
		{
			int idx = m_UserList.GetNextSelectedItem(pos);
			if (m_UserList.GetItemText(idx, 0) == m_UserName)
			{
				m_UserList.SetItemText(idx, 1, m_Password);
				break;
			}
		}
		//
		WriteUserData("user.dat", m_pUserData);
		return;
	}
}

//删除用户
void CUserMgrDlg::OnBnClickedOk2()
{
	POSITION pos = m_UserList.GetFirstSelectedItemPosition();
	if (!pos)
		return;
	int idx = m_UserList.GetNextSelectedItem(pos);
	//删除列表内荣.
	m_UserList.DeleteItem(idx);

	//删除链表内容.
	UserData Target;
	strcpy(Target.szUserName, CW2A(m_UserName));
	//
	UserData*pUser = (UserData*)search(m_pUserData, m_pUserData->Head.next, Compare, (Node*)&Target);
	if (pUser)
	{
		delnode(m_pUserData, (Node*)pUser);
		//
		WriteUserData("user.dat", m_pUserData);
	}
}
