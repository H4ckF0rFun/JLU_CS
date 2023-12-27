
// Exp7View.h : CExp7View 类的接口
//

#pragma once

struct Point
{
	double x;
	double y;
	double z;
};

class CExp7View : public CView
{
protected: // 仅从序列化创建
	CExp7View();
	DECLARE_DYNCREATE(CExp7View)

// 特性
public:
	CExp7Doc* GetDocument() const;

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
	virtual ~CExp7View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	int m_state;
	CArray<CPoint> m_Points;
	CArray<CPoint> m_TmpPoints;

	COLORREF m_colors[3];
	COLORREF m_CurrentColor;

// 生成的消息映射函数
protected:
	void CExp7View::deboor(CDC * pDC, int i, int k, float knot[], float u);
	void CExp7View::bspline_to_points(CDC * pDC, int k, float knot[]);

	void CExp7View::deboor3(CDC * pDC, int i, int k, float knot[], float u);
	void CExp7View::bspline_to_points3(CDC * pDC, int k, float knot[]);

	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void On43b();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDuichen();
	afx_msg void On3d();
	afx_msg void OnClear();
};

#ifndef _DEBUG  // Exp7View.cpp 中的调试版本
inline CExp7Doc* CExp7View::GetDocument() const
   { return reinterpret_cast<CExp7Doc*>(m_pDocument); }
#endif

