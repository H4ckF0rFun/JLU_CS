
// Exp1View.h : CExp1View 类的接口
//

#pragma once


class CExp1View : public CView
{
protected: // 仅从序列化创建
	CExp1View();
	DECLARE_DYNCREATE(CExp1View)

// 特性
public:
	CExp1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CExp1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

	int m_DrawShape;
	int m_IsDrawing;
	CPoint m_StartPoint;

public:


	void DrawCircle(CDC* pDC,int x,int y,int radius);
	void DrawEllipse(CDC* pDC, int start_x, int start_y, int a, int b);

	afx_msg void OnDrawCircle();
	afx_msg void OnDrawEllipse();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMove(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // Exp1View.cpp 中的调试版本
inline CExp1Doc* CExp1View::GetDocument() const
   { return reinterpret_cast<CExp1Doc*>(m_pDocument); }
#endif

