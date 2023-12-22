
// exp5View.h : Cexp5View 类的接口
//

#pragma once


class Cexp5View : public CView
{
protected: // 仅从序列化创建
	Cexp5View();
	DECLARE_DYNCREATE(Cexp5View)

// 特性
public:
	Cexp5Doc* GetDocument() const;

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
	virtual ~Cexp5View();

	void DrawHermite(CDC* pDC);

	void bez_to_points(CDC * pDC);
	
	void decas(CDC * pDC, float t);


	//
	void bspline_to_points(CDC * pDC, int k, float knot[]);
	void deboor(CDC * pDC, int i, int k, float knot[], float u);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int			   m_state;
	int			   m_type;

	CArray<CPoint> m_Points;


// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDraw();
	afx_msg void OnB();
	afx_msg void OnBezier();
	afx_msg void OnHermite();
	afx_msg void OnClear();
};

#ifndef _DEBUG  // exp5View.cpp 中的调试版本
inline Cexp5Doc* Cexp5View::GetDocument() const
   { return reinterpret_cast<Cexp5Doc*>(m_pDocument); }
#endif

