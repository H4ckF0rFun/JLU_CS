#pragma once


// CViewPointDlg 对话框

class CViewPointDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CViewPointDlg)

public:
	CViewPointDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CViewPointDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	CString m_X;
	CString m_Y;
	CString m_Z;
	afx_msg void OnBnClickedOk();
};
