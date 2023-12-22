
// Exp4View.h : CExp4View 类的接口
//

#pragma once


class CExp4View : public CView
{
protected: // 仅从序列化创建
	CExp4View();
	DECLARE_DYNCREATE(CExp4View)

// 特性
public:
	CExp4Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CExp4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	int m_state;
	CArray<CPoint> m_Shape;

	CPoint m_rect_p0;
	CPoint m_rect_p1;

	HPEN   m_Pen0;
	HPEN   m_Pen1;
	HPEN   m_Pen2;


	

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
};

#ifndef _DEBUG  // Exp4View.cpp 中的调试版本
inline CExp4Doc* CExp4View::GetDocument() const
   { return reinterpret_cast<CExp4Doc*>(m_pDocument); }
#endif

