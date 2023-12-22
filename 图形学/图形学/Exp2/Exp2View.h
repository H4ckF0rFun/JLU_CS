
// Exp2View.h : CExp2View 类的接口
//

#pragma once


class CExp2View : public CView
{
protected: // 仅从序列化创建
	CExp2View();
	DECLARE_DYNCREATE(CExp2View)

// 特性
public:
	CExp2Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CExp2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HBRUSH m_Brush;
	BOOL   m_finish;
	CArray<CPoint> m_Points;


	void EdgeMarkFill(HDC hDC,COLORREF color);

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exp2View.cpp 中的调试版本
inline CExp2Doc* CExp2View::GetDocument() const
   { return reinterpret_cast<CExp2Doc*>(m_pDocument); }
#endif

